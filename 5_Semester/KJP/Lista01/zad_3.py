def tabliczka(x1, x2, y1, y2):
    """
    Print a multiplication table of given size
    with labels for rows and columns.

    Uses fixed-width (with spaces and right-align).
    """
    # additional 2 cases for negative numbers
    digits_max = max(len(str(x2 * y2)),
                     len(str(x1 * y2)),
                     len(str(x2 * y1)))
    width = digits_max + 1

    print(" "*width, end="")  # top left empty space

    # labels for the columns
    for i in range(x1, x2 + 1):
        print(f'{i:>{width}}', end="")
    print()

    for i in range(y1, y2+1):
        print(f'{i:>{width}}', end="")  # labels for the rows
        for j in range(x1, x2+1):
            print(f'{i*j:>{width}}', end="")
        print()


tabliczka(3, 5, 2, 4)
print()
tabliczka(1, 10, 1, 10)
print()
tabliczka(-3, 5, -2, 6)
