# Treści - liczby pseudolosowe
## Zadanie 1 (1 pkt).
Zdefiniuj szablon funkcji, która losowo spermutuje zadaną tablicę obiektów. Każda permutacja ma być jednakowo prawdopodobna.

Uwaga: funkcję permutującą zdefiniuj samodzielnie, nie korzystaj z algorytmu `shuffle()`.

## Zadanie 2 (2 pkt).
Zdefiniuj własny rozkład prawdopodobieństwa, który będzie losował liczby z zadanego przedziału: liczby całkowite ze zbioru {a, ..., b-1} albo liczby rzeczywiste z przedziału [a, b). Liczby ze środka przedziału powinny się pojawiać rzadko a liczby zbliżone do brzegów zadanego przedziału często.

Uwaga: można wykorzystać rozkład `uniform_int_distribution<>` oraz `uniform_real_distribution<>` ale należy samodzielnie przekształcić otrzymane wartości aby spełniały warunki zadania.

## Zadanie 3 (3 pkt).
Napisz program, który wygeneruje 1000 losowych liczb z rozkładem:

1.  jednostajnym, używając `uniform_real_distribution`;
2.  dwumianowym, używając `binomial_distribution`;
3.  normalnym, używając `normal_distribution`.

Wygenerowane liczby zapisz w pliku .csv (dla każdego rozkładu w osobnym pliku). Zrób w arkuszu kalkulacyjnym wykresy dla danych wygenerowanych w taki sposób, aby sprawdzić poprawność zastosowanego rozkładu prawdopodobieństwa.

Z formatem pliku CSV można się zapoznać na przykład na Wikipedii:  
_https://pl.wikipedia.org/wiki/CSV_(format_pliku)_  
_https://en.wikipedia.org/wiki/Comma-separated_values_

## Zadanie 4 (4 pkt).
Napisz program, który wygeneruje losowy tekst złożony tylko z małych liter alfabetu angielskiego i spacji (bez znaków interpunkcyjnych). Długość tekstu oraz nazwę pliku .txt do zapisania tekstu podaj poprzez argumenty wywołania progamu. Litery w tym tekście mają się pojawiać z częstotliwością zgodną ze statystyką podaną w [tabelce](http://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html) (rozkład taki musisz więc samodzielnie zdefiniować/zaprogramować). Kolejne słowa w tekście mają być odzielone pojedynczymi spacjami. Każde słowo ma mieć losową długość z zakresu od 1 do 12 liter a długości te mają być wybierane zgodnie z rozkładem dwumianowym.