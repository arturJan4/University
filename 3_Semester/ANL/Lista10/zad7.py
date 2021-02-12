import numpy as np
import matplotlib.pyplot as plt

t = [0,   2,   4,   6,   8,  10]
H = [1, 1.6, 1.4, 0.6, 0.2, 0.8]
k = 5  # 0 .. 5

sumi = 6
sumCosSin = 0
for i in range(k+1):
    arg = (2.0 * np.pi * t[i])/12
    sumCosSin += np.sin(arg) * np.cos(arg)

sumH = 0
for i in range(k+1):
    sumH += H[i]

sumSin = 0
for i in range(k+1):
    arg = (2.0 * np.pi * t[i])/12
    sumSin += np.sin(arg)

sumCos = 0
for i in range(k+1):
    arg = (2.0 * np.pi * t[i])/12
    sumCos += np.cos(arg)

sumCosH = 0
for i in range(k+1):
    arg = (2.0 * np.pi * t[i])/12
    sumCosH += np.cos(arg) * H[i]

sumSinH = 0
for i in range(k+1):
    arg = (2.0 * np.pi * t[i])/12
    sumSinH += np.sin(arg) * H[i]

sumSinSin = 0
for i in range(k+1):
    arg = (2.0 * np.pi * t[i])/12
    sumSinSin += np.sin(arg) * np.sin(arg)

sumCosCos = 0
for i in range(k+1):
    arg = (2.0 * np.pi * t[i])/12
    sumCosCos += np.cos(arg) * np.cos(arg)

# Ax = b
a = np.array([[sumi, sumSin, sumCos], [sumSin, sumSinSin, sumCosSin], [sumCos, sumCosSin, sumCosCos]])
b = np.array([sumH, sumSinH, sumCosH])
x = np.linalg.solve(a, b)
print(x)  # ho a1 a2

h = x[0]
a1 = x[1]
a2 = x[2]


# spr
def func(t, h, a1, a2):
    arg = (2.0 * np.pi * t)/ 12
    return h + a1 * np.sin(arg) + a2 * np.cos(arg)


wynik = [func(i, h, a1, a2) for i in t]
print(wynik)

pointsx = np.linspace(0, 10, 1000)
pointsy = [func(i, h, a1, a2) for i in pointsx]

plt.plot(pointsx, pointsy)
plt.plot(t, H, 'bo')
plt.show()