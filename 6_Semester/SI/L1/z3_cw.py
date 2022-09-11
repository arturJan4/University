from math import comb

# extra-rules poker game win-chance using probability

hand_f = [4 * comb(4, 2) * 4 ** 3,  # para
          comb(4, 2) ** 3 * 2 * comb(4, 1),  # dwie pary
          4 * comb(4, 3) * comb(3, 2) * 4 ** 2,  # trójka
          0,  # strit
          0,  # kolor
          4 * comb(4, 3) * 3 * comb(4, 2),  # full
          4 * 3 * 4,  # kareta
          0]  # poker

hand_b = [9 * comb(4, 2) * comb(8, 3) * comb(4, 1) ** 3,  # para
          comb(9, 2) * comb(4, 2) ** 2 * 7 * 4,  # dwie pary
          9 * comb(4, 3) * comb(8, 2) * 4 ** 2,  # trójka
          5 * 4 ** 5 - 20,  # 20 - #ukladow z pokerem        # strit
          comb(9, 5) * 4 - 20,  # 20 - j.w.               # kolor
          9 * comb(4, 3) * 8 * comb(4, 2),  # full
          9 * 8 * 4,  # kareta
          5 * 4]  # poker

all_b = comb(36, 5)
all_f = comb(16, 5)


def ppb_b_wins():
    wins_b = 0
    for i in range(7):
        curr_hand = hand_b[i]
        sum_f = 0
        for j in range(i):
            sum_f += hand_f[j]
        wins_b += curr_hand * sum_f
    return wins_b / (all_b * all_f)


if __name__ == "__main__":
    print(ppb_b_wins())