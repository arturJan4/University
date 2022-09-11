# functions are first order in python
# but python is not functional

# functions as arguments
from functools import reduce
import operator
import itertools


def integral_def(f, a, b):
    krok, suma, x = 0.1, 0, a
    while x + krok < b:
        suma += f(x)*krok
        x += krok

    return suma


def fun(x): return (x+1)/x


def foo(x): return 2 * x


print(integral_def(fun, 1, 5))
funList = [fun, foo]

# lambdas
double = lambda x: 2*x

# filter
print(list(filter(lambda x: x % 2 == 0, range(10))))

# map
print(list(map(lambda x: x * 2, range(10))))

# reduce
print((reduce(lambda x, y: x + y, range(10), 0)))

# list comprehensions
print([(x, x*x*x) for x in range(10) if x % 2 == 0])

print([s.upper() if len(s) > 5 else s.lower() for s in ["wordddd", "ww", "wordrd", "werwe"]])

print([[z for z in s] for s in ["wordddd", "ww", "wordrd", "werwe"]])

# cartesian product
colors = ["R", "G", "B"]
fig = ["0", "1", "2", "A"]
print([(c, g) for c in colors for g in fig])

# functions return iterators instead of lists -> for laziness
for x in list(range(3)):
    print(x)

# iterable example
for x in range(3):
    print(x)

# functional ops -> operator lib
v1 = [1, 2, 3]
v2 = [4, 5, 6]
print(sum(map(operator.mul, v1, v2)))


# yield
def power2():
    power = 1
    while True:
        yield power
        power *= 2


it = power2()
for x in range(4):
    print(next(it))

for i in power2():
    if i > 10234:
        break
    print(i)

# generator expressions
wyr = (i**2 for i in range(100))
wyr_l = [i**2 for i in range(100)]
list(wyr)

# usage -> hex
print(":".join(":02x".format(ord(c)) for c in "abcd1234"))


# yield from (equivalent syntax)
def fn():
    for item in range(10):
        yield item


def fnn():
    yield from range(10)


# itertools -> 8 queens problem
print(list(itertools.permutations(range(5))))
print((itertools.permutations(range(5000))))  # this works!


def nonconflict(lista):
    for x, xi in enumerate(lista):
        for y, yi in enumerate(lista[x+1:]):
            if xi == yi or abs(x-y) == abs(xi-yi):
                return False
    return True


print(list(filter(nonconflict, itertools.permutations(range(8)))))

# files
# fh = open('file.txt', 'r')
# fh.close()

# "r", "w", "a"  - read/write/append, "r+" - read+save, "rb" - read binary
# fh.read(), fh.read(size), fh.readline(), fh.readlines()
# open(encoding=''utf-8'')

# file handler is iterable!
# for line in fh:

# with -> managing files
with open('file', 'r') as fh:
    data = fh.read()


# word generator from file
def slowa(fname):
    with open(fname, 'r') as fh:
        for w in fh.readline().split():
            yield w

# list(filter(lambda w: len(w) > 10, slowa('wojna.txt')))