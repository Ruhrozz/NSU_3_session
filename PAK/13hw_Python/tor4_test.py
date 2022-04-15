from tor4 import mse_loss, tensor


def test_tensor_sum():
    a = tensor(data=[-1, 1, 2])
    a_sum = a.sum()

    assert a_sum.tolist() == 2
    assert not a_sum.requires_grad


def test_tensor_sum_backward():
    a = tensor(data=[-1, 1, 2.0], requires_grad=True)
    a_sum = a.sum()
    a_sum.backward()

    assert a_sum.tolist() == 2
    assert a_sum.requires_grad
    assert a.grad.tolist() == [1, 1, 1]


def test_tensor_sum_backward2():
    a = tensor(data=[-1, 1, 2.0], requires_grad=True)
    a_sum = a.sum()
    a_sum.backward(tensor(3))

    assert a_sum.tolist() == 2
    assert a_sum.requires_grad
    assert a.grad.tolist() == [3, 3, 3]


def test_tensor_sum3_backward():
    a = tensor(data=[[[-1], [1], [2]], [[1], [2], [3.0]]], requires_grad=True)
    a_sum = a.sum()
    a_sum.backward()

    assert a_sum.tolist() == 8
    assert a_sum.requires_grad
    assert a.grad.tolist() == [[[1], [1], [1]], [[1], [1], [1]]]


def test_tensor_sum_keepdim3_backward():
    a = tensor(data=[[[-1], [1], [2]], [[1], [2], [3.0]]], requires_grad=True)
    a_sum = a.sum()
    a_sum.backward()

    assert a_sum.tolist() == 8
    assert a_sum.requires_grad
    assert a.grad.tolist() == [[[1], [1], [1]], [[1], [1], [1]]]


def test_tensor_sub():
    a = tensor([1, 2, 3])
    b = tensor([4, 5, 6])
    apb = a - b

    assert apb.tolist() == [-3, -3, -3]
    assert not apb.requires_grad


def test_tensor_sub_backward():
    a = tensor([1, 2, 3])
    b = tensor([-1, 0, 1.0], requires_grad=True)
    apb = a - b
    apb.backward(tensor([1, 1, 1]))

    assert apb.tolist() == [2, 2, 2]
    assert not a.requires_grad
    assert b.requires_grad
    assert apb.requires_grad
    assert a.grad is None
    assert b.grad.tolist() == [-1, -1, -1]


def test_tensor_rsub_backward():
    a = tensor([1, 2, 3.0], requires_grad=True)
    b = tensor([-1, 0, 1])
    apb = a - b
    apb.backward(tensor([1, 1, 2]))

    assert apb.tolist() == [2, 2, 2]
    assert a.requires_grad
    assert not b.requires_grad
    assert apb.requires_grad
    assert a.grad.tolist() == [1, 1, 2]
    assert b.grad is None


def test_tensor_mul():
    a = tensor(data=[1, 2, 3])
    b = tensor(data=[-1, 3, 1])
    amb = a * b

    assert amb.tolist() == [-1, 6, 3]
    assert not amb.requires_grad


def test_tensor_mul_backward():
    a = tensor(data=[1, 2, 3])
    b = tensor(data=[-1, 3, 1.0], requires_grad=True)
    amb = a * b
    amb.backward(tensor([1, 2, 3]))

    assert amb.tolist() == [-1, 6, 3]
    assert not a.requires_grad
    assert b.requires_grad
    assert amb.requires_grad
    assert a.grad is None
    assert b.grad.tolist() == [1, 4, 9]


def test_tensor_rmul_backward():
    a = tensor(data=[1, 2, 3.0], requires_grad=True)
    b = tensor(data=[-1, 3, 1])
    amb = a * b
    amb.backward(tensor([3, 2, 1]))

    assert amb.tolist() == [-1, 6, 3]
    assert a.requires_grad
    assert not b.requires_grad
    assert amb.requires_grad
    assert a.grad.tolist() == [-3, 6, 1]
    assert b.grad is None


def test_tensor_pow_scalar():
    a = tensor(data=[1, 2, 3])
    ap2 = a ** 2

    assert ap2.tolist() == [1, 4, 9]
    assert not ap2.requires_grad


def test_tensor_pow_scalar_backward():
    a = tensor(data=[1, 2, 3.0], requires_grad=True)
    ap2 = a ** 2
    ap2.backward(tensor(data=[1, 1, 2]))

    assert ap2.tolist() == [1, 4, 9]
    assert ap2.requires_grad
    assert a.requires_grad
    assert a.grad.tolist() == [2, 4, 12]


def test_sigmoid_backward():
    a = tensor(data=[0.0, 0, 0], requires_grad=True)
    a_sigmoid = a.sigmoid()
    a_sigmoid.backward(tensor(data=[1, 1, 1]))

    assert a_sigmoid.tolist() == [0.5, 0.5, 0.5]
    assert a_sigmoid.requires_grad
    assert a.grad.tolist() == [0.25, 0.25, 0.25]


def test_tensor_matmul():
    a = tensor(data=[1, 2, 3])
    b = tensor(data=[4, 5, 6])
    amb = a @ b

    assert amb.tolist() == 32
    assert not amb.requires_grad


def test_tensor_matmul2():
    a = tensor(data=[[1, 2, 3], [3, 2, 1]])
    b = tensor(data=[[1, 1], [1, 1], [1, 1]])
    amb = a @ b

    assert amb.tolist() == [
        [6, 6],
        [6, 6],
    ]
    assert not amb.requires_grad
    assert amb.shape == (2, 2)


def test_tensor_matmul2_backward():
    a = tensor(data=[[1, 2, 3], [4, 5, 6], [7, 8, 9]], requires_grad=True)
    b = tensor(data=[[10, 11, 12], [13, 14, 15], [16, 17, 18]], requires_grad=True)
    amb = a @ b
    amb.backward(tensor(data=[[1, 2, 3], [4, 5, 6], [7, 8, 9]]))

    assert amb.tolist() == [
        [84.,  90.,  96.],
        [201., 216., 231.],
        [318., 342., 366.]
    ]
    assert amb.requires_grad
    assert b.grad.tolist() == [
        [66.,  78.,  90.],
        [78.,  93., 108.],
        [90., 108., 126.]
    ]
    assert a.grad.tolist() == [
        [68.,  86., 104.],
        [167., 212., 257.],
        [266., 338., 410.]
    ]


def test_mse_backward():
    inputs = tensor(data=[1.0, 2, 3], requires_grad=True)
    targets = tensor(data=[2, 3, 2])

    mse_nn = mse_loss(inputs, targets)
    mse = ((inputs.data - targets.data) ** 2).sum()

    mse_nn.backward()

    assert mse_nn.data == mse == 3
    assert mse_nn.requires_grad
    assert inputs.grad.tolist() == [-2, -2, 2]


def test_my_backward1():
    a = tensor(data=[1, 2, 3], requires_grad=True)
    b = tensor(data=[-1, 3, 1.0], requires_grad=True)
    amb = a * b
    z = amb ** 2
    z.backward(tensor([1, 1, 1]))

    assert amb.tolist() == [-1, 6, 3]
    assert z.tolist() == [1, 36, 9]
    assert b.requires_grad
    assert amb.requires_grad
    assert z.requires_grad
    assert amb.grad.tolist() == [-2, 12, 6]
    assert b.grad.tolist() == [-2, 24, 18]
    assert a.grad.tolist() == [2, 36, 6]


def test_simple():
    x_ = 2.
    y_ = 3.
    x = tensor(data=[x_], requires_grad=True)
    y = tensor(data=[y_], requires_grad=True)

    f = x * y - (x - y)

    f.backward()

    assert x.grad.tolist() == [y_ - 1]
    assert y.grad.tolist() == [x_ + 1]


# =============================================================== #


def main():
    test_tensor_sum()
    test_tensor_sum_backward()
    test_tensor_sum_backward2()
    test_tensor_sum3_backward()             # <--- It's the same #
    test_tensor_sum_keepdim3_backward()     # <--- as this one   #
    test_tensor_sub()
    test_tensor_sub_backward()
    test_tensor_rsub_backward()
    test_tensor_mul()
    test_tensor_rmul_backward()
    test_tensor_pow_scalar()
    test_tensor_pow_scalar_backward()
    test_sigmoid_backward()
    test_tensor_matmul()
    test_tensor_matmul2()
    test_tensor_matmul2_backward()
    test_mse_backward()
    test_my_backward1()
    test_simple()


main()
