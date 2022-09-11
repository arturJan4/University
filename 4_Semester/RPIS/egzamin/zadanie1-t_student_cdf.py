import numpy as np
import scipy.special as special
from cmath import sin, sqrt, pi, exp
import matplotlib.pyplot as plt

# Artur Jankowski
# indeks 317928
# zadanie 4 - Egzamin 1 RPIS

# pisane w Pythonie 3 z wykorzystaniem scipy (w tym numpy) oraz matplotlib

# definite integral from a to b
# whole == true -> return full Romberg table
def my_romberg(function, k, a, b, whole):
    T = [[0.0]]  # romberg table

    T[0][0] = (b-a)/2.0 * (function(b) + function(a))

    n = 1
    for i in range(1, k+1):  # build first column
        hn = (b-a)/n
        # calc M
        sum_f = 0
        for j in range(1, n + 1):
            sum_f += hn * function(a + 0.5 * (2 * j - 1) * hn)

        rec = 0.5 * (T[0][i-1] + sum_f)
        n *= 2
        T[0].append(rec)

    for i in range(1, k + 1):   # rest of columns using recursive formula
        col = []
        for j in range(0, k - i + 1):  # shift down by i
            col.append((4**i * T[i-1][j+1] - T[i-1][j])
                       / (4**i - 1))
        T.append(col)
    if whole:
        return T
    return T[k][0]


# from wikipedia: https://en.wikipedia.org/wiki/Lanczos_approximation
p = [676.5203681218851,
     -1259.1392167224028,
     771.32342877765313,
     -176.61502916214059,
     12.507343278686905,
     -0.13857109526572012,
     9.9843695780195716e-6,
     1.5056327351493116e-7
     ]

EPSILON = 1e-07


def drop_imag(z):
    if abs(z.imag) <= EPSILON:
        z = z.real
    return z


# from wikipedia: https://en.wikipedia.org/wiki/Lanczos_approximation
def my_gamma(z):
    z = complex(z)
    if z.real < 0.5:
        y = pi / (sin(pi * z) * my_gamma(1 - z))  # Reflection formula
    else:
        z -= 1
        x = 0.99999999999980993
        for (i, pval) in enumerate(p):
            x += pval / (z + i + 1)
        t = z + len(p) - 0.5
        y = sqrt(2 * pi) * t ** (z + 0.5) * exp(-t) * x
    return drop_imag(y)


print("gamma comparison (1):")
value = 1
print(my_gamma(1))
print(special.gamma(1))
print(abs(value-my_gamma(1))/value)
print(abs(value-special.gamma(1))/value)

print("gamma comparison (5):")
print(my_gamma(5))
print(special.gamma(5))
value = 24
print(abs(value-my_gamma(5))/value)
print(abs(value-special.gamma(5))/value)

print("gamma comparison (10):")
print(my_gamma(10))
print(special.gamma(10))
value = 362880
print(abs(value-my_gamma(10))/value)
print(abs(value-special.gamma(10))/value)

print("gamma comparison (7/2):")
# actual 3.32335097045
print(my_gamma(7.0/2))
print(special.gamma(7.0/2))
value = 3.32335097045
print(abs(value-my_gamma(7.0/2))/value)
print(abs(value-special.gamma(7.0/2))/value)


def t_student(k, t, precision):
    const = my_gamma((k+1)/2) / (sqrt(k * np.pi)*my_gamma(k/2))

    def func(x):
        return np.power((1 + x**2/k), -((k+1)/2))

    if t >= 0:
        return const * my_romberg(func, precision, 0, t, False) + 1.0/2
    else:
        return -(const * my_romberg(func, precision, 0, -t, False)) + 1.0/2


# value, alg_value, error
print("\n")
value = 0.64758362
calculated = t_student(1, 0.5, 10)
print(calculated)
print(abs(calculated-value)/value)

# Plotting the graph
#
# t = np.linspace(-7, 7, 1024)
#
# def value(point_x, k):
#     point_y = []
#     for x in point_x:
#         point_y.append(t_student(k, x, 10))
#     return point_y

# plt.xlabel("t")
# plt.ylabel("G(t)")
# plt.plot(t, value(t, 1), label="k=1")
# plt.plot(t, value(t, 2), label="k=2")
# plt.plot(t, value(t, 5), label="k=5")
# plt.plot(t, value(t, 15), label="k=15")
# plt.plot(t, value(t, 50), label="k=50")
# plt.legend(loc="upper left")
# plt.show()


# romberg vs trapezoidal comparision
def error(exact, approx):
    return abs(exact - approx)/exact

k = 1
def func(x):
    return np.power((1 + x ** 2 / k), -((k + 1) / 2))

# exact = arctan(1/2) = 0.4636476090008061
# k = 1, t = 0.5
for column in (my_romberg(func, 6, 0, 0.5, True)):
    for element in column:
        string = error(0.4636476090008061, element)
        print(f'{string:.5E}', end=" ")
    print("\n")
