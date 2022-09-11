# Treści - liczby zespolone
## Zadanie 1 (2 pkt).
Zdefiniuj funkcję obliczającą wartość wielomianu zespolonego. Współczynniki wielomianu umieść w kolekcji `vector<complex<double>>`. Wykorzystaj do tego funkcję accumulate i labdę (z modyfikatorem mutable).

## Zadanie 2 (3 pkt).
Zdefiniuj funkcje pracujące na liczbach zespolonych, które będą wyliczać wartość:

1.  funkcji gamma Eulera Γ(z)

-   i odwrotności tej funkcji 1/Γ(z)

Symbol γ reprezentuje stałą Eulera-Mascheroniego wynoszącą około 0.5772156649. Funkcje te mają liczyć wartość funkcji w zadanym punkcie zespolonym z określoną dokładnością (liczba iteracji).

## Zadanie 3 (5 pkt).
Zdefiniuj funkcję pracującą na liczbach zespolonych, które będą wyliczać wartość funkcji dzeta Riemanna ζ(z)
Szereg ten jest zbieżny dla takich z, których część rzeczywista jest >1
Funkcja ta ma liczyć wartość funkcji w zadanym punkcie zespolonym z określoną dokładnością (liczba iteracji).

Policz i stablicuj wartości tej funkcji na _prostej krytycznej_ R(z)=0.5

z hipotezy Riemanna (musisz użyć innego wzoru). Wygenerowane liczby zapisz w pliku .csv (w osobnych kolumnach części rzeczywiste i urojone). Następnie zrób w arkuszu kalkulacyjnym podwójny wykres dla danych wygenerowanych w taki sposób (nałożone na siebie wykresy dla części rzeczywistych i urojonych).

Z formatem pliku CSV można się zapoznać na przykład na Wikipedii:  
_https://pl.wikipedia.org/wiki/CSV_(format_pliku)_  
_https://en.wikipedia.org/wiki/Comma-separated_values_