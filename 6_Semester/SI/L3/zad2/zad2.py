# Nonogram solver using deduction
# now with backtracking -> return when we know we won't get anywhere with our solution :(

import numpy as np
from collections import deque
import copy


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
            assert (n - i - current_hint >= 0)
            block = [0] * i + [1] * current_hint + [0] * (n - i - current_hint)
            assert (len(block) == n)
            solutions.append(block)

        return solutions

    sum_hints = sum(hints)
    # non-last hint, padding needed
    # 1 padding per hint
    for i in range(0, n - sum_hints - (num_hints - 2) + 1):
        left = [0] * i + [1] * current_hint + [0]
        assert (n - i - current_hint - 1 >= 0)
        rights = gen_filled(n - i - current_hint - 1, hints[1:])
        for right in rights:
            assert (len(left + right) == n)
            solutions.append(left + right)

    return solutions


def exclude(solutions, x, y, val, is_cols=False):
    """
    exclude those solutions that don't have bit of value val in (x, y) position
    """
    if is_cols:
        # x-th column possibilities, y-th bit in column
        return [col for col in solutions[x] if col[y] == val]
    else:
        # y-th row possibilities
        return [row for row in solutions[y] if row[x] == val]


def no_solution(rows_domain_l, cols_domain_l):
    """
    check if either domain is empty on some row/column
    """
    for row in range(rows):
        for col in range(cols):
            if not rows_domain_l[row]:
                return True
            if not cols_domain_l[col]:
                return True

    return False


def eliminate_good_pixel(bad_pixels_l, rows_domain_l, cols_domain_l, matrix_l):
    """
    find new bad pixels -> remove as much as possible first to reduce states
    """
    while True:
        exit_loop = True
        bad_pixels_l2 = deque()
        for i in range(len(bad_pixels_l)):
            y, x = bad_pixels_l[i]

            if fix(x, y, rows_domain_l, cols_domain_l, matrix_l):
                exit_loop = False  # added sth and changed domain -> repeat

                # check if adding breaks solution
                if not rows_domain_l[y]:
                    return False, []
                if not cols_domain_l[x]:
                    return False, []
            else:
                bad_pixels_l2.append((y, x))  # still a bad pixel

        bad_pixels_l = bad_pixels_l2

        if exit_loop:
            return True, bad_pixels_l2


def backtrack(bad_pixels_l, rows_domain_l, cols_domain_l, matrix_l):
    """
    backtrack on board -> insert True and then False on bad pixel
    """
    # no more possible moves
    if no_solution(rows_domain_l, cols_domain_l):
        # print("no moves")
        return False, []

    # eliminate good pixels using deduction
    result, bad_pixels_new = eliminate_good_pixel(bad_pixels_l, rows_domain_l, cols_domain_l, matrix_l)
    if not result:
        # print("elimination leads to failure")
        return False, []

    # there are still bad pixels
    if bad_pixels_new:
        # print_nonogram(matrix_l)
        # pick only first bad pixel
        y, x = bad_pixels_new.popleft()

        # prepare copies
        rows_domain_true = copy.copy(rows_domain_l)
        cols_domain_true = copy.copy(cols_domain_l)
        cols_domain_false = copy.copy(cols_domain_l)
        rows_domain_false = copy.copy(rows_domain_l)

        # set bad pixel to true
        matrix_l[y][x] = True
        cols_domain_true[x] = exclude(cols_domain_l, x, y, 1, True)
        rows_domain_true[y] = exclude(rows_domain_l, x, y, 1, False)

        # print(f"backtracking ({y}, {x}): True")
        result, matrix_res = backtrack(bad_pixels_new.copy(), rows_domain_true, cols_domain_true, copy.copy(matrix_l))
        # backtrack is successful -> pass result back
        if result:
            return True, matrix_res

        # backtrack unsuccessful
        # set bad pixel to false and continue
        # print(f"backtracking ({y}, {x}): False")

        matrix_l[y][x] = False
        cols_domain_false[x] = exclude(cols_domain_false, x, y, 0, True)
        rows_domain_false[y] = exclude(rows_domain_false, x, y, 0, False)

        result, matrix_res = backtrack(bad_pixels_new.copy(), rows_domain_false, cols_domain_false, copy.copy(matrix_l))

        if result:
            return True, matrix_res

        # print(f"backtracking ({y}, {x}): returning")
        return False, []

    # no bad pixels
    return True, matrix_l


# return true if can deduct (y, x)-pixel value ans save it to matrix[y][x]
def fix(x, y, rows_domain, cols_domain, matrix):
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
            return False

    return True


# matrix of filled values
matrix = np.zeros((rows, cols))


def solve_nonogram():
    # domains of possible rows and cols given hints
    rows_domain = [gen_filled(cols, hint) for hint in rows_hints]
    cols_domain = [gen_filled(rows, hint) for hint in cols_hints]

    # represent bits that for sure are filled correctly
    bad_pixels = deque()

    for y in range(rows):
        for x in range(cols):
            if not fix(x, y, rows_domain, cols_domain, matrix):  # try to deduct each pixel
                bad_pixels.append((y, x))  # still a bad pixel

    # backtrack on rest of domain
    result, matrix_res = backtrack(bad_pixels, copy.copy(rows_domain), copy.copy(cols_domain), matrix)

    if not result:
        raise Exception("invalid backtrack")

    return matrix_res


# SOLUTION
# print(rows_hints, "\n", cols_hints)
matrix = solve_nonogram()
with open("zad_output.txt", "w") as wr:
    print_nonogram(matrix, file=wr)
