# SO - Lista 12

## Materiały
### [1, 2.3] - tannenbaum
### [2, 6.1 – 6.6] - silberschatz (os concepts)
### [3, 28, 31 i 32] - 3ez pcs

## 1
![](https://i.imgur.com/ZTsWENb.png)

### Pojęcia
**zmienne współdzielone** - wykorzystywane przez wiele wątków
**wyścig (data race)** - kilka wątków czyta zasoby i przynajmniej jeden zmienia jego stan

### Omówienie kodu
przekazujemy napisy przez argumenty wywołania programu
dla każdego napisu przydzielamy id i tworzymy wątek

wątek:
czyta id ze wskaźnika na myid 
uwaga: użycie słowa kluczowego `__thread` sprawia, że myid ma jedną instancję na każdy wątek (`thread-local`), dzięki czemu nie korzystamy z jednego myid

![](https://i.imgur.com/TZJAjqN.png)

### Polecenie

| zmienna | współdzielona | wyścig |
| ------- | ------------- | ------ |
| myid    | TAK           | TAK    |
| strtab  | TAK           | NIE    |
| vargp   | NIE           | NIE    |
| cnt     | TAK           | TAK    |
| argc    | NIE           | NIE    |
| argv[0] | TAK           | NIE    |

uwagi:
współdzielone:
strtab jest zmienną globalną więc jest dostępna dla wszystkich wątków
cnt -> statyczna zmienna lokalna (a więc o 1 instancji współdzielonej między wątkami)
argv[0] -> bo `strtab = argv`
myid -> przekazywany adres przez argumenty wątku

wyścigi:
cnt -> wypisujemy oraz zwiększamy cnt wewnątrz watku (a cnt jest static)
Oczekiwalibyśmy wypisania id w kolejności malejącej, a w rosnącej cnt, a w praktyce wypisywane wartości cnt mogą się powtarzać, bo w jednym momencie dwa różne wątki robią na cnt odczyt i zapis

## 2
![](https://i.imgur.com/sS8Aj0M.png)

### Pojęcia
**sekcja krytyczna** - taki fragment kodu, który powinien być jednocześnie wykorzystywany przez jeden wątek (a korzystanie przez wiele może powodować wyścigi)

**wyłączanie przerwań (ang. interrupt disable)** - wyłączamy obsługę przerwań w momencie gdy proces wchodzi do sekcji krytycznej, a po wyjściu ją przywracamy. Rozwiązuje problem sekcji krytycznej ponieważ jądro  zmienia proces poprzez przerwania.

**blokowanie drobnoziarniste (ang. fine-grained locking)** - sposób pracy polegający na wydzieleniu pojedyńczych struktur danych lub zmiennych i nałożenie na nich osobnych blokad. W każdej takiej sekcji przebywa tylko jeden wątek, ale wiele wątków może być w wielu różnych sekcjach krytycznych co pomaga przyspieszyć program.

### Wymień i uzasadnij założenia jakie musi spełniać rozwiązanie problemu sekcji krytycznej
#### Wzajemne wykluczenie (ang. mutal exclusion)
jeśli dany wątek jest w swojej sekcji krytycznej to żaden inny wątek nie może się w niej znajdować

#### Postęp
![](https://i.imgur.com/CWNVPCy.png)

jeśli żaden wątek nie jest w ścieżce krytycznej i istnieje wątek, który chce do niej wejść to tylko wątki, które nie są w *pozostałym* fragmencie kodu (po ścieże krytycznej) mogą decydować, który wątek wejdzie jako następny do ścieżki krytycznej

dodatkowo ten wybór nie może być odkładany w nieskończoność (chcemy, żeby wreszcie nastąpił jakiś postęp)

#### Ograniczone czekanie (ang. Bounded waiting)
istnieje ograniczenie/limit na liczbę wątków które mogą wejść do ścieżki krytycznej po tym gdy dany wątek poprosił o zgodę na wejście, ale jeszcze jej nie otrzymał

### Czemu w programach przestrzeni użytkownika do jej implementacji nie możemy używać wyłączania przerwań (ang. interrupt disable)?
Dla 1-CPU komputera:
wyłączamy obsługę przerwań -> z jakiegoś powodu nie możemy jej przywrócić -> system się zawiesza (proces zużywa 100% mocy CPU)
lub mamy spore spowolnienie obsługi przerwań

multi-core:
blokujemy przerwania dla jednego procesora, a wątki z innych dalej mogą namieszać we współdzielonej pamięci

### Odwołując się do Prawa Amdahla powiedz czemu programistom powinno zależeć na tym, by sekcje krytyczne były możliwie jak najkrótsze
![](https://i.imgur.com/CSZO2F4.png)

Jeśli $P$ jest proporcją programu którą można zrównoleglić to 
$1-P$ oznacza tą część której się nie da.

Wtedy przy wykorzystaniu $N$ procesorów maksymalne przyspieszenie wynosi:
$\frac{1}{(1-P) + \frac{P}{N}}$

przykładowo:
jesli $P=90%$ to ($1-P=10$), więc iloraz może wynosić maksymalnie (przy liczbe procesorów $N$ dążącej do nieskończoności) 10.
Z tego powodu dużą częścią programowania równoległego jest zredukowanie komponentu $(1-P)$

Chcemy więc, aby jak największa część kodu mogła wykonywać się równolegle (a długie ścieżki krytyczne to te fragmentu które nie dają się zrównoleglić)

## 6
![](https://i.imgur.com/zyBlkOx.png)

### Pojęcia
**wzajemne wykluczenie (mutual exclusion)** - jeśli dany wątek jest w swojej sekcji krytycznej to żaden inny wątek nie może się w niej znajdować

### omówienie kodu i idea
Chcielibyśmy by do linii 12 dotarł tylko jeden wątek, a drugi był zablokowany w pętli z linii 8.

Idea:
Wątek wchodzi do P, podnosi flagę dla swojego id, jeśli jest jego kolej to przechodzi do sekcji krytycznej (linijka 12).
w.p.p przechodzi `turn != id` i trafia do pętli `while(blocked[1-id])`, która będzie blokować dopóki drugi wątek nie zwolni swojej flagi, wtedy wątek ustala `turn=id`, by określić kolej i przechodzi do sekcji krytycznej.

### problem
Mamy dwa procesy: 0 i 1 o odpowiadającym id (0/1)

1. Proces 1 przechodzi do `turn = id` (linia 10), ale jeszcze jej nie wykonuje (może przejść bo początkowo `turn=0` i `blocked[0]=false`).
2. Proces 0 przechodzi do `while (turn != id)` i w tym momencie obie flagi blocked są podniesione.
3. `turn == 0` dla wątku 0, ponieważ proces 1 nie zdążył jeszcze nadpisać tej zmiennej. W takim razie proces 0 myśli, że nadeszła jego kolej, więc przechodzi dalej.
4. Proces 1 wykonuje linjkę 10 i przechodzi dalej.

Przy takim wywołaniu oba procesy wchodzą do sekcji krytycznej, więc takie rozwiązanie zawodzi.

## 7 
![](https://i.imgur.com/DlNeHV4.png)

### Idea i działanie
mamy flagi `blocked` dla obu wątków, które sygnalizują, że dany wątek chce przejść do sekcji krytycznej

```c=
shared boolean blocked [2] = { false, false }; // flagi sygnalizujące
shared int turn = 0; // tura

void P (int id) {
  while (true) {
    blocked[id] = true;
    turn = 1 - id;
    
    while (blocked[1 - id] && turn == (1 - id))
      continue;
    
    /* put code to execute in critical section here */
    blocked[id] = false;
    
  }
}

void main() { parbegin (P(0), P(1)); }
```

dla wątku 0:
```c=
while (true) {
    // podnosimy flagę
    blocked[0] = true;
    turn = 1; // przepuszczamy drugi wątek "przodem"
    
    // jeśli drugi watek czeka i to jego tura to wątek 0 czeka
    while (blocked[1] && turn == 1)
      continue;
    
    /* put code to execute in critical section here */
  
    // opuszczamy flagę
    blocked[0] = false;
  }
```

dla watku 1:
```c=
while (true) {
    // podnosimy flagę
    blocked[1] = true;
    turn = 0; // przepuszczamy pierwszy wątek "przodem"
    
    // jeśli pierwszy watek czeka i to jego tura to wątek 1 czeka
    while (blocked[0] && turn == 0)
      continue;
    
    /* put code to execute in critical section here */
  
    // opuszczamy flagę
    blocked[1] = false;
  }
```


### Poprawność dla założenia o wzajmnym wykluczaniu
Chcemy pokazać, że dwa wątki nie wejdą jednocześnie do sekcji krytycznej.

Mamy zmienną turn, która może przyjmować wartośc 0/1 współdzieloną miedzy oba wątki.
Wątek, gdy chce wejść do sekcji krytycznej to zgłasza to przez zapalenie flagi `blocked`.

Weźmy wątek 0 (dla 1 symetrycznie) i przejdźmy do pętli `while()` (bo dopiero tam jest sens przeprowadzać analizę), wtedy możliwe wartości blocked i turn to:
- `blocked: [1, 1], turn: 1` (wątek 1 jeszcze nie nadpisał turn) -> wątek 0 blokuje się aż do opuszczenia flagi `blocked[1]`, a wątek 1 przechodzi
- `blocked: [1, 1], turn: 0` (wątek 1 nadpisał turn) -> wątek 0 przechodzi, a wątek 1 blokuje się aż do opuszczenia flagi `blocked[0]`
- `blocked: [1, 0], turn: 1` (wątek 1 nie podniósł flagi) -> wątek 0 przechodzi do sekcji, a wątek 1 podnosi flagę i nadpisuje czyli: `blocked: [1, 1], turn: 0`, więc musi czekać w pętli `while` na opuszczenie flagi `blocked[0]`

W takim razie, warunek pętli `while` będzie spełniony tylko dla jednego z wątków, drugi może mieć zapaloną flagę, ale `turn` nie będzie wskazywać na niego. 
Dzięki temu tylko jeden z dwóch procesów będzie mógł jednocześnie znaleźć się w sekcji krytycznej. C.K.D

### Uwaga-ciekawostka
Jako, że współczesne procesory potrafią przestawiać instrukcje w celach optymalizacji wykorzystanie algorytmu Petersona na takich architekturach może skończyć się źle.