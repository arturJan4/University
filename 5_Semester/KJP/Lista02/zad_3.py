import functools

def sudan(n, x, y):
    if n == 0:
        return x + y

    if x >= 0 and y == 0:
        return x

    return sudan(n-1, sudan(n, x, y-1), sudan(n, x, y-1) + y)


@functools.lru_cache(maxsize=None)
def sudan_memo(n, x, y):
    if n == 0:
        return x + y

    if x >= 0 and y == 0:
        return x

    return sudan(n-1, sudan(n, x, y-1), sudan(n, x, y-1) + y)

# correctness

assert sudan(1, 5, 4) == 106
assert sudan(1, 5, 5) == 217

assert sudan(2, 2, 1) == 27
assert sudan(2, 5, 1) == 440
assert sudan(2, 0, 0) == 0
assert sudan(2, 0, 1) == 1
assert sudan(2, 1, 0) == 1
assert sudan(2, 0, 2) == 19
assert sudan(2, 1, 2) == 10228


# stress
import time
start = time.process_time()

print(sudan(1, 20, 20))

print(time.process_time() - start)  ## 11s

start = time.process_time()

print(sudan_memo(1, 20, 20))

print(time.process_time() - start)  ## 11s

