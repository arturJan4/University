from functools import reduce
import timeit


def doskonale_imperatywna(n):
    result = []
    for i in range(1, n + 1):
        sum = 0

        for div in range(1, i):
            if i % div == 0:
                sum += div

        if sum == i:
            result.append(i)

    return result


def doskonale_skladana(n):
    # we calculate sum of divisors of i (which we get from list comprehension)
    # then we check if the sum is equal to number i
    return [i for i in range(1, n+1) if sum([div for div in range(1, i) if i % div == 0]) == i]


def doskonale_funkcyjna(n):
    # reduce calculates sum of divisors of i
    # filter filters from range() numbers that are not equal to sum of it's divisors
    return list(filter((lambda i: reduce((lambda x, y: x + y if i % y == 0 else x), range(1, i)) == i), range(2, n+1)))


# TESTS

print(doskonale_imperatywna(10000))
print(doskonale_skladana(10000))
print(doskonale_funkcyjna(10000))

setup = """
from __main__ import doskonale_imperatywna
from __main__ import doskonale_skladana
from __main__ import doskonale_funkcyjna
"""

n = 1000
number = 100
print("doskonale_imperatywna: ", timeit.timeit(f"doskonale_imperatywna({n})", setup=setup, number=number))
print("doskonale_skladana: ", timeit.timeit(f"doskonale_skladana({n})", setup=setup, number=number))
print("doskonale_funkcyjna: ", timeit.timeit(f"doskonale_funkcyjna({n})", setup=setup, number=number))

n = 10
number = 10000
print("doskonale_imperatywna: ", timeit.timeit(f"doskonale_imperatywna({n})", setup=setup, number=number))
print("doskonale_skladana: ", timeit.timeit(f"doskonale_skladana({n})", setup=setup, number=number))
print("doskonale_funkcyjna: ", timeit.timeit(f"doskonale_funkcyjna({n})", setup=setup, number=number))

# skladana ~ imperatywna < funkcyjna
