# opt-dist = num of flips for a nonogram row

import math

def opt_dist(bits, D):
    """
    :param arglist: list of 0/1 bits
    :param D: length of expected sequence of 1's
    :return: minimum number of bit swaps needed to achieve sequence of D 1's (rest are 0's)
    """
    maximum = len(bits)  # index one past the last one
    bit_count = sum(bit == '1' for bit in bits)

    min_moves = bit_count + D  # swap all 1->0 and make a sequence of length D

    # use sliding-window technique (window of length D)
    for i in range(0, maximum - D + 1):
        window_len = 0  # 1's in the window

        for j in range(i, i + D):
            if bits[j] == '1':
                window_len += 1
        to_flip_out = bit_count - window_len  # 1's to flip outside the window
        to_flip_in = D - window_len           # 0's to flip inside the window

        if to_flip_in + to_flip_out < min_moves:
            min_moves = to_flip_in + to_flip_out

    return min_moves


# tests
# print(opt_dist("0010001000", 5))
# print(opt_dist("0010001000", 4))
# print(opt_dist("0010001000", 3))


# Take string input and pass to opt_bits"
def input_handler():
    with open("zad4_input.txt", "r") as rd:
        with open("zad4_output.txt", "w") as wr:
            for line in rd:
                line = line.split()
                print(opt_dist(line[0], int(line[1])), file=wr)


input_handler()
