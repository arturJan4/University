import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate

# print(len(x_points)) # 96

x_points = [5.5, 8.5, 10.5, 13, 17, 20.5, 24.5, 28, 32.5, 37.5, 40.5, 42.5, 45, 47,
            49.5, 50.5, 51, 51.5, 52.5, 53, 52.8, 52, 51.5, 53, 54, 55, 56, 55.5, 54.5, 54, 55, 57, 58.5,
            59, 61.5, 62.5, 63.5, 63, 61.5, 59, 55, 53.5, 52.5, 50.5, 49.5, 50, 51, 50.5, 49, 47.5, 46,
            45.5, 45.5, 45.5, 46, 47.5, 47.5, 46, 43, 41, 41.5, 41.5, 41, 39.5, 37.5, 34.5, 31.5, 28, 24,
            21, 18.5, 17.5, 16.5, 15, 13, 10, 8, 6, 6, 6, 5.5, 3.5, 1, 0, 0, 0.5, 1.5, 3.5, 5, 5, 4.5, 4.5, 5.5,
            6.5, 6.5, 5.5]

y_points = [41, 40.5, 40, 40.5, 41.5, 41.5, 42, 42.5, 43.5, 45, 47, 49.5, 53, 57, 59,
            59.5, 61.5, 63, 64, 64.5, 63, 61.5, 60.5, 61, 62, 63, 62.5, 61.5, 60.5, 60, 59.5, 59, 58.5,
            57.5, 55.5, 54, 53, 51.5, 50, 50, 50.5, 51, 50.5, 47.5, 44, 40.5, 36, 30.5, 28, 25.5, 21.5,
            18, 14.5, 10.5, 7.50, 4, 2.50, 1.50, 2, 3.50, 7, 12.5, 17.5, 22.5, 25, 25, 25, 25.5, 26.5,
            27.5, 27.5, 26.5, 23.5, 21, 19, 17, 14.5, 11.5, 8, 4, 1, 0, 0.5, 3, 6.50, 10, 13, 16.5, 20.5,
            25.5, 29, 33, 35, 36.5, 39, 41]

# print(len(tk))


def nifs3(xi, yi):  # returns interpolated value f(x) given points xi, yi
    length = len(xi)

    if np.any(np.diff(xi) < 0): # check if points are sorted, if not -> sort indexwise
        idx = np.argsort(xi)
        xi = xi[idx]
        yi = yi[idx]

    h = [0.0] + [(xi[i] - xi[i-1]) for i in range(1, length)]  # 1 .. n
    lam = [0.0] + [(h[k])/(h[k] + h[k+1]) for k in range(1, length-1)]  # 1..(n-1)
    M = [0.0] * length
    d = [0.0] * length
    q = [0.0] * length
    u = [0.0] * length
    p = [0.0] * length

    def diff(k):  # iloraz różnicowy
        left = (yi[k+1] - yi[k])/(xi[k+1] - xi[k])
        right = (yi[k] - yi[k-1])/(xi[k] - xi[k-1])
        return (left - right)/(xi[k+1] - xi[k-1])

    for k in range(1, length - 1):
        d[k] = 6 * diff(k)

    for k in range(1, length - 1):  # 1 .. n-1
        p[k] = lam[k] * q[k - 1] + 2
        q[k] = (lam[k] - 1) / p[k]
        u[k] = (d[k] - (lam[k] * u[k - 1])) / p[k]

    M[length - 2] = u[length - 2]  # 94 94 n-1 n-1
    for k in range(length - 2, 0, -1):  # n-2 ... 1
        M[k] = u[k] + (q[k] * M[k + 1])

    def sk(x):
        k = 0
        for i in range(1, length):  # find interval
            if xi[i - 1] <= x <= xi[i]:
                k = i
                break

        # one big sum
        f1 = (1.0/6) * M[k - 1] * ((xi[k] - x) ** 3)
        f2 = (1.0/6) * M[k] * ((x - xi[k - 1]) ** 3)
        f3 = (yi[k - 1] - ((1.0/6) * M[k - 1] * (h[k] ** 2))) * (xi[k] - x)
        f4 = (yi[k] - ((1.0/6) * M[k] * (h[k] ** 2))) * (x - tk[k - 1])
        return (h[k] ** -1) * (f1 + f2 + f3 + f4)

    return sk  # returns a sk(x) function which calculates value at given point x


def fun(x, x_points, y_points):  # using lib func
    tck = interpolate.splrep(x_points,  y_points)
    return interpolate.splev(x, tck)


tk = [k/95 for k in range(0, 95 + 1)]

M = 1000
# final_points = [(fun(k/M, tk, x_points), fun(k/M, tk, y_points)) for k in range(0, M+1)]  # scipy lib NIFS3
XInterpolated = nifs3(tk, x_points)  # returns function f(x)
YInterpolated = nifs3(tk, y_points)  # returns function f(x)

final_points = [(XInterpolated(k/M), YInterpolated(k/M)) for k in range(0, M+1)]    # my NIFS3

# print(final_points)
plt.plot(*zip(*final_points))
plt.show()