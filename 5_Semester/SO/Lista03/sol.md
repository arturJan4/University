# SO - Lista 3

## Materiały
## APUE 7.10 -> setjmp & longjmp
goto w innej funkcji nie działa -> longjmp (nonlocal goto)
zastosowanie -> error handling
przykłady z ramkami stosu

## APUE 10.10, 10.15, 10.21
### 10.10 alarm & pause
timer -> when expiration then signal, (ignoring|not catching -> terminate process)
one per process
call with zero -> cancel previous

pause -> suspend process to catch signal, (return -1, errno=EINTR)

oraz implementacje sleep z pewnymi wadami

### 10.15 sigsetjmp, siglongjmp
## APUE 18.1-18.2, 18.6
## TTY demisitified

## 1
![](https://i.imgur.com/gwJQHyq.png)

**zadanie drugoplanowe** - uruchomione przez shell ale działające niezależnie (bez wejścia od użytkownika), jeśli uruchomione z sesji terminala, to ten terminal jest dalej dostępny
**lider sesji** - jest z reguły proces powłoki. Żeby zostać 
liderem sesji należy utworzyć sesję setsid i ustalić terminal 
sterujący tcsetsid.
**sesja** - pewna liczba grup procesów podłączonych do tego 
samego terminala sterującego
**terminal sterujący** - należy do co najwyżej jednej sesji, można wyświetlić bieżący przy pomocy polecenia `tty`. 

### Sprawdzanie kto jest rodzicem
- (1) `xterm -e 'bash -i' &`
- (2) `sleep 1000 &`
- (2) `ps -o pid,ppid,comm` -> znajdujemy PPID i PID dla bash'a (bash jest rodzicem)

### sigkill do powłoki
- (1) `kill -9 <PID bash>`
- (1) `ps axo pid,ppid,comm | grep sleep` -> znajdujemy PPID sleep'a
- (1) `ps ax | grep <PPID sleep>` -> to jest systemd (default init system)

### sigkill do emulatora terminala
- (1) `xterm -e 'bash -i' &` -> zapisujemy sobie PID terminala
- (2) `sleep 1000 &`
- (2) `ps` -> zapisujemy PID powłoki
- (1) `sudo strace -e trace=signal -p <zapisane PID powłoki>`
- (3) `kill -9 <zapisane PID terminala>`
```
+++ killed by SIGHUP +++
[1]-  Killed                  xterm -e 'bash -i'
```

“The shell exits by default upon receipt of a SIGHUP. Before exiting, an interactive shell resends the SIGHUP to all jobs, running or stopped. Stopped jobs are sent SIGCONT to ensure that they receive the SIGHUP.”


## 2
![](https://i.imgur.com/jCTPQ5J.png)

### Pojęcia
**tryb kanoniczny** - tryb w którym wejście przetwarza się liniami, które są zakończone znakiem nowej linii ('\n'), końca pliku ('EOF'), lub końca linii (EOL)
**kolejka wejściowa** - kolejka do której trafiają znaki wpisane przez terminal, oczekują w niej na przeczytanie i przetworzenie przez jakiś proces
**kolejka wyjściowa** - kolejka do której trafiają znaki wpisane przez proces, oczekują w niej na wyswietlenie 

### Termios

### Zachowanie w trybie kanonicznym
Wejście przetwarza się liniami, które są zakończone znakiem nowej linii ('\n'), końca pliku ('EOF'), lub końca linii (EOL).

Dodatkowo mamy specjalne symbole: **ERASE** oraz **KILL**:
ERASE - usuwa ostatni znak z obecnie czytanej linii
KILL - usuwa całą obecnie czytaną linię
Te symbole nie dają żadnego efektu jeśli linia jest pusta.
Nie są one też wkładane na kolejkę wejściową.

![](https://i.imgur.com/fPNDIv4.png)
1. Urządzenie terminala przekazuje znaki do kolejki wejściowej.
2. (Jeśli włączone jest echo to dodajemy te znaki do kolejki wyjściowej).
3. Proces wykonujący operacje I/O wczytuje znaki z kolejki wejściowej.
4. Proces przekazuje swoje znaki na koleję wyjściową
5. Znaki z kolejki wyjściowej są odczytywane przez urządzenie terminala (i np. wyświetlane użytkownikowi)

### Zmiana konfiguracji podczas wpisywania hasła
`stty -a` -> flagi

`stty -echo` -> wyłączenie echo
Wyłączamy po to by znaki wpisywane przez użytkownika (czyli np. hasło!) nie było wyświetlane na terminalu

### Dlaczego edytory takie jak vi konfigurują sterownik terminala do pracy w trybie niekanonicznym?
W momencie wciśniecia klawisza edytor vi chce mieć dostęp do danych (zamiast czekać na return). To zadaniem programu (vi) jest interpretacja klawiszy.

Dodatkowo niektóre ze skrótów klawiszowych mają swoje własne, inne znaczenie w edytorze np. w vi
ctrl+D - przewiją ekran w dół (domyślnie o połowę)
ctrl+C - wychodzi z insert mode

aplikacja który czyta robie echo (np. nieefektywność ssh)

## 3
![](https://i.imgur.com/rd4LOxM.png)

https://man7.org/linux/man-pages/man1/stty.1.html
![](https://i.imgur.com/CVufVvb.png)

### zarządzanie zadaniami
- intr - CTRL+C - Interrupt (SIGINT)
- quit - CTRL+\ - wyjście (SIGQUIT)
- swtch(non-POSIX)- zmienia na inną warstwę powłoki
- start - CTRL+Q - resetuje wyjście po zatrzymaniu
- stop - CTRL+S - zatrzymuje wyjście
- susp - CTRL+Z - stop (SIGSTOP)

### edycja wiersza
- erase - CTRL+? - usuwa ostatnio wprowadzony znak
- kill - CTRL+U - usuwa obecny wiersz
- eof - CTRL+D - (END-OF-FILE znak końca pliku)
- eol/eol2(non-POSIX) - znak (alternatywny) końca wiersza ("The EOL2 character works just like the EOL character, but it can be a different character. Thus, you can specify two characters to terminate an input line, by setting EOL to one of them and EOL2 to the other. ")
- rprnt(non-POSIX) - CTRL+R - powtórz aktualny wiersz
- werase(non-POSIX) - CTRL+W - usuń ostatnio wprowadzone słowo
- lnext(non-POSIX) - CTRL+V - verbatim: "the next character should be treated literally"-> pozwala np. wpisać ^C
- disard(non-POSIX) - CTRL+O - discardowanie wyjścia

### zmiana rozmiaru okna
`man ioctl_tty`
Sygnał, który informuje o zmianie rozmiaru okna to `SIGWINCH`, który jest wysyłany z jądra do pierwszoplanowej grupy procesów tego terminala.

Rozmiar można pobrać poprzez `TIOCGWINSZ`
a ustawić poprzez `TIOCSWINSZ`

## 4 (TODO)
![](https://i.imgur.com/XpwLi2q.png)

## 5
![](https://i.imgur.com/Wa45MY0.png)

### 1
`cat`
^W -> słowo
^U -> tekst
^S -> stop
^Q -> restart

### 2
`sleep 1000`
^Z -> SIGTSTP
`bg`

### 3
`find /`

CTRL+S używa kodu sterującego, który jest naleciałością z przeszłości.
Umożliwiało to zatrzymanie wypisywania na terminalu (po to by np. nie przegrzać dalekopisu (teletypewriter -> TTY), lub gdy drukarka nie nadążała nad otrzymywanymi danymi (i do tego dalej są wykorzystywane))
CTRL+S -> XOFF flow control command ("stop transmitting")
CTRL+Q -> XON flow control command ("continue")

![](https://i.imgur.com/WxQM3bF.jpg)

Skoro obecnie emulujemy fizyczne terminale to ten kod sterujący pozostał.

CTRL+S, CTRL+Q nie korzysta z sygnałów, blokuje przepływ znaku do konsumującego procesu, korzystając z mechanizmu "Software Flow Control" (standard: DC1-DC4)
W praktyce XOFF (DC3 - ASCI) mówi sterownikowi terminala by uśpił proces wysyłający dane, aż sterownik wyśle XON (DC1 - ASCII).

### 4
`cat -` (pobiera dane ze stanardowego wejścia i je natychmiast wypisuje). 
Uruchomienie w tle (grupa drugoplanowa) sprawia że zadanie nie ma dostępu do STDIN i zostaje wysłany sygnał SIGTTIN. 
(Bo gdyby było wiele zadań drugoplanowych to który powinien czytać z STDIN?)
Zawieszamy więc zadanie (bo najwyraźniej potrzebuje ono być pierwszoplanowe, bo chce czytać STDIN)

SIGTTIN można przechwycić i np. zapisać wtedy do pliku.

`man 7 signal`
`strace cat - &`

### 5
`cat /etc/shells &` - drugoplanowe wypisuje i kończy działanie zadania
Czyli możemy mieć współbieżne wypisywanie
`stty tostop` -> ustawia flagę tostop dla terminala
`strace cat /etc/shells &`
Teraz dla procesów drugoplanowych zablokowane jest również wypisywanie na terminal (stdout)

`tail -f` -> do przeglądania "live"

## 6
![](https://i.imgur.com/4th9nGb.png)

### csapp.h
```c=
/* Setjmp & longjmp implementation without sigprocmask */
typedef struct {
  long rbx;
  long rbp;
  long r12;
  long r13;
  long r14;
  long r15;
  void *rsp;
  void *rip;
} Jmpbuf[1];

int Setjmp(Jmpbuf env);
noreturn void Longjmp(Jmpbuf env, int val);
```

### Setjmp.s
```asm
// stałe
_JB_RBX = 0
_JB_RBP = 1
_JB_R12 = 2
_JB_R13 = 3
_JB_R14 = 4
_JB_R15 = 5
_JB_RSP = 6
_JB_RIP = 7

        .text

        .globl Setjmp
        .type Setjmp,@function
Setjmp(%rdi) == Setjmp(env)
Setjmp:
	movq    (%rsp),%r11				 // zapiusjemy adres powrotu
	movq    %rbx,(_JB_RBX * 8)(%rdi) // zapisujemy rejestry w strukturze w strukturze env w rdi
	movq    %rbp,(_JB_RBP * 8)(%rdi)
	movq    %r12,(_JB_R12 * 8)(%rdi)
	movq    %r13,(_JB_R13 * 8)(%rdi)
	movq    %r14,(_JB_R14 * 8)(%rdi)
	movq    %r15,(_JB_R15 * 8)(%rdi)
	movq    %rsp,(_JB_RSP * 8)(%rdi) // zapisujemy wskaźnik stosu
	movq    %r11,(_JB_RIP * 8)(%rdi) // zapisujemy adres powrotu
	xorl	%eax,%eax				 // zerujemy rax (setjmp zwraca 0 za pierwszym razem)
	ret
        .size Setjmp, . - Setjmp
        
        .globl Longjmp
        .type Longjmp,@function

Longjmp(%rdi, %rsi) == Longjmp(env, status)
Longjmp:
	movq    (_JB_RBX * 8)(%rdi),%rbx  // przywracamy wartości rejesterów  callee-saved
	movq    (_JB_RBP * 8)(%rdi),%rbp
	movq    (_JB_R12 * 8)(%rdi),%r12
	movq    (_JB_R13 * 8)(%rdi),%r13
	movq    (_JB_R14 * 8)(%rdi),%r14
	movq    (_JB_R15 * 8)(%rdi),%r15
	movq    (_JB_RSP * 8)(%rdi),%rsp  // przywracamy wskaźnik stosu
	movq    (_JB_RIP * 8)(%rdi),%r11  // zapisujemy adres powrotu z setjmp do %r11
	movl	%esi,%eax				  // ustawiamy status na %rax (wyniku)
	testl	%eax,%eax				  // sprawdzamy czy %rax == 0
	jnz	1f					
	incl	%eax					  // jeśli %rax == 0 -> %rax == 1 (zgodnie ze specyfikacją)
1:	movq	%r11,(%rsp)				  // wrzucamy adres setjmp na szczyt stosu
	ret								  // jeśli %rax != 1 to zwracamy %rdi == status
        .size Longjmp, . - Longjmp
```

### Dlaczego Jmpbuf nie przechowuje wszystkich rejestrów procesora?
Bo reszta rejestrów jest "caller saved", więc to procedura wołająca setjmp powinna zapisać te rejsetry.
My zapisujemy tylko te "callee saved".

### Czemu Longjmp zapisuje na stos wartość przed wykonaniem instrukcji ret?
Po to by na górze stosu znajdował się adres powrotu z procedury setjmp dla naszego env

## 7
![](https://i.imgur.com/or5Q82k.png)


## 8
![](https://i.imgur.com/MdCD0nm.png)

### Pojęcia