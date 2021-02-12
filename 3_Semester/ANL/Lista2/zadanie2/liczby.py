import itertools
lst = list(itertools.product([0, 1], repeat=3))

values = []
e2 = 1.0/4
e3 = 1.0/8
e4 = 1.0/16

values = []

for i in range(8):
    number = 1/2
    if(lst[i][2] == 1):
        number += e4
    if(lst[i][1] == 1):
        number += e3
    if(lst[i][0] == 1):
        number += e2
    values.append(number)

newlist = values.copy()
for i in values:
    newlist.append(i * 2)
    newlist.append(i/2)

listfinal = newlist.copy()
for i in newlist:
    listfinal.append(-i)

for i in listfinal:
    print(i, 0)