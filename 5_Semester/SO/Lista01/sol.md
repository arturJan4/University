# SO - Lista 1
Arpaci-Dusseau: Processes, Process API, Address Spaces
Tanenbaum (wydanie czwarte): 2.1, 10.3, 11.4

## Materiały
### Processes
### Process API
### Address Spaces
### Tanenbaum 2.1
### Tanenbaum 10.3
### Tanenbaum 11.4

## Skrypt
## 1 
![](https://i.imgur.com/3Hz2qbb.png)


### Pojęcia

**Rodzic-dziecko** - rodzic - proces który utworzył dziecko za pomocą `fork`

**indentyfikator procesu** - PID, unikalna liczba przypisana do procesu.
Używane np. do `wait` lub `kill`

**indentyfikator grupy procesów** - PGID, dziedziczone po rodzicu. Dziecko może utworzyć własną grupę procesów i wtedy PID == PGID. Używane do np. wysyłania do całej grupy procesów

**indentyfikator rodzica** - PPID

**indentyfikator właściciela** - UID, proces ma takie same prawa do plików jak właściciel

**wątek jądra** - lekki proces, asynchroniczny, działający w kernel-mode, niezwiązane z procesami użytkownika. Na liście procesów oznaczone nawiasami kwadratowymi i PPID = 2

**hierarchia procesów** - procesy posiadają proces nadrzędny

### Identyfikacja
```bash=
ps -eo user,pid,ppid,pgid,tid,pri,stat,wchan,cmd
```

![](https://i.imgur.com/D0AhcEL.png)

#### Kto jest rodzicem procesu init?
PPID=0 dla init, 0 - kernel scheduler,
init jest utworzony w boot-time "nie ma" rodzica

#### Które to wątki jądra?
oznaczone [] oraz PPID=2

### Jakie jest znaczenie znaków w kolumnie STAT
```bash=
man ps
```

![](https://i.imgur.com/f4MG70c.png)


### Drzewiasta hierarchia
```bash=
pstree
```

![](https://i.imgur.com/Te9dWdq.png)


#### Które są wątkami?
Te oznaczone liczba_wątków*[{nazwa_wątku}]

bez wątków jądra
ps -f -N --ppid=2 --pid=2

## 2 -> jakieś trudniejsze
![](https://i.imgur.com/L80ZOD2.png)


### Jak jądro systemu reaguje na sytuację kiedy proces staje się sierotą?
rodzic przejmuje kontrolę
**sierota**

### W jaki sposób pogrzebać proces, który wszedł w stan zombie?
to robi rodzic wait'em, albo waitpid
**zombie**

#### Czemu proces nie może sam siebie pogrzebać? 
chcemy żeby ktoś odczytał kod powrotu

dowolny wątek może pogrzebać inny

### Modyfikacja waitpid
Zauważ, że proces może, przy pomocy waitpid(2), czekać na zmianę stanu wyłącznie swoich dzieci.

**stan**

Co złego mogłoby się
stać, gdyby znieść to ograniczenie?

#### a - dziecko może czekać na zmianę stanu swojego rodzica
rodzic czeka na dziecko, a dziecko na rodzina

#### b - wiele procesów oczekuje na zmianę stanu jednego procesu
kto ma go pogrzebać (i otrzymać kod powrotu)
struktura jest drzewiasta

"tego nie ma w wątkach"

Wskazówka: Proces wykonujący w jądrze implementację wywołania systemowego _exit(2) nie może zwolnić stosu jądra, na którym się wykonuje. Kto zatem musi to zrobić?

## 3 
![](https://i.imgur.com/PX9PJXf.png)

### Do czego służy proc?
Proc to pseudosystem plików, który jest interfejsem do struktur danych jądra. Zazwyczaj w `/proc`. Większość "plików" w nim zawartych jest tylkko do odczytu

`/proc/PID` - informacje o procesie z danym PID

`hd` - by pokazać binarnie

### wydruk /proc/pid
`ls /proc/8283/`

![](https://i.imgur.com/mfdu0ta.png)

/proc/self -> symbolic link (każdy proces widzi tam co innego) 

### plik
**argumenty programu** - przekazywane przy wywołaniu:
`argc` - liczba argumentów
`argv` - tablica wskaźników na string (argv[0] - nazwa programu)

```c=
int main(int argc, char *argv[])
```

plik w: `/proc/PID/cmdline`

`ls -l /proc/PID/fd` -> deskryptory plików
`ls -l /proc/self/fd | cat`


**zmienne środowiskowe** - nazwana wartość zawierająca ciąg znaków zarządzana przez shell. Przekazywane niejawnie, dziedziczone po rodzicu, chyba, że ten zmieni wartości przy tworzeniu dzeicka

wartośći sprawdzamy poprzez: `echo $VAR`, np. `echo $PATH`

plik w: `/proc/PID/environ`

### Znaczenie pól statusu
**Uid**
**Gid**
**Groups** - lista grupuzupełniających
**VmPeak** - największy rozmiar pamięci wirtualnej
**VmSize** - aktualny rozmiar pamięci wirtualnej
**VmRSS** - rozmiar pamięci należącej do procesu w pamięci głównej (RAM)
Resident set size.  Note that the value here is the sum of RssAnon, RssFile, and RssShmem.  
This value is inaccurate
**Threads** - liczba wątków w danym procesie
**voluntary_ctxt_switches** - liczba dobrowolnych context switchy
**nonvoluntary_ctxt_switches** - liczba przymusowych context switchy

## 4 
![](https://i.imgur.com/FW5L6JM.png)

`lsof` - Służy do wyświetlania listy otwartych plików oraz programów które ich używają.

`lsof /tmp/.X11-unix/*`
![](https://i.imgur.com/P62xNNK.png)

`pmap 2886`
![](https://i.imgur.com/V8dKfR0.png)

te mapowania są też w /proc/PID/maps:
`cat /proc/2886/maps | grep stack`
![](https://i.imgur.com/CySaRhH.png)

`vim /proc/2886/maps -> /heap`
![](https://i.imgur.com/IA6FmEY.png)

### Obszary 
stos - [stack]

sterta - [heap]

pamięć anonimowa [anon] - nie powiązana z plikiem

segmenty programu - "Xorg" - spójne bloki pamięci o jednolitym przeznaczeniu i atrybutach z punktu widzenia procesu ładowania i uruchamiania programu

pliki odwzorowane w pamięć - ".so" - mapuje plik lub jego część do przestrzeni adresowej, wtedy czytanie i zapisywanie do pliku to operacje na pamięci. `mmap()`, wykorzystywane również do współdzielenia pamięci pomiędzy procesami

### Znaczenie kolumn:
**Address** - początkowy adres mapowania

**Kbytes** - rozmiar w KB mapy

**Mode** - pozwolenia: read, write, execute, mapping (p/s)
private/shared - jeśli jest ustawione p to zapisy do tego obszaru pamięci nie będą widoczne dla innych procesów (co może powodować kopiowanie stron więc stąd inna nazwa "copy on write")

**Mapping** - plik na jaki zmapowana jest pamięć, lub specjalne mappingi: [anon], [stack], [heap], [vdso], [vsyscall]

## 5 
![](https://i.imgur.com/UT6Nerf.png)

Zasoby plikopodobne - procesu, urzadzenia, gniazda itp. zarządzane przez kernel ale widnieją jako przedmioty w systemie plików i można dostać się do nich przez ściężkę. Można z nich czytać/do nich pisać jak do zwykłych plików.

`lsof -p 25859`

### kolumny
**COMMAND** - co uruchomiło proces

**PID**  - id procesu

**USER** - właścicel procesu

**FD** - numer deskryptora
cwd current working directory; 
Lnn library references (AIX); 
err FD information error (see NAME column); 
jld jail directory (FreeBSD); 
ltx shared library text (code and data); 
itd.

**TYPE** - typ node np:
DIR - katalog
DEL - usunięty, ale zmappowany plik
REG - plik zwykły
FIFO - FIFO special file (potok)
IPv4/IPv6 - socket IPv4/IPv6
or ''ax25'' for a Linux AX.25 socket;
or ''inet'' for an Internet domain socket;
or ''lla'' for a HP-UX link level access file;
or ''rte'' for an AF_ROUTE socket;
or ''sock'' for a socket of unknown domain;
or ''unix'' for a UNIX domain socket;
or ''x.25'' for an HP-UX x.25 socket; 

**DEVICE** - numer urządzenia

**SIZE/OFF** - rozmiar/offset

**NODE** - numer węzła/pliku

**NAME** - mount point

plik zwykły - plik na dysku
`-` dla oznaczenia plików zwykłych
`d` dla oznaczenia katalogów
`c` dla oznaczenia plików specjalnych
`l` dla oznaczenia łączy symbolicznych

### inne pojęcia

**katalog** - logiczna struktura organizacji danych na nośnikach danych. Katalog może zawierać pliki i kolejne katalogi. Katalog jest nieodłącznie związany z systemem plików i jest on fizycznie przechowywany na dysku.

**pliki urządzenia** - służą do nadawania praw dostępu do urządzeń i kierowania operacji na plikach do odpowiednich sterowników urządzeń

**gniazda** - służy do komunikacji pomiędzy procesami

**potoki** - pozwalają połączyć wyjście jednego procesu w wejście drugiego

- `ps ax | grep firefox`
- `lsof -p {pid} > before`
- przechodzimy na inną stronę
- `lsof -p {pid} > after`
- `diff -u before after | grep IPv4`

## 6 
![](https://i.imgur.com/AvZ9g2w.png)

**Czas wykonania** - czas spędzony na wykonywaniu zadania. 

**Ograniczenie czasu wykonania** - limit czasu przeznaczony na wykonanie zadania.

user - czas spedzony w user-mode

sys - czas spedzony w kernelu-mode

real - "clock" time

user + sys może być większe od real:
- gdy proces działa na paru rdzeniach jednocześnie wtedy czas "user" jest sumą czasów procesu na każdym wątku

user + sys jest często mniejsze od real:
 - Gdy używamy dużo I/O i czekamy na sygnał np. firefox czekający na odpowiedź i w tym czasie procesor można wykorzystać do obsługi innego procesu

```
time find /usr
```

```
real	0m2.135s
user	0m0.555s
sys	0m0.692s
```

wywołujemy:
-`ulimit -t 1``
-`time find /usr`

```
Killed

real	0m1.758s
user	0m0.453s
sys	0m0.541s
```

proces zostanie zabity gdy user + sys = 1s

- ``ulimit -t 1`` 
- ``strace yes`` 

```
+++ killed by SIGKILL +++
Killed
```