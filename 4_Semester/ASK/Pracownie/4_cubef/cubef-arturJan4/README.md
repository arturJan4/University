Podnoszenie do sześcianu z zaokrąglaniem
===

W pliku `cubef.s` zaprogramuj w asemblerze `x86-64` procedurę o sygnaturze
`uint32_t cubef(uint32_t)`. Jej zadaniem jest podnieść do sześcianu liczbę
zmiennopozycyjną typu `float`, której reprezentację binarną umieszczono w
32-bitowym słowie typu `uint32_t`. Wynik należy zaokrąglić do najbliższej parzystej.
Zakładamy, że parametr procedury będzie taki, że wynik nigdy nie będzie 
niezerową liczbą zdenormalizowaną ani nie przyjmie wartości NaN.

### Ważne:

1. Można używać wyłącznie tych instrukcji poznanych na wykładzie i ćwiczeniach,
   które operujących na liczbach całkowitych.
2. Modyfikowanie innych plików niż `cubef.s` jest niedozwolone!

### Pamiętaj:

1. Podpisz się w treści rozwiązania.
2. Nie zamykaj _Pull Request_ o nazwie _Feedback_!
3. W zakładce _zmienione pliki_ (ang. _changed files_) _Pull Request_ o nazwie
   _Feedback_ ma być widać wyłącznie treść Twojego rozwiązania!
