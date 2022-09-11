# Nonogram solver using logical deduction (for harder cases)

import numpy as np
from collections import deque


rows, cols = 0, 0  # dimensions
rows_hints = []
cols_hints = []


def input_handler():
    """reads into global variables"""
    global rows, cols, rows_hints, cols_hints
    with open("zad_input.txt", "r") as rd:
        rows, cols = [int(i) for i in rd.readline().split()]

        rows_hints = [[int(x) for x in rd.readline().strip().split()] for _ in range(0, rows)]
        cols_hints = [[int(x) for x in rd.readline().strip().split()] for _ in range(0, cols)]


input_handler()


def print_nonogram(matrix, file=None):
    for i in range(0, len(matrix)):
        row_str = ""
        for j in range(0, len(matrix[0])):
            if matrix[i][j] == 1:
                row_str += '#'
            else:
                row_str += '.'
        if file is None:
            print(row_str)
        else:
            print(row_str, file=file)


def gen_filled(n, hints):
    """Generate all possible segments of size n with given hints"""
    # no more hints -> fill with zeroes
    if not hints:
        return [[0] * n]

    solutions = []

    current_hint = hints[0]
    num_hints = len(hints)
    if num_hints == 1:
        # process last hint (no needed 0 padding at the end)
        # i zeroes, block
        for i in range(0, n - current_hint + 1):
            assert(n - i - current_hint >= 0)
            block = [0] * i + [1] * current_hint + [0] * (n - i - current_hint)
            assert(len(block) == n)
            solutions.append(block)

        return solutions

    sum_hints = sum(hints)
    # non-last hint, padding needed
    # 1 padding per hint
    for i in range(0, n - sum_hints - (num_hints - 2) + 1):
        left = [0] * i + [1] * current_hint + [0]
        assert (n - i - current_hint - 1 >= 0)
        rights = gen_filled(n-i-current_hint-1, hints[1:])
        for right in rights:
            assert (len(left+right) == n)
            solutions.append(left+right)

    return solutions


# domains of possible rows and cols given hints
rows_domain = [gen_filled(cols, hint) for hint in rows_hints]
cols_domain = [gen_filled(rows, hint) for hint in cols_hints]

# print(rows_domain)
# for x in cols_domain:
#   print_nonogram(x)

# for x in rows_domain:
#     print_nonogram(x)

# print(rows_domain)
# represent bits that for sure are filled correctly
bad_pixels = deque()

# queue of row/col indices to fix
# to_fix_rows = deque([i for i in range(0, rows)])
# to_fix_cols = deque([i for i in range(0, cols)])

# matrix of filled values
matrix = np.zeros((rows, cols))


# exclude those solutions that don't have bit of value val in (x, y) position
def exclude(solutions, x, y, val, is_cols=False):
    if is_cols:
        # x-th column possibilities, y-th bit in column
        return [col for col in solutions[x] if col[y] == val]
    else:
        # y-th row possibilities
        return [row for row in solutions[y] if row[x] == val]


def fix(x, y):
    global rows_domain, cols_domain, matrix, bad_pixels
    first = rows_domain[y][0][x]  # x-th column in y-th row, first possibility

    possibilities_row = len(rows_domain[y])
    # in all the possibilities of the row the pixel value is the same
    if all(rows_domain[y][k][x] == first for k in range(possibilities_row)):
        matrix[y][x] = first  # set the value in final matrix
        cols_domain[x] = exclude(cols_domain, x, y, first, True)  # exclude non matching in column
    else:  # something doesn't match -> repeat deduction for columns
        val = cols_domain[x][0][y]  # y-th column in x-th row (mirrored)

        possibilities_col = len(cols_domain[x])
        # in all the possibilities of the column the pixel value is the same
        if all(cols_domain[x][k][y] == val for k in range(possibilities_col)):
            matrix[y][x] = val
            rows_domain[y] = exclude(rows_domain, x, y, val, False)
        else:
            bad_pixels.append((y, x))  # can't deduct the correct val now


def solve_nonogram():
    global rows, cols, rows_hints, cols_hints

    for y in range(rows):
        for x in range(cols):
            fix(x, y)  # try to deduct each pixel

    # if there are some still not deducted -> use queue
    while bad_pixels:
        y, x = bad_pixels.popleft()
        fix(x, y)

    # final board
    return


# TESTS

# print_nonogram(gen_filled(9, [3, 2]))
# print_nonogram(gen_filled(5, [1, 1, 1]))
# print_nonogram(gen_filled(6, [1, 1, 1]))

# SOLUTION
#print(rows_hints, "\n", cols_hints)
solve_nonogram()
with open("zad_output.txt", "w") as wr:
    print_nonogram(matrix, file=wr)
