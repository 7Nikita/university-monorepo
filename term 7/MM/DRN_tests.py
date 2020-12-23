import unittest

from lab2 import expectation
from lab2 import dispersion
from lab2 import DRNGenerator
from lab2 import find_correlation
from lab2 import MultiplicativeCongruentRandomGenerator

from math import fabs


class DRNTests(unittest.TestCase):
    delta = 0.13
    selection_size = 100
    conGen = MultiplicativeCongruentRandomGenerator(seed=60000607, m=87178291199, k=479001599)
    drnGen = DRNGenerator(amount=selection_size, generator=conGen)

    px = []
    py = []

    def setUp(self):
        self.drnGen.generate()
        for i in range(0, self.drnGen.amount):
            self.px.append(sum(self.drnGen.distribution[i]))
            y_sum = 0
            for j in range(0, self.drnGen.amount):
                y_sum += self.drnGen.distribution[j][i]
            self.py.append(y_sum)

    def test_expectation(self):
        x_theoretical_expectation = 0
        y_theoretical_expectation = 0
        for i in range(0, self.drnGen.amount):
            x_theoretical_expectation += self.px[i] * self.drnGen.intervals[i]
            y_theoretical_expectation += self.py[i] * self.drnGen.intervals[i]

        mx = expectation(self.drnGen.x_selection)
        my = expectation(self.drnGen.y_selection)

        self.assertLess(fabs(mx - x_theoretical_expectation), self.delta)
        self.assertLess(fabs(my - y_theoretical_expectation), self.delta)

    def test_dispersion(self):
        x_theoretical_dispersion = 0
        y_theoretical_dispersion = 0

        x_theoretical_expectation = 0
        y_theoretical_expectation = 0
        for i in range(0, self.drnGen.amount):
            x_theoretical_expectation += self.px[i] * self.drnGen.intervals[i]
            y_theoretical_expectation += self.py[i] * self.drnGen.intervals[i]

        for i in range(0, self.drnGen.amount):
            x_theoretical_dispersion += ((self.drnGen.intervals[i] - x_theoretical_expectation) ** 2) * self.px[i]
            y_theoretical_dispersion += ((self.drnGen.intervals[i] - y_theoretical_expectation) ** 2) * self.py[i]

        dx = dispersion(self.drnGen.x_selection, expectation(self.drnGen.x_selection))
        dy = dispersion(self.drnGen.y_selection, expectation(self.drnGen.y_selection))

        self.assertLess(fabs(dx - x_theoretical_dispersion), self.delta)
        self.assertLess(fabs(dy - y_theoretical_dispersion), self.delta)

    def test_correlation(self):
        theoretical_correlation = 0

        x_theoretical_expectation = 0
        y_theoretical_expectation = 0
        for i in range(0, self.drnGen.amount):
            x_theoretical_expectation += self.px[i] * self.drnGen.intervals[i]
            y_theoretical_expectation += self.py[i] * self.drnGen.intervals[i]

        for i in range(0, self.drnGen.amount):
            theoretical_correlation += (self.drnGen.intervals[i] - x_theoretical_expectation) \
                                       * (self.drnGen.intervals[i] - y_theoretical_expectation) \
                                       * self.px[i] \
                                       * self.py[i]

        k = find_correlation(self.drnGen.x_selection, self.drnGen.y_selection)
        self.assertLess(fabs(k - theoretical_correlation), self.delta)


if __name__ == '__main__':
    unittest.main()
