import math
# python - kolekcje

# string, list, tuple, set, własne kolekcje

# " vs ' vs """

# old-style formatting
print("dwa plus dwa to %s czyli %i" % ('cztery', 4))

# new-style formatting
print("pi to {0:.2f}, a e to {1}".format(math.pi, math.e))

# f-string

print(f"2 razy e to {2 * math.e}")

# strings are immutable

# templates
from string import Template

template = Template("My name is $name")
print(template.substitute(name="Emin"))

# reverse and other processing
print("igła"[::-1])
print("informatyka"[::-2])
print("informatyka"[:1:-2])
print("informatyka"[-1:1:])
print("informatyka"[-1:1:-1])

# io.String streams

# raw strings
print(r"/r/r//r/n//n/dfdfer/n/t/t/n")

# strings as sequence of bytes
print(b"byte")
print(bytes([34, 56, 50, 40]))

# lists
# tuples
# in operator
print(len((1,)))
print(len((1, "")))

# iterables -> for in'able

# range generators

# enumerate -> (index, val)
# for a,b in zip(x, y)

# tuples are immutable
# lists are mutable
# del list[2:]
# list.pop(), list.append(), sort(), reverse(), extend(), insert(), remove(), index() itp.

# list.sort() vs sorted(list), reversed vs reverse etc.

# list are implemented as a vector of pointers
# access, add/delete at end -> amortized O(1)
# add/delete anywhere -> O(n)

# deque -> real O(1) at ends

