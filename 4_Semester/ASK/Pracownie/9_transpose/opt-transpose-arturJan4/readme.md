# Raport do zadania 2 - transpose

### Autor: Artur Jankowski
### Numer indeksu: 317928

Konfiguracja
---

Informacje o systemie:

 * Dystrybucja: Ubuntu 20.04.2 LTS
 * Jądro systemu: Linux 5.4.0-73-generic
 * Kompilator: GNU GCC 9.3.0
 * Procesor: Intel(R) Core(TM) i5-8300H CPU @ 2.30GHz
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
Moja wersja w porównaniu do wyników z `transpose.c` daje następujące wyniki
```
./transpose -n 32768 -v 0
Time elapsed: 19.998201 seconds
./transpose -n 32768 -v 1
Time elapsed: 3.379132 seconds
```
Wersja `transpose0` porusza się wierszami tabeli `src` i kolumnami `dest`. Przez co elementy `src` mogą być cachowane ale dla kolumn w `dest` będziemy mieli missy. Dla odpowiednio dużych `n` miss-rate dąży do 100% bo w pamięci zostaje tylko wiersz (lub jego część) który w kolejnej iteracji jest bezużyteczny.
Wersja `transpose1` wykorzystuje natomiast blokowanie podobnie jak w zadaniu `matmult`, gdzie małe bloki mieszczą się w pamięci cache i są wykorzystywane ponownie co minimializuje liczbę chybień.


### Wyniki dla `make sim`

W symulacji mamy do czynienia z pamięcią podręczną:
`L1: 32 KB, 4-drożnym`, 
`LL: 512kB, 16-drożnym`. 
Rozmiar komórki tablicy to `int` czyli `4` bajty. Można więc cachować `8192` elementów tablicy. 
Rozmiar macierzy dla `make sim` to `4096 x 4096`.
Dla bloku `BLOCK=8`, blok ma `4 * 8 * 8 = 256 bajty`.

| Wersja     | Czas (s) | Branch MR | L1 MR  | LL MR  |
| ---------- | -------- | --------- | ------ | ------ |
| transpose0 | 1.557326 | 0.025     | 53.125 | 50.855 |
| transpose1 | 1.727812 | 12.331    | 50.042 | 8.333  |

Jak widać powyżej "zoptymalizowana" wersja nie radzi sobie lepiej dla tej konfiguracji oraz danych. Wynika to z kosztu branch, który przeważa nad zyskiem w L1 i LL (który to jest o wiele niższy dla `transpose1`). Szerokość `n` jest na tyle niska, że cały wiersz tablicy `src` mieści się w L1, dlatego reszta chybień dotyczy `dest`. Dodatkowo n jest potęgą dwójki, a jak zobaczymy później są to wartości specyficzne, które maksymalizują liczbę chybień w L1, ze względu na podział cache na linie.

### Wykresy
Wszystkie czasy wykonania `transpose1`, w zależności od rozmiaru, dla poszczególnych BLOCK zamieściłem poniżej.
![](https://i.imgur.com/3HkY1GL.png)
Jako że widać, że niektóre wartości znacznie odbiegają, zostawmy tylko te interesujące:
![](https://i.imgur.com/zpHOx4Q.png)
Obserwujemy znaczące skoki dla `BLOCK = 32` w kolejnych wielokrotnościach 512 dla oraz `BLOCK = 16` w wielokrotnościach 1024. Można je wyjaśnić współczynnikiem chybień dla `L1` na poniższym wykresie (w tych pikach prawie zawsze chybiamy też w `L2` co jest jeszcze bardziej dotkliwe dla czasu działania)
![](https://i.imgur.com/0e7M4t4.png)

Dla ustalonego `n` będącego potęgą dwójki lepiej sprawować będzie się `BLOCK=8` ze względu na mniejsze wahania.
![](https://i.imgur.com/4Co8P1O.png)

Porównajmy jeszcze wpływ `transpose1` na działanie programu oraz o ile przyspieszył czas działania w porównaniu do `transpose0`
![](https://i.imgur.com/27Ar8sr.png)
Przybliżmy powyższy wykres dla małych `n`:
![](https://i.imgur.com/79EBuf1.png)

Czas działania algorytmu dla dużych n (pokazuje dobrze charakter kwadratowej złożoności algorytmu):
![](https://i.imgur.com/jafHm12.png)

Wnioski
---
Jak widać z wykresów wybór kafelka ma znaczenie na lokalność przestrzenną, a co za tym idzie na wydajność. Musimy też podjąć decyzję, czy wolimy wersję stabilniejszą `BLOCK=8` (jeśli chodzi o czas), lepiej pasującą do 8-drożnej pamięci, czy szybszą (np. `BLOCK=16`), ale nie radzącą sobie dobrze z szerokościami tablic będącymi pewnymi wielokrotnościami `512` lub `1024`.

Na podstawie wykresów czasu działania programu od rozmiaru tablicy oraz chybień od rozmiaru ciężko stwierdzić, jakie są rozmiary pamięci podręcznej, Nie widać zauważalnego piku dla jakichś wartości `n`, liczba chybień w `L1` także wydaje się rosnąć liniowo.
