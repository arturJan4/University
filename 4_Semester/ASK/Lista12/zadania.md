---
tags: ASK
---
# ASK - LISTA 12


## 1
```c=
void swap(long *xp, long *yp) {
    *xp = *xp + *yp; /* x+y */
    *yp = *xp - *yp; /* x+y-y = x */
    *xp = *xp - *yp; /* x+y-x = y */
}
```
Swap skompilowany z `-O2`
```c=
swap:                                   # @swap
        movq    (%rsi), %rax
        addq    (%rdi), %rax
        movq    %rax, (%rdi)
        subq    (%rsi), %rax
        movq    %rax, (%rsi)
        subq    %rax, (%rdi)
        retq
```
```c=
void swap2(long *xp, long *yp) {
    long x = *xp, y = *yp;
    x = x + y, y = x - y, x = x - y;
    *xp = x, *yp = y;
}
```
Swap2 skompilowany z `-O2`
```c=
swap2:                                  # @swap2
        movq    (%rdi), %rax
        movq    (%rsi), %rcx
        movq    %rcx, (%rdi)
        movq    %rax, (%rsi)
        retq
```

**Memory aliasing** - sytuacja w której więcej niż jeden symbol odwołuje się do tej samej pamięci. Zmiana tej pamięci przy pomocy jednego symbolu powoduje zmianę w innych.

**Czemu nie może zoptymalizować swap?**
Kompilator nie wie czy `*xp` i `*yp` wskazują na różne zmienne, a wtedy wykonanie wygląda tak:
```c=
void swap(long *xp, long *yp) { /* x == y         */
    *xp = *xp + *yp; /* xp = 2x, yp = 2x (x+x)    */
    *yp = *xp - *yp; /* xp = 0, yp = 0   (2x - 2x)*/
    *xp = *xp - *yp; /* xp = 0, yp = 0  (0 - 0)   */
}
```
**restrict** keyword - wskazuje kompilatorowi że dany wskaźnik do pamięci jest jedynym, który wskazuje na ten konkretny obiekty.

```c=
void swapOpt(long * restrict xp, long * restrict yp) {
    *xp = *xp + *yp; /* x+y */
    *yp = *xp - *yp; /* x+y-y = x */
    *xp = *xp - *yp; /* x+y-x = y */
}
```
Kod z restrict po skompilowaniu z `-O2`
```
swapOpt:
        movq    (%rsi), %rax
        movq    (%rdi), %rdx
        movq    %rax, (%rdi)
        movq    %rdx, (%rsi)
        ret
```

## 2
```c=
#include<stdio.h>
__attribute__((noinline))
size_t my_strlen(const char *s) {
    size_t i = 0;
    while (*s++)
        i++;
    return i;
}

const char *my_index(const char *s, char v) {
    for (size_t i = 0; i < my_strlen(s); i++)
        if (s[i] == v)
            return &s[i];
    return 0;
}
```

**z atrybutem noinline**
```c=
my_strlen:
        xorl    %eax, %eax
        cmpb    $0, (%rdi)
        je      .L4
.L3:
        addq    $1, %rax
        cmpb    $0, (%rdi,%rax)
        jne     .L3
        ret
.L4:
        ret
my_index:
        xorl    %edx, %edx
        jmp     .L8
.L10:
        leaq    (%rdi,%rdx), %rax
        cmpb    %sil, (%rdi,%rdx)
        je      .L7
        addq    $1, %rdx
.L8:
        call    my_strlen        // wołamy strlen
        cmpq    %rdx, %rax
        ja      .L10
        xorl    %eax, %eax
.L7:
        ret
```
Jak widać w każdym obrocie wołamy funkcję strlen
**z inliningiem**
```c=
my_strlen:
        xorl    %eax, %eax
        cmpb    $0, (%rdi)
        je      .L4
.L3:
        addq    $1, %rax
        cmpb    $0, (%rdi,%rax)
        jne     .L3
        ret
.L4:
        ret
my_index:
        movzbl  (%rdi), %ecx
        xorl    %edx, %edx
        xorl    %eax, %eax
        testb   %cl, %cl
        je      .L7
.L10:
        addq    $1, %rax
        cmpb    $0, (%rdi,%rax)
        jne     .L10
        cmpq    %rax, %rdx
        jnb     .L14
        leaq    (%rdi,%rdx), %rax
        cmpb    %sil, (%rdi,%rdx)
        je      .L7
        addq    $1, %rdx
        xorl    %eax, %eax
        testb   %cl, %cl
        jne     .L10
.L7:
        ret
.L14:
        xorl    %eax, %eax
        ret
```
https://en.wikipedia.org/wiki/Inline_expansion
**Inlining** - wklejenie ciała procedury w miejsce wywołania
Funkcja `my_strlen` została wklejona w ciało `my_index` i połączona (te same instrukcje dla tych samych i z `my_index` i `my_strlen`). W każdym obrocie "skaczemy" pomiędzy instrukcjami obu funkcji, ale całość ich ciała wykona się tylko raz.

**pure**
```c=
my_strlen:
        xorl    %eax, %eax
        cmpb    $0, (%rdi)
        je      .L4
.L3:
        addq    $1, %rax
        cmpb    $0, (%rdi,%rax)
        jne     .L3
        ret
.L4:
        ret
my_index:
        call    my_strlen            // call
        addq    %rdi, %rax
        jmp     .L8
.L10:
        movq    %rdi, %r8
        addq    $1, %rdi
        cmpb    %sil, -1(%rdi)
        je      .L7
.L8:
        cmpq    %rax, %rdi
        jne     .L10
        xorl    %r8d, %r8d
.L7:
        movq    %r8, %rax
        ret
```
Funkcja my_strlen zostaje jednokrotnie zawołana, a jej wynik zapisany do dalszego użycia.
https://en.wikipedia.org/wiki/Pure_function
__attribute__((pure))
**czysta funkcje** - 
Funkcja, która zawsze zwraca takie same wartości dla takich samych argumentów (czyli nie wykorzystuje zmiennych statycznych, wejścia, innych wejść). 
Wykonanie takiej funkcji nie ma żadnych efektów ubocznych (zmian w przekazanych argumentach, zapisów do pamięci itp.). 
Kompilator może założyć, że kolejne wywołania takiej funkcji z tymi samymi argumentami nie zmienią zwracanej wartości, więc wystarczy wywołać funkcję tylko raz.

## 3
```c=
void foobar(long a[], size_t n, long y, long z) {
    for (int i = 0; i < n; i++) {
        long x = y - z;
        long j = 7 * i;
        a[i] = j + x * x;
    }
}
```

https://en.wikipedia.org/wiki/Loop_invariant
**niezmienniki pętli** (ang. loop invariants) - własność programu prawdziwa przed wywołaniem i po wywołaniu pętli
https://en.wikipedia.org/wiki/Induction_variable
**zmienne indukcyjne** (ang. induction variable) - zmienne, które zwiększają lub zmniejszają się o stałą wartość przy każdej iteracji pętli lub jest funkcją liniową innej zmiennej indukcyjnej.

Niezmienniki:
- `x = y - z`
- `n, y, z`
Zmienne indukcyjne:
- `i`
- `j`
- `a[i]` (`j + x * x` - to funkcja linowa zmiennej indukcyjnej)

RDI - a[], RSI - n, RDX - y, RCX - z
```c=
foobar:
        testq   %rsi, %rsi            // n == 0
        je      .L1
        subq    %rcx, %rdx            // y = y - z
        leaq    (%rdi,%rsi,8), %rax   // addr = a + 8 * n -> adres końca tablicy (a[n])
        imulq   %rdx, %rdx            // y = y * y
.L3:
        movq    %rdx, (%rdi)          // a[i] = y
        addq    $8, %rdi              // i++
        addq    $7, %rdx              // y += 7
        cmpq    %rax, %rdi            // a != addr -> jump
        jne     .L3
.L1:
        ret
```
postać po optymalizacji:
```c=
void foobar(long a[], size_t n, long y, long z) {
    if(n == 0)
        return;
        
    y -= z;
    long* addr = a + 8 * n;
    y *= y;
    
    while(a != addr)
    {
        *a = y;
        y += 7;
        a++;
    }
}
```
Czyli przęd pętlę wyciągnięto obliczanie x: `(x = z - y)`
oraz jako, że nie korzystamy z wartości `x` a z wartości `x*x` to to mnożenie też wykonano przed pętlą.
Przed pętlą obliczamy także adres elementu "za" tablicą po to by nie wyliczać `a[i]`, albo wartości `i` w każdym obrocie (kompilator pominął istnienie `i`).

https://en.wikipedia.org/wiki/Strength_reduction
**osłabienie wyrażeń** (ang. strength reduction) - optymalizacja w której kompilator zastępuje droższe operacje, jedną lub wieloma sumarycznie tańszymi, a równoważnymi.
Osłabione zostało obliczanie wyrażenia `7 * i`, przez dodawanie do `j + 7` w każdym obrocie pętli.

## 4
```c=
long neigh(long a[], long n, long i, long j) {
    long ul = a[(i-1)*n + (j-1)];
    long ur = a[(i-1)*n + (j+1)];
    long dl = a[(i+1)*n - (j-1)];
    long dr = a[(i+1)*n - (j+1)];
    return ul + ur + dl + dr;
}
```
RDI - a[], RSI - n, RDX - i, RCX - j
```c=
neigh:
        subq    $1, %rdx            // i - 1
        leaq    -1(%rcx), %r8       // temp = j - 1
        addq    $1, %rcx            // j++
        imulq   %rsi, %rdx          // i *= n
        leaq    (%rdx,%rsi,2), %rsi // n = i + (2 * n)
        leaq    (%rdx,%r8), %r9     // temp2 = temp + i
        addq    %rcx, %rdx          // i += j
        movq    (%rdi,%rdx,8), %rax // result = *(a + 8 * i)
        movq    %rsi, %rdx          // i = n
        subq    %rcx, %rsi          // n -= j
        addq    (%rdi,%r9,8), %rax  // result += *(a + (8 * temp2))
        subq    %r8, %rdx           // i -= temp
        addq    (%rdi,%rdx,8), %rax // result += *(a + (8 * i))
        addq    (%rdi,%rsi,8), %rax // result += *(a + (8 * n))
        ret
```
Zoptymalizowana wersja (po uproszczeniach)
```c=
long neigh2(long a[], long n, long i, long j) {
    long temp = j - 1;
    j++;
    i = n * (i-1);
    n = i + 2 * n;
    long temp2 = temp + i;
    long result = *(a + 8 * (i+j));
    result += *(a + (8 * temp2));
    result += *(a + (8 * (n-temp)));
    result += *(a + (8 * (n-j)));
    
    return result;
}
```
czyli kompilator wylicza `j-1`, oraz `n * (i-1)` tylko raz

**Moja optymalizacja**
Wykorzystujemy fakt że elementy ul i ur, oraz dl i dr są odzielone jedną komórką tablicy.
```c=
long neigh2(long a[], long n, long i, long j) {
    long* ul = &(a[(i-1)*n + (j-1)]);
    long ur = *(ul+2);
    long* dl = &(a[(i+1)*n - (j+1)]);
    long dr = *(dl+2);
    return *ul + ur + *dl + dr;
}
```
Wygerowany kod:
```c=
neigh2:
        subq    $1, %rdx
        imulq   %rsi, %rdx
        leaq    -1(%rdx,%rcx), %r8
        leaq    (%rdx,%rsi,2), %rdx
        addq    $1, %rcx
        subq    %rcx, %rdx
        movq    (%rdi,%r8,8), %rax
        addq    16(%rdi,%r8,8), %rax
        addq    (%rdi,%rdx,8), %rax
        addq    16(%rdi,%rdx,8), %rax
        ret
```

https://en.wikipedia.org/wiki/Common_subexpression_elimination
**Eliminacja wspólnych podwyrażeń** - Optymalizacja, która szuka wyrażeń obliczających się do identycznej wartości i sprawdza czy opłaca zamienić się je przy pomocy zmiennej tymczasowej i liczyć jednokrotnie (np. czy nie braknie rejestrów i dane trzeba będzie trzymać w pamięci).

## 5
https://docs.freebsd.org/44doc/psd/18.gprof/paper.pdf
http://archive.ph/9r927#selection-1415.50-1415.167
https://stackoverflow.com/questions/4981121/how-exactly-does-gprof-work/5046039#5046039
http://aragorn.pb.bialystok.pl/~mkret/gprof_gcov_tutorial.pdf

**programy profilujące** - służą do sprawdzenia ile czasu zajmuje wykonywanie poszczególnych części programy. Przydatne w identyfikowaniu wąskich gardeł naszego programu, miejsc, które potencjalnie warto optymalizować.
**profil płaski** - zbiór informacji o przebiegu programu zawierający średni czas przebywania w danej funkcji, oraz liczbę wywołań
![](https://i.imgur.com/5sQKxXa.png)

**profil grafu wywołań**  - daje dodatkowe informacje o kolejności wywołań funkcji
![](https://i.imgur.com/NEVehNA.png)

**Czemu profilowanie programu wymaga zbudowania go ze specjalną opcją kompilatora -pg?**
Dodanie flagi `-pg` sprawia, że każda funkcja przechowuje informację o tym skąd była wołana oraz ile razy. Konkretniej dodaje `mcount` do początku każdej funkcji, która rejestruje "in-memory call graph table".

**Na czym polega zliczanie interwałowe?**
Program trzyma licznik dla każdej funkcji. System operacyjny wstrzymuje działanie programu w regularnych odstępach (interwałach). Następnie sprawdza w jakiej funkcji znajduje się program w trakcie przerwania i zwiększa dla niej jej licznik. Dla większych przedziałów czasowych, dobrze przybliża statyczny czas wykonywania.

**Jak przy pomocy programu profilującego zidentyfikowano w [1, §5.14.2] procedury, które należało zoptymalizować?**
Program w [1, §5.14.2] szuka unikatów n-gramów i liczy liczbę ich wystąpień.
n-gram - n słów następujących po sobie

Autorzy rozważyli następujący algorytm:
I) Czytanie z pliku i konwertowanie na lowercase (przy pomocy funkcji, która używa strlen w taki sposób że jest $O(n^2)$)
II) Tworzone jest hash-table z s kubełkami, funkcja hashująca sumuje ASCII modulo s
III) Każdy kubełek jest na liście (Linked List). Program szuka pasującego do n-gramu kubełka i zwiększa jego wartość. Jeśli brakuje kubełka to będzie on dodawany na końcu listy.
IV) Sortujemy elementy po częstotliwościach (początkowo przy użyciu Insert-Sort)

Wykorzystują przy tym 4 funkcje: *Sort, List, Lower, Strlen*

Decyzje o tym co należy optymalizować podejmują na podstawie wyników profiler'a
![](https://i.imgur.com/SLLNaiJ.png)
Początkowy czas to 3.5 minuty
1) Najpierw optymalizują złożoność asymptotyczną sortowania: $O(n^2)$ -> $O(nlogn)$
2) Zauważają, że teraz skanowanie listy jest wąskim gardłem. 
3) Zmiana funkcji rekurencyjnej na funkcję iteracyjną zwiększyła czas (!). Wynika to z tego że pierwsza wersja iteracyjna (**Iter first**), dodawała nowe elementy na początek listy, a rekurencyjna na koniec, a zgodnie z intuicją najczęściej występujące n-gramy powinny pojawiać się na początku listy, aby szybko je znajdować.
4) Wersja iteracyjna dodająca na koniec listy (**Iter last**) przyspieszyła działanie o 5 sekund względem wersji rekurencyjnej
5) Zwiekszamy liczbe kubełków z 1021 do 199999 dla struktury hashtable i obserwujemy małą różnicę 0.2s (**Big Table**)
6) Największy n-gram ma w obecnej funkcji hashującej wartośc 3,371, więc większość kubełków jest niewykorzystywana, dodatkowo może generować takie same sumy dla różnych słów ("tar" i "rat") -> zmieniamy funkcję hashującą (**Better hash**)
7) Zauważają, że teraz strlen jest wąskim gardłem. 
8) Zmieniamy funkcję Lower na taką, która jest O(n) (nie woła strlen w każdym obrocie) - > (**Linear lower**)
Czas spadł do 0.2 sekundy

**Które optymalizacje przyniosły największy efekt?**
Największą redukcję czasu (40 krotną!) przyniosła zmiana złożoności asymptotycznej poprzez zastąpienie sortowania przy pomocy insert-sort $(O(n^2))$, quicksortem $(O(nlogn))$.
Późniejsza duża redukcja była wynikiem zmiany funkcji haszującej.
