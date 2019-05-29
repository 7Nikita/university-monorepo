from util import *
from scipy.stats import chi2


# Input ###############
n = 200
exp = 1
dev = 2 * math.sqrt(3)
#######################


def G(y):
    val = 0
    for elem in Y:
        val += np.heaviside(y - elem, 1)
    return val / n


a, b = find_interval(exp, dev)
X = []
Y = []

X, Y, a, b = gen(a, b, n)

M = int(math.log2(n)) + 1
cnt = int(n / M)
v_i = cnt
l = a
chi2_test = 0
sanity_check = 0

for i in range(M):
    r = Y[(i + 1) * cnt - 1]
    delta = r - l
    h = 1 / (delta * M)

    p_i_theory = F(r) - F(l)
    sanity_check += p_i_theory
    chi2_test += (v_i - n * p_i_theory) ** 2 / (n * p_i_theory)

    l = r

alpha = 0.01
chi2_critical = chi2.isf(q=alpha, df=(M - 1))

print(f'M = {M}, quontity = {cnt}')
print(f'sanity check: {sanity_check}')
print(f'chi2 = {chi2_test}, hi_table (for alpha = {alpha}, k = {M - 1}) = {chi2_critical}')
print('accept' if chi2_test < chi2_critical else 'decline')

n = 30
a, b = find_interval(exp, dev)
X, Y, a, b = gen(a, b, n)

d = max(abs(F(Y[i]) - empirical_func(Y[i], Y, n)) for i in range(n))
l = math.sqrt(n) * d
critical_l = 1.63
print('#' * 100)

print(f'd = {d}, lambda = {l}, critical lambda = {critical_l}')
print('accept' if l < critical_l else 'decline')

n = 5
a, b = find_interval(exp, dev)
X, Y, a, b = gen(a, b, n)
Y = [3.34, 14.637, 20.539, 22.087, 25.028]

omega2_critical = 0.744
omega2 = sum((F(Y[i]) - (i + 0.5) / n) ** 2 for i in range(n)) + 1 / (12 * n)
#omega2 = sum((F(Y[i]) - empirical_func(Y[i], Y, n)) ** 2 for i in range(n)) + 1 / (12 * n)
print('#' * 100)
print(f'omega2 = {omega2}, critical omega2 = {omega2_critical}')
print('accept' if omega2 < omega2_critical else 'decline')
