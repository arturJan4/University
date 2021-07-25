64 bity -> odwrócić
przykład na 8 bitach
divide and conquer

abcdefgh
-> efgh abcd (maska: 0xF0, 0x0F)
-> gh ef cd ab (0xCC, 0x33)
-> h g f e d c b a (0xaa, 0x55)

ale mamy 64 bity 0xFFFFFFFFFFFFFFFF
czyli po 32 bity -> 16 -> 8 -> 4 -> 2 -> 1

and przyjmuje 32 bity stałą

Czyli jakie operacje?
Mamy x
x = (x & maskaL) >> step | (x & maskaR) << step

«» - logical shift

załaduj maskęL
y = x & maskaL
y = (x & maskaL) >> step
maskaL >> step
x = x & maskaR
x = x << step
x = x | y

Czyli jakie maski
step        maskaL                  maskaR = maskaL >> step
32          0xFFFFFFFF00000000      0x00000000FFFFFFFF
16          0xFFFF0000FFFF0000      0x0000FFFF0000FFFF
8           0xFF00FF00FF00FF00      0x00FF00FF00FF00FF
4           0xF0F0F0F0F0F0F0F0      0x0F0F0F0F0F0F0F0F
2           0xCCCCCCCCCCCCCCCC      0x3333333333333333
1           0xAAAAAAAAAAAAAAAA      0x5555555555555555
