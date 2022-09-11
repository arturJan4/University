---
tags: ASK
---

# ASK - LISTA 4

## Zadanie 1
![](https://i.imgur.com/mTxsiTK.png)

operand źródłowy - obiekt na którym wykonywane jest działanie
składnia movq: movq Source, Destination - Source to źródło

1. **%rax**  = 0x100
2. **0x110** = 0x13 (nie stała, a adres!)
3. **$0x108** = 0x108
4. **(%rax)** = 0xFF
5. **8(%rax)** = (0x100 + 8) = 0xAB
6. **21(%rax, %rdx)** = (%rax + %rdx + 21) = (0x100 + 3 + 21) = (0x100 + 0x18) = 0x11
7. **0xFC(,%rcx,4)** = (4 * 1 + 0xFC) = (0x100) = 0xFF
8. **(%rax, %rdx, 8)** = (0x100 + 8 * 3) = (0x100 + 0x18) = 0x11
9. **265(%rcx, %rdx, 2)** = (1 + 2 * 3 + 265) = (272) = (0x110) = 0x13
## Zadanie 2
q - 8 bajtów
1.
**addq %rcx, (%rax)** - dodaje do Dest wartość Source
Destination: (0x100) - pamięć
Source: 1
Wynik: 0x100: 0xFF + 1 = 0x100

2.
**subq 16(%rax), (%rdx)** - odejmuje od Dest wartość Source
Destination: %rdx - rejestr
Source: (0x100 + 16) = (0x110) = (0x13)
Wynik: %rdx = 3 - 0x13 = 0x0000 0000 0000 0003 - 0x0000 0000 0000 0013 = -(0x10) =
0xFFFF FFFF FFFF FFF0

3.
**shrq $4, %rax** - logical (wypełnia zerami) shift right
Destination: %rax - rejestr
Source: 4
Wynik: 0x100 >> 4 = 0x010
0x100 >> 4
0b0001 0000 0000 >> 4
0b0000 0001 0000 
0x010

4.
**incq 16(%rax)** - zwiększa Dest o 1
Destination: (0x100 + 16) = (0x110) - pamięć
Wynik = 0x110: (0x110) + 1 = 0x13 + 1 = 0x14

5.
**decq %rcx** - zmniejsza Dest o 1
Destination: %rcx
Wynik = %rcx = %rcx - 1 = 1 - 1 = 0

6.
**imulq 8(%rax)**
x64_cheatsheet
Signed full multiply of %rax by Source
Result stored in %rdx:%rax (wynik na 16 bajtach)

Destination: %rdx:%rax
Source: 8(%rax) = (0x100 + 8) = 0xAB
Wynik: %rax * 0x1FF = 0x100 * 0xAB = 0xAB00
%rdx = 0 (8 bajtów górne)
%rax = 0xAB00 (8 dolne)

7.
**leaq 7(%rcx, %rcx, 8), %rdx** - load effective adress
Destination: %rdx - rejestr
Source: 1 + 8 * 1 + 7 = 16
Wynik: %rdx = 0x10

8.
**leaq 0xA(, %rdx, 4), %rdx** - load effective adress
Destination: %rdx - rejestr
Source: 4 * 3 + 10 = 22
Wynik: %rdx = 0x16

## Zadanie 3 TODO
to walnięte zadanie jakieś
co ono robi na liście z assembly

## Zadanie 4
![](https://i.imgur.com/6ztujUV.png)
x - %rdi
y - %rsi
wynik - %rax
long == quadword 

1. t1(rax) = x + y
2. t2(rdi) = t1 ^ x
3. t3(rsi) = t1 ^ y
4. t1 = t2
5. t1 = t1 & t3
6. t1 = t1 >> 63

rozwijamy idąc w górę
t2 & t3 >> 63
(t1^x & t1^y) >> 63
((x+y)^x & (x+y)^y) >> 63

```c=
    uint64_t decode(uint64_t x,uint64_t y)
    {
        return (((x+y)^x) & ((x+y)^y)) >> 63;
    }
```
## Zadanie 5
little endian -> big-endian (uint32_t)

Chcemy: aabbccdd -> ddccbbaa

ROR - przesuwa wszystkie (oprócz najmłodszego) w kierunku najmniej znaczączego bitu, a najmłodszy wstawia w miejsce MSB

ROR S, D
gdzie:
S - co przesuwamy
D - ile razy wykonujemy przesunięcie
np: aabbccdd -> (o 4) -> daabbccd

%edi - argument funkcji (32 bity - 4 bajty)
%rax - wynik

Podejście 1:
aabbccdd -> ROR 8 -> ddaabbcc -> maska -> dd00bb00
aabbccdd -> ROL 8 -> bbccddaa -> maska -> 00cc00aa
i robimy | (or) na obu czyli 2 przesunięcia cykliczne i 3 operacje logiczne

Pytanie:
- które lepsze?
- czy zawsze minimalizować rejestry
- czy ładować do małych rejestrów
- czy logiczne robić na mniejszych?
```
convert:
    movl %edi, %eax
    ror  $8, %eax,      // >> 8 (w obrębie bajtów 0-3, rax)
    movl %edi, %ecx
    rol  $8, %ecx       // << 8 (w obrębie bajtów 0-3, rcx)
    and  $0x00FF00FF, %rcx
    and  $0xFF00FF00, %rax 
    orq  %ecx, %eax    
    ret
```

Podejście 2:
Wykorzystujemy że można dostać się do niższych (2 lub 1) bajtów rejestru
dla %eax, %ax - dolne 2 bajty (%ah, %al - wyższy i niższy z nich)
Mamy 32 bity: 
%eax = aabbccdd
%ax = ccdd
%ah = cc
%al = dd
```
convert:
    movl %edi, %eax
    rol  $8, %ax     // aabbddcc    
    rol  $16, %eax   // ddccaabb
    rol  $8, %ax     // ddccbbaa
    ret
```

dla unsigned32_t to jest
ror: (x >> n) | (x << 32 - n)
rol: (x << n) | (x >> 32 - n)

## Zadanie 6
x (%rdi:%rsi), y (%rdx, %rcx) - 128 bit, ze znakiem
wynik: (%rdx:%rax)

ADC - add with carry (wykorzystuje flagę przeniesienia - CF)
czyli adc Src, Dest = Dest = Dest + Src + CF
x + y


```
64 64
A  B
C  D
CF
```
```
add: addq %rsi, %rcx    // może ustawić CF
     adc  %rdi, %rdx    // jeśli nie będzie overflow to po tej instrukcji CF = 0
     movq %rcx. %rax
     ret
```
## Zadanie 7 
x (%rdi:%rsi), y (%rdx, %rcx) - 128 bit, ze znakiem
wynik: (%rdx:%rax)

x * y bez znaku

OF i CF gdy pierwsza połowa to 0

mul S:
Unsigned full multiply of %rax by S
Result stored in %rdx:%rax

$n=n_{127....64} \cdot 2^{64} + n_{63...0}$
$n = xy$
i jak ze wskazówki
$x = x_{64} \cdot 2^{64} + x_{63...0} = x_{1} \cdot 2^{64} + x_{2}$
podobnie:
$y = y_{64} \cdot 2^{64} + y_{63...0} = y_{1} \cdot 2^{64} + y_{2}$ 
Wtedy
$n = xy = (x_{1} \cdot 2^{64} + x_{2})(y_{1} \cdot 2^{64} + y_{2})$
$n = (x_1y_1 * 2^{128}) + (x_2y_1 * 2^{64}) + (x_1y_2 * 2^{64}) +(x_2y_2)$
$n = S1 + S2 + S3 + S4$
$x_1=x_{127...64}$
$y_1=y_{127...64}$
$x_2=x_{63...0}$
$y_2=y_{63...0}$
S1 jest za duże na 128 bitów, więc odrzucamy
liczymy S2 + S3 i zapisujemy dolne 64 bity w %rdx
S4 i dodajemy do %rdx:%rax

pomocniczne rejestry: %r8 %r9
```
                  x1           x2
x:         |     %rdi    |    %rsi    |
y:         |     %rdx    |    %rcx    |
                  y1           y2
                  
wynik:     |     %rdx    |    %rax    |
```

```
mult:
1   movq %rdx, %rax   // najpierw używamy %rdx bo mul go używa
2   mul  %rsi         // x_2y_1 wynik na rdx:rax, tracimy %rdx
3   movq %rax, %r8    // dolne 64 bity x_2y_1 tymczasowo w r8
4   movq %rdi, %rax
5   mul  %rcx         // x_1y_2 wynik na rdx:rax
6   addq %rax, %r8    // w r%8 - suma
7   movq %rsi, %rax
8   mul  %rcx         // x_2y_2 wynik na rdx:rax
9   addq %r8, %rdx
10  ret
```

Chcemy na wyniku (_down - dolne 64 bity wyniku, _up - górne):
w %rdx = (x2y1)_down + (x1y2)_down + (x2y2)_up
w %rax = (x2y2)_down


| linia | %rdx                            | %rax      | %r8                   |
| ----- | ------------------------------- | --------- | --------------------- |
| 1     | y1                              | y1        | null                  |
| 2     | x2y1_up                         | x2y1_down | null                  |
| 3     | x2y1_up                         | x2y1_down | x2y1_down             |
| 4     | x2y1_up                         | x1        | x2y1_down             |
| 5     | x1y2_up                         | x1y2_down | x2y1_down             |
| 6     | x1y2_up                         | x1y2_down | x2y1_down + x1y2_down |
| 7     | x1y2_up                         | x2        | x2y1_down + x1y2_down |
| 8     | x2y2_up                         | x2y2_down | x2y1_down + x1y2_down |
| 9     | x2y2_up + x2y1_down + x1y2_down | x2y2_down | x2y1_down + x1y2_down |


## Zadanie 8
x - %rdi
y - %rsi
wynik - %rax

ULONG_MAX - same jedynki binarnie
uint64_t -> q

jae(CF=0) albo jb (CF=1)
ze skokiem:
```
addu:
            addq %rdi, %rsi
            jea success:                       // jump if CF = 0
            movq $0xFFFFFFFFFFFFFFFF, %rsi     // osiem bajtów (ULONG_MAX) do rsi
success:    movq %rsi, %rax
            ret
```

sbb - substraction with borrow (używa flagi CF)
destination = destination - (source + carry)

pomysł
wykonujemy dodawanie normalnie
jeśli mamy overflow to CF = 1:
    - wtedy "sbb x, x" da nam -1 
jeśli nie ma overflow to:
    - wtedy "sbb x, x" daje 0
robimy OR z wynikiem sbb (w x) a wynikiem sumy

bez skoku:
```
addu:
    add  %rdi, %rsi
    sbb  %rax, %rax
    orq  %rsi, %rax
    ret
```
## Zadanie 9 

x - %rdi
y - %rsi
wynik - %rax

uint64_t -> q

adc - add with carry (wykorzystuje flagę przeniesienia - CF)
czyli adc Src, Dest = Dest = Dest + Src + CF

sbb - substraction with borrow (używa flagi CF)
destination = destination - (source + carry)

neg - two complement of operand
The CF flag set to 0 if the source operand is 0; otherwise it is set to 1

```
cmp:
    sub  %rsi, %rdi     // ustawia CF dla x < y, == 0 dla x == y
    sbb  %rax, %rax     // -1 dla x < y, w.p.p 0
    neg  %rdi           // jeśli x == y to CF = 0, w.p.p. 1
    adc  %rax, %rax    
    ret
```
Mamy 3 przypadki:
1) x == y
subq -> CF = 0
sbb  -> %rax = 0
negq -> CF = 0
adcq -> %rax = (0 + 0 + 0) = 0

2) x < y
subq -> CF = 1
sbb  -> %rax = -1
negq -> CF = 1
adcq -> %rax = (-1 + -1 + 1) = -1

3) x > y
subq -> CF = 0
sbb  -> %rax = 0
negq -> CF = 1
adcq -> %rax = (0 + 0 + 1) = 1
