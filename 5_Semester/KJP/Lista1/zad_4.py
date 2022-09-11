import random


def throw_coin():
    """Binary coin: e.g. 1 - heads, 0 - tails."""
    return random.randint(0, 1)


def experiment(in_row=3):
    """
    Throws a coin until the same side is thrown $in_row times in a row.
    :return number of total throws
    """
    side_cnt = [0, 0]

    last_side = throw_coin()
    side_cnt[last_side] += 1
    throws_cnt = 1

    while side_cnt[0] != in_row and side_cnt[1] != in_row:
        side = throw_coin()
        if side != last_side:
            side_cnt = [0, 0]

        last_side = side
        side_cnt[side] += 1
        throws_cnt += 1

    return throws_cnt


def experiment_runner(tries, in_row=3):
    """
    Runs the coin experiment given number of times.
    :param tries: number of experiment
    :param in_row: how many of same side in row is needed
    :return: average number of throws in an experiment
    """

    throws_count = 0
    for i in range(tries):
        throws_count += experiment(in_row)

    return throws_count / tries


t = 100
r = 3
result = experiment_runner(tries=t, in_row=r)
print(f"Average number of throws to get {r} same sides in a row, for {t} tries is {result}.")
