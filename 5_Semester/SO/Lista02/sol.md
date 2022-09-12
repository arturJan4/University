# SO - Lista 2
## Materiały

### Tannenbaum 10.3, 11.4
### Stallings 4.6
Stany procesów i parę pojęć o wątkach i przestrzeniach nazw.

### APUE 8, 10
## Skrypt

## 1
![](https://i.imgur.com/45ZOGfP.png)

### Pojęcia

**Stany procesu** - stan wykonania procesu (executing, ready, suspended, stopped, zombie)
**sen przerwany** - oczekuje na sygnał zewnętrzny
**sen nieprzerwany** - nie oczekuje na sygnał
**blokowanie sygnału** - kernel blokuje dostarczenie sygnału, aż do odblokowania, specyfikowane przez maskę sygnałów
**ignorowanie sygnału** - ignorujemy poprzez zainstalowanie SIG_IGN w sigaction, oczekujący sygnał jest odrzucany (niezależenie czy jest blokowany)

![](https://i.imgur.com/UJA2iw3.png)

### Jakie mamy stany?
- Running (executing/ready) -> aktualnie wykonywany lub oczekujący na wykonanie
- Interruptible -> uśpiony (blocked np. czeka na koniec operacji I/O), ale do wybudzenia przez sygnał zewnętrzny
- Uninterruptible -> uśpiony (blocked) i nie oczekuje na sygnały, czeka na spełnienie pewnych warunków w hardware (sterowniki)
- Stopped -> zatrzymany i może być wznowiony jedynie przez sygnał z innego procesu, np. debuggowany proces
- Zombie -> zakończony, ale dalej w tablicy procesów (czeka na pogrzebanie)

### Które przejścia oraz akcje i zdarzenia
**Ready -> Executing** - scheduling (jądro)
**Executing -> Ready** - scheduling (jądro)

**Executing -> Stopped** -  SIGSTOP
**Executing -> Uninterruptible** - czytanie z pamięci, operacje wewnątrz jądra
**Executing -> Interruptible** - czekanie na sygnał
**Executing -> Zombie** - SIGKILL, exit(), bład I/O -> zakończenie procesu

**Uninterruptible -> Ready** - hardware condition (kod sterownika)

**Interruptible -> Ready** - hardware + sygnały

**Stopped -> Ready** - SIGCONT (proces użytkownika) 

### SIGKILL, SIGSEGV
man signal(7)
![](https://i.imgur.com/VsxSE52.png)

- SIGKILL -> nie można go zablokwać ani zignorować -> maski SIGKILL i SIGSTOP są maskowalne jedynie przez jądro
- SIGSEGV -> może zostać zignorowany (własna obsługa sygnału) lub zablokowany (sigprocmask)

## 2
![](https://i.imgur.com/kSq5AzM.png)

## 3
![](https://i.imgur.com/GgKVlli.png)

### Najważniejsze zasoby procesu dziedziczone przez:
#### proces potomny:
logiczna kopia kontekstu procesu:
-  współdzielony obszar instrukcji (text segment);
-  w nowoczesnych implementacjach, wykorzystywana jest polityka copy-on-write, czyli data space, stack, heap są współdzielone, ale ustawione przez kernel na read-only. Przy próbie modyfikacji jednego z tych miejsc przez którykolwiek z procesów, tworzona jest kopia tylko tego miejsca w pamięci, (zazwyczaj jest to strona w wirtualnej pamięci).
- otwarte pliki (otwarte deskryptory)
- nowemu procesowi jest przydzielany PID oraz PGID jest dziedziczony po rodzicu
 
dodatkowe własności dziedziczone przez dziecko:
- identyfikatory tj. real user ID, real group ID, effective user ID, effective group ID, supplementary groups ID, process group ID, session ID
- terminal sterujący
- flagi set-user-ID oraz set-group-ID
- bieżąca ścieżka robocza (pwd)
- ścieżka root'a 
- maska trybu tworzenia pliku
- maska sygnałów
- flagi close-on-exec dla każdego otwarte deskryptora pliku
- środowisko (env)
- współdzielone segmenty pamięci
- mappowanie pamięci
- limity zasobów


#### nowy program załadowany do przestrzeni adresowej:

```
 int execve(const char *pathname, char *const argv[], char *const envp[]);
```
np.
```
char *newargv[] = { NULL, "hello", "world", NULL };
char *newenviron[] = { NULL };
execve(argv[1], newargv, newenviron);
```

- dla execve jest uruchamiany z pliku, którego ścieżka jest podana w pathname
- dziedziczy takie właściwości jak:
    - PIG i PPID (Process ID and parent process ID), -> id się nie zmienia
    - real user ID i real group ID
    - ID uzupełniających grup (Supplementary group IDs)
    - PGID (Process group ID)
    - Session ID
    - terminal sterujący (controlling terminal)
    - pozostały czas do alarm clock
	- bieżąca ścieżka robocza (pwd)
	- ścieżka root'a 
    - maska trybu tworzenia pliku (file mode creation mask)
	- file locks
	- maska sygnałów
	- oczekujące sygnały
	- limity zasobów
    - wartości dla tms_utime, tms_stime, tms_cutime, tms_cstime

### Czemu przed wywołaniem ```fork``` należy opróżnić bufory biblioteki ```stdio```?

Powinno się je opróżnić z tego względu, że jeśli się tego nie zrobi, to wszystkie bufory ```stdio```, które istnieją w rodzicu, jak i w dziecku, będą np. wypisane/wpisane w rodzicu oraz dziecku.


### Co jądro robi w trakcie wywołania ```execve``` z konfiguracja zainstalowanych procedur obsługi sygnałów?
man signal(7)
![](https://i.imgur.com/DWVXmN0.png)
![](https://i.imgur.com/k9lPzOz.png)
![](https://i.imgur.com/6DPxGPC.png)


Jądro przywraca domyślną obsługę wyłapywanych sygnałów. (z zachowaniem maski sygnałów oraz sygnałów które są ignorowane i oczekujące)

Jeżeli nastąpiłaby sytuacja, że handler jest zdefiniowany w rodzicu, a rodzica by już nie było, to dostalibyśmy segfault. Ewentualnie rodzic mógłby zmienić procedurę obsługi sygnału (a handler to adres kodu procedury).

## 4
![](https://i.imgur.com/dGVEKuC.png)

### Pojęcia
**sygnały oczekujące** - wygnerowane i wysłane ale nie dostraczone sygnały

### Polecenia
po uruchomieniu `xeyes` w osobnym terminalu
```
ps -a
kill (pid)
pkill <nazwa procesu==xeyes>
xkill <kliknięcie na okno procesu>
```
### Domyślne sygnały
`man kill` oraz `man pkill`
kill - TERM
pkill - SIGTERM
xkill - każe XServerowi zamknąć klienta

### zatrzymywanie
`ctrl + z ` - wstrzymuje proces
`fg` lub `bg` wznawia.

### Inspekcja pliku
Zatrzymujemy `xeyes`
i podglądamy w `/proc/<pid>/status`
i seria sygnałów:
```
kill -SIGUSR1 <pid>
kill -SIGUSR2 <pid>
kill -SIGHUP <pid>
kill -SIGINT <pid>
```
```
cat /proc/<pid>/status > filename.txt
diff -u --color before after
```
Interesujące pola to:

**SigQ** - liczba sygnałów oczekujących i limit sygnałów dla tego procesu
**SigPnd, ShdPnd** - maska sygnałów (zapisana w hexie) oczekujących na wątek i proces (signpnd - wątek a shdpnd - proces całościowo)
**SigBlk, SigIgn, SigCgt** - maski sygnałów aktualnie blokowanych, ignorowanych i złapanych

po zrobienu `fg` widzimy na terminalu:
`
Hangup
`
czyli został dostarczony jako pierwszy sygnał Hangup.

## 5
![](https://i.imgur.com/DjK2ZW2.png)

### kod
```c=
/* See LICENSE file for copyright and license details. */
#include <sys/types.h>
#include <sys/wait.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEN(x)	(sizeof (x) / sizeof *(x))
#define TIMEO	30

static void sigpoweroff(void);
static void sigreap(void);
static void sigreboot(void);
static void spawn(char *const []);

static struct {
	int sig;
	void (*handler)(void);
} sigmap[] = {
	{ SIGUSR1, sigpoweroff },
	{ SIGCHLD, sigreap     },
	{ SIGALRM, sigreap     },
	{ SIGINT,  sigreboot   },
};

#include "config.h"

static sigset_t set;

int
main(void)
{
	int sig;
	size_t i;

	if (getpid() != 1)
		return 1;
	chdir("/");
	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, NULL);
	spawn(rcinitcmd);
	while (1) {
		alarm(TIMEO);
		sigwait(&set, &sig);
		for (i = 0; i < LEN(sigmap); i++) {
			if (sigmap[i].sig == sig) {
				sigmap[i].handler();
				break;
			}
		}
	}
	/* not reachable */
	return 0;
}

static void
sigpoweroff(void)
{
	spawn(rcpoweroffcmd);
}

static void
sigreap(void)
{
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
	alarm(TIMEO);
}

static void
sigreboot(void)
{
	spawn(rcrebootcmd);
}

static void
spawn(char *const argv[])
{
	switch (fork()) {
	case 0:
		sigprocmask(SIG_UNBLOCK, &set, NULL);
		setsid();
		execvp(argv[0], argv);
		perror("execvp");
		_exit(1);
	case -1:
		perror("fork");
	}
}

```

nagłowki i stałe
oraz mapa (sygnał -> handler)

```c=
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEN(x)	(sizeof (x) / sizeof *(x))
#define TIMEO	30

static void sigpoweroff(void);
static void sigreap(void);
static void sigreboot(void);
static void spawn(char *const []);

// id sygnału -> wskaźnik na procedurę obsługi sygnału
static struct {
	int sig;
	void (*handler)(void);
} sigmap[] = {
	{ SIGUSR1, sigpoweroff },
	{ SIGCHLD, sigreap     },
	{ SIGALRM, sigreap     },
	{ SIGINT,  sigreboot   },
};

#include "config.h"

static sigset_t set;
```

config.def.h
```c=
static char *const rcinitcmd[]     = { "/bin/rc.init", NULL };
static char *const rcrebootcmd[]   = { "/bin/rc.shutdown", "reboot", NULL };
static char *const rcpoweroffcmd[] = { "/bin/rc.shutdown", "poweroff", NULL };
```

funkcja spawn 
tworzymy nowy proces `fork`, jeśli mamy błąd to dajemy komunikat o błędzie, a jeśli jesteśmy w dziecku to wywołujemy `sigprocmask(SIG_UNBLOCK, &set, NULL)`, które odblokowuje sygnały, które znajdują się w set z obecnie blokowanych. Potem tworzymy nową sesję (`setsid`), której dziecko zostanie liderem. Następnie przy pomocy `exevp` uruchamiamy podane jako argument funkcji polecenie (w.p.p. przy błędzie wracamay z _exit(1))

```c=
static void
spawn(char *const argv[])
{
	switch (fork()) {
	case 0:
		sigprocmask(SIG_UNBLOCK, &set, NULL);
		setsid();
		execvp(argv[0], argv);
		perror("execvp");
		_exit(1);
	case -1:
		perror("fork");
	}
}
```

main
```c=
int main(void)
{
	int sig;			// numer sygnału
	size_t i; 			

	if (getpid() != 1)  // sprawdzamy czy jesteśmy w init
		return 1;
	chdir("/");			// przechodzimy do katalogu głównego
	sigfillset(&set);	// dodajemy do set wszystkie sygnały
	sigprocmask(SIG_BLOCK, &set, NULL); // blokujemy wszystkie sygnały w set
	spawn(rcinitcmd); 	//  uruchamiamy /bin/rc.init
	while (1) {
		alarm(TIMEO);	// co 30s generujemy SIGALRM
		sigwait(&set, &sig); // czekamy aż dostaniemy któryś z sygnałów w set i zapisujemy go do sig
		for (i = 0; i < LEN(sigmap); i++) {
			if (sigmap[i].sig == sig) { // znajdujemy odpowiadający sygnał w mapie
				sigmap[i].handler(); // przechodzimy do procedury obsługi sygnału
				break;
			}
		}
	}
	/* not reachable */
	return 0;
}
```


### Jakie akcje wykonuje pod wpływem sygnałów w sigmap?
```c=
static void sigpoweroff(void)
{
	spawn(rcpoweroffcmd);
}

static void sigreap(void)
{
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
	alarm(TIMEO);
}

static void sigreboot(void)
{
	spawn(rcrebootcmd);
}
```

sigpoweroff -> wyłącza system
sigreboot -> restartuje system
sigreap -> grzebanie dzieci

### Do czego służą sigprocmask i sigwait?
`sigprocmask` - do otrzymywania i zmieniania maski sygnałów dla wołającego wątku, zachowanie zależy od wartości `how = SIG_BLOCK || SIG_UNBLOCK || SIG_SETMASK`
`int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset);`
jeśli `oldset != NULL` to tam przechowamy starą maskę

`int sigwait(const sigset_t *restrict set, int *restrict sig);`
`sigwait` - wstrzymuje wykonywanie wołającego wątku aż otrzyma, któryś z sygnałów w set i dodaje jego numer do sig.

### Jak sinit grzebie swoje dzieci
W funckji `sigreap` mamy

`while (waitpid(-1, NULL, WNOHANG) > 0)`
`waitpid(-1)` czeka na zmianę stanu ("the child terminated; the child was stopped by a signal; or the child was resumed by a signal") któregokolwiek z dzieci,
`WNOHANG` powraca natychmiast jeśli żadne dziecko nie wyszło.

Czyli jeśli żadne dziecko nie wyszło to kończymy pętlę, jeśli zmienił się stan dziecka to waitpid zwróci id czyli pęßla trwa dalej. Błąd też kończy pętlę.
Na koniec ustawiamy SIGALRM na 30 s (TIMEO==30)

## 6
![](https://i.imgur.com/0ILDo2w.png)

### Pojęcia
**kod wyjścia** - liczba zwracana przez proces do procesu nadrzędnego (tzw. procesu-rodzica) po zakończeniu jego działania. W systemach uniksowych (w tym w Linuksie) ma on 8 bitów, co umożliwia zwrócenie liczby z zakresu od 0 do 255. Przyjęło się, że 0 oznacza, iż proces zakończył swoje działanie z powodzeniem, a wszystkie inne liczby – z niepowodzeniem. 


### KOD
```

```

## 7
![](https://i.imgur.com/VHeXPUH.png)

Można zatrzymać ojca -> dostanie wszystkie piłki
jak go wznowimy -> on ma jedną piłkę

### Kod