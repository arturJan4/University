# Raport do zadania 1 

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

Skrypty testujące zawarłem w pliku `matmult_tests.py`.
Uśrednione wyniki dla parunastu testów wykonywanych przy pomocy `make sim` znajdujdują się w poniższej tabeli (funkcja `make_sim`):

| Wersja    | Czas wykonywania (s) | Branch MR | L1 MR   | LL MR   |
| --- | -------------------- | --------- | ------- | ------- |
| matmult0    | 1.6144               | 0.391     | 50.167 | 50.147  |
| matmult1    | 1.3834               | 0.391     | 6.4570  | 0.404   |
| matmult2    | 1.9609              | 0.391     | 100.0  | 100.0   |
| matmult3    | 1.4779               | 6.25   | 2.085   | 0.440   |


Wyniki dla parunastu uruchomień w zależności parametru `-n` od cpi (wyliczonego skryptem na podstawie IPC i liczby instrukcji z flagi `-p`) zawarłem na poniższym wykresie (funkcja `cpi_to_n_csv`):
![](https://i.imgur.com/GqqjMP6.png)
Widać podobieństwo dla slajdu 46 (modulo pewne skoki).

Poniżej widać zależność rozmiaru bloku (stała `BLOCK` z matmult.h), testy wykonałem z flagami `-n 1024 -v 3` - `block_size_test`
![](https://i.imgur.com/qP8VGAN.png)

Natomiast przy próbie analizy wpływu offsetu naszykowałem dwa wykresy analogiczne do pierwszego (czyli przedstawiam różne warianty funkcji `matmult`, w zależności od rozmiaru tablicy i czasu, dodatkowo obciąłem oś **OX**, aby móc lepiej zauważyć różnice, `BLOCK = 16`) - `offset_test`:
![](https://i.imgur.com/AZIZbbB.png)
Tutaj mamy przykład dla offsetów ustawionych na zero:
![](https://i.imgur.com/gRMsCUu.png)
A tutaj przykład odwrotny do domyślnego:
![](https://i.imgur.com/e96rzV4.png)


Wnioski
---
### Wyniki z wykładu
Wyniki różnią się, mamy do czynienia z o wiele mniejszym CPI, co może wynikać z różnicy pomiedzy procesorami. Wykres przypomina jednak ten z wykładu. Dodatkowo obserwowalne są duże, mimo uśrednienia, wahania wyników dla jki (`matmult2`). Spodziewane ilości missów można odczytać z tabeli np. 1.0 miss-ratio dla `matmult2`, ale np. miss-ratio dla `matmult0` jest większe, niż spodziewalibyśmy się z wykładu.

### Rozbieżność pomiedzy wynikami
Gdy spojrzymy na tabelę wyników `make sim`, zauważamy, że wynika to z wysokiego współczynnika chybień na iterację dla `matmult0`, oraz `matmul2` (zgodnie z wykładem).  
Sposób skanowania macierzy zmienia lokalność cache (to, co pozostaje po wewnętrznej iteracji), a to ma wpływ na miss-ratio i sumaryczne miss-penalty.
Wersja kafelkowana: `matmult3` charakteryzuję się wysokim branch miss ratio, ale za to o wiele częściej trafiamy w cache L1.

### Rozmiar kafelka, a matmult3
Jak widać, na wykresie dotyczącym BLOCK, rozmiar kafelka ma znaczenie, ale nie to znaczy, że im więcej, tym lepiej. Optymalny rozmiar dla mojej konfiguracji to 8 (co koreluje z 8-drożną wieolodrożną sekcyjno-skojarzeniowo pamięcią). Mniejszy rozmiar niż 8 daje gorsze wyniki, a większe rozmiary zwiększają liczbę chybień L1.

### Spadek wydajności
Ze względu na to, że nasza funkcja jest O(n^3) to dla wersji `jki` obserwujemy drastyczny spadek wydajności przy n w okolicach 2048. Inne wersje radzą sobie jeszcze przyzwoicie (~6 sekund).

### Inny wybór OFFSET
Inny wybór wartości OFFSET nie ma u mnie większego znaczenia. Nie zauważyłem spadku wydajności `matmult3` po ustawieniu wartości na 0.

### Podsumowanie
Dla testowanych rozmiarów tablic, oraz mojej konfiguracji kafelkowanie nie przyniosło pożądanych rezultatów. Należałoby więc z niego zrezygnować, by nie tracić na czytelności kodu lub zmodyfikować paramatery pod poszczególne zadanie, by optymalizacja była warta. Może dla pewnych zastosowań byłoby to warte użycia (np. jeśli zależy nam na każdej milisekundzie, a n jest wysokie). Widać natomiast dużą różnicę pomiędzy wydajnościami `matmult0` i `matmult1`, a `matmult2` które lepiej wykorzystują cache L1 oraz L2, dzięki lepszej lokalności przestrzennej.
