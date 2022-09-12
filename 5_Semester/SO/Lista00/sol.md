# SO - Lista 0

## 1
Wyjątek - nagła zmiana w przepływie sterowania w wyniku zmiany stanu procesora, częsciowo OS, częściowo hardware

- page fault
- arithmetic overflow
- divide by zero

przerwanie sprzętowe - asynchronicznie z I/O device, zapala pin na procesorze i na szynie adresowej zostawia numer wyjątku, 
intrukcja się wykonuje -> exception handler -> następna instrukcja
- hardware timer
- packets in network arrived
- disk data is ready

pułapka - intencjonalnie synchronicznie (czyli zależy od obecnej instrukcji), interfejs pomiędzy programami i jądrem - syscall:
- read a file (read)
- reate a process (fork)
- terminate current process (exit)

fault - handler może naprawić albo abort
abort - fatal error

w jakim scenariuszu?
trap, interrupt albo naprawiony fault

## 2

Mechanizm:
wektor przerwań - to tablica gdzie indeksy to liczby naturalne - numer wyjątku, wskazuje na kod exception handler i-ty
te numery są prznane przez procesor lub jądro.

Przy boot system inicjalizuje to jump table.

Przed pobraniem instrukcji zostawiamy adres powrotu z procedury na stosie (następnej lub obecnej), oraz rejestr EFLAGS z condition codes

Po obsłużeniu wyjątku ściąga flagi, stan rejestrów i przywraca user-mode, wraca do programu.

Tryb jądra blokuje dostęp do niedozwolonych dla zwykłych programów działań np. kontrola I/O, wyłączenie procesora, dostęp do całej pamięci.
Bezpieczeństwo i podatność na błędy.

Osobny stos - bezpieczeństwo (brak dostępu z user-mode)
Separation of privileges and security. 
Stack-ptr w user-mode może być wszystkim więc jadro nie ufa.

## 3

![](https://i.imgur.com/qQ0KXE0.png)


ELF:
- nagłówek ELF (parametry, format pliku, platformy na która został skonfigurowany, wersji, informacji o położeniu nagłówków sekcji i programu, entry-point programu)
- nagłówki sekcji -> typ i położenie
- nagłówki programu -> typ i położenie jednego segmentu
- zawarto≥ść sekcji/segmentów


Segment header table - informacje o fragmencie pamięci, takie jak: gdzie wczytać, z jakich sekcji, z jakimi flagami.

.init - instrukcje należące do inicjalizacyjnego kodu procesu. Kod w tej sekcji jest wykonywany zamin system wywoła główne wejście programu.

.text - wykonywalne instrukcje programu, kod.

.rodata - read only data (dane tylko do oczytu).

.data - globalne zainicjowane zmienne oraz static.

.bss - globalne niezainicjowane zmienne.

.symtab - tablica symboli, czyli informacje o funkcjach i globalnych zmiennych, do których są odwołania w programie.

.debug - informacje dla debuggera, kod źródłowy, lista lokalnych zmiennych i definicje typów, lista globalnych zmiennych zdefiniowanych przez program oraz tych, do których się odwołuje.

.line - informacje dla debuggera, informacje o mapowaniu linii kodu źródłowego na linie kody maszynowego

.strtab - tablica stringów dla sekcji .debug, .symtab oraz nazw sekcji w nagłówkach.

Section header table - opis sekcji programu, rozmiar i lokacja.

Sekcja - spójny blok pamięci (linkowanie)
Segmenty (runtime), segmenty mają sekcje

Nagłówki programów przechowują informacje o segmentach programów (offset, align, flagi, virtaddr, physaddr, memsize.

System wie pod jakim adresem umieścić segmenty dzięki segment header table. Elf header zawiera adres pierwszej instrukcji.

## 4
przestrzeń adresowa - mapa możliwej do zaadresowania przez proces pamięci. Przestrzenie adresowe procesów muszą być rozłączne. Uzyskuje się to m. in. dzięki mechanizmowi pamięci wirtualnej: adres wirtualny jest dla każdego procesu tłumaczony na adres fizyczny w pamięci operacyjnej, przy czym każdy proces ma przydzielone inne adresy fizyczne Rozmiar przestrzeni adresowej jest zwykle dużo większy niż rozmiar pamięci operacyjnej (np. dla x86 – 4GB, bowiem adresy są 32-bitowe), przez co nie wszystkie adresy wirtualne są prawidłowe. Prawidłowe adresy wirtualne należą do tzw. obszarów pamięci procesu.
W skład wchodzi: kod procesu, pamięć dzielona, zainicjowane dane, niezaincjowane dane (BSS), bibloteki dynamczine, stos, sterta

wywołanie systemowe (system call -> syscall) - stanowi interfejs między wykonywanym programem a (posiadającym zwykle wyższe uprawnienia) jądrem systemu operacyjnego.
np: dostęp do systemu plików, komunikacja między procesorami, uruchamianie innych programów, komunikacja sieciowa


![](https://i.imgur.com/quxkcQe.png)

SSE2 orz x87 mają wyczysczone flagi floating-point

Auxiliary vector to tabelka z parami typu klucz-wartość, gdzie klucze to wartości “AT” z ELF headera. Część informacji jest przekazywana z jądra systemu i może być wyciągnięta przez interfejsy, np. syscon

```
typedef struct
{
	int a_type;
	union {
		long a_val;
		void *a_ptr;
		void (*a_fnc)();
	} a_un;
} auxv_t;
```

tabela typów a_type na stronie 31 (Figure 3.11)

![](https://i.imgur.com/qvCx5LP.png)

## 5

jest to sposób na powiedzenie kompilatorowi, że dana zmienna może zmieniać się niezależnie od naszego programu

volatile – pomiędzy różnymi odczytami, wartości zmiennej mogą być różne, nawet jeśli nie były zmodyfikowane w kodzie.
Zastosowanie volatile powstrzymuje kompilator optymalizujący przed pomijaniem zapisów do pamięci.

Zazwyczaj używa się tego słowa kluczowego, gdy zmienna może być zmieniona przez akcje niewidoczne w kodzie.

```
typedef struct {
    int shouldWait;
} Timer;

void setData (Timer * timer) {
    while (timer->shouldWait) {
        // jakis kod i nie modyfikujemy shouldWait
    }
}
```

```
typedef struct {
    int x;
    int y;
} Point

void swap(Point *p) {
    // some code
    pair->x = pair->y;
    pair->y = pair->x;
}
```

## 8

2_cat.c
```c=
#include "apue.h"

#define BUFFSIZE 4096

int main(void) {
  int n;
  char buf[BUFFSIZE];

  while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    if (write(STDOUT_FILENO, buf, n) != n)
      err_sys("write error");

  if (n < 0)
    err_sys("read error");

  exit(0);
}

```
STDIN_FILENO, STDOUT_FILENO - deskryptory pliku jak się okazuje 
STDIN_FILENO = 0
STDOUT_FILENO = 1
STDERR_FILENO = 2

odpalamy i widzimy 0 i 1

jak użyjemy CTRL + D

```
read(0, "", 4096)                       = 0
```

```c=
#include "apue.h"

#define BUFFSIZE 4096

int main(int argc, char* argv[]) {
  int n;
  char buf[BUFFSIZE];
  
  FILE *file;
  
  file = fopen(argv[1], "r");

  while ((n = fread(buf, sizeof(char), 10, file)) > 0)
    if (write(STDOUT_FILENO, buf, n) != n)
      err_sys("write error");

  if (n < 0)
    err_sys("read error");

  exit(0);
}
```

2_cat_line.c
```c=
 #include <fcntl.h>
 #include "apue.h"
 
 #define BUFFSIZE 4096
 
 int fd;
 
 int main(int argc, char *argv[]) {
   int n;
   char buf[BUFFSIZE];
 
   fd = open(argv[1], O_RDONLY);
 
   while ((n = read(fd, buf, BUFFSIZE)) > 0)
     if (write(STDOUT_FILENO, buf, n) != n)
       err_sys("write error");
 
   if (n < 0)
     err_sys("read error");
 
   exit(0);
 }
```

w Makefile:
```
PROGS =	1_ls 2_cat 2_cat_line
```

plik:
```
strace ./2_cat_line test.txt
```
```
openat(AT_FDCWD, "test.txt", O_RDONLY)  = 3
read(3, "Hello World!\n", 4096)         = 13
write(1, "Hello World!\n", 13Hello World!
)          = 13
```

próba otwarcia katalogu:
```
strace ./2_cat_line libapue/
```
```
read(3, 0x7ffc6ca3e370, 4096)           = -1 EISDIR (Is a directory)
```