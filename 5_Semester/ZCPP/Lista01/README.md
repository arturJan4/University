# Treści - nowe elementy języka C++
## Zadanie 1 (1 pkt).
Sprawdź, czy w stosowanym przez Ciebie kompilatorze (co najmniej c++17) działają trójznaki (ang. trigraphs), takie jak na przykład `??-` co tłumaczy się na znak tyldy `˜`, itp. Co zrobić, aby kompilator właściwie zinterpretował występujące w programie trójznaki?

## Zadanie 2 (1 pkt).
Wypisz na standardowym wyjściu `std::out` surowy łańcuch znaków (ang. raw string) zawierający:

1.  adres naszego Instytutu (w pierwszej linii pełną nazwę Instytutu, w drugiej ulicę z numerem, w trzeciej kod pocztowy i miasto);
2.  ścieżkę bezwzględną do katalogu z programami użytkowymi w systemie Windows;
3.  różne sekwencje znaków cudzysłowia i nawiasów okrągłych (a w szczególności sekwencję `)"`).

## Zadanie 3 (2 pkt).
Stwórz alias dla typu będącego zbiorem `std::set<>` łańcuchów znakowych. Następnie zadeklaruj i zainicjalizuj taki zbiór używając jednolitej inicjalizacji. Na koniec przejdź po tym zbiorze pętlą _for_ dla zakresów (ang. range-based _for-each_ loop)) dedukując automatycznie typ elementów zbioru; wypisz w pętli wszystkie łańcuchy na standardowym wyjściu `std::cout`).

## Zadanie 4 (2 pkt).
Zdefiniuj silnie stypizowany typ wyliczeniowy dla kilku wybranych imion męskich i żeńskich, którego elementy będa typu `uint_16`. Następnie zdefiniuj funkcję, która jako argumenty przyjmuje komunikat typu `string` i imię odbiorcy zdefiniowanego wcześniej typu wyliczeniowego (funkcja może wypisywać komunikat personalnie skierowany do wskazanej osoby używając instrukcji _switch-case_).

## Zadanie 5 (1 pkt).
Zdefiniuj funkcję rekurencyjną, która będzie wyznaczała _n_-tą liczbę Lucasa. Funkcja ta ma przyjmować argument typu `uint32_t` i powinna automatycznie dedukować typ wyniku.

## Zadanie 6 (2 pkt).
Napisz program, który dla podanych współczynników równania kwadratowego wyliczy wyróżnik tego równania (często oznaczany symbolem Δ) i w zależności od jego wartości wypisze miejsca zerowe. Użyj do tego celu instrukcji warunkowej _if-else_ z lokalnym inicjalizatorem dla wyróżnika.

## Zadanie 7 (1 pkt).
Napisz program, który dla podanej daty wypisze ją z nazwą miesiąca (na przykład: 12 października 2021). Użyj do tego celu instrukcji wyboru _switch-case_ z lokalnym inicjalizatorem miesiąca w dacie.

