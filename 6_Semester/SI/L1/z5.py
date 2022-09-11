# simplified nonograms solver (inspired by WalkSat algorithm)
# given row/column hints prints a nonogram to stdout

import random

rows, cols = 0, 0
rows_hints = []
cols_hints = []
small_change = 0.03

def input_handler():
    """reads into global variables"""
    global rows, cols, rows_hints, cols_hints
    with open("zad5_input.txt", "r") as rd:
        rows, cols = [int(i) for i in rd.readline().split()]

        for i in range(0, rows):
            line = rd.readline().strip()
            rows_hints.append(int(line))

        for i in range(0, cols):
            line = rd.readline().strip()
            cols_hints.append(int(line))


def opt_dist(bits, D):
    """
    :param arglist: list of 0/1 bits
    :param D: length of expected sequence of 1's
    :return: minimum number of bit swaps needed to achieve sequence of D 1's (rest are 0's)
    """
    maximum = len(bits)  # index one past the last one
    bit_count = sum(bit == 1 for bit in bits)

    min_moves = bit_count + D  # swap all 1->0 and make a sequence of length D

    # use sliding-window technique (window of length D)
    for i in range(0, maximum - D + 1):
        window_len = 0  # 1's in the window

        for j in range(i, i + D):
            if bits[j] == 1:
                window_len += 1
        to_flip_out = bit_count - window_len  # 1's to flip outside the window
        to_flip_in = D - window_len           # 0's to flip inside the window

        min_moves = min(to_flip_in + to_flip_out, min_moves)

    return min_moves


def assign_random(rows, cols):
    """
    Build rows x cols matrix where
    1 - filled, 0 - unfilled field
    """
    return [[random.randint(0, 1) for i in range(0, cols)] for j in range(0, rows)]


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


def unfilled_rows(matrix):
    """ returns set of rows which don't fit the description/hint"""
    global rows_hints
    # for each row
    rows = set()

    for i in range(0, len(matrix)):
        opt = opt_dist(matrix[i], rows_hints[i])

        if opt > 0:
            rows.add(i)

    return rows


def unfilled_columns(matrix):
    global cols_hints
    # for each col
    cols = set()

    for i in range(0, len(matrix[0])):
        opt = opt_dist([matrix[j][i] for j in range(0, len(matrix))], cols_hints[i])

        if opt > 0:
            cols.add(i)

    return cols


def fix_pixel_row(matrix, row_idx):
    """
        Given fixed row pick a column so that (i, j) pixel makes the biggest positive change possible.
        With small chance, make random choice.
    """
    global rows_hints, cols_hints, small_change

    # len of row + len of column
    minimum = len(matrix[0]) + len(matrix) + 2
    minimum_idx = 0

    # opt before changes
    opt_row = opt_dist(matrix[row_idx], rows_hints[row_idx])

    # go through columns
    for j in range(0, len(matrix[0])):
        # column opt (TODO: optimize -> list of opts)
        opt_col_old = opt_dist([matrix[i][j] for i in range(0, len(matrix))], cols_hints[j])
        old_opt = opt_col_old + opt_row

        matrix[row_idx][j] = (1 - matrix[row_idx][j])  # flip

        # recalculate opts
        opt_col = opt_dist([matrix[i][j] for i in range(0, len(matrix))], cols_hints[j])
        opt_row_new = opt_dist(matrix[row_idx], rows_hints[row_idx])

        new_opt = opt_col + opt_row_new

        if new_opt < old_opt and new_opt < minimum:
            minimum = new_opt
            minimum_idx = j

        matrix[row_idx][j] = (1 - matrix[row_idx][j])  # flip again to fix

    # low probability -> random choice
    if random.random() < small_change:
        minimum_idx = random.randint(0, len(matrix[0]) - 1)

    matrix[row_idx][minimum_idx] = (1 - matrix[row_idx][minimum_idx])

    return minimum_idx


def fix_pixel_col(matrix, col_idx):
    global rows_hints, cols_hints

    # go through rows
    minimum = len(matrix[0]) + len(matrix) + 2
    minimum_idx = 0

    opt_col = opt_dist([matrix[i][col_idx] for i in range(0, len(matrix))], cols_hints[col_idx])

    for i in range(0, len(matrix)):
        opt_row_old = opt_dist(matrix[i], rows_hints[i])

        matrix[i][col_idx] = (1 - matrix[i][col_idx])  # flip

        opt_row = opt_dist(matrix[i], rows_hints[i])
        opt_col_new = opt_dist([matrix[i][col_idx] for i in range(0, len(matrix))], cols_hints[col_idx])

        old_opt = opt_row_old + opt_col
        new_opt = opt_row + opt_col_new

        if new_opt < old_opt and new_opt < minimum:
            minimum = new_opt
            minimum_idx = i

        matrix[i][col_idx] = (1 - matrix[i][col_idx])  # flip

    if random.random() < small_change:
        minimum_idx = random.randint(0, len(matrix) - 1)

    matrix[minimum_idx][col_idx] = (1 - matrix[minimum_idx][col_idx])

    return minimum_idx


def solve_nonogram(rows, cols, rows_hints, cols_hints):
    # random assignment
    matrix = assign_random(rows, cols)

    # wybieramy wiersze, które są niezgodne ze specyfikacją
    rows_unfilled = unfilled_rows(matrix)
    cols_unfilled = unfilled_columns(matrix)

    # print_nonogram(matrix)
    # print()
    # print(rows)
    ITER = 0

    while rows_unfilled or cols_unfilled:
        if ITER > 10000:
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
            opt_col = opt_dist([matrix[j][changed_column] for j in range(0, len(matrix))], cols_hints[changed_column])
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
            opt_col = opt_dist([matrix[j][random_col] for j in range(0, len(matrix))], cols_hints[random_col])
            opt_row = opt_dist(matrix[changed_row], rows_hints[changed_row])

            if opt_col == 0:
                cols_unfilled.remove(random_col)

            if opt_row == 0:
                rows_unfilled.remove(changed_row)
            else:
                rows_unfilled.add(changed_row)

    return matrix


input_handler()
matrix = solve_nonogram(rows, cols, rows_hints, cols_hints)
with open("zad5_output.txt", "w") as wr:
    print_nonogram(matrix, file=wr)
