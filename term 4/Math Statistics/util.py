import math
import random
import numpy as np


def find_interval(exp, dev):
    a = exp - math.sqrt(3) * dev
    b = a + 2 * math.sqrt(3) * dev
    return [a, b]


def find_characteristics(a, b):
    exp = (a + b) / 2
    dev = (b - a) / (2 * math.sqrt(3))
    return [exp, dev]


def gen(a, b, N):
    X = [random.random() * (b - a) + a for _ in range(N)]
    Y = sorted([i ** 2 for i in X])
    return X, Y, Y[0], Y[-1]


def empirical_func(x, Y, N):
    return sum([np.heaviside(x - i, 1) for i in Y]) / N


def F(x):
    if x < 0:
        return 0
    if x < 25:
        return 2 * x ** 0.5 / 12
    if x < 49:
        return (5 + x ** 0.5) / 12
    return 1
