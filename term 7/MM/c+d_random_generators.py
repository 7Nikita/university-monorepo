import random
import matplotlib.pyplot as plot

from abc import ABC
from abc import abstractmethod

from math import sqrt
from math import log10

from typing import List
from random import random
from itertools import repeat
from bisect import bisect_right
from scipy.special import erfinv


class RandomGenerator(ABC):
    _NUM_LENGTH = 8
    _LEFT_BOUND = 10000000
    _RIGHT_BOUND = 99999999

    def __init__(self, *, seed: int = None):
        if seed is None:
            self.seed = random.randint(self._LEFT_BOUND, self._RIGHT_BOUND)
        elif not self._LEFT_BOUND <= seed <= self._RIGHT_BOUND:
            raise ValueError(f"Seed must be in [{self._LEFT_BOUND};{self._RIGHT_BOUND}].")
        else:
            self.seed = seed

    @abstractmethod
    def once(self) -> float:
        pass

    @abstractmethod
    def generate(self, *, amount: int) -> List[float]:
        pass


class MultiplicativeCongruentRandomGenerator(RandomGenerator):
    def __init__(self, *, seed: int = None, m: int, k: int):
        super().__init__(seed=seed)
        self.m = m
        self.k = k

    def once(self) -> float:
        self.seed = self.k * self.seed % self.m
        return round(self.seed / self.m, self._NUM_LENGTH)

    def generate(self, *, amount: int) -> List[float]:
        selection = []
        for _ in repeat(None, amount):
            self.seed = self.k * self.seed % self.m
            selection.append(round(self.seed / self.m, self._NUM_LENGTH))
        return selection


expectation = lambda seq: sum(seq) / len(seq)
dispersion = lambda seq, exp: sum([e ** 2 - exp ** 2 for e in seq]) / len(seq)


def find_correlation(seq_x, seq_y):
    xy = [e1 * e2 for (e1, e2) in zip(seq_x, seq_y)]
    x_exp = expectation(seq_x)
    y_exp = expectation(seq_y)
    xy_exp = expectation(xy)
    x_disp = dispersion(seq=seq_x, exp=x_exp)
    y_disp = dispersion(seq=seq_y, exp=y_exp)
    return (xy_exp - x_exp * y_exp) / sqrt(x_disp * y_disp)


def create_histogram(*, seq):
    size = len(seq)
    sections = int(sqrt(size) + 1 if size <= 100 else 3 * log10(size))
    delta = 1 / sections
    left = 0
    for i in range(sections):
        right = left + delta
        cnt = sum([1 if left <= e < right else 0 for e in seq])
        h = cnt / size
        plot.bar(left, h, width=delta, align="edge")
        left = right
    return plot


def m_confidence_interval(*, seq, alpha=0.95) -> (float, float):
    size = len(seq)
    exp = expectation(seq)
    dev = sqrt(dispersion(seq, exp))
    z = erfinv(alpha / 2)
    lhs = exp - dev * z / sqrt(size)
    rhs = exp + dev * z / sqrt(size)
    return lhs, rhs


def d_confidence_interval(*, seq, alpha=0.95) -> (float, float):
    size = len(seq)
    exp = expectation(seq)
    disp = dispersion(seq, exp)
    z = erfinv(alpha / 2)
    lhs = disp - z * sqrt(2 / (size - 1)) * disp
    rhs = disp + z * sqrt(2 / (size - 1)) * disp
    return lhs, rhs


class CRNGenerator:
    def fxy(self, *, x: float, y: float) -> float:
        return 2 * (x ** 2 + y / 3)

    def fx(self, x: float) -> float:
        return 2 * x ** 2 + 1 / 3

    def fy(self, y: float) -> float:
        return (2 + 2 * y) / 3

    x_supremum = 2 + 1 / 3
    y_supremum = 4 / 3
    xy_y_supremum = 0

    x_selection = []
    y_selection = []

    def __init__(self, *, generator: RandomGenerator):
        self.generator = generator

    def generate(self, *, amount: int) -> (List[float], List[float]):
        self.x_selection.clear()
        self.y_selection.clear()
        while len(self.x_selection) != amount:
            rand_x, rand_z = self.generator.generate(amount=2)
            if rand_z * self.x_supremum < self.fx(rand_x):
                self.x_selection.append(rand_x)
        while len(self.y_selection) != amount:
            rand_y, rand_z = self.generator.generate(amount=2)
            cur_x = self.x_selection[len(self.y_selection)]
            if rand_z * self.xy_y_supremum < self.fxy(x=cur_x, y=rand_y) / self.fx(cur_x):
                self.y_selection.append(rand_y)
        return self.x_selection, self.y_selection


class DRNGenerator:
    intervals = []
    distribution = []
    x_selection = []
    y_selection = []

    def F(self, *, x: float, y: float) -> float:
        return (x * y * (2 * x ** 2 + y)) / 3

    def _F(self, *, x: float, y: float) -> float:
        return self.F(x=x, y=y) \
               - self.F(x=x - self.step, y=y) \
               - self.F(x=x, y=y - self.step) \
               + self.F(x=x - self.step, y=y - self.step)

    def __init__(self, *, amount: int, generator: RandomGenerator):
        self.amount = amount
        self.generator = generator
        self._get_intervals()
        self._get_distribution()

    def generate(self):
        while len(self.x_selection) < self.amount:
            rand_x = self.generator.once()
            rand_y = random()
            p = self._F(x=rand_x, y=rand_y)
            x, y = self._find_p(p)
            self.x_selection.append(1 / self.amount * (x + 1))
            self.y_selection.append(1 / self.amount * (y + 1))

    def _find_p(self, p) -> (float, float):
        pos = bisect_right(self.sorted_p, p)
        return self.p_indexes[self.sorted_p[pos]]

    def _get_intervals(self):
        self.intervals.clear()
        self.step = 1 / self.amount
        right = self.step
        while len(self.intervals) != self.amount:
            self.intervals.append(right)
            right += self.step

    def _get_distribution(self):
        self.distribution.clear()
        self.p_indexes = {}
        self.sorted_p = []
        for i in range(0, self.amount):
            self.distribution.append([])
            for j in range(0, self.amount):
                _x = self.intervals[i]
                _y = self.intervals[j]
                cur = self._F(x=_x, y=_y)
                self.p_indexes[cur] = (i, j)
                self.sorted_p.append(cur)
                self.distribution[-1].append(cur)
        self.sorted_p.sort()


def analise_crn():
    conGen = MultiplicativeCongruentRandomGenerator(seed=60000607, m=87178291199, k=479001599)
    c = CRNGenerator(generator=conGen)
    c.generate(amount=10000)

    create_histogram(seq=c.x_selection).show()
    create_histogram(seq=c.y_selection).show()

    mxl, mxr = m_confidence_interval(seq=c.x_selection)
    myl, myr = m_confidence_interval(seq=c.y_selection)
    dxl, dxr = d_confidence_interval(seq=c.x_selection)
    dyl, dyr = d_confidence_interval(seq=c.y_selection)
    print(f"{mxl} < mx < {mxr}")
    print(f"{myl} < my < {myr}")
    print(f"{dxl} < dx < {dxr}")
    print(f"{dyl} < dy < {dyr}")


def analise_drn():
    conGen = MultiplicativeCongruentRandomGenerator(seed=60000607, m=87178291199, k=479001599)
    d = DRNGenerator(amount=100, generator=conGen)
    d.generate()

    create_histogram(seq=d.x_selection).show()
    create_histogram(seq=d.y_selection).show()

    mxl, mxr = m_confidence_interval(seq=d.x_selection)
    myl, myr = m_confidence_interval(seq=d.y_selection)
    dxl, dxr = d_confidence_interval(seq=d.x_selection)
    dyl, dyr = d_confidence_interval(seq=d.y_selection)
    print(f"{mxl} < mx < {mxr}")
    print(f"{myl} < my < {myr}")
    print(f"{dxl} < dx < {dxr}")
    print(f"{dyl} < dy < {dyr}")


if __name__ == "__main__":
    # analise_crn()
    analise_drn()
