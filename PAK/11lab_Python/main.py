from tqdm import tqdm
from torch.optim import Adam
from torch.utils.data import DataLoader
from torch.nn import CrossEntropyLoss
from torchvision.models import mobilenet_v2
from torchvision import transforms, datasets
import torch.nn.functional

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

train = datasets.FashionMNIST('', train=True, download=True,
                              transform=transforms.Compose([
                                  transforms.ToTensor(),
                                  transforms.Lambda(lambda h: h.repeat(3, 1, 1))
                              ]))
test = datasets.FashionMNIST('', train=False, download=True,
                             transform=transforms.Compose([
                                 transforms.ToTensor(),
                                 transforms.Lambda(lambda h: h.repeat(3, 1, 1))
                             ]))

train_set = DataLoader(train, batch_size=32, shuffle=True, pin_memory=True)
test_set = DataLoader(train, batch_size=32, shuffle=False, pin_memory=True)

model = mobilenet_v2(num_classes=10)
model.to(device)

loss_function = CrossEntropyLoss()
opt = Adam(model.parameters(), lr=0.01)
loss = None

for epoch in range(10):
    sm = 0
    for x, y in tqdm(train_set):
        x = x.to(device=device, non_blocking=True)
        y = y.to(device=device, non_blocking=True)

        opt.zero_grad()
        model.zero_grad()

        y_pred = model(x)
        y_pred.requires_grad_()
        loss = loss_function(y_pred, y)
        loss.backward()
        sm += loss.item()
        opt.step()
    print(sm / 1875)

print("\n\n\n======================================", end="\n\n\n")

model.eval()
test_loss, correct = 0, 0

with torch.no_grad():
    for x, y in test_set:
        x = x.to(device=device, non_blocking=True)
        y = y.to(device=device, non_blocking=True)
        output = model(x)
        test_loss += loss_function(output, y).item()
        # test_loss += torch.nn.functional.nll_loss(output, y, reduction='sum').item()
        pred = output.argmax(1, keepdim=True)
        correct += pred.eq(y.view_as(pred)).sum().item()

test_loss /= len(test_set)
acc = correct / (len(test_set) * 32)
print(acc, test_loss)
