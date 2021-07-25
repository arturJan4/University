# Raport do zadania 4 - binsearch

### Autor: Artur Jankowski
### Numer indeksu: 317928

Konfiguracja
---

Informacje o systemie:

 * Dystrybucja: Ubuntu 20.04.2 LTS
 * Jądro systemu: Linux 5.4.0-73-generic
 * Kompilator: GNU GCC 9.3.0
 * Procesor: Intel(R) Core(TM) i5-8300H CPU @ 2.30GHz (Coffee Lake)
 * Liczba rdzeni: 4

Pamięć podręczna:

 * L1d: 32 KiB, 8-drożny (per rdzeń), rozmiar linii 64B
 * L2: 256 KiB, 4-drożny (per rdzeń), rozmiar linii 64B
 * L3: 8 MiB , 16-drożny (współdzielony), rozmiar linii 64B

Pamięć TLB:

 * L1d: 4KiB strony, 4-drożny, 64 wpisy
 * L2: 4KiB strony, 6-drożny, 1536 wpisów

Informacje o pamięciach podręcznych uzyskano na podstawie wydruku programu
`x86info` oraz `lscpu`, `getconf`,  `cpuid`.

Wyniki eksperymentów
---
Moja wersja w porównaniu do wyników z `randwalk.c` daje następujące wyniki
```
./randwalk -S 0xea3495cc76b34acc -n 7 -s 16 -t 14 -v 0
>>> VARIANT 0 <<<
Time elapsed: 7.962320 seconds

./randwalk -S 0xea3495cc76b34acc -n 7 -s 16 -t 14 -v 1
>>> VARIANT 1 <<<
Time elapsed: 3.477898 seconds
```

Nowa wersja eliminuje skoki warunkowe dzięki zamianie warunków `if` na zawsze obliczane instrukcje oparte na wartościach logicznych. Dzięki temu kompilator może skorzystać z instrukcji `setcc`, zamiast wykorzystywać operacje skoków warunkowych `j*`, które wymagają przewidywania skoku przez predyktor skoków. Złe przewidywanie skutkuje natomiast dużym kosztem dla źle przewidzianych rozgałęzień, gdyż procesor, który ładuje wcześniej i wykonuje instrukcje out-of-order, po wykryciu błędu, musi wyczyścić wszystkie instrukcje od momentu źle przewidzianego skoku i zacząć liczyć ponownie.

Przykładowa zamiana:

z:
```c=
if (d == 0)
    if (i > 0)
        i--;
```
w:
```c=
    i -= (d == 0) & (i > 0);
```
nie musimy więc przewidywać czy `d == 0` i czy `i > 0`.

### Wyniki dla `make sim`
Symulacja uruchamia się z parametrami: `./randwalk -S 0xea3495cc76b34acc  -n 7 -s 12 -t 10 -v 0`, a więc mamy do czynienia z 1024 przejściami po 4096 kroków każde, po tablicy rozmiaru 128x128 (16KiB).

Uśrednione wyniki `make sim`:

| Wersja    | Czas (s) | Branch MR | L1 MR | LL MR |
| --------- | -------- | --------- | ----- | ----- |
| randwalk0 | 1.23871  | 20.728    | 0     | 0     |
| randwalk1 | 1.30381  | 1.563     | 0     | 0     |

Jak widzimy, czas wykonania nie zmienił się znacząco. Ze względu na mały rozmiar tablicy, mniejszy niż rozmiar cache L1, zawsze trafiamy w pamięć podręczną. Obserwujemy jednak duży spadek branch-MR z `~20%` do `~1,5%`. 

Jako, że koszt źle przewidzianego skoku to ok. `15-20` cykli (źródło: "The microarchitecture of Intel, AMD,and VIA CPUs - An optimization guide for assembly programmers and compiler makers") , to przy IPC randwalk0 (`~0.765`) mamy do czynienia ze stratą `~11.475-15.3` instrukcji. 

### Wykresy
**Wykres 1:** Porównanie uśrednionego IPC dla randwalk1 i randwalk0:
![](https://i.imgur.com/RCLHg5Q.png)

**Wykres 2:** Wykresy uśrednionego czasu działania dla interesujących ustawień instrukcji:
![](https://i.imgur.com/xFdXwJx.png)

**Wykres 3:** Porównanie uśrednionego czasu działania dla różnych rozmiarów tablic:
![](https://i.imgur.com/huJ4KNC.png)

### Tabela
tabela została wygenerowana dla `/randwalk -n {1..15} -S 0x5bab3de5da7882fb -t 10 -s 12 -v {0,1}`

| n   | time (v0) | L1 (v0) | L2 (v0) | L3(v0) | time (v1) | L1 (v1) | L2 (v1) | L3(v1) |
| --- | --------- | ------- | ------- | ------ | --------- | ------- | ------- | ------ |
| 1   | 0.038148  | 0.137   | 0.506   | 0.007  | 0.017588  | 0.123   | 0.304   | 0.003  |
| 2   | 0.035522  | 0.122   | 0.404   | 0.015  | 0.016904  | 0.068   | 0.137   | 0.002  |
| 3   | 0.035668  | 0.109   | 0.296   | 0.007  | 0.017501  | 0.19    | 0.126   | 0.002  |
| 4   | 0.035497  | 0.13    | 0.357   | 0.01   | 0.017481  | 0.122   | 0.217   | 0.018  |
| 5   | 0.035473  | 0.163   | 0.36    | 0.011  | 0.016899  | 0.105   | 0.257   | 0.013  |
| 6   | 0.035359  | 0.234   | 0.478   | 0.002  | 0.017642  | 0.225   | 1.043   | 0.01   |
| 7   | 0.035143  | 0.638   | 0.642   | 0.03   | 0.016876  | 0.506   | 0.942   | 0.009  |
| 8   | 0.035279  | 1.909   | 1.138   | 0.016  | 0.017749  | 2.932   | 0.647   | 0.007  |
| 9   | 0.036592  | 3.545   | 2.757   | 0.106  | 0.01785   | 4.741   | 2.18    | 0.037  |
| 10  | 0.03755   | 4.192   | 4.346   | 0.113  | 0.017652  | 6.106   | 3.546   | 0.638  |
| 11  | 0.036066  | 6.088   | 7.882   | 0.385  | 0.017836  | 8.477   | 7.598   | 0.145  |
| 12  | 0.035743  | 7.659   | 15.652  | 0.826  | 0.017532  | 10.651  | 22.234  | 0.758  |
| 13  | 0.03524   | 5.794   | 13.026  | 0.776  | 0.017438  | 7.965   | 16.708  | 0.798  |
| 14  | 0.036121  | 6.728   | 13.115  | 0.945  | 0.017492  | 8.109   | 18.535  | 0.959  |
| 15  | 0.035489  | 5.019   | 17.682  | 3.398  | 0.018164  | 7.357   | 25.045  | 0.904  |

Widać na niej wyraźnie jak rozkłada się procent chybień dla rosnących rozmiarów tablicy dla obu wersji funkcji. Uwagę zwraca bardzo wolno rosnąca liczba chybień w pamięć podręczną mimo rosnącego `n` (gdzie macierze mają bok długości 2^n).

Wnioski
---
### Ile instrukcji maszynowych ma ciało pętli przed i po optymalizacji? Ile spośród nich to instrukcje warunkowe?
Długość całych programów jest podobna:

`objdump --disassemble=randwalk0 randwalk.o | tail -n +8 | wc -l` -> 79

`objdump --disassemble=randwalk1 randwalk.o | tail -n +8 | wc -l` -> 78

Natomiast wnętrze pętli przeanalizowałem w pliku `data_wydruk1.txt` - oznaczając interesujące instrukcje oraz miejsce początku i końca.

**randwalk0:** 46 instrukcji (przedzielonych blokiem z instrukcją `ret`)

Wewnątrz mamy 9 skoków (w tym 6 warunkowych), wykorzystujemy też 4 instrukcje `setcc`.

**randwalk1:** również 46 instrukcji

Wewnątrz mamy 3 skoki, w tym: 2 warunkowe - z pętli `do while`, oraz z pętli z `fast_random`, 

Wykorzystujemy natomiast 8 instrukcji `setcc`, czyli spodziewanie zwiększyło się to o 4 (bo zastąpiliśmy cztery `if`'y, czterema wyrażeniami logicznymi).

Interesują nas skoki warunkowe (dlatego, że wtedy musimy ufać, że dobrze działa predyktor).

Mamy 2 oczywiste skoki: 
- z pętli, w której wołamy `fast_random `,
- z pętli `do`, gdy sprawdzamy czy `len-1 == 0`.

Skoki te ciężko byłoby optymalizować, gdyż predyktor prawdopodobnie przewiduje je bardzo dobrze.

Oraz cztery skoki, których zoptymalizowanie było celem zadania (i tak rzeczywiście jest 6 -> 2).

### Jak optymalizacja wpłynęła na IPC?
Jak widzimy na **wykresie nr 1** optymalizacja znacznie wpłynęła na IPC. Jako że mamy do czynienia z programami z podobną liczbą instrukcji to możemy śmiało powiedzieć, że polepszyliśmy działanie programu też pod tym względem. 

Możemy założyć, że program ma obecnie krótszą ścieżkę krytyczną, tj. procesor może przetwarzać więcej instrukcji jednocześnie, bo ma lepiej ułożone instrukcje względem wolnych jednostek funkcyjnych.

### Jak na IPC wpływa zmiana kolejności instrukcji w ciele pętli?
Niech poniższa wersja będzie wersją domyślną:
```c=
    i -= (d == 0) & (i > 0);        // 1
    i += (d == 1) & (i < n - 1);    // 2
    j -= (d == 2) & (j > 0);        // 3
    j += (d == 3) & (j < n - 1);    // 4
```
Powyższe instrukcje możemy ułożyć na (4! = 24) sposobów. Dokonałem tych zamian, a uśrednione wyniki dla paru wartości `n`, po ponownym skompilowaniu umieściłem w pliku `data_ipc_n_combined.dat`. 

Znalazłem w nim wersję, która sprawuje się najlepiej (kolejność: `2-1-4-3`) oraz taką, która sprawuje się najgorzej (kolejność: `1-3-4-2`), oraz wyliczyłem medianę IPC dla 24 wersji. Znalezione wersje dawały najlepsze/najgorsze wyniki dla każdego `n`. Na **wykresie nr 2** można zobaczyć porównanie tych wersji `randwalk1`.

Obserwujemy prawie dwukrotną różnicę pomiędzy najlepszą i najgorszą wersją. Po deasemblacji obu procedur okazuje się, że są one tej samej długości oraz składają się prawie z tych samych instrukcji (jeden `and` więcej w lepszej zamiast instrukcji `test`). Jedyne większe różnice są w ich rozstawieniu.

```
+----------------------------+----------------------------+
| best:                      | worst:                     |
|         movl    %edi, %eax |         cmpl    $1, %edx   |
|         andl    $3, %eax   |         sete    %r8b       |
|         sete    %r8b       |         xorl    %eax, %eax |
|         xorl    %edi, %edi |         cmpl    %esi, %ebx |
|         testl   %ebx, %ebx |         setl    %al        |
|         setg    %dil       |         andl    %r8d, %eax |
|         andl    %r8d, %edi |         addl    %ebx, %eax |
|         subl    %edi, %ebx |         testl   %edx, %edx |
|         cmpl    $2, %eax   |         sete    %r9b       |
|         sete    %r9b       |         xorl    %r8d, %r8d |
|         xorl    %edi, %edi |         testl   %eax, %eax |
|         testl   %ebp, %ebp |         setg    %r8b       |
|         movl    %ebx, %r8d |         andl    %r9d, %r8d |
|         setg    %dil       |         subl    %r8d, %eax |
|         andl    %r9d, %edi |         cmpl    $3, %edx   |
|         subl    %edi, %ebp |         sete    %r8b       |
|         cmpl    $3, %eax   |         movl    %eax, %ebx |
|         sete    %r9b       |         xorl    %eax, %eax |
|         xorl    %edi, %edi |         cmpl    %esi, %ebp |
|         cmpl    %edx, %ebp |         setl    %al        |
|         setl    %dil       |         andl    %r8d, %eax |
|         andl    %r9d, %edi |         addl    %ebp, %eax |
|         addl    %edi, %ebp |         cmpl    $2, %edx   |
|         cmpl    $1, %eax   |         sete    %r8b       |
|         sete    %al        |         xorl    %edx, %edx |
|         xorl    %ebx, %ebx |         testl   %eax, %eax |
|         cmpl    %edx, %r8d |         setg    %dl        |
|         setl    %bl        |         andl    %r8d, %edx |
|         andl    %eax, %ebx |         subl    %edx, %eax |
|         addl    %r8d, %ebx |         movl    %eax, %ebp |
|         subl    $1, %r12d  |         subl    $1, %r12d  |
|         je      .L7        |         je      .L7        |
+----------------------------+----------------------------+
```
Możemy uznać, że najlepsza wersja lepiej wykorzystuje jednostki funkcyjne, tj. używa wcześniej operacji `mov`, nie stawia tak często po sobie instrukcji wymagających tych samych jednostek (np. `test` jest lepiej rozłożony po całej pętli). Najlepsza wersja dużo lepiej wykorzystuje pipelining.

### Czy rozmiar tablicy ma duży wpływ na działanie programu?
Na podstawie **wykresu nr 3** możemy stwierdzić, że dla testowanych rozmiarów (od 2^1 - 16B do 2^15 - 1024 MiB) nie zauważamy większej różnicy w czasie wykonania. 

Różnice obserwowalne są oczywiście pomiędzy różną liczbą kroków, więc wielokrotne wykonywanie funkcji dla małego rozmiaru jest o wiele bardziej kosztowne, dlatego też optymalizujemy wnętrze pętli. 

Może to wynikać z tego, że poruszamy się w jednym z 4 kierunków, więc lokalność przestrzenna oraz czasowa będzie wysoka. To, że lokalność jest wysoka, wynika również z wygenerowanej tabeli ze średnimi współczynnikami chybień dla różnych rozmiarów. 

### Podsumowanie
Sumaryczne koszty złego przewidywania pętli dla losowych lub niepodążających jakimś trendem danych są duże. 

Mimo że współczesne predyktory skoków są bardzo zaawansowane, to są momenty, w których możemy je wspierać, np. pisząc kod wykorzystujący operator `?:`, lub obliczając wszystkie gałęzie, tak by nasz kompilator mógł wygenerować kod maszynowy ograniczający skoki warunkowe. 

Zauważyliśmy też, że zmiana kolejności instrukcji może mieć duży wpływ na działanie programu, dzięki lepszemu wykorzystaniu mikroarchitektury procesora.
