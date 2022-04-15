import numpy as np

np.random.seed(12313)


def sigmoid(x):
    return 1 / (1 + np.exp(-x))


def sigmoid_derivative(x):
    return x * (1 - x)


def loss(predicted, expected):
    return (expected - predicted)[0]


class Model:
    predicted_output: np.ndarray
    hidden_layer_output: np.ndarray

    def __init__(self, hidden_neurons_count=2, output_neurons_count=1, input_neurons_count=2):
        self.hidden_neurons_count = hidden_neurons_count
        self.output_neurons_count = output_neurons_count
        self.input_neurons_count = input_neurons_count

        self.h_neurons = [Neuron(input_neurons_count) for _ in range(0, hidden_neurons_count)]
        self.o_neurons = [Neuron(hidden_neurons_count) for _ in range(0, output_neurons_count)]

    def forward(self, inputs):
        res = []
        out = []
        for j in self.h_neurons:
            out.append(j.forward(inputs))
        for j in self.o_neurons:
            res.append(j.forward(out))
        return res

    def backwards(self, error, lr=0.1):
        ehl = []
        for j in self.o_neurons:
            ehl.append(j.backwards(error, lr))
        for p in ehl:
            for k, j in enumerate(self.h_neurons):
                j.backwards(p[k], lr)

    def train(self, inputs, e_inputs, epochs=10000):
        for i in range(0, epochs):
            err = []
            for p, j in enumerate(inputs):
                y = self.forward(j)
                err.append(loss(y, e_inputs[p]))
                self.backwards(err[p], lr=0.2)
            print("Error: ", (np.array(err)**2).mean())

    def predict(self, inputs):
        res = []
        for i in inputs:
            res.append(self.forward(i))
        return (np.array(res) > 0.5) * 1


class Neuron:
    def __init__(self, in_size):
        self.weight = np.random.random(in_size)
        self.bias = np.random.random()
        self.output = None
        self.input = None

    def set_weight(self, weight):
        self.weight = weight

    def set_bias(self, bias):
        self.bias = bias

    def forward(self, inputs):
        hidden_layer_activation = np.dot(inputs, self.weight)
        hidden_layer_activation += self.bias
        self.input = inputs
        self.output = sigmoid(hidden_layer_activation)
        return self.output

    def backwards(self, error, lr):
        d_predicted_output = error * sigmoid_derivative(self.output)
        error_hidden_layer = d_predicted_output * self.weight

        self.weight += np.array(self.input) * d_predicted_output * lr
        self.bias += d_predicted_output * lr

        return error_hidden_layer


def main():
    inp1 = np.array([[1, 1], [1, 0], [0, 1], [0, 0]])
    e_out1 = np.array([[0], [1], [1], [0]])
    net = Model()
    net.train(inp1, e_out1)
    print(net.predict(inp1))


main()
