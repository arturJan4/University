# I) program correctness
# assertions

# def add(x, y):
#     assert type(x) == int
#
#     return x + y
#
# add("a", "b")
# print("test")

# assertions slow down the program
# __debug__ variable (default True)
# if __debug__
# if -O flag is passed during compilation -> debug = False

# II) Tests
# if __name__ = __main__ -> check if file is imported or ran
# unit tests -> test suite
# regressive tests -> ran after changes to the codebase
# python3.8 vs python3.9 example: "".replace("", 'abc', 3)

# pyunit example

# does correct data give correct result
# AND does incorrect data throw exception (is handled etc.)

# input, expected, actual pattern
# identity test

# assertEqual, assertRaises
# .setUp and .tearDown method for the class
# class inherits unittest.TestCase
# unitest naming convetions test* prefix
# TestSuite
# app/tests separation into separate folders -> context file
# (testers/developers)

# doctest -> smaller projects
# not only docs (help() usage)
# using examples from docs
# format:
# >>> operation
# expected results

# nose -> extension to pyunit
# stdout analysis (for tests)
# run only selected tests (useful for omitting longer tests for faster feedback loop)
# calculating code coverage

# selenium -> web testing
# recording scenarios
# programing scenarios (with assertions)


# type annotations (static typing)
def greet(name : str) -> str:
    return "Hello " + name


# MyPY, Pytype, Pylance, Pyre

# debugging: pdb & pycharm

# profiling
# straight in code: timeit.Timer
# profiler: python -m profile -o output.prof <program to profile>
# ncalls/percall/tottime etc.

# projekt
# pep8 with comments and modules
# type annotations, unittests (coverage > 50 %), autodoc
# packing script -> Distributing Python Modules

# interfejs graficzny + trwałe dane + kod
# np. gra, baza etc.
# termin -> koniec semestru (nie sesji): 27.02
# ~ 15 punktow?

# project ideas:
# check github project based learning
# chess gui + engine ??? -> warcaby dla prostoty
# -> how to write tests for that
# chess games database + viewer (FEN format reader) ~~ 30h
# django project -> something web-based (what about DB's usage in that?)

# chess playing
# select gui library
# saving games in FEN format?
# reading games in FEN format?
# no AI (for now, but should be easy to add) -> Monte Carlo??




