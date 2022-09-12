# SO - Lista 6

## Materiały
### APUE 3.13, 4.4-4.5, 8.11
### LPI 9, 13, 38, 39

## 1
![](https://i.imgur.com/SJPxmls.png)

### Pojęcia:
**tożsamość** - własność procesu (identyfikatory użytkowników i grup), wykorzystywana do kontroli dostępu do zasobów, z reguły procesy mają tożsamość użytkownika, który je utworzył. W bloku kontrolnym procesu jądro trzyma niepodrabialne kredencjały.

###  Jak zmieni się tożsamość procesu po wywołaniu

start: 
- ruid=1000 - real user id (rzeczywisty)
- euid=0 - effective user id (obowiązujący)
- suid=0 - saved user id (zachowany - do np. zachowania uprzywilejowanej wartości i późniejszego powrotu)

![](https://i.imgur.com/7P7hfHK.png)


#### setuid(2000)
euid == 0 -> setuid() sprawdza euid -> jesteśmy rootem a więc możemy zmienić wszystkie 3 id

finalnie:
ruid = 2000
euid = 2000
suid = 2000

zauważamy że tracimy przywileje root'a -> nie zostawiliśmy saved
#### setreuid(-1, 2000)
:::info
setreuid() sets real and effective user IDs of the calling process.

Supplying a value of -1 for either the real or effective user ID forces the system to leave that ID unchanged.

(*)If the real user ID is set (i.e., ruid is not -1) or the effective user ID is set to a value not equal to the previous real user ID, the saved set-user-ID will be set to the new effective user ID.
:::

- ruid=1000 -> 1000 (bo -1)
- euid=0    -> 2000
- suid=0    -> 2000 (z (*))

#### seteuid(2000)
set effective id

- ruid=1000 -> 1000 
- euid=0    -> 2000
- suid=0    -> 0

"chwilowa" zmiana tożsamości procesu

#### setresuid(-1, 2000, 3000)
:::info
setresuid - set real, effective, and saved user

A privileged process may set its real UID, effective UID, and saved set-user-ID to arbitrary values.
	  
If one of the arguments equals -1, the corresponding value is not changed.
:::

- ruid=1000 -> 1000 
- euid=0    -> 2000
- suid=0    -> 3000

### Czy proces ruid=0, euid=1000, suid=1000 jest uprzywilejowany?
Nie jest, ponieważ gdy system sprawdza czy proces może coś zrobić to sprawdza effective-id, które teraz wynosi 1000. 

Był uprzywilejowany bo real user-id wynosi 0, ale zmienił uprawnienia.

## 2
![](https://i.imgur.com/5cgGGch.png)

### Pojęcia:
**upoważnienie** - (authorization) to proces sprawdzania, czy proces o danej tożsamości ma dostęp do zasobu

### Jaką rolę pełnią bity uprawnień «rwx» dla katalogów w systemach uniksowych?
R - można czytać wyłącznie zawartość pliku katalogu (getdirents, ale nie stat)	

W - można modyfikować zawrtość pliku katalogu (creat, unlink, rename)

X - można czytać metadane, można czytać zawartość pliku lub przejść do podkatalogu jeśli znamy nazwę

### Znaczenie bitów «set-gid» i «sticky» dla katalogów
set-gid - **nowe** pliki i katalogi dziedziczą group id katalogu zamiast grupy podstawowej użytkownika, który stworzył plik,
dodatkowo katalogi dziedziczą bit setgid
`chmod g+s`

sticky - plik może zostać usunięty jedynie przez właściciela
`/tmp`

### my_access
:::info
The mode specifies the accessibility check(s) to be performed, and is either the value F_OK, or a mask consisting of the bitwise OR of one or more of R_OK, W_OK, and X_OK.  F_OK tests for the existence of the file.  R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively.
:::
![](https://i.imgur.com/JGsJm9M.png)

![](https://i.imgur.com/4e19EMk.png)
![](https://i.imgur.com/YOrzMpT.png)
![](https://i.imgur.com/Qv7Vegt.png)


```c=
bool my_acces(struct stat *sb, int mode)
{
  // superuser ma dostęp
  if (geteuid() == 0)
    return true;
	
  uint8_t pr  = (mode & R_OK); 	     // flagi z mode
  uint8_t pw  = (mode & W_OK);  
  uint8_t px  = (mode & X_OK);
  
	int sb_mode = sb->st_mode;

  // user ID procesu == uid programu
  // to sprawdzamy bit dostępu
  if (getuid() == sb->st_uid)
  {
    uint8_t sb_ur = (sb_mode & S_IRUSR); // uprawnienia pliku
    uint8_t sb_uw = (sb_mode & S_IWUSR);
    uint8_t sb_ux = (sb_mode & S_IXUSR);
  
    if (!sb_ur && pr) 
      return false;
    if (!sb_uw && pw)
      return false;
    if (!sb_ux && px)
      return false;

    return true;
  }
	
  // sprawdzamy dla grup
  gid_t gid = sb->st_gid;

  if (getgid() == gid)
  {
    gid_t *groups = NULL;

    int groups_n = getgroups(0, NULL); // when passing 0 -> get size without modyfing groups
    groups = malloc(groups_n * sizeof(gid_t));
    groups_n = getgroups(groups_n, groups);

    for (int i = 0; i < groups_n; ++i)
    {
      if (gid == groups[i])
      {
        uint8_t sb_gr = (sb_mode & S_IRGRP); // uprawnienia pliku
        uint8_t sb_gw = (sb_mode & S_IWGRP);
        uint8_t sb_gx = (sb_mode & S_IXGRP);
    
        if (!sb_gr && pr) 
            return false;
        if (!sb_gw && pw)
            return false;
        if (!sb_gx && px)
            return false;

        return true;
      }
    }
  }
	
  // others 
  uint8_t sb_or = (sb_mode & S_IROTH); // uprawnienia pliku
  uint8_t sb_ow = (sb_mode & S_IWOTH);
  uint8_t sb_ox = (sb_mode & S_IXOTH);
  
  if (!sb_or && pr) 
    return false;
  if (!sb_ow && pw)
    return false;
  if (!sb_ox && px)
    return false;

return true;
}
```

Uwaga:
root nie zrobi execute na skrypcie z uprawnieniami `chmod 0`
bo to jądro robi `execve`

## 3 (TODO)
![](https://i.imgur.com/Wedeux6.png)

### Pojęcia:
**uwierzytelnienie** - mechanizm potwierdzania tożsamości np. podanie hasła, 
klucza prywatnego, odcisku palca, zdjęcia siatkówki.

### tożsamość `su`
właściciel `su` -> root
ma ustawiony bit set-uid -> pozwala na uruchomienie z uprawnieniami właściciela
przed execve(2) -> euid=1000
normalnie po execve do saved id kopiowane jest euid, ale z flagą set-uid:

:::info
Similarly, if the set-group-ID bit is set on the program file, then the
effective group ID of the calling process is set to the group of the program file.
::: 

czyli euid = 0 i jest kopiowane suid
czyli mamy
ruid=1000, euid=0, suid=0

### referowanie `su`

## 4
![](https://i.imgur.com/nW0Kpzk.png)

#### Czemu programy uprzywilejowane należy projektować w taki sposób, by operowały z najmniejszym możliwym zestawem upoważnień (ang. the least privilege)?
Chcemy jednocześnie minimalizować szansę przejęcia kontroli nad programem oraz ograniczyć możliwości atakującego jeśli przejęcie się powiedzie.

Zwiększone uprawnienia dla danego programu są potrzebne do wykonania konkretych operacji, poza tymi operacjami program nie powinien mieć nadmiarowych uprawnień (wyłączamy lub zabieramy uprawnienia).

#### Wytyczne dotyczące projektowania takich programów

##### Utrzymuj uprawnienia tylko gdy są wymagane
przykład z 38.2
```c=
uid_t = orig_euid;
orig_euid = getuid();

if(seteuid(getuid()) == -1)  //drop privileges (euid == ruid)
	errExit("seteuid");

// do some unprivileged work here!

if(seteuid(orig_euid) == -1) //reaquire privileges (restore effective ID)
	errExit("seteuid");

// do priviliged work!
```

dla programów z set-gid, `setegid()` jest wykorzystywany do podobnego celu/

Najbezpiecznej jest zabrać uprawnienia na starcie programu i przywracać w późniejszych fragmentach kiedy są konieczne.

##### Usuwaj na stałe niepotrzebne uprawnienia
Gdy uprawnienia nie będą już potrzebne powinny zostać całkowicie usunięte (zmieniamy również saved suid), po to by program nie został zmuszony do odzyskania uprawnień w wyniku ataku (np. stack-crashing).

#### Usuwaj na stałe przed `exec` dla innego programu
Jeśli program ma uprawnienia SUID, (GUID) to przed wywołaniem `exec` należy zresetować wszystkie identyfikatory procesu (grupy), tak by nie startował z uprawnieniami lub nie mógł ich uzyskać.
np. `setuid(getuid())`-> zmienia euid (bo exec kopiuje euid do suid nowego)

przykład z 38.3
załóżmy, że mamy program, którego właścicielem jest UID=200
Program zostaje uruchomiony przez użytkownika o ID=1000
wtedy proces ma:
real=1000, effective=200, saved=200

po wywołaniu setuid(getuid()):
real=1000, effective=1000, saved=200

po wywołaniu execve -> effective jest kopiowany do saved
real=1000, effective=1000, saved=1000

i nie mamy dostępu do UID = 200

#### Nie uruchamiaj powłoki lub interpretera z uprawnieniami
Chodzi o wywołania bezpośrednie lub pośrednie (np. system(), popen(), exelp(), execvp())

Złożoność i możliwości shell'a sprawiają, że ma wiele pułapek bezpieczeństwa. Użytkownik może wtedy urucohmić dowolne polocenie z euid procesu.

W Linux (i niektórych innych implementacjach UNIX) bity set-uid i set-gid są ignorowane gdy robimy exec() na skrypcie.

#### Zamykaj niepotrzebne deskryptory plików przed exec()
Uprzywilejowany program może otworzyć plik, którego nieuprzywilejowany nie mógłby. Jako że przy exec() zostają przekazane otwarte deskryptory, a uprawnienia są sprawdzane jedynie przy otwieraniu pliku to mamy dostęp do pliku.

Należy zamknąć deskryptor (lub ustawić flagę close-on-exec)

#### Czemu standardowy zestaw funkcji systemu uniksowego do implementacji programów uprzywilejowanych jest niewystarczający? (39.1)
Standardowo UNIX dzieli procesu na dwie kategorie
- euid = 0 -> su -> omija sprawdzanie uprawnień
- inne procesy, które wymagają sprawdzania uprawnień użytkownika/grupy

przykład: chcemy zmienić system-time, zmieniamy uprawnienia euid=0, by wykonać tę zmianę
problem: proces może wtedy wykonać wszystkie akcje wymagające uprawnień, co może powadzić do niespodziewanych błędów i jest zagrożeniem bezpieczeństwa

Można sobie z tym radzić tradycyjnie (tak jak opisano wyżej).
Ale jest to skomplikowane i wymaga pamiętania o pozbywaniu się i śledzenia uprawnień dla każdej linii kodu, co może powodować problemu dla większych programów, z większą liczbą zależności.

Ale mamy też zdolności ... ->

#### Jak starają się to naprawić zdolności (ang. capabilities )? 
Zamiast wykorzystywania jednego uprawnienia (np. euid==0), uprawnienie su dzieli się na tzw. zdolności.

Każda operacja wymagająca uprawnień ma przypisaną zdolność.
Proces musi posiadać tę zdolność (niezależnie od euid), by wykonać działanie.
Każda zdolność możę być niezależnie włączana/wyłączana

Gdy aplikacja nie wykorzystuje zdolności i euid=0 to kernel przydziela pełny zestaw zdolności.

str 800. LPI -> tabela

#### Dla nieuprzywilejowanego procesu posiadającego zdolności «CAP_DAC_READ_SEARCH» i «CAP_KILL» jądro pomija sprawdzanie upoważnień do wykonywania pewnych akcji – wymień je
CAP_DAC_READ_SEARCH - Bypass file read permission checks and directory read and execute (search) permission checks

CAP_KILL - Bypass permission checks for sending signals (kill(), sigqueue())

#### Kiedy proces użytkownika może wysłać sygnał do innego procesu?
Proces powinien być uprzywilejowany, a konkretniej posiadać zdolność (CAP_KILL), lub muszą się zgadzać.

Lub: mamy zgodność
![](https://i.imgur.com/ZMsrql1.png)

Dla `SIGCONT` wystarczy przynależność obu procesów do jednej sesji.

## 5
![](https://i.imgur.com/mX8DlJC.png)

### Jakie zadania pełni procedura exit(3) z biblioteki standardowej? 
:::info
exit - cause normal process termination

The exit() function causes normal process termination and the least significant byte of status (i.e., status & 0xFF) is returned to the parent (see wait(2)).

All open stdio(3) streams are flushed and closed.  Files created by tmpfile(3) are removed.
:::

### Opisz problemy z buforowaniem plików, które mogą wystąpić dla strumieni biblioteki stdio(3) w przypadku użycia wywołań fork(2), execve(2) i _exit(2).
#### fork(2)
```c=
	pid_t pid;

    fprintf(stderr, "print me only once!");
    //printf("print me only once!\n");
    //fflush(stdout);

    pid = fork();
    pid = fork();
    pid = fork();

    printf("pid = %d\n", getpid());

    exit(0);
```
po fork() -> nowy proces jest dokładną kopią rodzica -> ten sam bufor

#### execve(2)
https://man7.org/linux/man-pages/man2/execve.2.html
utrata zawartości bufora, a dalej możemy mieć otwarte deskryptory

#### exit(2)
zapomnieliśmy zawołać close, przed _exit -> tracimy zawartość bufora

#### Jak zapobiec tym problemom?
3 wyjścia:
- jeśli buforujemy liniami (np. podłączenie z terminalem), dodanie znaku końca linii
- wyłączenie buforowanie przy pomocy `setbuf(3)`
- wywołanie `flush` na strumieniu przed `fork()`

### Jaka jest domyślna strategia buforowania strumienia związanego z: 
#### plikiem terminala 
buforowanie liniami (po napotkaniu '\n' piszemy do pliku)

#### plikiem zwykłym 
buforowanie pełne (piszemy wszystko do bufora aż się zapełni -> wtedy piszemy do pliku)

#### standardowym wyjściem błędów «stderr»
brak buforowania -> by wypisać błędy natychmiast w momencie zdarzenia

### rozwiązanie problemu z przerwaniem SIGINT
Piszesz program który używa biblioteki «stdio». Działanie programu da się przerwać sygnałem «SIGINT».
Ma on wtedy opróżnić wszystkie bufory otwartych strumieni i dopiero wtedy wyjść. Zaproponuj rozwiązanie pamiętając, że w procedurach obsługi sygnału nie wolno korzystać z funkcji, które nie są wielobieżne

Nie możemy korzystać z funkcji które nie są reentrant, czyli bezpieczne są np.
`write()`, `wait()`, `kill()`, `_exit()`, ale nie `exit()`, czy fflush
`tcsflush` jest reentrant -> można go wykorzystać do stdout/stdin/stderr

inne rozw.
```c=
// sig_atomic_t -> data type inside of signal handler (read/write atomic - async signal safe)
// volatile to always check for changes

volatile sig_atomic_t keep_running = 1;
void sig_handler(int sig_n)
{
	if (sig_n == SIGINT)
		keep_running = 0;
}

int main()
{
	signal(SIGINT, sig_handler)
	while(keep_running)
	{
		// program używający stdio
		
	}
	
	// czyszczenie strumieni
	
	return 0;
}
```