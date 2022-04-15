from typing import Callable, List, NamedTuple, Optional

import numpy as np
from scipy import special

Array = np.ndarray


def ensure_array(array):
    return np.array(array, dtype="float32", copy=False)


class Dependency(NamedTuple):
    tensor: "Tensor"
    grad_fn: Callable[[Array], Array]


class Tensor:
    def __init__(
        self,
        data,
        depends_on: Optional[List[Dependency]] = None,
        requires_grad: bool = False,
    ) -> None:
        self.data = ensure_array(data)
        self.depends_on = depends_on or []
        self.requires_grad = requires_grad
        self.grad: Optional[Tensor] = None

    def __sub__(self, other) -> "Tensor":
        return sub(self, other)

    def __mul__(self, other) -> "Tensor":
        return mul(self, other)

    def __pow__(self, other) -> "Tensor":
        return power(self, other)

    def __matmul__(self, other) -> "Tensor":
        return matmul(self, other)

    def sum(self) -> "Tensor":
        return reduce_sum(self)

    def sigmoid(self) -> "Tensor":
        return sigmoid(self)

    def zero_grad_(self) -> None:
        self.grad = 0

    def tolist(self):
        return self.data.tolist()

    @property
    def shape(self):
        return self.data.shape

    def backward(self, grad: Optional["Tensor"] = None) -> None:
        if grad is None:
            if np.prod(self.data.shape) == 1:
                grad = Tensor(1)
            else:
                raise RuntimeError

        if self.grad is None:
            self.grad = Tensor(np.zeros_like(self.data))

        for x in self.depends_on:
            if x.tensor.grad is None:
                x.tensor.zero_grad_()
            x.tensor.grad += x.grad_fn(grad.data)
            x.tensor.backward(tensor(x.tensor.grad))


def tensor(data, requires_grad: bool = False) -> Tensor:
    return Tensor(data, requires_grad=requires_grad)


def reduce_sum(inp: Tensor) -> Tensor:
    data = np.sum(inp.data)

    requires_grad = inp.requires_grad

    depends_on = []
    if requires_grad:

        def grad_fn(grad: Array) -> Array:
            middle = np.array(np.ones_like(inp.data), dtype="float32")
            return np.multiply(middle, grad)

        depends_on.append(Dependency(tensor=inp, grad_fn=grad_fn))

    return Tensor(data, depends_on=depends_on, requires_grad=requires_grad)


def sub(left: Tensor, right: Tensor) -> Tensor:
    data = np.subtract(left.data, right.data)

    depends_on = []
    if left.requires_grad:

        def grad_fn_left(grad: Array) -> Array:
            middle = np.ones_like(left.data)
            return np.multiply(middle, grad)

        depends_on.append(Dependency(tensor=left, grad_fn=grad_fn_left))

    if right.requires_grad:

        def grad_fn_right(grad: Array) -> Array:
            middle = np.array(np.where(left.data == -1, -1, -1), dtype="float32")
            return np.multiply(middle, grad)

        depends_on.append(Dependency(tensor=right, grad_fn=grad_fn_right))

    requires_grad = left.requires_grad or right.requires_grad

    return Tensor(data=data, depends_on=depends_on, requires_grad=requires_grad)


def mul(left: Tensor, right: Tensor) -> Tensor:
    data = np.multiply(left.data, right.data)

    depends_on = []
    if left.requires_grad:

        def grad_fn_left(grad: Array) -> Array:
            middle = np.array(right.data, dtype="float32")
            return np.multiply(middle, grad)

        depends_on.append(Dependency(tensor=left, grad_fn=grad_fn_left))

    if right.requires_grad:

        def grad_fn_right(grad: Array) -> Array:
            middle = np.array(left.data, dtype="float32")
            return np.multiply(middle, grad)

        depends_on.append(Dependency(tensor=right, grad_fn=grad_fn_right))

    requires_grad = left.requires_grad or right.requires_grad

    return Tensor(data=data, depends_on=depends_on, requires_grad=requires_grad)


def power(inp: Tensor, exponent: int) -> Tensor:
    data = np.power(inp.data, exponent)

    requires_grad = inp.requires_grad

    depends_on = []
    if requires_grad:

        def grad_fn(grad: Array) -> Array:
            middle = np.power(inp.data, exponent - 1)
            middle = np.array(np.multiply(middle, exponent), dtype="float32")
            return np.multiply(middle, grad)

        depends_on.append(Dependency(tensor=inp, grad_fn=grad_fn))

    return Tensor(data=data, depends_on=depends_on, requires_grad=requires_grad)


def sigmoid(inp: Tensor) -> Tensor:
    data = special.expit(inp.data)

    requires_grad = inp.requires_grad

    depends_on = []
    if requires_grad:

        def grad_fn(grad: Array) -> Array:
            return np.multiply(np.multiply(np.ones_like(data) - data, data), grad)

        depends_on.append(Dependency(tensor=inp, grad_fn=grad_fn))

    return Tensor(data=data, depends_on=depends_on, requires_grad=requires_grad)


def matmul(left: Tensor, right: Tensor) -> Tensor:
    data = np.matmul(left.data, right.data)

    depends_on = []
    if right.requires_grad:

        def grad_fn_right(grad: Array) -> Array:
            return left.data.T.dot(grad)
            # middle = np.zeros_like(right.data)
            # for i in range(0, len(middle)):
            #     for j in range(0, len(middle[0])):
            #         for k in range(0, len(middle[0])):
            #             middle[i][j] += left.data[k][i] * grad[k][j]
            # return middle

        depends_on.append(Dependency(tensor=right, grad_fn=grad_fn_right))

    if left.requires_grad:

        def grad_fn_left(grad: Array) -> Array:
            return right.data.dot(grad.T).T
            # middle = np.zeros_like(left.data)
            # middle = middle.T
            # for i in range(0, len(middle)):
            #     for j in range(0, len(middle[0])):
            #         for k in range(0, len(middle[0])):
            #             middle[i][j] += right.data[i][k] * grad[j][k]
            # middle = middle.T
            # return middle

        depends_on.append(Dependency(tensor=left, grad_fn=grad_fn_left))

    requires_grad = left.requires_grad or right.requires_grad

    return Tensor(data=data, depends_on=depends_on, requires_grad=requires_grad)


class SGD:
    def __init__(self, parameters: list, lr: float = 1e-3) -> None:
        self.parameters = parameters
        self.lr = lr

    def step(self):
        for i in self.parameters:
            i.data -= i.grad * self.lr
        return self.parameters

    def zero_grad(self):
        for i in self.parameters:
            i.zero_grad_()


def mse_loss(inp: Tensor, target: Tensor) -> Tensor:
    return ((target - inp) ** 2).sum()
