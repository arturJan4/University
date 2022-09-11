---
tags: ASK
---
# ASK - LISTA 8
pomodoro - 12

## Zadanie 1 
![](https://i.imgur.com/jSRp0ud.png)
-s symbols
-t section details

**Plik relokowalny** (ang. relocatable file) to rodzaj pliku obiektowego generowanego przez kompilator lub asembler podczas kompilacji pliku z kodem źródłowym. Plik relokowalny może zostać również utworzony przez konsolidator w wyniku połączenia kilku plików relokowalnych. Proces ten nazywamy konsolidacją przyrostową.

Pliki relokowalne są przeznaczone do późniejszego przetwarzania przez konsolidator w celu otrzymania pliku wykonywalnego lub biblioteki dynamicznej. Istnieje też możliwość załadowania pliku relokowalnego do pamięci wykonywanego programu, a następnie odwoływania się do symboli zdefiniowanych w tym pliku (np. odczytu i modyfikacji zmiennych globalnych oraz wywoływania funkcji). Wspomniana możliwość jest wykorzystywana przez systemy operacyjne z jądrem monolitycznym do ładowania modułów jądra oraz przez programy trybu użytkownika do ładowania wtyczek. 

```c=
extern int buf[];

int *bufp0 = &buf[0];
static int *bufp1;

static void incr() {
  static int count = 0;
  count++;
}

void swap() {
  int temp;
  incr();
  bufp1 = &buf[1];
  temp = *bufp0;
  *bufp0 = *bufp1;
  *bufp1 = temp;
}
```

Wydruk readelf -s

```elf=
Symbol table '.symtab' contains 12 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     2: 0000000000000000     8 FUNC    LOCAL  DEFAULT    1 incr
     3: 0000000000000000     4 OBJECT  LOCAL  DEFAULT    5 count.1915
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 
     8: 0000000000000000     0 SECTION LOCAL  DEFAULT    8 
     9: 0000000000000008    38 FUNC    GLOBAL DEFAULT    1 swap
    10: 0000000000000000     8 OBJECT  GLOBAL DEFAULT    3 bufp0
    11: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND buf
```
adres symbolu - value
typ symbolu - bind
rozmiar danych - size

teraz żeby zdobyć numer i nazwę sekcji trzeba spojrzeć w section headers i zmapować [nr] na [ndx]



| numer | nazwa     |
| ----- | --------- |
| UND   | undefined |
| 5   |    .bss       |
|1|.text|
|3|.data|
|6|.comment|
|7|.note.GNU-stack|
|8|.note.gnu-property|



```.strtab``` - String Table
String Table jest trzyma stringi z nazwami symboli.


```.shstrtab``` - Section Header String Table
Section Header String Table trzyma stringi z nazwami sekcji.


https://stackoverflow.com/questions/3065535/what-are-the-meanings-of-the-columns-of-the-symbol-table-displayed-by-readelf

## Zadanie 2
![](https://i.imgur.com/QspakvG.png)

```c=
/* mismatch-a.c */
void p2(void);

int main() {
  p2();
  return 0;
}
```
```c=
/* mismatch-b.c */
#include <stdio.h>

char main;

void p2() {
  printf("0x%x\n", main);
}
```

$0xfffffff3$ - zwracana wartość

```char main``` jest symbolem słabym, ponieważ nie jest zainicjowany,
natomiast ```int main()``` jest symbolem silnym. 
Konsolidator preferuje symbole silne, zatem wynik będzie pochodził z ```int main()```.
Wykonując objdum -d mismtach-a.o dostajemy:
```
000000000000000 <main>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 83 ec 08          	sub    $0x8,%rsp
   8:	e8 00 00 00 00       	callq  d <main+0xd>
   d:	b8 00 00 00 00       	mov    $0x0,%eax
  12:	48 83 c4 08          	add    $0x8,%rsp
  16:	c3                   	retq   
```

Możemy zauważyć, że zwracana wartość to pierwszy bajt kodu funkcji ```int main()``` rozszerzony do 4 bajtów.

Jeślibyśmy chcieli zmienić wartość ```char main``` w funkcji ```void p2()```, to dostalibyśmy błąd podczas kompilacji ponieważ main nie jest w tamtym momencie znanym symbolem. 
Gdybyśmy jednak wcześniej zadeklarowali ```int main()``` to takie przypisanie także byłoby nieprawidłowe gdyż main to symbol funkcji czyli nie jest l-wartością w C. 
Gdyby natomiast zadeklarować wcześniej ```char main``` to kompilator gdy natrafi na funkcję ```int main()``` znajduje ponowną deklarację symbolu i rzuca błąd.

Jeślibyśmy zaincjalizowali ```char main```, to stałby się on silnym symbolem, więc otrzymalibyśmy konflikt silnych symboli co spowodowałoby ```linker error``` i zatrzymało proces konsolidacji.

## Zadanie 3
![](https://i.imgur.com/z71rfGB.png)

### Punkt 1
1) Wejście do podanego katalogu
2) ```ar t libc.a | wc -l``` zwraca $1740$
3) ```cat libm.a``` (wyświetlenie ścieżek)
4) ```ar t libm-2.31.a | wc -l``` zwraca $802$
5) ```ar t libmvec.a | wc -l``` zwraca $128$

Biblioteka ```libc.a``` zawiera więc $1740$ pliktów, natomiast ```limb.a``` $802+128=930$ plików

### Punkt 2
```-Og``` wyłącza optymalizacje, które mogłyby kolidować z debuggerem.
```-g``` włącza standardowe informacje dla debuggera
czyli jak  odpalimy gdb na pliku to gdy nie ma flagi -g to nie przekażemy symboli, czyli na przykład nie ma kodu źródłowego

```readelf --debug-dump a.out``` - wypisuje zawartość sekcji .debug przekazanych przez -g

```
gcc -Og -o without main.c
gcc -Og -g -o with main.c
```

Możemy porównać diffem
```
diff <(objdump -x --all-headers without) <(objdump -x --all-headers with)
```
### Punkt 3

1) wejście do podanego katalogu
2) objdump -p /usr/bin/python | grep "NEEDED" lub
objdump -p /usr/bin/python3 | grep "NEEDED"
```
  NEEDED               libc.so.6
  NEEDED               libpthread.so.0
  NEEDED               libdl.so.2
  NEEDED               libutil.so.1
  NEEDED               libm.so.6
  NEEDED               libexpat.so.1
  NEEDED               libz.so.1
```

## ZADANIE 4
![](https://i.imgur.com/sSAurqw.png)


instrukcja po której kończy się program:
```
0x0000000000401d45  ? movb   $0x0,0x5(%rax)
```

odpowiada ona
```c=
s[5] = '\0'
```
rax jest równy 0x0000000000495004 
Poszukajmy czemu jest to nielegalne przypisanie do pamięci
```
objdump -D str | grep \495004 -B 6
```

Widzimy, że jest to w .rodata (read-only) czy nie wolno nam tego edytować. Innymi słowy ten napis w C to string-literal, którego nie możemy zmieniać.

Żeby to naprawić możemy stworzyć zmienną ze słowem kluczowym static (to będzię pamięć zainicjalizowana przy pomocy string-literal)

```c=
char *somestr(void) {
  static char str[] = "Hello, world!";
  return str;
}
```

## Zadanie 5
### Rozmiar i pozycje sekcji/symboli

Flaga -fno-common: sprawia, że niezainicjalizowane zmienne globalne trafiają do sekcji .bss, co powoduje, że po napotkaniu ponownie symbolu dostaniemy błąd wielokrotnej deklaracji.

#### Rozmiar sekcji
Robimy readelf -S na foo.o i bar.o

##### foo.o
```elf=
There are 10 section headers, starting at offset 0x1e0:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       0000000000000000  0000000000000000  AX       0     0     1
  [ 2] .data             PROGBITS         0000000000000000  00000040
       0000000000000008  0000000000000000  WA       0     0     8
  [ 3] .bss              NOBITS           0000000000000000  00000050
       0000000000000011  0000000000000000  WA       0     0     16
  [ 4] .comment          PROGBITS         0000000000000000  00000050
       000000000000002b  0000000000000001  MS       0     0     1
  [ 5] .note.GNU-stack   PROGBITS         0000000000000000  0000007b
       0000000000000000  0000000000000000           0     0     1
  [ 6] .note.gnu.propert NOTE             0000000000000000  00000080
       0000000000000020  0000000000000000   A       0     0     8
  [ 7] .symtab           SYMTAB           0000000000000000  000000a0
       00000000000000d8  0000000000000018           8     7     8
  [ 8] .strtab           STRTAB           0000000000000000  00000178
       000000000000000a  0000000000000000           0     0     1
  [ 9] .shstrtab         STRTAB           0000000000000000  00000182
       0000000000000058  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  l (large), p (processor specific)
```

Widzimy, że rozmiar $.bss$ to 0x11 = 17 natomias rozmiar $.data$ to 0x8

##### bar.o

```elf=
There are 10 section headers, starting at offset 0x1e0:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       0000000000000000  0000000000000000  AX       0     0     1
  [ 2] .data             PROGBITS         0000000000000000  00000040
       0000000000000004  0000000000000000  WA       0     0     4
  [ 3] .bss              NOBITS           0000000000000000  00000050
       000000000000001e  0000000000000000  WA       0     0     16
  [ 4] .comment          PROGBITS         0000000000000000  00000050
       000000000000002b  0000000000000001  MS       0     0     1
  [ 5] .note.GNU-stack   PROGBITS         0000000000000000  0000007b
       0000000000000000  0000000000000000           0     0     1
  [ 6] .note.gnu.propert NOTE             0000000000000000  00000080
       0000000000000020  0000000000000000   A       0     0     8
  [ 7] .symtab           SYMTAB           0000000000000000  000000a0
       00000000000000d8  0000000000000018           8     7     8
  [ 8] .strtab           STRTAB           0000000000000000  00000178
       000000000000000a  0000000000000000           0     0     1
  [ 9] .shstrtab         STRTAB           0000000000000000  00000182
       0000000000000058  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  l (large), p (processor specific)
```

Widzimy, że rozmiar $.bss$ to 0x1E = 30 natomiast rozmiar $.data$ to 0x4


#### Rozmiar i pozycja symboli względem sekcji

skorzystamy z readelf -s

##### foo.o

```
Symbol table '.symtab' contains 9 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    2 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     7: 0000000000000000    17 OBJECT  GLOBAL DEFAULT    3 code
     8: 0000000000000000     8 OBJECT  GLOBAL DEFAULT    2 foo
```


code - offset 0 i size 17 
foo - offset 0 i size 8

##### bar.o

```elf=
Symbol table '.symtab' contains 9 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    2 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     7: 0000000000000000    30 OBJECT  GLOBAL DEFAULT    3 dead
     8: 0000000000000000     4 OBJECT  GLOBAL DEFAULT    2 bar

```

dead - offset 0 i size 30, 
bar - offset 0 i size 4


#### Częsciowa konsolidacja z -r

częsciowa konsolidacja (partial linking) z -r polega na stworzeniu nowego pliku relokowalnego na podstawie innych plików relokowalnych.
```
-r --relocateable Generate relocatable output--i.e., generate an output file that can in turn serve as input to ld
```
#### Różnica między merge-1.0 a merge-2.o

różnią się one kolejnością plików -

merge1.0 konsoliduje częściowo foo.o z bar.o

merge2.0 konsoliduje częściowo bar.o z foo.o

Skąd to wiemy? A no z makefile

```makefile
merge-1.map: foo.o bar.o
	$(LD) -M=$@ -r -o merge-1.o $^

merge-2.map: bar.o foo.o 
	$(LD) -M=$@ -r -o merge-2.o $^
     
```
mapa konsolidacji (linker map) - https://interrupt.memfault.com/blog/get-the-most-out-of-the-linker-map-file
Decyzje podejmowane przez konsolidator zapisywane są w mapie konsolidacji. Można z niej odczytać kolejność ładowania plików, sekcji. Skąd, pod jakim adresem i jakiego rozmairu dane umieszcza.

#### Najważniejsze fragmenty map
merge-1.map:

```
.data           0x0000000000000000        0xc            <---
 *(.data)
 .data          0x0000000000000000        0x8 foo.o
                0x0000000000000000                foo
 .data          0x0000000000000008        0x4 bar.o
                0x0000000000000008                bar

.data1
 *(.data1)

.bss            0x0000000000000000       0x3e            <---
 *(.bss)
 .bss           0x0000000000000000       0x11 foo.o
                0x0000000000000000                code
 *fill*         0x0000000000000011        0xf 
 .bss           0x0000000000000020       0x1e bar.o
                0x0000000000000020                dead


```

merge-2.map
```
data           0x0000000000000000       0x10            <---
 *(.data)
 .data          0x0000000000000000        0x4 bar.o
                0x0000000000000000                bar
 *fill*         0x0000000000000004        0x4 
 .data          0x0000000000000008        0x8 foo.o
                0x0000000000000008                foo

.data1
 *(.data1)

.bss            0x0000000000000000       0x31           <---
 *(.bss)
 .bss           0x0000000000000000       0x1e bar.o
                0x0000000000000000                dead
 *fill*         0x000000000000001e        0x2 
 .bss           0x0000000000000020       0x11 foo.o
                0x0000000000000020                code
```
offset - 2 kolumna
size   - 3 kolumna

Różnica w rozmiarze wynika z konieczności wyrównania.  Konsolidator układa w kolejności otrzymania plików. Żeby sprawdzić jaki jest align dla danej sekcji sprawdzamy to w readelf -t

```
readelf -t merge-1.o
There are 10 section headers, starting at offset 0x240:

Section Headers:
  [Nr] Name
       Type              Address          Offset            Link
       Size              EntSize          Info              Align
       Flags
  [ 0] 
       NULL             0000000000000000  0000000000000000  0
       0000000000000000 0000000000000000  0                 0
       [0000000000000000]: 
  [ 1] .note.gnu.property
       NOTE             0000000000000000  0000000000000040  0
       0000000000000020 0000000000000000  0                 8
       [0000000000000002]: ALLOC
  [ 2] .text
       PROGBITS         0000000000000000  0000000000000060  0
       0000000000000000 0000000000000000  0                 1
       [0000000000000006]: ALLOC, EXEC
  [ 3] .data
       PROGBITS         0000000000000000  0000000000000060  0
       000000000000000c 0000000000000000  0                 8
       [0000000000000003]: WRITE, ALLOC
  [ 4] .bss
       NOBITS           0000000000000000  0000000000000070  0
       000000000000003e 0000000000000000  0                 16
       [0000000000000003]: WRITE, ALLOC
  [ 5] .comment
       PROGBITS         0000000000000000  0000000000000070  0
       0000000000000056 0000000000000001  0                 1
       [0000000000000030]: MERGE, STRINGS
  [ 6] .note.GNU-stack
       PROGBITS         0000000000000000  00000000000000c6  0
       0000000000000000 0000000000000000  0                 1
       [0000000000000000]: 
  [ 7] .symtab
       SYMTAB           0000000000000000  00000000000000c8  8
       0000000000000108 0000000000000018  7                 8
       [0000000000000000]: 
  [ 8] .strtab
       STRTAB           0000000000000000  00000000000001d0  0
       0000000000000013 0000000000000000  0                 1
       [0000000000000000]: 
  [ 9] .shstrtab
       STRTAB           0000000000000000  00000000000001e3  0
       0000000000000058 0000000000000000  0                 1
       [0000000000000000]: 
```

```
There are 10 section headers, starting at offset 0x240:

Section Headers:
  [Nr] Name
       Type              Address          Offset            Link
       Size              EntSize          Info              Align
       Flags
  [ 0] 
       NULL             0000000000000000  0000000000000000  0
       0000000000000000 0000000000000000  0                 0
       [0000000000000000]: 
  [ 1] .note.gnu.property
       NOTE             0000000000000000  0000000000000040  0
       0000000000000020 0000000000000000  0                 8
       [0000000000000002]: ALLOC
  [ 2] .text
       PROGBITS         0000000000000000  0000000000000060  0
       0000000000000000 0000000000000000  0                 1
       [0000000000000006]: ALLOC, EXEC
  [ 3] .data
       PROGBITS         0000000000000000  0000000000000060  0
       0000000000000010 0000000000000000  0                 8
       [0000000000000003]: WRITE, ALLOC
  [ 4] .bss
       NOBITS           0000000000000000  0000000000000070  0
       0000000000000031 0000000000000000  0                 16
       [0000000000000003]: WRITE, ALLOC
  [ 5] .comment
       PROGBITS         0000000000000000  0000000000000070  0
       0000000000000056 0000000000000001  0                 1
       [0000000000000030]: MERGE, STRINGS
  [ 6] .note.GNU-stack
       PROGBITS         0000000000000000  00000000000000c6  0
       0000000000000000 0000000000000000  0                 1
       [0000000000000000]: 
  [ 7] .symtab
       SYMTAB           0000000000000000  00000000000000c8  8
       0000000000000108 0000000000000018  7                 8
       [0000000000000000]: 
  [ 8] .strtab
       STRTAB           0000000000000000  00000000000001d0  0
       0000000000000013 0000000000000000  0                 1
       [0000000000000000]: 
  [ 9] .shstrtab
       STRTAB           0000000000000000  00000000000001e3  0
       0000000000000058 0000000000000000  0                 1
       [0000000000000000]: 

```