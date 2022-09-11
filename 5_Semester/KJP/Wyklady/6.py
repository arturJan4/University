# callable objects - functions, methods, classes, objects implementing __call__


# function is an object
def foo(x):
    return 2 * x


print(dir(foo))


class Triple:
    def __call__(self, n):
        return 3 * n


f = Triple()

print(f(123))


class Counter:
    def __init__(self):
        self.counter = 0

    def __call__(self, *args, **kwargs):
        self.counter += 1
        return self.counter


# Threads
# parallel input/output, WWW server communication etc.

# thread -> low-level
# threading -> high level uses thread
# multiprocessing
# concurrent.futures

class Thead:
    def run(self):
        pass

    def start(self):
        pass


import threading
total_distance = 0


class Runner(threading.Thread):
    def __init__(self, start_nr):
        self.number = start_nr
        threading.Thread.__init__(self)

    def run(self):
        global total_distance
        distance = 42195
        while distance > 0:
            distance -= 1
            total_distance += 1
            if distance % 10000 == 0:
                print(f"Runner nr {self.number}")

        print(f"Runner nr {self.number} finished!")


# 3 threads: main and 2 additional
r1 = Runner(1)
r2 = Runner(2)

r1.start()
r2.start()

r1.join()
r2.join()

print(f"end of race: total distance: {total_distance}")

# another syntax
tbr = threading.Thread(target=pow, args=(2, 10))

# increment is 4 bytecode operations
# so it's not atomic

# locks
lock = threading.Lock()

# only one thread can lock
# using lock.acquire() then it has to remove it with
# lock.release()
# other threads are waiting if another thread is in a critical section

# Rlock (multiple times) -> slow
# Semaphore (enter given number of times)

# producer and customer pattern
lck = threading.Lock()

glass_of_milk = 0
# produce
lck.acquire()
for i in range(5):
    glass_of_milk += 1
lck.release()

# active wait :/
while glass_of_milk != 5:
    pass

lck.acquire()
while glass_of_milk > 0:
    glass_of_milk -= 1
lck.release()

# waking and putting threads to sleep
# conditional locks
# lock = threading.Condition()
# lck.wait() -> sleep
# lck.notify() -> wake (.notifyAll())

# but there is only one glass
# producer cannot produce more for future

# safe data structures
# must be thread-safe

# e.g. Queue and it's variants -> threadSafe
# example -> slides

# Global Interpreter Lock (GIL

# task: go through files and directories and calculate MD5
# goal: find duplicate files

# browse: add files to file_queue
# analyze: in a few threads, takes file_queue outputs to result_queue
# report: separate thread, reads from result_queue
# 1:15 lecture -> code

# multiprocessing
# based on process, not threads
# p = multiprocessing.Process(target,args)
# JoinableQueue
# Pool (of processes)
# .Value -> exchange of information between processes
# synchronised communication -> Pipe

# concurrent.futures -> automatic decision between process and thread


# Remark: threads in Python can be not the same as POSIX threads (in CPython they are)
