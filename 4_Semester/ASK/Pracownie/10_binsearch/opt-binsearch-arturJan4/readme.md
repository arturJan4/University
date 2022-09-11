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
Moja wersja w porównaniu do wyników z `binsearch.c` daje następujące wyniki
```
./binsearch -S 0x5bab3de5da7882ff -n 23 -t 24 -v 0
>>> VARIANT 0 <<<
Time elapsed: 5.730897 seconds

./binsearch -S 0x5bab3de5da7882ff -n 23 -t 24 -v 1
>>> VARIANT 1 <<<
Time elapsed: 3.329408 seconds

```
Nowa wersja bierze binarne drzewo przeszukiwań i układa węzły poziomami drzewa tak jak w kopcu. 

To znaczy, że środkowy element tablicy `src` trafi jako pierwszy w `dest`. 

Podobnie: lewe dziecko `i`-tego elementu `src` to `i/2`, prawe to `3/4 * i`.

W implementacji kopcowej natomiast kolejne poziomy drzewa sąsiadują tj. lewe dziecko `i`-tego elementu jest w `i * 2 + 1`, a prawe w `i * 2 + 2`.

W ten sposób rozkładam kolejne poziomy rozmiarów rosnących potęg dwójki.

Przykładowo tablicę o indeksach `0 1 2 3 4 5 6 7` ustawimy `3 | 1 5 | 2 4 6 8`.

### Wyniki dla `make sim`

Uśrednione wyniki `make sim`:

| Wersja     | Czas (s) | Branch MR | L1 MR  | LL MR  |
| ---------- | -------- | --------- | ------ | ------ |
| binsearch0 | 3.045480 | 2.819     | 77.831 | 49.904 |
| binsearch1 | 2.764867 | 2.742     | 35.703 | 10.373 |

Jak widzimy, funkcje mają podobne branch `MR`, ale różnią się znacznie współczynnikiem chybień dla `L1` i `LL`. Dwukrotna poprawa dla `binsearch1` może skutkować znacznie lepszym czasem działania dla pewnych odpowiednio dużych `n`, lub dla rosnącej liczby zapytań.

### Wykresy
Porównanie uśrednionych czasów działania dla mojej konfiguracji:
![](https://i.imgur.com/FoRejfK.png)
Widać poprawę dla odpowiednio dużych `n`.

Porównanie IPC dla 3 różnych wariantów `binsearch1`:

**wariant 0:**
```c
bool binsearch1(T *arr, long size, T x) {
  long iter = 0;
  while(iter < size) {
    T y = arr[iter];
    if(x == y)
      return true;
    iter <<= 1;
    iter += 1 + (y < x);
  }
  return false;
}
```
**wariant 1:**
```c
bool binsearch1(T *arr, long size, T x) {
  long iter = 0;
  while(iter < size) {
    T y = arr[iter];
    iter <<= 1;
    if(x == y)
      return true;
    iter += 1 + (y < x);
	}
  return false;
}
```
**wariant 2:**
```c
bool binsearch1(T *arr, long size, T x) {
  long iter = 0;
  while(iter < size) {
    T y = arr[iter];
    iter <<= 1;
    iter += 1 + (y < x);
    if(x == y)
      return true;
  }
  return false;
}
```
![](https://i.imgur.com/2RrwNA1.png)
Dla większych `n`, trzeci wariant cechuje się najlepszym IPC.

Wykorzystanie funkcji wbudowanej `__builtin_prefetch()`:
![](https://i.imgur.com/zmtOiyd.png)
Wykorzystanie funkcji przyniosło rezultaty. 

Wykresy dla różnych parametrów `__builtin_prefetch()` dotyczących lokalności, gdy uwzględnimy błędy pomiarowe, nie wykazują jednak różnicy między sobą. Możemy wybrać domyślną wartość parametru `locality`, `rw` oczywiście zostawiamy na `0`, gdyż nie robimy zapisów do pamięci, a tylko odczyty.

### Tabela
tabela została wygenerowana dla `/binsearch -p l1 -n {1..24} -S 0x5bab3de5da7882fb -t 20 -v {0,1}`

| n        | time (v0) | L1 (v0)   | L2 (v0)    | L3(v0)     | time (v1) | L1 (v1)   | L2 (v1)    | L3(v1)    |
| -------- | --------- | --------- | ---------- | ---------- | --------- | --------- | ---------- | --------- |
| 1        | 0.006373  | 0.001000  | 0.007000   | 0.000333   | 0.007039  | 0.001000  | 0.002333   | 0.000000  |
| 2        | 0.007270  | 0.001000  | 0.002333   | 0.000000   | 0.008342  | 0.001000  | 0.002667   | 0.000000  |
| 3        | 0.009792  | 0.001000  | 0.002333   | 0.000000   | 0.011433  | 0.001000  | 0.003000   | 0.000667  |
| 4        | 0.011269  | 0.001000  | 0.002333   | 0.000000   | 0.013129  | 0.001000  | 0.004333   | 0.000000  |
| 5        | 0.011997  | 0.001000  | 0.002000   | 0.000000   | 0.014914  | 0.001000  | 0.002667   | 0.000000  |
| 6        | 0.013476  | 0.001000  | 0.002000   | 0.000000   | 0.017341  | 0.001000  | 0.003000   | 0.000000  |
| 7        | 0.014771  | 0.001000  | 0.002000   | 0.000000   | 0.018740  | 0.001000  | 0.002667   | 0.000000  |
| 8        | 0.016468  | 0.001000  | 0.003333   | 0.000000   | 0.021318  | 0.001000  | 0.003000   | 0.000000  |
| 9        | 0.017615  | 0.001000  | 0.003333   | 0.000000   | 0.022595  | 0.001000  | 0.003000   | 0.000000  |
| 10       | 0.019169  | 0.001667  | 0.003000   | 0.000000   | 0.025071  | 0.002000  | 0.003333   | 0.000000  |
| 11       | 0.020693  | 0.003000  | 0.005000   | 0.000000   | 0.027679  | 0.010000  | 0.003000   | 0.000667  |
| 12       | 0.021960  | 0.007333  | 0.004000   | 0.000000   | 0.029911  | 0.012667  | 0.006000   | 0.000000  |
| 13       | 0.024560  | 0.750333  | 0.015667   | 0.000333   | 0.033188  | 0.260333  | 0.142333   | 0.000333  |
| 14       | 0.029062  | 20.701333 | 1.846667   | 0.000000   | 0.036770  | 4.724333  | 0.234667   | 0.000000  |
| 15       | 0.034087  | 32.719667 | 6.621333   | 0.000000   | 0.041239  | 9.780000  | 0.763333   | 0.000000  |
| 16       | 0.043082  | 42.219000 | 43.492667  | 0.000000   | 0.047123  | 14.693000 | 7.516667   | 0.000000  |
| 17       | 0.061107  | 49.871333 | 121.943333 | 0.000333   | 0.056466  | 19.267667 | 14.964000  | 0.000000  |
| 18       | 0.078949  | 59.154667 | 188.126333 | 0.001667   | 0.066673  | 23.464000 | 26.872000  | 0.001000  |
| 19       | 0.095207  | 67.687667 | 210.598667 | 0.048667   | 0.077708  | 27.271667 | 39.924000  | 0.012000  |
| 20       | 0.107233  | 72.490000 | 210.815333 | 1.030000   | 0.090564  | 30.790667 | 51.671667  | 0.324667  |
| 21       | 0.159159  | 80.448000 | 206.472000 | 26.694000  | 0.116798  | 35.640667 | 65.606000  | 3.887667  |
| 22       | 0.271559  | 87.775333 | 217.712667 | 96.369333  | 0.181934  | 42.309333 | 83.432333  | 15.458000 |
| 23       | 0.350072  | 93.836333 | 218.282333 | 129.834667 | 0.215615  | 48.359667 | 95.402667  | 23.139000 |
| 24       | 0.411254  | 99.526667 | 224.982667 | 134.548000 | 0.264914  | 54.315667 | 110.827000 | 34.401333 |

Widać na niej wyraźnie jak rozkłada się procent chybień dla rosnących rozmiarów tablicy dla obu wersji funkcji. Wyraźne różnice dla większych `n` można wyjaśnić dużą liczbą chybień.

Wnioski
---
### Czemu zmiana organizacji danych spowodowała przyspieszenie algorytmu wyszukiwania? Jak zmieniła się lokalność czasowa elementów przechowywanych w pamięci podręcznej? 
W momencie wyszukiwania w zwyczajnym algorytmie po załadowaniu środkowego elementu, do pamięci podręcznej zostają załadowane elementy na prawo od niego. Mogą znajdować się tam elementy z samego dołu drzewa wyszukiwań lub może się okazać, że wyszukujemy elementu na lewo od środkowego i wtedy wszystkie załadowane komórki będą bezużyteczne. Dodatkowo ładujemy oddalone od siebie elementy tablicy, co jest bardziej kosztowne.

Po ustawieniu poziomów drzewa liniowo, jeżeli rozmiar danego poziomu nie przekracza rozmiaru cache, to ładujemy też następny poziom (lub poziomy). Dzięki temu, jeśli nie uda nam się trafić w szukanego `x`, to element z kolejnego poziomu będzie już w pamięci podręcznej i mamy trafienie w cache.

Na niższych poziomach, prawdopodobieństwo trafienia elementu maleje, więc chcielibyśmy mieć tablicę posortowaną według poziomów, tak, żeby elementy poziomu były obok siebie, a nie porozrzucane po całej tablicy. 
### W jaki sposób zmiana kolejności instrukcji w ciele pętli zmienia IPC?  Czy  można  to  wytłumaczyć  posługując  się  programem llvm-mca?  
Zmiana kolejności zmienia IPC pokrywa się to z wydrukami llvm-mca, które przygotowałem (z parametrami: `llvm-mca -iterations=10000 -timeline -bottleneck-analysis`): 
pliki raportów znajdują się w `llvm_{0,1,2}.txt` - dla odpowiednich wariantów (kod tych wariantów jest przy wykresie IPC).

Na podstawie wydruków:
- wersja 2 (w której warunek `x==y` jest na samym końcu) charakteryzuje się najwyższym IPC, później mamy wersję 0, a najgorsza jest wersja 1,
- wersja 2 kompiluje się do 20 instrukcji, gdzie 0 i 1 ma ich 16,
- wersja 2 i 1 mają Data Dependecies na poziomie 10%, wersja 0 na poziomie 20%,
- gdy spojrzymy na Resource pressure to jest on najrównomierniej rozłożony w wersji 2.

Czyli wersja 2 lepiej wykorzystuje zasoby, rozkładając nacisk na różne instrukcje, jednocześnie ma więcej instrukcji, które wykonuje w podobnym czasie co wersja 0 i 1 (więc współczynnik IPC jest większy).

Finalnie jednak wersja 2 charakteryzuje się u mnie wysokim współczynnikiem chybień przewidywania skoków, a przez to wersja 0 (domyślna) dalej pozostaje dobra.

### Czy  użycie  instrukcji  wbudowanych  kompilatora«__builtin_expect» i «__builtin_prefetch» przynosi jakieś zyski?

`long __builtin_expect (long exp, long c)` - mówi kompilatorowi, że przewidujemy, że `exp` obliczy się do wartości `c`

Próbowałem ją zastosować w ten sposób (gdzie ustawiałem `c` na `0` lub `1`):
```c=
if(__builtin_expect((x == y), c))
      return true;
```
Nie zauważyłem jednak poprawy czasu działania programu po wykorzystaniu tej instrukcji wbudowanej. Zgodne jest to z tezą z wykładu, dotyczącą tego, że predyktory skoków we współczesnych procesorach są na tyle dobre, że ciężko programiście poprawić przewidywanie rozgałęzień w tak prosty sposób.

`void __builtin_prefetch(const void *addr, rw, locality)` - ładuje wcześniej do pamięci podręcznej pamięć z adresu `addr`, w celu zminimalizowania chybień. 
Wykorzystywane, jeśli wiemy, że z dużym prawdopodobieństwem będziemy wkrótce wykorzystywać daną pamięć.

Parametr  `rw` określa czy chcemy tylko czytać z pamięci, czy też do niej zapisywać. (w zadaniu tylko czytamy).

Parametr `locality` natomiast określa, jaka jest lokalność czasowa danych, np. jeśli `0` - to po dostępie, pamięć nie jest potrzebna i można ją wyrzucić z pamięci podręcznej, dla `3` trzymamy ją na każdym poziomie.

**Wykorzystanie** - przygotowałem 4 wersje ładujące następne poziomy drzewa wyszukiwań iterację (lub 2) wcześniej.

**wersja 0 **- bez prefetchingu

**wersja 1 **- ładuje następny poziom (trafimy w 1 z 2):
```c=
bool binsearch1(T *arr, long size, T x) {
  long iter = 0;
  while(iter < size) {
    T y = arr[iter];
    __builtin_prefetch(&arr[(iter << 1) + 1], 0, 3);
    __builtin_prefetch(&arr[(iter << 1) + 2], 0, 3);
    
    if(x == y)
      return true;
    
    iter <<= 1;
    iter += 1 + (y < x);
  }

  return false;
}
```
**wersja 2** - ładuje poziom niżej niż wersja1 (trafimy w 1 z 4):
```c=
    __builtin_prefetch(&arr[(iter << 2) + 3], 0, 3);
    __builtin_prefetch(&arr[(iter << 2) + 4], 0, 3);
    __builtin_prefetch(&arr[(iter << 2) + 5], 0, 3);
    __builtin_prefetch(&arr[(iter << 2) + 6], 0, 3);
```
**wersja 3** - połączenie wersji 1 i 2  (trafimy do 2 z 6)
```c=
    __builtin_prefetch(&arr[(iter << 1) + 1], 0, 3);
    __builtin_prefetch(&arr[(iter << 1) + 2], 0, 3);
    __builtin_prefetch(&arr[(iter << 2) + 3], 0, 3);
    __builtin_prefetch(&arr[(iter << 2) + 4], 0, 3);
    __builtin_prefetch(&arr[(iter << 2) + 5], 0, 3);
    __builtin_prefetch(&arr[(iter << 2) + 6], 0, 3);
```
Na pojedynczych testach można zauważyć spory spadek współczynnika chybień (o ~10% dla `L1`). 

![](https://i.imgur.com/5sL5uSI.png)
Jak widzimy na wykresie, prefetching pomaga dla większych `n`, natomiast wariant 2 i 3 są lepsze od wariantu 1 (z małą przewagą dla wariantu 2).

### Wnioski
Jak przedstawiłem, warto było przeprowadzić tę optymalizację. Może być ona szczególnie skuteczna, gdy wykonujemy wiele zapytań, a nasze dane rzadko się zmieniają, wtedy wykonanie funkcji tworzącej liniową reprezentację kosztuje mało w porównaniu do możliwych zysków.

Okazało się również, że wykorzystanie prefetchingu pozwoliło zyskać 1/10 sekundy już dla tablicy rozmiaru 2^25 - 1, oraz, że ciężko jest lepiej manualnie przewidywać skoki, niż robią to predyktory skoków.
