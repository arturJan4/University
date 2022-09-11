# Treści - metaprogramowanie

## Zadanie 1 (1 pkt).
Wykorzystując metaprogramowanie zdefiniuj szablon obiektu funkcyjnego, pozwalającego obliczyć na poziomie kompilacji _n_-tą liczbę Lucasa dla liczby naturalnej `n ≥ 0`. Funkcja powinna działać (w trakcie kompilacji) w liniowym czasie `O(n)`.

## Zadanie 2 (2 pkt).
Wykorzystując metaprogramowanie zdefiniuj szablon obiektu funkcyjnego, pozwalającego obliczyć na poziomie kompilacji współczynnik dwumianowy `(n po k)` dla liczb naturalnych `0 ≤ k ≤ n`. Funkcja powinna działać (w trakcie kompilacji) w liniowym czasie `O(n)`.

## Zadanie 3 (1 pkt).
Wykorzystując metaprogramowanie zdefiniuj szablon obiektu funkcyjnego, pozwalającego obliczyć na poziomie kompilacji największy wspólny dzielnik _`NWD(a, b)`_ dla liczb naturalnych `a, b ≥ 1`_ dla naturalnych liczb `0 ≤ k ≤ n`. Funkcja powinna działać (w trakcie kompilacji) w logarytmicznym czasie _`O(log a + log b)`.

## Zadanie 4 (2 pkt).
Wykorzystując metaprogramowanie zdefiniuj szablon funkcji liczącej iloczyn skalarny dwóch wektorów:  
`template<size_t N> double inner(double *x, double *y);`  
Parametrem szablonu ma być dlugość mnożonych wektorów.  
Zmodyfikuj poprzedni szablon funkcji liczącej iloczyn skalarny w taki sposób, aby drugim parametrem był typ danych:  
`template<size_t N, typename T = double> T inner(T *x, T *y);`