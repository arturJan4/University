Reszta z dzielenia przez 17
===
W pliku `mod17.s` zaprogramuj w asemblerze `x86-64` procedurę o sygnaturze
`int mod17(uint64_t)`, która liczy resztę z dzielenia danej liczby przez 17.
Cała trudność zadania polega na tym, że rozwiązanie **nie może** używać
instrukcji mnożenia ani dzielenia.

<sub>*Wskazówka:* Przypomnij sobie następującą własność reszty z dzielenia
przez 11: różnica sum cyfr (dziesiętnych) na parzystych i nieparzystych
pozycjach ma taką samą resztę z dzielenia przez 11 co cała liczba, np.
reszta z dzielenia 183716 przez 11 to 5, bo (8+7+6)-(1+3+1) = 16, a reszta
z dzielenia 16 przez 11 to właśnie 5. Okazuje się, że analogiczna własność
zachodzi w dowolnym systemie pozycyjnym, np. w systemie szesnastkowym łatwo
liczy się resztę z dzielenia przez 17.</sub>

### Ważne:

1. Można używać wyłącznie instrukcji arytmetyczno-logicznych poznanych na
   wykładzie i ćwiczeniach z wyłączeniem instrukcji mnożenia, dzielenia i
   podobnych.
2. Użycie instrukcji `div` lub `idiv` jest niedozwolone!
3. Modyfikowanie innych plików niż `mod17.s` jest niedozwolone!

### Pamiętaj:

1. Podpisz się w treści rozwiązania.
2. Nie zamykaj _Pull Request_ o nazwie _Feedback_!
3. W zakładce _zmienione pliki_ (ang. _changed files_) _Pull Request_ o nazwie
   _Feedback_ ma być widać wyłącznie treść Twojego rozwiązania!
