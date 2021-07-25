=========Pomysł==========
Posłużę się rozwiązaniem zad2 z listy 1, gdzie należało O(logn) policzyć popcount.

"Rozsmarowujemy" pierwszą napotkaną jedynkę idąc od lewej strony na bity po prawej.
Potem wykorzystujemy popcount do policzenia pozycji tej jedynki. 

=========================
np:
0000 0000 0101 1011 
0000 0000 0111 1111

Wtedy mamy:
liczba zapalonych bitów - p (7)
długośc słowa - n (16)
liczba wiodących zer - (n - p) (9)

=========================
Jak "rozsmarować" tę jedynkę?
- przy pomcy masek 
t = t | t >> 1
t = t | t >> 2
t = t | t >> 4
t = t | t >> 8
t = t | t >> 16
t = t | t >> 32
W najgorszym przypadku '1' bedzie wedrować z 64 bitu do 64 -> 63 -> 61 -> 57 -> 49 -> 33 -> 1 do 1 bitu.
