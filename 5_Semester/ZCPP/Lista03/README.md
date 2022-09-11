# Treści - czasomierze
## Zadanie 1 (1 pkt).
Wypisz najmniejszą i największą wartość jaką można zapisać w typie `long long int`. Na ilu bitach jest ta liczba zapisywana i ile to będzie cyfr dziesiętnych?

## Zadanie 2 (1 pkt).
Jaka jest najbliższa 0 liczba dodatnia dla typów `float` i `double`? Jakie są maksymalne wartości zapisywane w tych typach? Jaka jest różnica pomiędzy 1 a najmniejszą liczbą >1 w tych typach?

## Zadanie 3 (2 pkt).
Zdefiniuj początkowe liczby harmoniczne posługując się statyczną arytmetyką liczb wymiernych z wykorzystaniem szablonu `ratio`. Jaką największą liczbę harmoniczną udało Ci się zdefiniować?

## Zadanie 4 (3 pkt).
Zdefinuj szablon funkcji, które przeniesie wartość ze wskazanego obiektu do innego obiektu. Uwzględnij dwa aspekty: po pierwsze obiekt źródłowy może być zadany przez wartość/referencję albo przez wskaźnik (rozróżnij te dwa przypadki za pomocą cechy typowej `is_pointer`), a po drugie obiekt docelowy ma być wskazany przez referencję niekoniecznie tego samego typu (ustal możliwość konwersji za pomocą cechy typowej `is_convertible`)

## Zadanie 5 (3 pkt).
Stwórz macierze o rozmiarach odpowiednio 100×100, 1000×1000 i 10000×10000 i wypełnij je losowymi wartościami z zakrsu od 0.5 do 2.0. Następnie podnieś do kwadratu każdą z tych macierzy mierząc czas wykonania tych operacji za pomocą obiektu `duration`. Dla małych macierzy powtórz operację wielokrotnie a potem zmierzony czas podziel przez tą wielokrotność. Do pomiaru czasu użyj czasomierzy opartych na zegarze `high_resolution_clock`.
