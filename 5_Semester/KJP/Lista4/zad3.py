def valid_numbers(grid, x, y):
    """
    :param grid: 9x9 grid of numbers from 1-9 range representing sudoku grid,
    0's represent empty fields
    :param x: position's column (0 indexed)
    :param y: position's row (0 indexed)
    :return: valid numbers to place for a given grid and position (x, y)
    """
    if grid[y][x] != 0:  # field is already filled
        return grid[y][x]

    used_numbers = [0] * 10  # count of number's usage

    # row
    for i in range(9):
        used_numbers[grid[y][i]] += 1

    # column
    for i in range(9):
        used_numbers[grid[i][x]] += 1

    # 3x3 block
    block_r = y // 3  # (0, 1, 2)
    block_c = x // 3

    for row in range(block_r*3, (block_r+1)*3):
        for col in range(block_c*3, (block_c+1)*3):
            used_numbers[grid[row][col]] += 1

    # return only non-used numbers
    return [i for i in range(1, 10) if used_numbers[i] == 0]


def first_empty(grid):
    """
    :return: first non-empty field (represented by 0) in a grid,
    or None if there are no empty spaces
    """
    for i in range(0, 9):
        for j in range(0, 9):
            if grid[i][j] == 0:
                return i, j

    return None


def solve_sudoku(grid):
    """
    Solves sudoku using recursion (backtracking)
    :param grid: 9x9 grid with numbers in [1, 9] range, 0-s represent empty space's
    :return: solved sudoku grid or None if there is no valid solution
    """
    empty_spot = first_empty(grid)

    if empty_spot is None:
        return grid  # there are no empty spaces -> we are done

    y, x = empty_spot
    valid = valid_numbers(grid, x, y)
    if valid is not None:
        for num in valid:     # checks each valid number to place
            grid[y][x] = num  # and places it

            if solve_sudoku(grid) is not None:
                return grid

            grid[y][x] = 0    # placing num didn't lead to solution so we remove it

    return None


def pretty_print_sudoku(grid):
    ver_sep = '|| '  # appears every third number
    hor_sep = '='
    separator = ' '  # separates numbers from themselves and borders

    # 8 separators in between numbers, 2 vertical separators
    row_length = 9 + len(separator) * 8 + len(ver_sep) * 4

    for row in range(0, 9):
        if row % 3 == 0:
            print(hor_sep*row_length)

        for col in range(0, 10):
            if col % 3 == 0:
                print(ver_sep, end='')

            if row < 9 and col < 9:
                print(grid[row][col], end=separator)
        print("")
    print(hor_sep * row_length)


# ================================================================
#                           TESTS
# ================================================================

# 186 iterations of solve_sudoku()
# easy example
example_easy = [[0, 7, 0, 0, 5, 0, 0, 9, 2],
                [2, 5, 9, 1, 0, 0, 6, 3, 4],
                [0, 0, 0, 4, 0, 2, 5, 0, 0],
                [3, 0, 2, 7, 1, 6, 0, 0, 0],
                [5, 0, 1, 2, 0, 0, 0, 0, 0],
                [0, 0, 0, 5, 0, 0, 0, 2, 3],
                [6, 2, 0, 0, 0, 0, 0, 0, 5],
                [0, 0, 7, 0, 0, 0, 0, 0, 6],
                [0, 8, 5, 0, 0, 4, 0, 1, 0]]

# 12207092 iterations solve_sudoku()
# from: https://www.researchgate.net/figure/A-Sudoku-with-17-clues-and-its-unique-solution_fig1_311250094
example_hard = [[0, 0, 0, 8, 0, 1, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 4, 3],
                [5, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 7, 0, 8, 0, 0],
                [0, 0, 0, 0, 0, 0, 1, 0, 0],
                [0, 2, 0, 0, 3, 0, 0, 0, 0],
                [6, 0, 0, 0, 0, 0, 0, 7, 5],
                [0, 0, 3, 4, 0, 0, 0, 0, 0],
                [0, 0, 0, 2, 0, 0, 6, 0, 0]]

# printing tests
pretty_print_sudoku(example_easy)
# pretty_print_sudoku(example_hard)

# valid_numbers tests
# print(valid_numbers(example_hard, 0, 0))
# print(valid_numbers(example_hard, 1, 0))
# print(valid_numbers(example_hard, 8, 5))

# solve_sudoku test
pretty_print_sudoku(solve_sudoku(example_easy))
# pretty_print_sudoku(solve_sudoku(example_hard)) # this takes a while
