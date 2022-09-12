# SO - Lista 10

### APUE  [11.1 – 11.5, 12.8 – 12.10]
### 3EP [26, 27 i 33]

## 1
![](https://i.imgur.com/YCwoI2d.png)

### Czym różni się przetwarzanie równoległe (ang. parallel) od przetwarzania współbieżnego (ang. concurrent)? 
![](https://i.imgur.com/uUnPefl.jpg)

**przetwarzanie równoległe (parallel)** - zadania działają w tym samym czasie (dokładnie tym samym kwancie czasu), np. procesor wielordzeniowy

**przetwarzanie współbieżne (concurrent)** - wykonywane zadania przeplatają się czasem aktywnego wykonywania, np. procesor symulujący równoczesne wykonanie przy pomocy `time-slicing` (zmienia kontekst i przydziela fragmenty czasu)

### Czym charakteryzują się procedury wielobieżne (ang. reentrant)? 
**Procedura wielobieżna** - procedura, której możemy wołać z wielu miejsc i będzie działać współbieżnie. Wykonywanie procedury może zostać przerwane i może ona zostać bezpiecznie zawołana ponownie ("re-enter") zanim poprzednie jej wywołania się zakończą.
czyli kod takiej procedury:
- nie powinien posiadać globalnego zmienialnego stanu bez synchronizacji
- nie powinien modyfikować sam siebie
- wołać procedur które nie są wielobieżne

https://en.wikipedia.org/wiki/Reentrancy_(computing)

wcześniej mówiliśmy o funkcjach wielobieżnych które dodatkowo blokowały niektóre sygnały tzw: `async-signal safe` -> bezpieczne w obsłudze sygnałów

To że procedura jest współbieżna nie implikuje że jest thread-safe.

### Podaj przykład procedury w języku C: 
**Procedura wątkowo-bezpieczna** - współdzieli pamięć z innymi wątkami w taki sposób by nie zachodziły pomiędzy nimi niechciane interakcje, można ją wykonywać przez wiele wątków współbieżnie i nie zajdzie wyścig.

#### pre - nie wielobieżna, nie wątkowo-bezpieczna
```c=
int sum;
int add1(int to) {
	sum = to;
	return sum + 1;
}
```

jeśli w momencie `return` dostaniemy przerwanie a obsługa sygnałów wywoła `add1` z inną wartością to zmieni wartość `sum` i po powrocie do oryginalnego wywołania `sum` będzie miało złą wartość.

Wiele wątków ma dostęp do sum, nie jest to więc procedura wątkowo bezpieczna.

#### a) wielobieżnej, ale nie wątkowo-bezpiecznej (ang. thread-safe)
```c=
int sum;
int add1(int to) {
	sum = to;
	return to + 1;
}
```
sum = 4
1) add(1)
2) sum = 1
3) przerwanie -> add1(42)
4) sum = 42
5) return 43
6) powrót do add(1)
7) return 2

czyli jest współbieżna, ale dalej nie jest bezpieczna wątkowo

#### b) wątkowo-bezpiecznej, ale nie wielobieżnej
```c=
thread_local int sum;
int add1(int to) {
	sum = to;
	return sum + 1;
}
```
https://www.gnu.org/software/libc/manual/html_node/ISO-C-Thread_002dlocal-Storage.html
`thread_local` - oznacza, że zmienna tworzona gdy wątek startuje i sprzątana po zakończeniu wątku

#### oba 
```c=
int add1(int to) {
	return to + 1;
}
```


### Kiedy w jednowątkowym procesie uniksowym może wystąpić współbieżność?
np. przy obsłudze sygnałów w procedurze obługi błędów, asynchroniczna obsługa I/O (kernel threads)

## 2
![](https://i.imgur.com/8Nw3uyT.png)


### Pojęcia

#### Zakleszczenie (deadlock)
Wątki czekają na siebie nazwajem (na zwolnienie blokady). (wątek A czeka aż B skończy obecną operację, wątek B czeka aż A skończy obecną operację). Program nigdy się nie sdkończy.

#### Uwięzienie (livelock)
Wątki zatrzymuja się by umożliwić działanie innym (i np. powstrzymać deadlock'a), ale robią to naraz i przez to blokują się nazwajem. Stan się zmienia, ale dalej jest blokujący.

#### Głodzenie (starvation)
Mimo postępu innych wątków pewna konkretna grupa nigdy nie będzie miała dostępu do zasobu, którego potrzebuje.

### Przykład w ruchu ulicznym

Zakładamy, że wszystkie samochody jadą prosto
#### Zakleszczenie (deadlock)
![](https://i.imgur.com/mQrixv7.png)
pojazdy stoją i nie mogą się ruszyć ze względu na zablokowany pojazd z naprzeciwka

#### Uwięzienie (livelock)
![](https://i.imgur.com/mwC5QhE.jpg)
pojazdy wstępnie ustępują pierwszeństwa pojazdowi po prawej stronie, po pewnym czasie by zapobiec deadlockowi wszystkie ruszają, a wtedy by zapobiec kolizji zatrzymują się i cofają na początkowe pozycje.

#### Głodzenie (starvation)
![](https://i.imgur.com/G0qKSQx.png)

Nieskończony ciąg zielonych samochodów jedzie drogą z pierwszeństwem.
Jest czyniony jakiś postęp, ale żółte samochody nigdy nie przejadą.

### Wykrywanie i usuwanie zakleszczeń
Tworzymy graf zasobów:
zasoby - wierzchołki grafu
zapotrzebowanie - krawędzie
wykrycie cyklu w takim grafie oznacza możliwość zakleszczenia

Resource-Allocation Graph
![](https://i.imgur.com/N4GcTGr.png)

![](https://i.imgur.com/rHWrqSZ.png)


1) Zabieramy tymczasowo dany zasób procesowi w cyklu - wywłaszczenie
2) Przywracamy stan procesu sprzed zakleszczenia i powtarzamy licząc, że tym razem do niego nie dojdzie (rollback) -> jeśli występują rzadko to dobre rozwiązanie
3) zabicie któregoś procesu

### Zapobieganie zakleszczeniom
na podstawie: https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/7_Deadlocks.html

#### Mutual Exclusion - wzajemne wykluczenie
po prostu nie dajemy wyłącznego dostępu do zasobu (np. jest read-only)

nie zawsze jest to możliwe

#### Hold and Wait - trzymaj i czekaj
nie chcemy żeby proces trzymał jakiś zasób i czekał na inny (bo wtedy powoduje blokowanie)

możliwości:
- wszystkie wątki wołają zasób jednorazowo (za każdym razem) -> drogie, bo np. zasób potrzebny jest pod koniec działania programu
- przed wzięciem nowego zasobu zwróć poprzednie, a potem odzyskaj poprzednie wraz z nowym w jednym zapytaniu -> problem jeśli wykonamy częściowe operacje na jakimś zasobie i go zwalniamy

obie metody mogą doprowadzić do zagłodzenia jeśli proces potrzebuje "popularnych" zasobów

#### No Preemption - bez wywłaszczenia
wywłaszczamy alokacje zasobów procesu

możliwości:
- jeśli proces musi czekać na dostęp do zasobu to wywłaszczamy wszystkie jego poprzednie zasoby, co sprawia że musi on w jednym zapytaniu uzyskać do nich dostęp wraz z nowym zasobem
- jeśli czekamy na niedostępny zasób to kernel szuka innych procesów, które mają ten zasób i je wywłaszcza

obie metody są aplikowalne do zasobów, których stan jest łatwo zapisać (np. rejestry i pamięćm, ale nie drukarka)

#### Circular Wait - cykliczne czekanie
numerujemy zasoby i ustalamy ścisły porządek wybierania zasobów.
np. by dotsać zasób $R_j$ proces musi zwolnić wszystkie zasoby $R_i$ takie że $i \geq j$

## 3
![](https://i.imgur.com/zpS7Chr.png)


### Pojęcia
**sytuacja wyścigu** - wiele wątków pracuje na współdzielonej pamięci i wynik zależy od tego w jakiej kolejności będą przeplatać się ich wykonania

zakładamy że mamy `k` wątków

### wyznaczenie minimum
1) wszystkie k wątków wchodzi do `total()` i ładują do swoich rejestrów tally=0
2) wątki oprócz 1 i 2 wykonują pętlę `for`
3) wątek 1 wykonuje iteracje aż do `count == (n-1)`
4) wtedy wątek 2 wykonuje wykonuje pierwszą iterację nadpisując dzieloną wartość tally ($tally = 1$)
5) wątek 1 wczytuje $tally=1$
6) wątek 2 wykonuje resztę iteracji i się kończy
7) wątek 1 wykonuje ostatnią iterację pętli (`count==n`) i $tally = 1 + 1 = 2$ 

### wyznacznie maksimum
Wątki wykonują się po kolei w całości wtedy $total = kn$

## 5
![](https://i.imgur.com/NFgiPtG.png)


### Co nieoczekiwanego może wydarzyć się w wielowątkowym procesie uniksowym gdy:

#### Jeden z wątków zawoła funkcję fork(2) lub execve(2) lub exit_group(2)?
![](https://i.imgur.com/6J1aFuW.png)

Proces dziecka będzie miał tylko jeden wątek (wołający funkcję), reszta wątków umiera, co może być problematyczne jeśli w tych wątkach mamy ustawiono blokady (muteksy). Dane otoczone takimi blokadami mogą być wtedy nie do odzyskania.

![](https://i.imgur.com/UDQzwQN.png)
`execve` podmienia cały proces, a nie wątek

`exit_group` - exit all threads in a process
w przeciwieństwie do  `_exit(2)`, który zamyka tylko wołający wątek.

#### proces zadeklarował procedurę obsługi sygnału «SIGINT», sterownik terminala wysyła do procesu «SIGINT» – w kontekście którego wątek zostanie obsłużony sygnał?
![](https://i.imgur.com/vjb4Tu4.png)

Jądro wybiera który wątek obsłuży sygnał, nie jest to możliwe do przewidzenia co w konsekwencji możę powodować przerwanie wątku w trakcie jakichś kluczowych fragmentów działania.

są sygnały które nie wysyłamy do grupy procesów a do wątków (`int pthread_kill(pthread_t thread, int sig)`)

można zdefiniować wątek do obsługi sygnałów poprzez użycie `pthread_sigmask`

#### określono domyślną dyspozycję sygnału «SIGPIPE», a jeden z wątków spróbuje zapisać do rury pipe(2), której drugi koniec został zamknięty?
Skoro `pipe(2)` koniec jest współdzielony (jako deskryptor), to zamknięcie w jednym wątku zamyka we wszystkich.

![](https://i.imgur.com/mDhoQSD.png)
czyli piszący wątek dostanie sygnał `SIGPIPE`, a write zwróci błąd `EPIPE`

a skoro:
![](https://i.imgur.com/XwRL2he.png)
to proces zginie.

#### czytamy w wielu wątkach ze pliku zwykłego korzystając z tego samego deskryptora pliku?
Może wystąpić problem z przestawianiem kursora i odczytem, ponieważ są to dwa wywołania, które mogą się przeplatać na różnych wątkach, a kursor jest współdzielony.
Będziemy wtedy czytać w obu wątkach ten sam fragment tekstu. (np. dwa wątki czytają, dwa przesuwają wskaźnik i znowu czytają, zamiast przesuwa 1, czyta 1, przesuwa 2, czyta 2)


można użyć zamiast tego atmowych `pread` i `pwrite`
![](https://i.imgur.com/8QuQPjN.png)
![](https://i.imgur.com/BqGvlj9.png)