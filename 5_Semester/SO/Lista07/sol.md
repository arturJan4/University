# SO - Lista 7

# 1
![](https://i.imgur.com/UiktmNe.png)

### Na podstawie [3, 49.1] wyjaśnij słuchaczom różnicę między odwzorowaniami plików w pamięć (ang. memory-mapped files) i odwzorowaniami pamięci anonimowej (ang. anonymous mappings).
#### LPI 
![](https://i.imgur.com/u8Hkgix.png)


#### odwzorowanie plików w pamięć
Mapujemy bajt po bajcie dany obszar pliku (To może być plik zwykły, ale wystarczy nam deskryptor pliku i swobodny dostęp) bezpośrednio do pamięci wirtualnej. Po zmapowaniu mamy dostęp do zawartości pliku przez operację na bajtach w odpowiadającym regionie pamięci. Strony są ładowane automatycznie i leniwie.

#### odwzorowanie pamięci anonimowej
Pamięć nie posiadająca odpowiadającego pliku. Zaincjalizowana zerami.
Inaczej: mapowanie wirtualnego pliku które zawartość jest inicjalizowana zerami.

### Jaką zawartością wypełniana jest pamięć wirtualna należąca do tychże odwzorowań?

#### odwzorowanie plików w pamięć
Strony są ładowane leniwie z pliku (wtedy kiedy są wymagane).

#### odwzorowanie pamięci anonimowej
Zaincjalizowana zerami.

### Czym różni się odwzorowanie prywatne od dzielonego?
prywatne - modyfikacje nie są widoczne dla innych procesów, a przy odwzorowaniach w pamięć nie są zapisywane na dysku.
Używa mechanizmu (copy-on-write), który kopiuje strony, gdy chcemy pisać (ale mamy uprawnienia read-only), więc tworzymy nową stronę-kopię do zapisu, dla danego procesu, który ten zapis wykonuje. (początkowo więc te strony są dzielone)

dzielone - zmiany są widoczne dla innych procesów, które wspóldzielą odwzorowanie, zapis zmienia oryginalny plik.

### Czy pamięć obiektów odwzorowanych prywatnie może być współdzielona?
Tak, obszar może być współdzielony aż do próby zapisu (pozwalamy na odczyty), wtedy musi zostać wykonana kopia.

### Czemu można tworzyć odwzorowania plików urządzeń blokowych w pamięć, a znakowych nie?
urządzenia blokowe są buforowane i pozwalają na swobodny dostęp (można wykonać lseek)
znakowe natomiast adresują dane sekwencyjnie (należy wczytać całość)
Przy tworzeniu odwzorowań natomiast checemy mieć swobodny dostęp do pliku. (czytamy i ściągamy konkretne strony/obszary)

# 2
![](https://i.imgur.com/cQnMpUW.png)

### Scenariusze użycia (tabela 49-1)
![](https://i.imgur.com/qG0WpNp.png)

#### prywatne odwzorowanie pliku
zaincjalizowanie obszaru pamięci programu z zawartości pliku,

np. inicjalizacja sekcji `.text`, .`data` procesu z odpowiadających części pliku wykonywalnego lub biblioteki wspódzielonej .

#### prywatne odwzorowanie pamięci anonimowej
każde zawołanie `mmap()` tworzy nowe prywatne anonimowe odwzoroanie, które jest różne od innych (utworzonych przez ten sam lub inny proces).

główne użycie:
alokacje nowej pamięci (np. `malloc()` używa `mmap()`do alokowanie dużych bloków pamięci), pamięć zostaje wypełniona zerami.

#### współdzielone odwzorowanie pliku
wszystkie procesy mapujące ten sam region pliku, mają te se ame strony w pamięci (ale mogą być na różnych adresach wirtualnych). Modyfikacje zawartości modyfikują plik.

Dwa cele:
- pozwala na **memory-mapped I/O** czyli ładowanie programu do pamięci wirtualnej procesu i automatyczne zapisywanie do pliku po zmianie wewnątrz, jest to więc alternatywa dla `read()` i `write()` w komunikacji z plikiem.
- pozwala na szybką komunikację niepowiązanych ze sobą procesów współdzielących pamięć (fast IPC - szybka komunikcja międzyprocesowa)

#### współdzielone odwzorowanie anonimowe
podobnie jak wyżej, ale jest pewna różnica:
strony odwzorowanie nie są kopiowane przy zapisie (copy-on-write) co oznacza, że przy `fork()` dziecko i rodzic współdzielą strony z RAM.

pozwalają na fast IPC, ale tylko w powiązanych procesach

### Jak tworzyć mapowanie z użyciem mmap(2)?
```c=
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
```
- addr (zwykle NULL (%4096))
- len (długość mapowania zaokrąglona w górę do rozmiaru strony (4096))
- prot - ochrona pamięci (nie może kolidować z `mode` otwartego pliku)
- flags - widoczność mapowania
- fd - deskryptor pliku ze swobodnym dostępem

![](https://i.imgur.com/v4lYxZX.png)

z `mmap(2)`
![](https://i.imgur.com/JoWMi3i.png)
![](https://i.imgur.com/K35lo6A.png)

mówimy o rwx dla stron (w `pgd`) lub dla segmentów (w `vm_area_struct`) pamięci wirtualnej (nie dla pamięci fizycznej)

flagi (np. umożliwiające copy-on-write) sa dla całego segmentu

### Co się dzieje z odwzorowaniami po wywołaniu fork(2)?
![](https://i.imgur.com/7mNNpAP.png)

mapowanie oraz typ tego mapowania jest dziedziczony
### Czy wywołanie execve(2) tworzy odwzorowania prywatne czy dzielone?
![](https://i.imgur.com/XPY2hsp.png)
W większości prywatne, ale jeśli proces był zmapowany z dzielonymi objektami jak np. biblioteka standardowa C (`libc.so`), to te objekty są dynamicznie linkowe i mapowane do dzielonego obszaru pamięci wirtualnej.

### W jaki sposób jądro systemu automatycznie zwiększa rozmiar stosu do ustalonego limitu?
1) Odwołuje się do obszaru poniżej stosu
2) dostaje błąd strony
3) błąd strony zostaje obsłużony (jeśli nie przekroczono limitu rozmiaru)
4) stos zostaje powiększony

### Kiedy jądro wyśle sygnał SIGBUS do procesu posiadającego odwzorowanie pliku w pamięć [3, §49.4.3]?
Zwykle rozmiar odwzorowania to wielokrotność systemego rozmiaru strony, i odwzorawnie znajduje się w całości w ramach pliku.

próba dostępu do pamięci za "odwzorowaniem" spowoduje sygnał `SIGSEGV`

#### SIGBUS
![](https://i.imgur.com/FomFP0j.png)
Sytuacja jest bardziej skomplikowana gdy odwzorowanie jest dłuższe od pliku wspierającego.

W wyniku zaokręglenia do 4096 górna część strony jest nie mapowana do pliku (bo nie istnieją odpowiadające bajty), ale jest inicjalizowana zerami.
Będzie to pamięć współdzielona z innymi procesami, ale zapisy do niej nie będą zapisywane do żadnego pliku.

Ale gdy odwzorowanie jest jeszcze dłuższe (niż zaokrąglony rozmiar pliku) to próba dostępu do adresów w tych stronach powoduje powstanie `SIGBUS`, które ostrzega procesy o braku odpowiadającego odwzorowaniu pliku.

Jak wyżej próba dostępu poza 8192 bajt spowoduje `SIGSEGV`

#### Po co w ogóle robić to mapowanie?
jeśli użyjemy `ftruncate` lub `write` by rozszerzyć plik to wcześniej nieużywane fragmenty odwzorowania są użyteczne.

# 3
### Pojęcia:
**zbiór roboczy (working set)** - podzbiór zbioru rezydentego, część danych których program potrzebuje w danej chwilii
**zbiór rezydentny (resident set)** - ta część pamięci procesu która jest załadowana do RAM, zawiera stos, kopiec, pamięć współdzielona (załadowane do pamięci strony)


### polecenie
`cat /proc/$(pgrep Xorg)/status | egrep "Vm|Rss"`

`grep VmSize /proc/*/status | awk '{tot += $2} END{print tot}'`
`grep VmRSS /proc/*/status | awk '{tot += $2} END{print tot}'`

![](https://i.imgur.com/U6NPgNg.png)

## poszczególne pola na podstawie proc(5)
https://man7.org/linux/man-pages/man5/proc.5.html

- VmPeak : największy zapisany rozmiar pamięci wirtualnej
- VmSize: obecny rozmiar pamięci wirtualnej (suma przestrzenie procesów), wlicza również strony z `PROT_NONE`
- VmLck: rozmiar pamięci zablokowanej (przy pomocy wywołania systemowego `mlock` możemy zablokować częśc pamięci RAM'ie, gwarantujemy że te strony będą rezydentne w RAM'ie, nie mogą być swapowane)
- VmPin - rozmiar pamięci przypiętej (czyli stron które nie mogą zostać przeniesione bo coś wymaga bezpośredniego dostępu do fizycznej pamięci, w przeciwieństwie do VmLck nie dojdzie do page-fault bo strony nie zostaną przeniesione wewnątrz RAMU)
- VmHWM: największy zapisany rozmiar zbiory rezydentnego
- VMRSS - obecny rozmiar zbioru rezydentnego (zawiera strony read-only z bibliotek wspóldzielonych)
- RSSAnon: - rozmiar zbioru rezydentnego pamięci odwzorowanej anonimowo (inaccurate)
- RssFile: Rozmiar zbioru rezydentnego pamięci odzworowanej w plik (inaccurate)
- RssShmem - rozmiar współdzielonego zbioru rezydentnego (rópwnież prywatnego współdzielonego)
- VmData: - Rozmiar segmentu data (inaccurate)
- VmStk: - Rozmiar segmentu stack poczatkowego wątku w procesie (inaccurate
- VmExe: - Rozmair segmentu text, nie zawiera współdzielonych bibliotek, JIT wyjścia kompilatora (inaccurate)
- VmLib: - Rozmiar kodu współdzielonych bibliotek (rozmiar stron "executable" z odjętym VmExe)
- VmPTE: - rozmiar wpisów w tablicy stron 
- VmSwap - Rozmiar prywatnych anonimowych stron wyrzuconych na swap (inaccurate)

## Skrypt
-> test.py
-> `python3 test.py`

## skąd różnica?
Oba zbiory nie są rozłączne co sprawia że sumujemy wielokrotnie rozmiary mapujące te same obszary i otrzymujemy większą sumę niż wynik `vmstat -s`

Jeśli mamy dwa procesy, które współdzielą pamięć to liczymy podwójnie (np. `libc.so`)

# 4 (TODO)
![](https://i.imgur.com/DSg1NZD.png)

### Pojęcia:
**pomniejsza usterka strony (minor page fault)**
**poważna usterka strony (major page fault) **
**bufor stron (page cache)**

### Na podstawie slajdów do wykładu opisz algorytm obsługi błędu stronicowania w systemie Linux.

### Jakie informacje musi dostarczyć procesor, żeby można było wykonać procedurę obsługi błędu stronicowania?

### Do czego służą struktury jądra «mm_struct::pgd» i «mm_struct::mmap» zdefiniowane w pliku include/linux/mm_types.h? 
https://elixir.bootlin.com/linux/latest/source/include/linux/mm_types.h


### iedy jądro wyśle procesowi sygnał SIGSEGV z kodem «SEGV_MAPERR» lub «SEGV_ACCERR»?

### W jakiej sytuacji wystąpi pomniejsza usterka strony (ang. minor page fault) lub poważna usterka strony (ang. major page fault)? 

### Jaką rolę pełni w systemie bufor stron (ang. page cache)?

# 7
![](https://i.imgur.com/22YncJn.png)

### Pojęcia:
**zużycie procesora (CPU time)** - czas zużyty przez proces na wykonanie instrukcji (`user + sys`)
**czas przebywania w systemie (turnaround time)** - czas potrzebny do wykonania programu (`real`)

dla programów równległych user jest sumą z każdego wykorzystywanego procesora (może być większy od real)

### Porównanie zużycia
![](https://i.imgur.com/EzUNcSZ.png)

### Prawo Amdahla
Jeśli $P$ jest proporcją programu którą można zrównoleglić to 
$1 - P$ oznacza tą część której się nie da.

Wtedy przy wykorzystaniu $N$ procesorów maksymalne przyspieszenie wynosi:
$$\frac{1}{(1-P) + \frac{P}{N}}$$

przykładowo:
jesli $P=90%$ to $(1-P=10%/)$, więc iloraz może wynosić maksymalnie (przy liczbe procesorów $N$ dążącej do nieskończoności) 10.
Z tego powodu dużą częścią programowania równoległego jest zredukowanie komponentu $(1-P)$

### Wyjaśnienie różnic
W pierwszej wersji mamy jeden proces wykonujący wszystkie obliczenia.

W wersji drugiej:
Duża część algorytmu jest wykonywana równolegle przy delegacji zadań do podprocesów, dzięki temu realny czas jest ponad 3-krotnie mniejszy.

### Których elementów naszego algorytmu nie da się wykonywać równolegle?
funkcji: InsertionSort or Partition
Sortowanie byłoby nieopłacalne dla małych danych, gdyby miałosię wywoływać w podprogramach. (narzut Fork i rekursji)
Partition w tej postaci nie jest możliwy do zrównoleglenia.

# o projekcie
SGCHLD handler
czy ma przejść po wszystkim i pogrzebać
waitpid(-1, &status, WNOHANG) -> while z tym

`echo A | while true; do echo 'A'; sleep 1; done &`
`sleep 10 | while true; do echo 'A'; sleep 1; done &`
`cat | while true; do echo 'A'; sleep 1; done &` -> jeden sleep, a drugi running (job jest running)

cat próbuje czytać więc dostaje po łapach

SIGTTIN -> do grupy jest wysyłany (default: zatrzymaj się) 

`cat | cat`: randomowy fork

running -> sleeping -> stopped job check (wystarczy 1)

waitpid - sygnał
waitpid nie zwraca nic jak dziecko czyta z pustego pipe

ifdef READLINE error - jak go naprawić

monitorjob -> dojob (monitor w rodzicu)

kill_job

skąd wiemy jakie stringi