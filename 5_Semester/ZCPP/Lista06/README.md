# Treści - iteratory i algorytmy
## Zadanie 1 (3 pkt).
Pojedyncza osoba jest opisana za pomocą iminia, nazwiska, wieku, wagi i wzrostu (zdfiniuj klasę reprezentującą osobę `person`). Dane o 11 osobach są zgromadzone w deku `deque<person>`. Wykonaj po kolei następujące czynności:

1.  posortuj osoby według współczynnika BMI (funkją porównującą niech będzie lambda); posortowaną grupę osób wypisz na standardowym wyjściu;
2.  osoby odchudziły się na obozie sportowym i straciły 10% swojej pierwotnej wagi (funkją modyfikującą niech będzie lambda); zmodyfikowaną grupę osób wypisz na standardowym wyjściu;
3.  podziel osoby na dwie grupy: ciężkie z wagą powyżej 100[kg] i lekkie z wagą niewiększą niż 100[kg] (użyj lambdy jako predykatu); wypisz grupę osób po podziale na standardowym wyjściu;
4.  ustaw osobę o środkowym w tej populacji wzroście na pozycji 5 (pośrodku listy); wypisz grupę osób po takiej modyfikacji na standardowym wyjściu;
5.  losowo poprzestawiaj między sobą pierwsze 5 osób a potem ostatnie 5 osób; wypisz grupę osób po takiej modyfikacji na standardowym wyjściu;
6.  wypisz osobę najstarszą i najmłodszą na standardowym wyjściu (nie korzystaj z sortowania danych).

## Zadanie 2 (2 pkt).
Pojedynczy punkt jest opisany za pomocą współrzędnych, koloru w postaci RGB i nazwy (zdfiniuj klasę reprezentującą punkt `point`). Dane o 17 kolorowych punktach na płaszczyźnie są zgromadzone w liście `list<point>`. Wykonaj po kolei następujące czynności:

1.  usuń z listy wszystkie punkty, których nazwy są dłuższe niż 5 znaków; wypisz pozostałe na liście punkty;
2.  policz ile jest punktów leżących w I, II, III i IV ćwiartce układu współrzędnych;
3.  posortuj punkty ze względu na ich jasność (luminancja koloru RGB jest określona wzorem 0.3⋅R + 0.59⋅G + 0.11⋅B); wypisz punkty po posortowaniu;
4.  policz ile jest ciemnych punktów, dla których luminancja ma warość poniżej 64; prznieś te punty do innej listy i wypisz je.

## Zadanie 3 (2 pkt).
Napisz funkcję, która zwróci najczęściej pojawiający się element w zbiorze danych oraz liczbę jego wystąpień. Dane to liczby całkowite z pewnego wąskiego zakresu umieszczone w wektorze `vector<int>`. Jeśli więcej niż jeden element pojawia się pojawia się taką samą maksymalną liczbę razy, to funkcja powinna zwrócić wszystkie je wszystkie - na przykład dla danych {1, 1, 3, 5, 8, 9, 5, 8, 8, 5} powinny zostać zwrócone dwie pary {5, 3} oraz {8, 3} (pierwsza pozycja w parze to wartość a druga to liczba wystąpień).

## Zadanie 4 (2 pkt).
Napisz progam, który oblicza i wyświetla histogram zawierający częstość występowania liter alfabetu angielskiego (bez rozróżniania małych i dużych liter) w zadanym tekście. Tekst pobierz z pliku tekstowego, którego nazwę przekażesz do progamu poprzez argumenty wywołania. Częstość występowania danej litery jest zdefiniowana jako proporcja liczby wystąpień tej litery w stosunku do wszstkich liter w tekście (częstość musi być określona na podstawie liczby liter a nie rozmiaru tekstu).

## Zadanie 5 (1 pkt).
Napisz funkcję, która wygeneruje wszystkie możliwe permutacje podanego napisu `string`.