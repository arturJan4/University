# larger nonograms solver (15x15 or smaller)

import random
import numpy as np

rows, cols = 0, 0
rows_hints = []
cols_hints = []
small_change = 0.1


def input_handler():
    """reads into global variables"""
    global rows, cols, rows_hints, cols_hints
    with open("zad_input.txt", "r") as rd:
        rows, cols = [int(i) for i in rd.readline().split()]

        rows_hints = [[int(x) for x in rd.readline().strip().split()] for _ in range(0, rows)]
        cols_hints = [[int(x) for x in rd.readline().strip().split()] for _ in range(0, cols)]


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


opt_dist_mem = {}


def opt_dist(bits, hints):
    """
    :param arglist: list of 0/1 bits
    :param hints: of given list (numbers denoting length of colored-black sequence)
    :return: minimum number of bit swaps needed to achieve correct row/column in nonogram with given hints
    """
    bits = list(bits)
    global opt_dist_mem  # optimization

    # check if such row/colmn was already calculated
    curr_pair = (tuple(bits), tuple(hints))
    if curr_pair in opt_dist_mem:
        return opt_dist_mem[curr_pair]

    bits = [0] + bits
    # infinity matrix to calculate using DP
    matrix = [[np.inf for i in range(len(bits) + 1)] for j in range(len(hints) + 1)]

    # prefix sum for 0..j bits
    for j in range(len(bits) + 1):
        matrix[0][j] = sum(bits[0:j])

    # for each hint
    for i in range(1, len(hints) + 1):
        # calculate using DP
        for j in range(sum(hints[0:i]) + i, len(bits) + 1):
            # options:
            # - inf
            # - add prev bit (+1 for #)
            # - use current hint to get previous DP value but minus prefix from that element to current j (colum) and adding that element

            matrix[i][j] = min(matrix[i][j], \
                               matrix[i][j - 1] + bits[j - 1], \
                               matrix[i - 1][j - hints[i - 1] - 1] + hints[i - 1] \
                               - sum(bits[j - hints[i - 1]: j]) + bits[j - hints[i - 1] - 1])

    result = matrix[len(hints)][len(bits)]
    opt_dist_mem[curr_pair] = result
    return result


def assign_random(rows, cols):
    """
    Build (rows x cols) matrix where
    1 - filled, 0 - unfilled field
    """
    return [[random.randint(0, 1) for i in range(0, cols)] for j in range(0, rows)]


def unfilled_rows(matrix):
    """ returns set of rows which don't fit the description/hint"""
    global rows_hints, rows, cols
    # for each row
    rows_set = set()

    for i in range(0, rows):
        hint_num = 0  # current block hint
        max_hint = len(rows_hints[i]) - 1  # index of last hint
        needs_space = False  # do we need space between the blocks now?

        current_block = 0
        if max_hint != -1:  # special case: empty hint table
            current_block = rows_hints[i][0]

        started_block = 0
        for j in range(0, cols):
            if matrix[i][j] == 0:  # empty field
                needs_space = False

                # stopped filling the block
                if started_block == 1:
                    if current_block != 0:
                        rows_set.add(i)
                        break
                started_block = 0
            else:
                started_block = 1
                if needs_space:  # needed empty got filled
                    rows_set.add(i)
                    break

                if hint_num > max_hint:  # more filled than hints
                    rows_set.add(i)
                    break

                current_block -= 1
                if current_block == 0:  # finished current hint's block
                    hint_num += 1
                    started_block = 0

                    if hint_num > max_hint:  # no more blocks after last one
                        current_block = 0
                    else:
                        current_block = rows_hints[i][hint_num]
                    needs_space = True  # need space between blocks

        # finished block has zero on current_block and no more hints
        if current_block != 0 or hint_num != max_hint + 1:
            rows_set.add(i)

    return rows_set


def unfilled_columns(matrix):
    global cols_hints, rows, cols
    # for each col
    cols_set = set()

    for j in range(0, cols):
        hint_num = 0
        max_hint = len(cols_hints[j]) - 1
        needs_space = False

        if max_hint == -1:  # special case: empty hint table
            current_block = 0
        else:
            current_block = cols_hints[j][0]

        started_block = 0
        for i in range(0, rows):
            if matrix[i][j] == 0:
                needs_space = False

                # stopped filling the block
                if started_block == 1:
                    if current_block != 0:
                        cols_set.add(j)
                        break
                started_block = 0
            else:
                started_block = 1
                if needs_space:
                    cols_set.add(j)
                    break

                if hint_num > max_hint:
                    cols_set.add(j)
                    break

                current_block -= 1
                if current_block == 0:
                    hint_num += 1
                    started_block = 0

                    if hint_num > max_hint:
                        current_block = 0
                    else:
                        current_block = cols_hints[j][hint_num]
                        needs_space = True

        if current_block != 0 or hint_num != max_hint + 1:
            cols_set.add(j)

    return cols_set


def fix_pixel_row(matrix, row_idx):
    """
        Given fixed row pick a column so that (i, j) pixel makes the biggest positive change possible.
        With small chance, make random choice.
    """
    global rows_hints, cols_hints, small_change, cols, rows

    # len of row + len of column
    minimum = cols + rows + 2
    minimum_idx = 0

    # opt before changes
    opt_row = opt_dist(matrix[row_idx], rows_hints[row_idx])

    # go through columns
    for j in range(0, cols):
        # column opt (TODO: optimize -> list of opts)
        opt_col_old = opt_dist([matrix[i][j] for i in range(0, rows)], cols_hints[j])
        old_opt = opt_col_old + opt_row

        matrix[row_idx][j] = (1 - matrix[row_idx][j])  # flip

        # recalculate opts
        opt_col = opt_dist([matrix[i][j] for i in range(0, rows)], cols_hints[j])
        opt_row_new = opt_dist(matrix[row_idx], rows_hints[row_idx])

        new_opt = opt_col + opt_row_new

        if new_opt < old_opt and new_opt < minimum:
            minimum = new_opt
            minimum_idx = j

        matrix[row_idx][j] = (1 - matrix[row_idx][j])  # flip again to fix

    # low probability -> random choice
    if random.random() < small_change:
        minimum_idx = random.randint(0, cols - 1)

    matrix[row_idx][minimum_idx] = (1 - matrix[row_idx][minimum_idx])

    return minimum_idx


def fix_pixel_col(matrix, col_idx):
    global rows_hints, cols_hints, rows, cols

    # go through rows

    # len of row + len of column
    minimum = cols + rows + 2
    minimum_idx = 0

    opt_col = opt_dist([matrix[i][col_idx] for i in range(0, rows)], cols_hints[col_idx])

    for i in range(0, len(matrix)):
        opt_row_old = opt_dist(matrix[i], rows_hints[i])

        matrix[i][col_idx] = (1 - matrix[i][col_idx])  # flip

        opt_row = opt_dist(matrix[i], rows_hints[i])
        opt_col_new = opt_dist([matrix[i][col_idx] for i in range(0, rows)], cols_hints[col_idx])

        old_opt = opt_row_old + opt_col
        new_opt = opt_row + opt_col_new

        if new_opt < old_opt and new_opt < minimum:
            minimum = new_opt
            minimum_idx = i

        matrix[i][col_idx] = (1 - matrix[i][col_idx])  # flip

    if random.random() < small_change:
        minimum_idx = random.randint(0, rows - 1)

    matrix[minimum_idx][col_idx] = (1 - matrix[minimum_idx][col_idx])

    return minimum_idx


def solve_nonogram(rows, cols, rows_hints, cols_hints):
    # random assignment
    matrix = assign_random(rows, cols)

    # wybieramy wiersze, które są niezgodne ze specyfikacją
    rows_unfilled = unfilled_rows(matrix)
    cols_unfilled = unfilled_columns(matrix)

    # print_nonogram(matrix)
    # print(rows_hints, cols_hints)
    # print(rows_unfilled, cols_unfilled)

    # print_nonogram(matrix)
    # print()
    # print(rows)
    ITER = 0

    while rows_unfilled or cols_unfilled:
        if ITER > 125000:
            # solve_calls += 1
            matrix = solve_nonogram(rows, cols, rows_hints, cols_hints)
            break

        ITER += 1

        # choose between row/column
        row_column = random.randint(0, 1)

        if row_column == 1 and len(rows_unfilled):
            # losujemy wiersz z niewypełnionych
            random_row = random.choice(tuple(rows_unfilled))

            # wybierz piksel
            changed_column = fix_pixel_row(matrix, random_row)
            # sprawdź czy można wyrzucić
            opt_col = opt_dist([matrix[j][changed_column] for j in range(0, rows)], cols_hints[changed_column])
            opt_row = opt_dist(matrix[random_row], rows_hints[random_row])

            if opt_row == 0:
                rows_unfilled.remove(random_row)

            if opt_col == 0:
                cols_unfilled.remove(changed_column)
            else:
                cols_unfilled.add(changed_column)

        elif len(cols_unfilled):
            random_col = random.choice(tuple(cols_unfilled))

            changed_row = fix_pixel_col(matrix, random_col)

            # sprawdź czy można wyrzucić
            opt_col = opt_dist([matrix[j][random_col] for j in range(0, rows)], cols_hints[random_col])
            opt_row = opt_dist(matrix[changed_row], rows_hints[changed_row])

            if opt_col == 0:
                cols_unfilled.remove(random_col)

            if opt_row == 0:
                rows_unfilled.remove(changed_row)
            else:
                rows_unfilled.add(changed_row)

    return matrix


# # =============================TESTS=====================================
# rows = 3
# cols = 5
# rows_hints = [[4], [2], [2]]
# cols_hints = [[]]
# matrix = [[1, 1, 1, 1, 0], [0, 0, 1, 1, 0], [1, 0, 1, 0, 0]]
# print_nonogram(matrix)
# print(unfilled_rows(matrix))  # expected: 2
#
# rows = 4
# cols = 5
# rows_hints = [[5], [2, 1], [2, 1], [2, 1]]
# cols_hints = [[], [], [], [], []]
# matrix = [[1, 1, 1, 1, 1], [1, 1, 1, 0, 0], [1, 1, 0, 1, 0], [1, 1, 0, 0, 1]]
# print_nonogram(matrix)
# print(unfilled_rows(matrix))  # expected 1
# print(unfilled_columns(matrix))  # expected 0, 1, 2, 3, 4
#
# rows = 4
# cols = 5
# rows_hints = [[4], [3, 1], [2, 1], [2, 1]]
# cols_hints = [[4], [5], [3], [2], [1, 1]]
# matrix = [[1, 1, 1, 1, 1],
#           [1, 1, 1, 0, 0],
#           [1, 1, 0, 1, 0],
#           [1, 1, 0, 1, 1]]
# print_nonogram(matrix)
# print(unfilled_rows(matrix))  # expected 0, 1, 3
# print(unfilled_columns(matrix))  # expected 1, 2, 3
#
# print(opt_dist([0, 0, 0], [1]))     # 1
# print(opt_dist([0, 0, 0], [1, 1]))  # 2
# print(opt_dist([1, 0, 1], [3]))     # 1
# print(opt_dist([1, 0, 1, 0, 1], [3, 1])) # 1

input_handler()
# print(cols_hints)

matrix = solve_nonogram(rows, cols, rows_hints, cols_hints)
with open("zad_output.txt.txt", "w") as wr:
    print_nonogram(matrix, file=wr)
