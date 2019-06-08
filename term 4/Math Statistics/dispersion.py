import numpy as np
from scipy import stats
import random
import matplotlib.pyplot as plt


n = 20
A = -5
B = 7

X = []
Y = []

LEVELS = [0.99, 0.95, 0.90, 0.85, 0.7]
N = [20, 30, 50, 70, 100, 150]

epsilons_1 = []
epsilons_2 = []

theory_expected_value = 13
theory_dispersion = 163


def generate(n):
    X.clear()
    Y.clear()
    for i in range(n):
        x = random.uniform(A, B)
        X.append(x)
        Y.append(x ** 2)


def unknown_get_bound_disp(dispersion, alpha, n):
    chi2 = stats.chi2.isf(alpha / 2, n - 1)
    bound = n * dispersion / chi2
    return bound


def known_get_bound_disp(dispersion, alpha, n):
    chi2 = stats.chi2.isf(alpha / 2, n)
    bound = dispersion / chi2
    return bound

for n in N:
    generate(n)
    Y = sorted(Y)
    a = Y[0]
    b = Y[-1]

    expected_value = np.mean(Y)
    dispersion = 1 / (n - 1) * np.sum([(y - expected_value) ** 2 for y in Y])

    print(f'Expected value : {expected_value}, dispersion : {dispersion}')
    points_x_1 = []
    points_y_1 = []
    points_y_2 = []
    for level in LEVELS:
        lbound = unknown_get_bound_disp(dispersion, 1 - level, n)
        hbound = unknown_get_bound_disp(dispersion, 1 + level, n)
        print(f'alpha = {1 - level}')
        points_x_1.append(level)
        points_y_1.append(hbound - lbound)
        print(f'Interval (dispersion is unknown): {lbound} <= D <= {hbound}')

        edisp = np.sum([(y - expected_value) ** 2 for y in Y])
        lbound = known_get_bound_disp(edisp, 1 - level, n)
        hbound = known_get_bound_disp(edisp, 1 + level, n)
        print(f'alpha = {1 - level}')
        points_y_2.append(hbound - lbound)
        print(f'Interval (dispersion is known): {lbound} <= D <= {hbound}')

        print('-' * 40)
    epsilons_1.append(points_y_1[0])
    epsilons_2.append(points_y_2[0])
    plt.plot(points_x_1, points_y_1, '.', label='Student')
    plt.plot(points_x_1, points_y_2, '.', label='Normal')
    plt.legend()
    plt.show()
    print('#' * 40)
    print('-' * 40)

    print(f'Theoretical expected value : {theory_expected_value}, theoretical dispersion : {theory_dispersion}')

plt.plot(N, epsilons_1, '.', label='Unknown dispersion, aplha = 0.01')
plt.plot(N, epsilons_2, '.', label='Known dispersion, alpha = 0.01')
plt.legend()
plt.show()
