---
tags: ASK
---

# ASK - LISTA 3

## Zadanie 1
https://stackoverflow.com/questions/36039509/why-does-the-0x55555556-divide-by-3-hack-work
![](https://i.imgur.com/i11ZEs0.png)
```
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>

// divides by 3, round to zero
int32_t div3(int32_t n)
{
    int64_t temp = n;
    int64_t magic = 0x55555556; // (2^32 + 2)/3

    int64_t part1 = temp * magic;
    printf("part1: %ld\n", part1);    
    
    return (int32_t)((part1 >> 32) + ((n >> 31) & 0x1));
    //return (int32_t)(((temp * magic) >> 32) + ((n >> 31) & 0x1)); 
}


int32_t div3_wrong(int32_t n)
{
    int64_t temp = n;
    int64_t magic = 0x55555555; // (2^3)/3

    int64_t part1 = temp * magic;
    printf("part1: %ld\n", part1);
    return (int32_t)((part1 >> 32) + ((n >> 31) & 0x1));
    //return (int32_t)(((temp * magic) >> 32) + ((n >> 31) & 0x1)); 
}

int main() {
    int counter = 0;
    double div = 3.0;
    /*    
    for (int x = INT32_MIN; ; x++) {
        int32_t result = (int32_t)(x/div);
        if(result != div3(x))
        {
            counter++;
        }
        if (x == INT32_MAX) break;
    }
    
    printf("%d", counter);
    */

    //int32_t x = 5;
    //printf("%d", div3(x));
    int32_t number = 3;
    printf("%d\n", div3(number));
    printf("%d\n", div3_wrong(number));
    return 0;
}

```
Chcemy wykonać mnożenie przez odwrotność dzielnika $d$, w przybliżeniu $2^{32} / d$ oraz poźniej wyodrębnić 32 bity od lewej strony iloczynu.

Bierzemy **magiczną** liczbę:
$int32_t \ m = 0x55555556$, czyli inaczej $0x100000000 / 3$ zaokrąglone w górę.
A dokładniej jest to $(2^{32} + 2)/3$

Następnie mnożymy ją razy $n$ podane jako argument funkcji $div3$ oraz dzielimy przez $2^{32}$:
$int64_t \ q = (m * n) >> 32$

Do finalnego wyniku chcemy dodać 1 tylko wtedy, jeśli $n<0$.

$n$ może mieć maksymalną wartość $2^{31} - 1$, ponieważ jest na 32 bitach.

```c=
int32_t div3(int32_t n)
{
    int64_t temp = n;
    int64_t magic = 0x55555556; // (2^32 + 2)/3
    return (int32_t)(((temp * magic) >> 32) + ((n >> 31) & 0x1)); 
}
```

**Dowód:**
1. Przypadek $n>=0$
    
    $q = (m * n) >> 32$, czyli inaczej $q = \lfloor(m * n)/2^{32}\rfloor$
    $m = (2^{32} + 2)/3$
    
    Więc $q = \lfloor \frac{(((2^{32} + 2)/3) * n)}{2^{32}} \rfloor$
    
    Czyli $q = \lfloor \frac{(2^{32} * n + 2 * n)}{(3 * 2^{32})} \rfloor$
    $= \lfloor n/3 + (2 * n)/(3 * 2^{32}) \rfloor$
    
    Jako, że $n < 2^31$, to reszta stanie się zerem.
    
2. Przypadek $n<0$

    $q = ((m * n) >> 32) + 1$, czyli inaczej $q = (m * n)/2^{32} + 1$
    $m = (2^{32} + 2)/3$
    
    Więc $q = \lfloor \frac{(((2^{32} + 2)/3) * n)}{2^{32}} + 1 \rfloor$
    
    Czyli $q = \lfloor \frac{(2^{32} * n + 2 * n + 3 * 2^{32})}{(3 * 2^{32})} \rfloor$
    
    Potrzebujemy skorzystać ze wzoru $\lceil n/d \rceil = \lfloor (n + d - 1)/d \rfloor$
    
    Dzięki temu otrzymujemy:
    $q = \lceil \frac{(2^{32} * n + 2 * n + 1)}{(3 * 2^{32})} \rceil$
    $= \lceil n/3 + (2 * n + 1)/(3 * 2^{32}) \rceil$
    
    Jako, że $n >= -2^{31}$, to reszta nie zmieni wyniku, ponieważ osiągnie maksymalną wartość w przybliżeniu równą $1/3$.
    
## Zadanie 2

### Obliczenie

Przedstawmy liczbę $0.15625$ za pomocą **half-precision floating-point**.

Liczby w tej precyzji są zapisane w postaci:
1 bit znaku, 5 bitów cechy, 10 bitów mantysy

Najpiew obliczamy $0.15625$ jako **fixed-precision:**
$0.00101$, inaczej $1/2^{3} + 1/2^{5}$

Następnie przesuwamy ją o 3 miejsca w lewo, czyli mnożymy przez $2^3$.
Otrzymujemy wtedy $1.01$

$BIAS$ dla tej precyzji jest równy 15, więc odejmujemy: $15 - 3 = 12$.

bit znaku $s = 0$
bity cechy $exp = 12_{10} = 01100_2$
bity mantysy = $0100000000_2$

**Wynik:** $(0 \ 01100 \ 0100000000_2)$


### Porównanie precyzji

#### **1. Zakres liczbowy**

**Single-precision:** $[-3.4 * 10^{38}, 3.4 * 10^{38}]$
**Half-precision:** $[-65504, 65504]$

#### **2. Dokładność**

**Single-precision:** $log_{10}(2^{24})$
**Half-precision:** $log_{10}(2^{11})$


## Zadanie 2 - wersja 2

### IEEE 754-2008 - reprezentacja liczb 16 bitowych,

* s - bit znaku: 1 jeśli ujemna 0 w.p.p
* exp - 5 bitów na wykładnik
* frac - 10 bitow na mantyse

Liczba to $(-1)^s * M * 2^E$ gdzie $E$ to exp - BIAS

Wartość BIAS to $2^5 -1 = 15$

### Konwersja 0.15625 do postaci binarnej
zauważmy że 0.15625 to inaczej $\frac{5}{32}$ czyli $\frac{1}{8} + \frac{1}{32}$ zatem $0.15625_{10} = 0.00101_2$

Czyli $0.15625_{10} = 1.01_{2} * 2^{-3}$

### konwersja do Half-precision floating-point format

* s = 0
* exp = e + BIAS = $(-3 + 15)_{10} =12_{10}= 01100_{2}$
* frac = $0100000000_{2}$

Czyli liczba to $0$ $01100$ $0100000000_{2}$

### porównanie Half-precision i Single precision

#### Half-precision:

* zakres: [-65504,65504]
* najmniejsza liczba co do modułu $0$ $00001$ $0000000000_{2}$ = $2^{-14}$

#### Single precision:

* zakres: [$-3.40*10^{38}$,$3.40*10^{38}$]
* najmniejsza liczba co do modułu $0$ $00001$ $0000000000_{2}$ = $2^{-126}$


## Zadanie 3

Musimy obliczyć $3.984375 * 10^{-1} + 3.4375 * 10^{-1} + 1.771 * 10^3$.

Najpierw zmieńmy te liczby na reprezentację **half-precision**.

$3.984375 * 10^{-1} = 0.0110011_2 = 1.10011_2 * 2^{-2}$
$3.4375 * 10^{-1} = 0.01011_2 = 1.011_2 * 2^{-2}$
$1.771 * 10^3 = 11011101011_2 = 1.1011101011_2 * 2^{10}$

Obliczamy sumę w pierwszej kolejności:
$1.10011_2 * 2^{-2} + 1.011_2 * 2^{-2} + 1.1011101011_2 * 2^{10}$
Pierwsza suma $= 10.11111_2 * 2^{-2}$
$10.11111_2 * 2^{-2} + 1.1011101011_2 * 2^{10} =$
$= (0.00000000001011111_2 + 1.1011101011_2) * 2^{10} =$
$= 1.10111010111011111_2 * 2^{10} = 1.10111011_2 * 2^{10} =$ (po zaokrągleniu)
$= 1772_{10}$

Teraz obliczamy sumę w drugiej kolejności:
$1.011 * 2^{-2} + 1.1011101011_2 * 2^{10} + 1.10011_2 * 2^{-2} =$
$= (0.000000000001011_2 + 1.1011101011_2) * 2^{10} + 1.10011_2 * 2^{-2} =$
Pierwsza suma $= 1.101110101101011_2 * 2^{10} =$ (po zaokrągleniu)
$= 1.1011101011_2 * 2^{10}$
$1.10111011_2 * 2^{10} + 1.10011 * 2^{-2} =$
$= 1.1011101011_2 * 2^{10} + 0.00000000000110011_2 * 2^{10} =$
$= 1.10111010110110011_2 * 2^{10} =$ (po zaokrągleniu)
$= 1.1011101011_2 * 2^{10} = 1771_{10}$

```
1.1011101011 1 011111=
1.1011101011 1 011111 
           G R SSSSSS
```

Jak widać wyniki się różnią. Jest to spowodane tym, że sumując dwie liczby musimy zaokrąglić je tak, by otrzymać w danym momencie liczbę mieszcącą się na danej liczbie bitów.

Guard bit - Najmniej znaczący bit mantysy, który mieści się w rozmiarze mantysy. Od tego bitu zaczynamy zaokrąglanie.
Round bit - Najbardziej znaczący bit taki, który nie mieści się w rozmiarze mantysy, zostanie on usunięty jak i mniej znaczące od niego bity.
Sticky bit - Reszta bitów mniej znacząca od Round bit'a. ($OR$ na nich)

## Zadanie 4

![](https://i.imgur.com/8SP8Hnz.png)


1. $(float)x == (float)dx$

    Powinno zwrócić zawsze **prawdę**, ponieważ wartości te będą zawsze mniejsze/równe niż $|INT_{MIN}|$, a $|INT_{MIN}| < |FLT_{MIN}| < |DBL_{MIN}|$
    
    Odpowiedź może nie być jednoznaczna bo nie zawsze konwersja z int na double jest bezstratna

2. $dx - dy == (double)(x - y)$

    **Kontrprzykład:** 
    $x = INT_{MIN}$ oraz $y = 1$
    Wtedy prawa strona nam się najpierw przekręci i zwróci wynik dodatni,
    a lewa strona obliczy się poprawnie, ponieważ możemy tam przechowywać większe wartości.
    
3. $(dx + dy) + dz == dx + (dy + dz)$

    Zawsze **prawda**, ponieważ nawet jeśli dodamy do siebie same $INT_{MAX}$ to i tak wynik obliczy się poprawnie, ponieważ ich suma będzie dalej mniejsza od $DBL_{MAX}$, dla odejmowania analogicznie.
    
    
4. $(dx * dy) * dz == dx * (dy * dz)$

    Dla gcc zawsze zwraca **prawdę**, dla innych kompilatorów niekoniecznie przy bardzo dużych wartościach $x, y, z$.
    
5. $dx / dx == dz/dz$

    **Kontrprzykład:**
    $x = 0$ oraz dowolne $z \neq 0$, np $z = 1$
    Po lewej stronie otrzymamy wtedy losową liczbę, a po prawej 1.

## Zadanie 5
![](https://i.imgur.com/cxRfF64.png)


1) x = x ^ (1 << 31)
2) ((x >> 23) & $11111111_2$) -$127_{10}$ - korzystamy z EXP
3) (x==y) | (x == 0 & (y == (1 << 31))) | (y == 0 & (x == (1 << 31))) - sprawdzamy 3 możliwości:
    1) x==y
    2) x==+0  & y==-0
    3) x==-0 & y==+0 
4) Chcielibyśmy sprawdzać bity w następującej kolejności -> bit znaku -> bity cechy -> bity mantysy. Szczęśliwie dla nas one są w takiej kolejności ułozone w x,y. Rozpatrzmy przypadki:
    1) x ujemne, y dodatnie - od razu zwracamy 1
    2) obie dodatnie -> robimy x-y: jeśli bit znaku = 1 to zwracamy 1, w.p.p. 0
    3) obie ujemne -> robimy x-y: jeśli bit znaku = 1 to zwracamy 1, w.p.p. 0
    4) sprawdzamy 0  


najprościej:
```cpp   
return ((x >> 31) == 1 & (y >> 31) == 0 & (x != (1 << 31) & y!= 0)) 
        | ((((x-y) >> 31) == 1) & ( (x >> 31) == 0 & (y >> 31) == 0))
        | ((((x-y) >> 31) == 1) & ( (x >> 31) == 1 & (y >> 31) == 1));
```
krócej:
```cpp    
return ((x >> 31) == 1 & (y >> 31) == 0 & (x != (1 << 31) & y!= 0)) 
        | ((((x-y) >> 31) == 1) & ( (x >> 31) == (y >> 31)));
```

```cpp    
return ((x >> 31) & !(y >> 31) & (x != (1 << 31)) & (y != 0)) 
        | (((x-y) >> 31) & ((x >> 31) == (y >> 31)));

```


## Zadanie 6
Mamy wzór:
$(-1)^S * M * 2^{E + i}$

Najpierw musimy obliczyć sumę $i$ + $exp$
```cpp=
E = ((x & 0x7F800000) >> 23); // otrzymujemy cechę
E = E - 127; // odejmujemy BIAS
E = E + i; // dodajemy potęgę i, przez którą chcemy wymnożyć liczbę
```

Następnie sprawdzamy kilka możliwości:

1) $E$ jest za duże. Wtedy zwracam nieskończoność +- $INF$.

```cpp=
if (E > 127)
    return x | 0x7F800000;
```

2) Wynik jest zdenormalizowany
$0 \  00000000 \  00000000000000000000001 = 2 ^ {-150}$
Czyli exp = 0 i M = 0.{frac}
Przesuwamy mantysę o $-(E + 127) + 1$ i tracimy potencjalnie bity.
```cpp=
if (-150 <= E && E <= -127)
    return (x & 0x80000000) + (((x & 0x007fffff) | 0x0080000) >> -(E + 126));
```
3) $E$ jest zbyt małe (+-0)

```cpp=
if (E <= -150)
    return x & 0x80000000;
```

4) Inaczej wynik jest jest znormalizowany

```cpp=
x = (x & 807FFFFF) + ((E + 127) << 23);
```