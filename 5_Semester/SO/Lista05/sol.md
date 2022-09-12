# SO - Lista 5

## Materiały
### APUE - 3.15, 4.14-4.18, 17.2
#### 3.15 - ioctl
#### 4.14-4.18 filesystems, lonk, rename, symlinks
#### 17.2 UNIX Domain sockets
### LPI - 62
terminals
### Tannenbaum - 4.1, 4.2, 10.6
#### files, drectories, linux files system

## 1
![](https://i.imgur.com/hamrCEr.png)

### Pojęcia:
**jednokierunkowe** - przepływ danych w prawo w potoku
**bufor rury** - pamięć (w jądrze) służaca do przesyłania danych pomiędzy procesami

###  Co robi operacja read(2) i write(2), jeśli bufor rury jest odpowiednio pusty albo pełny?

#### pusty
proces w potoku który woła read jest blokowany (bo potencjalnie w potoku mogą pojawić się jeszcze jakieś dane)
read() zwróci 0, gdy bufor rury zostanie opróżniony i read odczyta EOF

#### pełny
proces wywołujący write zostaje zablokowany, aż do zwolnienia przestrzeni (odczytania przez inny proces)

### Jakie gwarancje daje nam operacja write na rurze, do której pisze wiele procesów – każdy z nich wiersze tekstu nie dłuższe niż «PIPE_BUF»?
Daje gwarancję atomowości zapisu (write()). Czyli możemy mieć wiele procesów wypisujących jednocześnie i jeśli każdy z nich będzie wypisywał wiersze nie dłuższe niż PIPE_BUF (w bajtach) to wiemy, że zostaną one wypisane w całości. (nie będzie przeplatania fragmentów wierszy)

### przykładowy potok
`«ps -ef | grep sh | wc -l`

#### Czemu wszystkie procesy należące do potoku zakończą się bez interwencji powłoki, jeśli co najmniej jeden z nich umrze?

Jeśli zostanie zamknięty koniec do zapisu, to konsument ostatecznie opróżni bufor rury po czym dostanie EOF (read zwróci 0)
np. umiera `ps`, `grep` wczytuje bufor i dostaje EOF

Jeśli zostanie zamknięty koniec do odczytu, to producent przy zapisie dostanie SIGPIPE, którego domyślną akcją jest zakończenie procesu.

np. `wc` kończy działanie to `grep` dostanie SIGPIPE, umrze, a potem ps dostanie SIGPIPE

####  Kiedy operacje read i write na rurze zwracają „short count”?
Read: 
- przerwanie sygnałem
- wczytano mniej niż `nbyte` (np. terminal kończy znakiem '\n')

Write - według wykładu nie da się

#### Jak można połączyć rodzica i dziecko rurą, która została utworzona po uruchomieniu dziecka?
Nie jest to możliwe, ponieważ rury dziedziczmy (w dół) relacji. Czyli warunkiem aby 2 procesy połączyć rurą jest to, że pipe musiał zostać utworzony przez wspólnego przodka tychże procesów.

Wyjątek: przekazanie deskryptorów plików przez UNIX domain socket umożliwia połączenie rurą niepowiązanych procesów.
APUE 17.2 ->
`socketpair(int domain, int type, int protocol, int sockfd[2])`
szczegoły dot. argumentów -> https://man7.org/linux/man-pages/man2/socket.2.html
domain -> rodzina protokołów
typ -> semantyka komunikacji
protocol -> wyszczególniony protokół


![](https://i.imgur.com/DfwIeuh.png)

#### Notatki
named PIPE -> FIFO

## 2
![](https://i.imgur.com/fMgLIF7.png)
### Pojęcia
**urządzenia znakowe** - służą do czytania/zapisywania danych znak po znaku. Nie są zwykle buforowane. np. konsole, wirtualne konsole, generatory (`/dev/null`)
**urządzenia blokowe** - pozwalają na odczytywanie danych blokami, czyli grupami bajtów: sektory, klastry itp. np. dyski, partycje

### krytyka
http://www.catb.org/~esr/writings/taoup/html/ch20s03.html
oryginalne, historyczne zastowanie ioctl to kontrola parametrów w sterownikach transmisji szregowej, a w późniejszych latach liczba komend dla `ioctl` i `fcntl` zaczęła się mnożyć. 

Słaba dokumentacja, wiele makr nałożonych na siebie opisujących typ operacji powodują błędy i wymagają umiejętności programisty, który je stosuje.

### Do czego służy wywołanie systemowe ioctl(2)?
"input/output control" - wykonuje specyficzne dla danego urządzenia operację I/O (i inne), których nie da się wykonać zwykłymi wywołaniami systemowymi

### ioccom.h
```c=
#ifndef	_SYS_IOCCOM_H_
#define	_SYS_IOCCOM_H_

/*
 * Ioctl's have the command encoded in the lower word, and the size of
 * any in or out parameters in the upper word.  The high 3 bits of the
 * upper word are used to encode the in/out status of the parameter.
 *
 *	 31 29 28                     16 15            8 7             0
 *	+---------------------------------------------------------------+
 *	| I/O | Parameter Length        | Command Group | Command       |
 *	+---------------------------------------------------------------+
 */
#define	IOCPARM_MASK	0x1fff		/* parameter length, at most 13 bits */
#define	IOCPARM_SHIFT	16
#define	IOCGROUP_SHIFT	8
#define	IOCPARM_LEN(x)	(((x) >> IOCPARM_SHIFT) & IOCPARM_MASK)
#define	IOCBASECMD(x)	((x) & ~(IOCPARM_MASK << IOCPARM_SHIFT))
#define	IOCGROUP(x)	(((x) >> IOCGROUP_SHIFT) & 0xff)

#define	IOCPARM_MAX	NBPG	/* max size of ioctl args, mult. of NBPG */
				/* no parameters */
#define	IOC_VOID	(unsigned long)0x20000000
				/* copy parameters out */
#define	IOC_OUT		(unsigned long)0x40000000
				/* copy parameters in */
#define	IOC_IN		(unsigned long)0x80000000
				/* copy parameters in and out */
#define	IOC_INOUT	(IOC_IN|IOC_OUT)
				/* mask for IN/OUT/VOID */
#define	IOC_DIRMASK	(unsigned long)0xe0000000

#define	_IOC(inout, group, num, len) \
    ((inout) | (((len) & IOCPARM_MASK) << IOCPARM_SHIFT) | \
    ((group) << IOCGROUP_SHIFT) | (num))
#define	_IO(g,n)	_IOC(IOC_VOID,	(g), (n), 0)
#define	_IOR(g,n,t)	_IOC(IOC_OUT,	(g), (n), sizeof(t))
#define	_IOW(g,n,t)	_IOC(IOC_IN,	(g), (n), sizeof(t))
/* this should be _IORW, but stdio got there first */
#define	_IOWR(g,n,t)	_IOC(IOC_INOUT,	(g), (n), sizeof(t))

#define IOCSNPRINTF(buf, len, cmd) \
    snprintf((buf), (len), "_IO%s%s('%c', %hhu)", \
	(((cmd) >> 30) & 1) ? "R" : "", \
	(((cmd) >> 30) & 2) ? "W" : "", \
	(char)IOCGROUP(cmd), (unsigned char)(cmd))


#endif /* !_SYS_IOCCOM_H_ */
```

#### znaczenie drugiego i trzeciego paramateru ioctl
```c=
/*
 * Ioctl's have the command encoded in the lower word, and the size of
 * any in or out parameters in the upper word.  The high 3 bits of the
 * upper word are used to encode the in/out status of the parameter.
 *
 *	 31 29 28                     16 15            8 7             0
 *	+---------------------------------------------------------------+
 *	| I/O | Parameter Length        | Command Group | Command       |
 *	+---------------------------------------------------------------+
 */
```

int ioctl(int fd, unsigned long request, ...)

drugi: kod żądanej operacji, czy argument jest parametrem wejściowym czy wyjściowym i rozmiar argumentu w bajtach

trzeci: nietypowany wskaźnik do pamięci (char* -> void*)

### definicje i znaczenie operacji «DIOCEJECT», «KIOCTYPE» i «SIOCGIFCONF»
wszystkie 3 odwołują się do definicji w `iocomm.h`
#### DIOCEJECT
"eject removable disk"

/src/sys/sys/dkio.h
`#define DIOCEJECT	_IOW('d', 112, int)	/* eject removable disk */`

#### KIOCTYPE
"get keyboard type"

/src/sys/arch/alpha/include/kbio.h
`#define	KIOCTYPE	_IOR('k', 9, int)	/* get keyboard type */`
np: 
- `KB_ASCII` - ASCII terminal as keyboard
- `KB_PC` - type 101 PC keyboard
- `KB_USB`
- `KB_SUN3` - Sun Type 3 keyboard

#### SIOCGIFCONF
"get ifnet list"

/src/sys/sys/sockio.h
`#define	SIOCGIFCONF	_IOWR('i', 38, struct ifconf)	/* get ifnet list */`

SIOCGIFCONF ioctl retrieves a list of interface names and addresses for all interfaces and protocols on the host
kernel interfaces for manipulating network interfaces - interfejsy jądrą do zarządzania sieciami

## 3
![](https://i.imgur.com/VmtwDqe.png)

### Pojęcia
**nieużytki** - fragment, który jest nieużywany ale znajduje się w reprezentacji katalogu

**kompaktowanie** - operacja zmniejszająca rozmiar katalogu polegająca na usuwaniu nieużytków

### reprezentacja katalogu
![](https://i.imgur.com/FDhrkG5.png)
Nazwy plików do 255 znaków (null terminated, wyrównana do 32 bitów). 

Katalog składa się z pewnej (całkowitej) liczby bloków.

Wewnątrz mamy wpisy plików i katalogów. Jeśli któryś z wpisów nie zajmuje całego bloku to wówczas bajty na końcu to nieużytki.

Każdy wpis składa się z 4 stałych pól:
- numer i-węzła
- rozmiar wpisu (w bajtach, wlicza padding), służący do znajdowania następnego wpisu
- typ pliku (plik, katalog itp.), zdublowany w celach optymalizacji
- długość nazwy pliku
oraz pola o zmiennym rozmiarze - nazwy.

### jak wygląda usuwanie i dodawanie
Usuwanie - zwiększamy rozmiar wpisu poprzedzającego usuwany wpis, miejsce które zajmował obecny wpis jest uznawane za nieużytek, st_nlink pliku jest dekrementowane.

Dodawanie - sprawdzamy czy plik jest w katalogu, jeśli brakuje miejsca wykonuejmy kompaktowanie

## 4
![](https://i.imgur.com/3ETNXPK.png)

### Pojęcia
**ścieżka bezwględna** - napis oznaczający ścieżkę specyfikującą lokalizację pliku idąc od katalogu głównego `/`, wskazuje na ten sam plik niezaleznie od aktualnego katalogu roboczego
**i-węzeł** - opis zasobu dyskowego zawierający spis atrybutów

### Przykład trawersowania
`ls -lia` - opcja i wyświetla i-node
`stat`
`/usr/bin/cc`


`stat /`
`stat /usr`
`ls -lia / | grep <i-node usr>`
`stat /usr/bin`
`ls -lia /usr | grep <i-node bin>`
`stat /usr/bin/cc`

Szukanie zaczyna się od i-węzła nr 2 (`/`).
Nastepnie szukamy w bloku nazwy `usr` i odpowiadającego jej i-węzła.
I tak aż do dotarcia do końca ścieżki.

Gdy mamy do czynienia z ścieżką względną to szukanie rozpoczyna się od i-węzła bieżącego katalogu roboczego.

### Skąd sterownik uniksowego systemu plików wie gdzie na dysku znajduje się i-ty bajt pliku?
![](https://i.imgur.com/HDD61co.png)
dany i-node posiada wskaźniki na bloki danych i bloki pośrednie dla zwiększenia objętości.

Jeśli znamy rozmiar bloku to należy policzyć w którym bloku będzie znajdować się i-ty bajt. 

https://ext4.wiki.kernel.org/index.php/Ext4_Disk_Layout
### błąd «EXDEV»
EXDEV (Erroc cross DEVice)

Nie można tworzyć dowiązań do zamonotowanej pamięci, ponieważ może być ona w tymczasowa. W sytuacji odłączenia licznik dowiązań wskazywałby zawsze wartość wiekszą od 1 co uniemożliwiałoby usunięcie danych nawet po usunięciu lokalnych dowiązań.

## 5
![](https://i.imgur.com/1Huj6wZ.png)

### Pojęcia
**numer urządzenia** - para <major, minor>, gdzie major to identyfikator sterownika powiązanego z urządzeniem, minor to numer używany przez sterownik, używany gdy jeden sterownik kontroluje wiele urządzeń

https://man.openbsd.org/ls.1

## 6
![](https://i.imgur.com/nXO3y7d.png)

## po dodaniu pause + ctrl + z
`ps -l | grep prime | wc -l` -> 1231 procesów
`lsof | grep prime | grep FIFO`

## 7
![](https://i.imgur.com/vI7FkmV.png)
**lokalna dwukierunkowa metoda komunikacjii** - pozwalają na dwustronną wymianę danych pomiędzy procesami jednego systemu. Działają w obrębie jądra systemu.

`./gen-nums.py 100 | ./mergesort `