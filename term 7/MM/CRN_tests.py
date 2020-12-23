import unittest

from lab2 import expectation
from lab2 import dispersion
from lab2 import CRNGenerator
from lab2 import find_correlation
from lab2 import MultiplicativeCongruentRandomGenerator

from math import fabs


class CRNTests(unittest.TestCase):
    delta = 0.07
    selection_size = 10000
    conGen = MultiplicativeCongruentRandomGenerator(seed=60000607, m=87178291199, k=479001599)
    crnGen = CRNGenerator(generator=conGen)

    def test_expectation(self):
        x_theoretical_expectation = 2 / 3
        y_theoretical_expectation = 5 / 9

        self.crnGen.generate(amount=self.selection_size)
        mx = expectation(self.crnGen.x_selection)
        my = expectation(self.crnGen.y_selection)

        self.assertLess(fabs(mx - x_theoretical_expectation), self.delta)
        self.assertLess(fabs(my - y_theoretical_expectation), self.delta)

    def test_dispersion(self):
        x_theoretical_dispersion = 1 / 15
        y_theoretical_dispersion = 13 / 162

        self.crnGen.generate(amount=self.selection_size)
        dx = dispersion(self.crnGen.x_selection, expectation(self.crnGen.x_selection))
        dy = dispersion(self.crnGen.y_selection, expectation(self.crnGen.y_selection))

        self.assertLess(fabs(dx - x_theoretical_dispersion), self.delta)
        self.assertLess(fabs(dy - y_theoretical_dispersion), self.delta)

    def test_correlation(self):
        theoretical_correlation = - 9 / 972

        self.crnGen.generate(amount=self.selection_size)
        k = find_correlation(self.crnGen.x_selection, self.crnGen.y_selection)
        self.assertLess(fabs(k - theoretical_correlation), self.delta)


if __name__ == "__main__":
    unittest.main()
