# Treści - iteratory strumieniowe i plikowe

## Zadanie 1 (2 pkt).
Odczytaj ze standardowego wejścia ciąg liczb rzeczywistych pooddzielanych białymi znakami. Używając iteratora strumieniowego `istream_iterator` odczytaj te liczby, zapisz w wektorze a następnie policz średnią arytmetyczną i odchylenie standardowe dla tego zbioru danych i wypisz wyniki na standardowym wyjściu z dokładnością do 3 miejsc po kropce dziesiętnej.

## Zadanie 2 (2 pkt).
Niech Φ(n) oznacza funkcję Eulera (tocjent), która dla każdej dodatniej liczby naturalnej zwraca liczbę liczb naturalnych nie większych od n i względnie pierwszych z n. Dla zadanej wartości k stablicuj kolejne wartości tocjenta Φ(1), Φ(2),…, Φ(k)
a następnie zapisz je do pliku `phi.txt`, używając iteratora strumieninowego `ostream_iterator` z separatorem w postaci średnika i spacji `"; "`.

## Zadanie 3 (2 pkt).
Napisz program, który sprawdzi czy w lokalnym systemie plików istnieją podane pliki lub foldery. Jeśli tak, to wypisz ich najważniejsze parametry (ścieżka kanoniczna, data ostatniej modyfikacji, rozmiar dla pliku itp.). Nazwy plików i folderów przekaż do programu poprzez argumenty wywołania.

## Zadanie 4 (2 pkt).
Napisz program, który wypisze zawartoś wskazanego folderu w lokalnym systemie plików. Jeśli podany przez użytkownika folder nie istnieje, to wypisz stosowną informację. Wypisując zawartość folderu posłuż się iteratorem `directory_iterator`.

## Zadanie 5 (2 pkt).
Napisz program, który policzy i wypisze sumę rozmiarów wszystkich plików we wskazanym folderze i jego podfolderach. Jeśli podany przez użytkownika folder nie istnieje, to wypisz stosowną informację. Analizując zawartość folderu i podfolderów posłuż się iteratorem