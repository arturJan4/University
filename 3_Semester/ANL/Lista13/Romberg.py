import csv
import numpy as np
import scipy.integrate as integrate


# -1, 2
def func_a(x):
    return 2021 * x**5 - 2020 * x**4 + 2019 * x**2


# -2, 2
def func_b(x):
    return 1.0/(1 + 25 * x**2)


# 2, 3pi
def func_c(x):
    return np.sin(7*x - 2)/x


# definite integral from a to b
def my_romberg(function, k, a, b):
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

    # print(np.matrix(T))

    return T[k][0], T


def runTest(k, func, a, b):
    result = my_romberg(func, k, a, b)
    print("{0:<29}".format("prawidłowy wynik (z błędem): "), end='')
    print(integrate.quad(func, a, b))
    print("{0:<30}".format(f"Romberg-mój (k={k}): "), end='')
    print(result[0])
    # print(np.matrix(result[1]))  # print Romberg table
    print("{0:<30}".format(f"Romberg-biblioteczny: "), end='')
    print(integrate.romberg(func, a, b))


print("podpunkt a)")
runTest(16, func_a, -1, 2)
print("\npodpunkt b)")
runTest(16, func_b, -2, 2)
print("\npodpunkt c)")
runTest(16, func_c, 2, 3 * np.pi)
