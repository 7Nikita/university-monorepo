import numpy as np
import math
import matplotlib.pyplot as plt

from scipy.optimize import fsolve
from warnings import filterwarnings
from statsmodels.graphics import tsaplots
from statsmodels.tsa.stattools import adfuller

filterwarnings("ignore")

DISP = 1
ALPHA = 1

expectation = lambda seq: sum(seq) / len(seq)
dispersion = lambda seq, exp: sum([e ** 2 - exp ** 2 for e in seq]) / len(seq)


class FixedProcessGenerator:
    def _get_equations(self, c):
        equations = []
        for i in range(self._n):
            equations.append(sum(c[j] * c[i + j] for j in range(self._n - i)) - self.corr_func(i))
        return equations

    def _find_c(self):
        return fsolve(self._get_equations, [1] * self._n)

    def __init__(self, *, func, coefs_amount):
        self.corr_func = func
        self._n = coefs_amount
        self.c = self._find_c()

    def generate(self, n):
        x = np.random.normal(0, 1, size=n)
        seq = []
        for i in range(n):
            cur = 0
            for j in range(self._n):
                cur += self.c[j] * x[(i + j) % n]
            seq.append(cur)
        return seq


class Tests:
    _tests = []

    def __init__(self, *, generator, func, amount, duration):
        self.generator = generator
        self._N = amount
        self._L = duration
        self.corr_func = func
        for i in range(self._N):
            self._tests.append(self.generator.generate(self._L))

    def check_exp_in_point(self):
        expectations = []
        for i in range(self._L):
            vals = [self._tests[j][i] for j in range(self._N)]
            expectations.append(expectation(vals))
        return expectations

    def check_disp_in_point(self):
        dispersions = []
        for i in range(self._L):
            vals = [self._tests[j][i] for j in range(self._N)]
            exp = expectation(vals)
            disp = dispersion(vals, exp)
            dispersions.append(disp)
        return dispersions

    def check_exp(self):
        expectations = []
        for e in self._tests:
            expectations.append(expectation(e))
        return expectations

    def check_disp(self):
        dispersions = []
        for e in self._tests:
            exp = expectation(e)
            disp = dispersion(e, exp)
            dispersions.append(disp)
        return dispersions

    def check_dicky_fuller(self):
        flag = True
        for e in self._tests:
            flag &= (adfuller(e)[0] < 0)
        return flag

    def check_slutskiy(self):
        range_sum = sum((1 - u / self._L) * self.corr_func(u) for u in range(self._L))
        return 1 / self._L * range_sum

    def show_plot(self):
        plt.plot(range(0, self._L), self._tests[0])
        plt.show()

    def show_corr_plots(self):
        tsaplots.plot_acf(self._tests[0], lags=10)
        plt.show()

    def show_exp_plots(self):
        exp = self.check_exp_in_point()
        disp = self.check_disp_in_point()

        plt.subplot(1, 2, 1)
        plt.title("Expectation")
        plt.plot(range(0, self._L), exp, '.')

        plt.subplot(1, 2, 2)
        plt.title("Dispersion")
        plt.plot(range(0, self._L), disp, '.')

        plt.show()


def main():
    corr_func = lambda t: DISP * math.e ** (-ALPHA * abs(t)) * (1 - ALPHA * abs(t))
    generator = FixedProcessGenerator(func=corr_func, coefs_amount=10)

    tests = Tests(generator=generator, func=corr_func, amount=100, duration=100)
    tests.show_plot()
    tests.show_corr_plots()
    tests.show_exp_plots()

    print(f"exp: {tests.check_exp()[0]}")
    print(f"disp: {tests.check_disp()[0]}")
    print(f"dicky-fuller: {tests.check_dicky_fuller()}")
    print(f"slutskiy: {tests.check_slutskiy()}")


if __name__ == "__main__":
    main()
