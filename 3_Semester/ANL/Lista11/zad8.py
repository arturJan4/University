import csv
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import lagrange

# Least squares approximation - regression

points = []

with open('punkty.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        points.append([float(row[0]), float(row[1])])

print(points)

# a
def func(t):
    return (t + 3.6) * (t - 2.1) * (t - 3.7)


pointsx = np.linspace(-100, 100, 1000)
pointsy = [[i, func(i)] for i in pointsx]

plt.scatter(*zip(*points))
plt.plot(*zip(*pointsy))
plt.show()

# b
interpolatedf = lagrange(*zip(*points))
pointsy = [[i, interpolatedf(i)] for i in pointsx]
plt.plot(*zip(*pointsy))
plt.show()

# c
# 2 <= n <= 8

N = 49
xk, yk = map(list, zip(*points))  # list of all x'es and y'es


def dotproduct(f, g):  # (f,g) {x0, x1, xN}
    sum = 0
    for i in range(0, N + 1):
        sum += f(xk[i]) * g(xk[i])
    return sum


def dotproductwithx(f, g):  # (f,g) {x0, x1, xN}
    sum = 0
    for i in range(0, N + 1):
        sum += xk[i] * f(xk[i]) * g(xk[i])
    return sum


def ak(P):  # (yk, P)
    sum = 0
    for i in range(0, N + 1):
        sum += yk[i] * P(xk[i])
    return sum


P = [lambda x: 1]  # P0 is a always 1

dot = [dotproduct(P[0], P[0])]  # (Pk, Pk)
dotwithX = dotproductwithx(P[0], P[0]) # (xPk, Pk)
c = dotwithX/dot[0]
d = 0
P.append(lambda x: x - c)  # P1(x)

for i in range(2, 4):
    print(P[i-1](2))
    dot.append(dotproduct(P[i-1], P[i-1]))
    print(dot[i-1])
    c = 1
    d = 1
    #c = dotproductwithx(P[i-1], P[i-1])/dot[i-1]
    #d = dot[i-1]/dot[i-2]
    P.append(lambda x: P[i-1](x))


def wm():
    def wmx(x):
        sum = 0
        for k in range(0, 9):
            sum += ak(P[k]) * (P[k])(x)
        return sum
    return wmx


interpolated = wm()
pointsx = np.linspace(-5, 6, 100)
pointsy = [[i, interpolated(i)] for i in pointsx]
plt.plot(*zip(*pointsy))
plt.show()

