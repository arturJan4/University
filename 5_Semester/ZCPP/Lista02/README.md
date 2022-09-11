# Treści - sprytne wskaźniki
## Zadanie 1 (4 pkt).
Zdefiniuj prostą klasę zawierającą licznik typu `uint64_t`, początkowo ustawiony na wartość 1. W kasie tej, oprócz innych funkcjonalności, umieść wirtualny destruktor, który wypisze komunikat ze stanem licznika na standardowym wyjściu dla błędów.

Następnie stwórz _n_-elementową tablicę takich liczników i opakuj ją wskaźnikiem `unique_ptr`.

Napisz też funkcję, która wywoła się rekurencyjnie _m_ razy z argumentem będącym wskaźnikiem na taką tablicę (wskaźnik `unique_ptr` ustaw za pomocą przniesienia). W _i_-tym wywołaniu funkcja ta ma losowo wybrane elementy zwiększyć o _i_-tą z kolei liczbę naturalną.

Na koniec wywołaj tą funkcję, a po jej wywołaniu wypisz wartości wszystkich _n_ liczników w tablicy. Parametry _n_ i _m_ możesz ustalić arbitralnie.

## Zadanie 2 (4 pkt).
Zdefiniuj klasę opakowującą plik tekstowy `line_writer`. Obiekt takiej klasy ma przetrzymywać wskaźnik/referencję do strumienia plikowego `ofstream`. Zadaniem obiektów tej klasy będzie pisanie do pliku wiersz po wierszu. Czy klasa ta powinna zamykać strumień w destruktorze?

Dalej w programie głównym stwórz kilka wskaźników `shared_ptr` odnoszących się do tego samego obiektu plikowego. Niech każdy fragment programu posiadający taki własny wskaźnik zapisze w tym pliku swoje dane. Plik powinien zostać zamknięty dopiero, gdy wszystkie sprytne wskaźniki zostaną zlikwidowane.

## Zadanie 3 (2 pkt).
Przetestuj, kiedy wskaźnik `weak_ptr` będzie wskazywać na obiekt w pamięci, a kiedy stanie się wskaźnikiem wiszącym (po zwolnieniu zasobu przez wskaźnik macierzysty `shared_ptr`).
