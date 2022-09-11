import math
import timeit
import itertools


def pierwsze_imperatywna(n):
    result = []
    for i in range(2, n+1):
        is_prime = True
        for div in range(2, int(math.sqrt(i)) + 1):
            if i % div == 0:
                is_prime = False
                break

        if is_prime:
            result.append(i)

    return result


def pierwsze_skladana(n):
    # for each number i we check if a list of remainders of i
    # when divided by numbers less than sqrt(i) + 1 doesn't contain 0
    return [i for i in range(2, n+1) if 0 not in [i % div for div in range(2, int(math.sqrt(i)) + 1)]]


def pierwsze_funkcyjna(n):
    # for each number x we check if all remainders of x
    # when divided by numbers less than sqrt(i) + 1 is nonzero
    return list(filter(lambda x: all((x % i) != 0 for i in range(2, int(math.sqrt(x)) + 1)), range(2, n+1)))


# TESTS

print(len(pierwsze_imperatywna(100)))
print(len(pierwsze_imperatywna(1000)))

print(len(pierwsze_skladana(100)))
print(len(pierwsze_skladana(1000)))

print(len(pierwsze_funkcyjna(100)))
print(len(pierwsze_funkcyjna(1000)))


setup = """
from __main__ import pierwsze_imperatywna
from __main__ import pierwsze_skladana
from __main__ import pierwsze_funkcyjna
"""

n = 10000
number = 100
print("pierwsze_imperatywna: ", timeit.timeit(f"pierwsze_imperatywna({n})", setup=setup, number=number))
print("pierwsze_skladana: ", timeit.timeit(f"pierwsze_skladana({n})", setup=setup, number=number))
print("pierwsze_funkcyjna: ", timeit.timeit(f"pierwsze_funkcyjna({n})", setup=setup, number=number))

n = 100
number = 10000
print("pierwsze_imperatywna: ", timeit.timeit(f"pierwsze_imperatywna({n})", setup=setup, number=number))
print("pierwsze_skladana: ", timeit.timeit(f"pierwsze_skladana({n})", setup=setup, number=number))
print("pierwsze_funkcyjna: ", timeit.timeit(f"pierwsze_funkcyjna({n})", setup=setup, number=number))
# imperatywna < funkcyjna < skladana

# z ćwiczeń
# co drugi element

# timeit.timeit chce callable czyli można użyć lambdy
print("fun(100): " + str(timeit.timeit(lambda: pierwsze_funkcyjna(100), number=10)))

# print([kand for kand in [2] + list(range(3, 100, 2)) if isPrime(kand)])
# słabe bo generator -> lista
# ale mamy konkatenację (można listę z generatorem, gen z gen itp.)
for x in itertools.chain(range(2, 11, 2), range(11, 20, 2)):
    print(x)
