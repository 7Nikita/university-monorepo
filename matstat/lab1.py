# Y = X^2

import tabulate
import numpy as np
import sympy as sp
from util import *
import matplotlib.pyplot as plt

# Input ###############
N = 10000
exp = 1
dev = 2 * math.sqrt(3)
#######################

a, b = find_interval(exp, dev)
print(f'a = {a} \t b = {b}')

X = [random.random() * (b - a) + a for _ in range(N)]
Y = [i ** 2 for i in X]

empirical_func = lambda x: sum([np.heaviside(x - i, 1) for i in Y]) / N

print(tabulate.tabulate(zip(X, Y), headers=['X', 'Y'], tablefmt='orgtbl'))

Y = sorted(Y)
rng = np.arange(-10, b ** 2 + 10)
plt.plot(rng, empirical_func(rng), '.')
# plt.show()

y = sp.symbols('y', integer=False)

range1 = np.linspace(0, 25)
g1 = sp.lambdify(y, 2 * y ** 0.5 / 12, 'numpy')

range2 = np.linspace(25, 49)
g2 = sp.lambdify(y, (5 + y ** 0.5) / 12, 'numpy')


plt.plot([-10, 0], [0, 0])
plt.plot([b ** 2, b ** 2 + 10], [1, 1])
plt.plot(range1, g1(range1))
plt.plot(range2, g2(range2))
plt.plot(rng, empirical_func(rng), '.')
plt.xlim(-10, b ** 2 + 10)
plt.show()
