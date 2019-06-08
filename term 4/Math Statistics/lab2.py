from util import *
import numpy as np
import sympy as sp
import matplotlib.pyplot as plt


# Input ###############
N = 10000
exp = 1
dev = 2 * math.sqrt(3)
#######################

def count_intervals(l, r, Y):
    cnt = 0
    for elem in Y:
        if l <= elem and elem < r:
            cnt +=1
    return cnt



a, b = find_interval(exp, dev)

X = [random.random() * (b - a) + a for _ in range(N)]
Y = sorted([i ** 2 for i in X])

a = Y[0]
b = Y[-1]

M = 20

dy = (b - a) / M

# Figure init #####################################
fig = plt.figure()

g1 = fig.add_subplot('231')
g1.set_ylim(bottom=0)
g1.set_title('Равноинтервальный метод')

g2 = fig.add_subplot('233')
g2.set_ylim(bottom=0)

g2.set_title('Равновероятностный метод')

g3 = fig.add_subplot('234')
g3.set_title('Полигон равноинтервального метода')

g4 = fig.add_subplot('236')
g4.set_title('Полигон равновероятностного метода')
###################################################


left = a
x = []
y = []

for i in range(M):
    right = left + dy

    cnt = count_intervals(left, right, Y)

    h = cnt / (dy * N)
    g1.plot((left, right), (h, h), color='red')
    x.append((right + left) / 2)
    y.append(h)

    g3.bar(left, h, width=dy, align='edge')

    # print(f'{i} : l = {left}, r = {right}, h = {h}, count = {cnt}')

    left = right


g3.plot(x, y, color='red', marker='o', linewidth=1)
x.clear()
y.clear()

cnt = int(N / M)
left = a

for i in range(M):
    if (i + 1) * cnt != len(Y):
        right = (Y[(i + 1) * cnt - 1] + Y[(i + 1) * cnt]) / 2
    else:
        right = Y[(i + 1) * cnt - 1]

    delta = right - left
    h = 1 / (delta * M)
    g2.plot((left, right), (h, h), color='green')
    x.append((right + left) / 2)
    y.append(h)

    g4.bar(left, h, width=delta, align='edge')

    # print(f'{i} : l = {left}, r = {right}, delta = {delta}, h = {h}, s = {delta * h}')

    left = right

g4.plot(x, y, color='green', marker='o', linewidth=1)

x = sp.symbols('x', integer=False)

range1 = np.linspace(0.045, 25)
f1 = sp.lambdify(x,  1 / (x ** 0.5 * 12), 'numpy')

range2 = np.linspace(25, 49)
f2 = sp.lambdify(x, 1 / (x ** 0.5 * 24), 'numpy')

g1.plot(range1, f1(range1), color='indigo', linewidth=1)
g1.plot(range2, f2(range2), color='indigo', linewidth=1)
g1.set_ylim(0, 0.5)

g2.plot(range1, f1(range1), color='indigo', linewidth=1)
g2.plot(range2, f2(range2), color='indigo', linewidth=1)
g2.set_ylim(0, 0.5)

plt.show()

