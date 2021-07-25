---
tags: ASK
---

# ASK 2021 - Lista 0
## 1

$$ 42_{8} = 4 \times 8^1 + 2 \times 8^0= 34_{10} $$

$4_{8} = (100)_{2}$ i $2_{8} = (010)_{2}$ więc
$42_{8}= (100|010)_{2}$
grupujemy w czwórki:
$(0010)_{2} = 2_{16}$ i $(0010)_{2} = 2_{16}$ 
więc:
$42_{8} = 22_{16}$

$$ 255_{8} = 2 \times 8^2 + 5 \times 8 + 5 = 173_{10} $$

$255_{8} = (010|101|101)_{2}$
grupujemy w czwórki:
$(1010)_{2} = A_{16}$ i $(1101)_{2} = D_{16}$ 
więc:
$255_{8} = AD_{16}$

$$ 3047_{8} = 3 \times 8^3 + 4 \times 8 + 7 = 1536 + 32 + 7 = 1575_{10} $$

$3047_{8} = (011|000|100|111)_{2}$
grupujemy w czwórki:
$(0110|0010|0111)_{2} = 627_{16}$ 
więc:
$3047_{8} = 627_{16}$

$$ 140336_{8} = 1 \times 8^5 + 4 \times 8^4 + 3 \times 8^2 + 3 \times 8 + 6 = 49374_{10} $$

$140336_{8} = (001|100|000|011|011|110)_{2}$
grupujemy w czwórki:
$(00|1100|0000|1101|1110)_{2} = C0DE_{16}$ 
więc:
$140336_{8} = C0DE_{16}$

## 2
![](https://i.imgur.com/D6jS8sR.png)

```
   2 2
+    8 
------
   2 A

   7 3
+  2 C 
------
   9 F
   
  +1
   7 F
+  7 F 
------
   F E

  
   C 2
+  A 4 
------
 1 6 6
```


## 3
```c=
#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t x;
    uint32_t k;

    x = 19;
    k = 1;

    // x=10011
    // k=00010

    // 1 << k
    // 000..010..000
    //       k 
    
    // wyzeruj k-ty
    printf("%d\n", x & ~(1 << k));

    // ustal k-ty
    printf("%d\n", x | ( 1 << k));

    // zaneguj k-ty
    printf("%d\n", x ^ (1 << k));
    
    return 0;
}
```

## 4
```c=
#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t x;
    uint32_t y;

    x = 29;
    y = 3;

    // x * (2^y) = 232
    // 29 = 0000 0000 0001 1101
    printf("%d\n", x << y);

    // floor(x/2^y) = 3
    // obcięcie całkowite
    printf("%d\n", x >> y);

    // x mod 2^y = 5 (24 + 5)
    printf("%d\n", x & ((1 << y) - 1));
    // 29    = 0000 0000 0001 1101
    // 2^y   = 0000 0000 0000 1000
    // 2^y-1 = 0000 0000 0000 0111
    // 5     = 0000 0000 0000 0101
    
    // ceil(x/2^y) = 4
    printf("%d\n", (x + (1 << y) - 1) >> y);
    // 29    = 0000 0000 0001 1101
    // 2^y   = 0000 0000 0000 1000
    // 2^y-1 = 0000 0000 0000 0111
    // 5     = 0000 0000 0000 0101
    
    return 0;
}
```
## 5
```c=
#include <stdio.h>
#include <stdint.h>

int main (int argc, char *argv[]) {
    uint32_t x;

    x = 3;

    // x dla 0
    // x & (x - 1) == 0 tylko dla x = 2^y
    printf("%d\n", x && !(x & (x - 1))); // zwraca 1 gdy x jest potęgą 2

    // np: 8
    // x    = 1000
    // x-1  = 0111
    // np: 9
    // x    = 1011
    // x-1  = 1000
    // & na MSB

    return 0;
}
```
## 6
```c=
#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t x; // little-endian (32b = 4B)
    uint32_t byte0, byte1, byte2, byte3; // podzielone na 4 bajty

    x = 0x456789ab;
    printf("%x\n", x);

    byte3 = x << 24;
    byte2 = (x & 0x0000ff00) << 8;
    byte1 = (x & 0x00ff0000) >> 8;
    byte0 = x >> 24;
    x = (byte3 | byte2 | byte1 | byte0); // big-endian

    printf("%x\n", x);
}
```
## 7
0 - NUL - Null character
4 - EOT - End of Transmission (ctrl+D)
7 - BEL - Bell character
10 - LF - Newline
12  - FF - Form feed - page break, nowa strona

Standard ASCII przeznacza pierwsze 32 kody (0–31) na znaki sterujące. Nie są one przeznaczone do przenoszenia drukowalnych symboli, lecz do sterowania urządzeniem odbierającym dane.

## 8
https://unicode-table.com/
ASCII:
7 bitów na znak (0-127)
a np. Japoński potrzebuje parę tysięcy

UTF-8 używa 1 do 4 bajtów, backward-compatibility do ASCII (czyli jeśli znak jest w tabeli ASCII to w UTF-8 jest taki sam)

0xxxxxxx - ASCII
110xxxxx 10xxxxxx 
1110xxxx 10xxxxxx 10xxxxxx 
11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

np: 
P = U + 0050 ($50_{16}$)

€ = U+ $20AC_{16}$ (Unicode code point)
$$0010 \; 0000 \; 1010 \; 1100_{2}$$

$$0010 \; 000010 \; 101100_{2}$$

$$ 1110xxxx  \; 10xxxxxx \; 10xxxxxx $$ 
$$11100010 \; 10000010 \; 10101100 $$

$$E2 \; 82 \; AC$$

ę = U+0119

$$ 0000 \; 0001 \; 0001 \; 1001 $$
$$ 0000 \; 000100 \; 011001 $$
$$ 11000100 \; 10011001 $$
$$ C4 \; 99$$
ę = $C499_{16}$

ł = U + $0124_{16}$

$$0000 \; 0001 \; 0100 \; 0010$$
$$0000 \; 000101 \; 000010$$
$$11000101 \; 10000010$$
$$C5 \; 82$$
ł = $C582_{16}$

ć = U+0107
$$ 0000 \; 0001 \; 0000 \; 0111 $$
$$ 0000 \; 000100 \; 000111$$
$$ 11000100 \; 10000111 $$
$$ C4 \; 87$$
ć = $C487_{16}$

Proszę zapłacić 5€! =
```
50726f737ac499207a6170c582616369c4872035e282ac20
P r o s z ę   _ z a p ł   a c i ć   _ 5 €     !
```