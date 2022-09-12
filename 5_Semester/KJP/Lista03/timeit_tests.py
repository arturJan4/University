import timeit


setup = """
from zad1 import *
from zad2 import *
"""

testcode = """
pierwsze_imperatywna(1000)
"""

if __name__ == '__main__':
    print(timeit.timeit(stmt=testcode, setup="from zad1 import pierwsze_imperatywna"))