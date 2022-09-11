# n = k^2
# sqrt(n) = k -> sum(2i - 1)


def pierwiastek(n):
    """
    Calculates floor of square root of number n using iterative formula.
    :param n: natural number n
    :return:
    """
    sum = 0
    for i in range(1, n+1):
        sum += 2*i - 1

        if sum > n:
            return i-1

    return n  # for n == 0


# testy

for i in range(1, 37):
    print(f"pierwiastek({i}): {pierwiastek(i)}")
