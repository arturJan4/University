import numpy as np
import matplotlib.pyplot as plt
import scipy.special


def binom(n, k):  # dwumian Newtona
    return scipy.special.binom(n, k)


def beren(n, k, x):  # wielomian Berensteina
    return binom(n, k) * (x**k) * ((1-x)**(n-k))


def rn(t, W, weights, n):  # wymierna krzywa Beziera
    numerator = np.array([0.0, 0.0])
    denominator = 0.0
    for i in range(n+1):
        temp = weights[i] * beren(n, i, t)
        numerator += W[i] * temp
        denominator += temp
    return numerator * 1.0/denominator


W = np.array([[39.5, 10.5], [30, 20], [6, 6], [13, -12], [63, -12.5], [18.5, 17.5], [48, 63], [7, 25.5],
              [48.5, 49.5], [9, 19.5], [48.5, 35.5], [59, 32.5], [56, 20.5]])
weights = np.array([1, 2, 3, 2.5, 6, 1.5, 5, 1, 2, 1, 3, 5, 1])
# weights = np.array([1, 2, 3, 1, 6, 1.5, 5, 1, 2, 1, 3, 5, 1])
# weights = np.array([1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1])
# weights = np.array([1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1])
# weights = np.array([1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1])

x = []
y = []
points = len(W) - 1  # n
t = np.linspace(0, 1, 512)  # rownoodlegle punkty 0 <= t <= 1

for i in range(len(t)):
    temp = rn(t[i], W, weights, points)
    x.append(temp[0])
    y.append(temp[1])
plt.xlim([0, 60])
plt.ylim([0, 60])

plt.plot(x, y)
plt.show()


# https://arxiv.org/pdf/1803.06843.pdf
def ratBEval(t, W, weights, n):
    t1 = 1 - t
    w = [weights[i] for i in range(n+1)]
    Q = [W[i] for i in range(n + 1)]
    for k in range(1, n+1):
        u = 0.0
        v = 0.0
        for i in range(0, n-k+1):
            u = t1 * w[i]
            v = t * w[i+1]
            w[i] = u + v
            u = u/w[i]
            v = 1 - u
            Q[i] = u * Q[i] + v * Q[i+1]
    return Q[0]


x = []
y = []

for i in range(len(t)):
    temp = ratBEval(t[i], W, weights, points)
    x.append(temp[0])
    y.append(temp[1])

# plt.plot(x, y)
# plt.show()