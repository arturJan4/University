# classes, objects, object model & exceptions


# class declaration
class Figura:
    """Test"""
    def __init__(self, x, y):  # dunder/magic methods
        self.x = x  # object field -> we can dynamically change how many fields there are
        self.y = y

    def info(self):
        print(self.x, self.y)

    def change(self, x, y):
        self.x = x
        self.y = y


o = Figura(1, -1)
o.info()


# inheritance
class Okrag(Figura):
    pi = 3.1414  # static field -> created during declaration
    """Okrag"""
    def __init__(self):
        self.x, self.y, self.r = 0, 0, 1

    def info(self):
        print(f"x = {self.x}, y = {self.y}, r = {self.r}")

    def przesun(self, dx, dy):
        self.x, self.y = self.x + dx, self.y + dy
        self.info()  # virtual methods -> need to use self. prefix


#   super().__init__ -> parent class constructor
# | Figura.__init__(2.0, 3.0)
# super(self._class__, self).__init__()

# multiple inheritance
class Car:
    def forward(self):
        print("car")


class Boat:
    def forward(self):
        print("boat")


class Amphibian(Car, Boat):
    def __init__(self):
        return


amf = Amphibian()
amf.forward()

# how to resolve -> MRO (method resolution order)
# left to right subtree search (DFS)

# super(Boat, self).forward() -> forcing boat method

# operators
# is | is not
# if x is None:
# if x is not None

# is is implemented using id() function
# id() -> object adress as unique identifier (in CPython)

# isinstance(None, NoneType)
# None is only object of NoneType class
# isinstance returns True if object is of given class or a subclass

# creating new fields on the fly
amf.new_field = "I am very dynamic"
amf.foo = lambda x: x * x

# deleting fields
del amf.foo

# "private" variables
# double '_' prefix, and [0-1] '_' suffix
# (this is pseudo-private) -> mangling


# static methods and class methods (decorators)
class Class_test:
    @staticmethod
    def add(a, b):
        return a + b

    @classmethod
    def create(cls):
        return cls()

# they can be called by another classes/methods
# classmethod has additional argument for class of given method
# used for example to call constructors and return object

# Control Flow
# exceptions are objects (of course they are!)

try:
    f = open("x.txt", 'w')
    f = open("plik"[10] + '.py', 'r')
except IOError:
    print("io err")
except IndexError as x:
    print(x)
except:                         # don't use bare except
    print("another err")
finally:
    f.close()

# raise RuntimeError("Something went terribly wrong")

class myexc(Exception):
    pass

try:
    raise myexc("cont")
except:
    print("passed")

# `__class__`
# `__base__` & `__bases__`
x = 5
print(x.__class__)
print(x.__class__.__bases__)

# vector class definition example
# we want operations and str/len methods

class Vector:
    def __init__(self, list_v):
        self.value = list_v

    def __add__(self, arg):  # mul/sub/div/mod
        res = Vector([x + y for x, y in zip(self.value, arg.value)])
        return res

    def __str__(self):
        return '<' + ', '.join(str(x) for x in self.value) + '>'

    def __getitem__(self, index):  # [] operator
        return self.value[index]

    def __setitem__(self, index, value):
        self.value[index] = value


v1 = Vector([0, 2, 5])
v2 = Vector([2, 5, 3])
v3 = v1 + v2
print(v3)
print(v3[1])

for x in v3:
    print(x, end=', ')

print()
# we can also add del/len etc.
# __eq__ -> check object's attributes (using dict of attr.?)
# -> == -> True
# -> is -> False (check memory)

# we can check object state
# .__clas__
# .__doc__
# .__dict__
# .__file
# __name__

# dir() -> returns possible names

if "__str__" in dir(object):
    print("str is here")


# universal object -> has all fields, implements all methods
class Universal(object):
    def __getattr__(self, item):
        print("You are accessing attribute: ", item)

    def __setattr__(self, key, value):
        print(f"setting {key} to {value}")

    def __call__(self, *args, **kwargs):
        print("called", args)

# useful for dynamic objects (for example downloading webpage)

