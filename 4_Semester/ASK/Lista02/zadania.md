---
tags: ASK
---

# ASK 2021 - Lista 2

## 1

**INT_MIN** = **-2147483648**
**INT_MAX** = **2147483647**
Zakładamy int32_t


### (x > 0) || ( x - 1 < 0)

Weźmy x = **$(100..00) _2$** = **INT_MIN**
wtedy x-1 = **$(01111..11)_2$** = **INT_MAX**
czyli mamy (INT_MIN > 0 ) || (INT_MAX < 0) 
a to daje 0 || 0 == 0


### (x & 7) != 7 || (x << 29 < 0) 

Obie strony muszą być fałszywe, ale jeśli lewa strona jest fałszywa to zapalone są bity 2, 1, 0 bo x = 7. 

Ale wtedy przesunięcie bitu 2 o 29 miejsc w lewo przesunie go na bit znaku więc prawa strona będzie == 1.


### (x * x) >= 0
Chcemy otrzymać $2^{31}$
* Weźmy $x = 2^{16} + 2^{14}$. Wtedy $x^2 = 2^{32} + 2 * 2^{16} * 2^{14} + 2^{28} = 2^{32} + 2^{31} + 2^{28} = (1 << 32) + (1 << 31) +  (1 << 28) = 0 + INT_{MIN} + 2^{28}$ < 0, ponieważ $2^{28} < INT_{MAX} < |INT_{MIN}|$
a $2^{32} = 0$ i $-2^{31} = INT_{MIN}$


### x < 0 || -x <=0 

jesli x < 0 to całość prawdziwa
jeśli x >= 0 to $x \in <0, 2147483647>$ czyli $-x \in <INT_{MIN} + 1, 0>$ zatem zawsze prawda


### x > 0 || -x >= 0

jeśli x > 0 działa
dla x <= 0:
jeśli x = $INT_{MIN}$ to
$-x = 2147483648 = INT_{MAX} + 1 = INT_{MIN}$ czyli mamy fałsz po prawej stronie


### (x | -x) >> 31 == -1
 
dla $x = 0$ mamy $-x = 0$ więc dostaniemy $0 | 0$ czyli $0$


### x + y == (uint32_t)y + (uint32_t)x

Zawsze działa, ponieważ unsigned jest zaraźliwy, więc zmienne na lewo zrzutują się przed wyliczeniem sumy na uint32_t.


### x * ~y + (uint32_t)y * (uint32_t)x == -x

~y możemy przedstawić jako (-y - 1)
wtedy otrzymujemy z tego (i zaraźliwości unsigned):
(uint32_t)$[x\cdot(-y-1)]$ + (uint32_t)$y\cdot$(uint32_t)$x == -x$
inaczej:
$-xy -x + x_{u}y_{u}$, ale:
$-xy + x_{u}y_{u} = 0$
Po lewej stronie zostaje -x a po prawej -x więc jest to zawsze prawda.

Mnożenie dwóch unsigned i dwóch signed a późniejsz cast na unsigned odbywa się tak samo.


## 2
![](https://i.imgur.com/idB6n6Z.png)

```c=
x = x ^ y;
y = x ^ y;
x = x ^ y;
```

y = (x xor y) xor y =
    x xor (y xor y) =
    x xor 0 = x

wtedy podobnie x = (x xor y) xor x = y

to wynika stąd, że
a xor b = b xor a
(a xor b) xor c = a xor (b xor c)
a xor a = 0 i a xor 0 = a


## 3

Nadmiar (ang. overflow) - przekroczenie dodatniego zakresu wartości, które może przyjąć zmienna, np. dla int32_t będzie to wyjście poza INT_MAX.

Niedomiar (ang. underflow) - analogicznie, tylko ujemengo zakresu

Nie mylić z niedomiarem dla zmiennopozycyjnych, który oznacza liczbę tak małą (bezwględnie), że nie da się jej zareprezentować.

Jeśli xy < 0 to nie może wystąpić nadmiar albo niedomiar przy x+y.

Jeśli x, y sa dodatnie a x+y < 0 to mamy nadmiar
lub x, y są ujemne a x+y > 0 to mamy niedomiar
(róznica na bitach znaku)


```cpp
does_overflow = (((x+y) ^ x) & ((x + y) ^ y)) >> 31
```
Sprawdzenie:
```
x | y | (x+y) |  LHS
0   0     0     0 & 0
0   0     1     1 & 1 = 1
0   1     0     0 & 1
0   1     1     1 & 0
1   0     0     1 & 0
1   0     1     0 & 1
1   1     0     1 & 1 = 1
1   1     1     0 & 0
```

## 5


$\lfloor x\cdot3/4 \rfloor

$x-x/4= \lceil 3\cdot x/4 \rceil$

Żeby otrzymać podłogę z dzielenia $3/4$ musimy od powyższego wzoru odjąć 1, jeśli reszta z tego dzielenia jest różna od 0.
Robimy to tak:
```c=
(x | x >> 1) & 1
```

Natomiast $x-x/4$ to po prostu:
```c=
x - (x >> 2)
```

Tak więc finalnie otrzymujemy, że $x \cdot 3/4$:
```c=
x - (x >> 2) - ((x | x >> 1) & 1)
```

## 6 TODO
x/2 - y/2 
```c= 
bool lessthan(T x, T y) // dla T == (uint32_t || int32_t)
{
    return (x >> 1) - (y >> 1) - (~x & y & 1) >> 31 & 1  ;
}
```

(~x & y & 1) - naprawia przypadek (parzysta - nieparzysta)

| ostatni bit x | ostatni bit y| Wynik | 
| :-----------: | :----------: | :---: | 
| $0$           | $0$          | $0$   | 
| $0$           | $1$          | $1$   | 
| $1$           | $0$          | $0$   | 
| $1$           | $1$          | $0$   |

Z uczty:
(x - y) ^ ((x ^ y) & (x - y) ^ x)
(x & ~y) | (~(x ^ y) & (x - y))
## 7
«b ? x : y»     => «x >= 0 ? x : -x»
«b * x + !b * y»  => «(x >= 0) * x + (x < 0) * (-x)»
fakt 1: -x = ~x + 1
fakt 2: x >> 31 to (11...11) dla x < 0 i (00...00) dla x >=0
((x >> 31) & x) | ((x >> 31) & (~x + 1)) - to nie działa nie zwraca abs i nie działa dla x >= 0

z uczty:
(x + (x >> 31)) ^ (x >> 31)
wykorzystanie masek - do opisania
## 8
```
(x >> 31) | ((-x >> 31) & 1)
```

```
x > 0 -> 0 | 1 -> 1
x = 0 -> 0 | 0 -> 0
x < 0 -> LHS uzupełnia się jedynkmi -> -1
```

```
np:
int_{MAX}=
```

## 9
Na L1 sprawdzaliśmy liczbę zapalonych bitów, teraz możemy to wykorzystać i sprawdzić czy ta liczba jest parzysta sprawdzając LSB.
```c=
#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t x;
    
    const uint32_t mask1  = 0x55555555; // 01010101010101010101010101010101
    const uint32_t mask2  = 0x33333333; // 00110011001100110011001100110011
    const uint32_t mask4  = 0x0f0f0f0f; // 00001111000011110000111100001111
    const uint32_t mask8  = 0x00ff00ff; // 00000000111111110000000011111111
    const uint32_t mask16 = 0x0000ffff; // 00000000000000001111111111111111

    x = 255;
    
    x = (x & mask1 ) + ((x >>  1) & mask1 );  // ile jest zapalonych bitów na 2 bitach
    x = (x & mask2 ) + ((x >>  2) & mask2 );  // ile jest zapalonych bitów na 4 bitach
    x = (x & mask4 ) + ((x >>  4) & mask4 ); 
    x = (x & mask8 ) + ((x >>  8) & mask8 ); 
    x = (x & mask16) + ((x >> 16) & mask16);  // ile jest zapalonych bitów  32 bitach
    printf("%d", x & 1);
}
```

z uczty:
```c=
    x = x ^ (x >> 1)
    x = x ^ (x >> 2)
    x = x ^ (x >> 4)
    x = x ^ (x >> 8)
    x = x ^ (x >> 16)
```