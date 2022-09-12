# SO - Lista 9

## 2
![](https://i.imgur.com/GWAMGEj.png)

### Materiały
#### TCP
https://man7.org/linux/man-pages/man7/tcp.7.html
![](https://i.imgur.com/Glu5FUM.png)
### UDP
https://man7.org/linux/man-pages/man7/udp.7.html
![](https://i.imgur.com/V9FBooH.png)
![](https://i.imgur.com/B4izUxy.png)


### Pojęcia
**Protokół datagramowy (UDP)** - prosty protokół warstwy transportowej, pozwala przesyłać datagramy pomiędzy komputerami podłączonymi do sieci komunikacyjnej.
Aplikacja zapisuje wiadomość do gniazda UDP, następnie enkapsuluje to w postać datagramu UDP, który jest następnie dalej enkapsulowanu do datagramu IP, który jest już wysyłany do miejsca docelowego. Nie ma wielu gwarancji.

**Protokół połączeniowy (TCP)** - nawiązuje sesję(logiczne połączenie) pomiędzy dwoma utworzonymi wcześniej nazwami. Nie muszą one znajdować się na dwóch różnych stacjach. Można dokonywać połączeń w ramach jednej maszyny, a nawet procesu.
TCP zapewnia połączenie między klientami a serwerami. Klient TCP tworzy połączenie z danym serwerem, wymienia dane z nim oraz kończy połączenie.

**Segment** - informacje złożone z nagłówka oraz pola danych.

**sterowanie przepływem** - limit przepustowości wysyłanych danych (jak dużo w danej jednostce czasu)

### omów różnice między tcp a udp
![](https://i.imgur.com/AuezBSc.jpg)

protokół UDP jest zawodny: mogą nie dotrzeć do miejsca docelowego (albo dociera ale checksum wykrywa błąd i nie ma ponownego wysłania), mogą dotrzeć w złej kolejności, mogą powstawać duplikaty lub fragmentacje datagramów.
Programista chcący danych gwarancji musi więc zaimplementować je samodzielnie w swojej aplikacji. (potwierdzenia, retransmisje, timeouty itp.)
Jest natomiast szybszy bo nie musi oczekiwać na reakcję serwera (jest dzięki temu "connectionless", możemy stworzyć socket wysłać datagram na serwer A i natychmiastowo wysłać przez to samo gniazdo na serwer B, i vice-versa datagramy z różnych klientów mogą trafiać na to samo gniazdo)

protokół TCP nawiązuje połączenie pomiędzy klientem, a serwerem. TCP grupuje przesyłane dane w segmentu i przesyła w kolejności do miejsca docelowego.
Jest niezawodny (reliable), w znaczeniu, że oczekuje na potwierdzenie odbioru danych. Jeśli nie otrzyma takiego potwierdzenia to wysyła dane ponownie i powtarza to (określoną liczbę razy, 4-10min). 
Po odbiorze segmentu są one sortowane do porządku wysłania oraz zostają naprawione błędy tj. n.p. duplikaty (w wyniku retransmisji).

### Czym różni się komunikacja półdupleksowa od dupleksowej?
półdupleksowa (half duplex/semidupleks) - przesyłanie i odbieranie infroamcji odbywa się naprzemiennie (np. walkie-takie, CB-radio)

dupleksowa (full duplex) - informacje przesyłane w obu kierunkach jednocześnie (a zatem nie ma spadku prędkości transmisji), np. TCP (UDP może być full-duplex)

### Jak TCP radzi sobie z zagubieniem segmentu lub faktem, że segmenty mogą przyjść do odbiorcy w innej kolejności niż zostały wysłane?
TCP oczekuje potwierdzenia otrzymania segmentu, po pewnym czasie próbuje wysłać ponownie (i tak powtarza określoną liczbę razy).

TCP sortuje segmenty względem kolejności wysłania (na podstawie metadanych segmentów)

### Skąd protokół TCP wie kiedy połączenie zostało zerwane
TCP oczekuje potwierdzenia otrzymania segmentu, może wysłać kontrolny, pusty pakiet. Jeśli kilukrotnie nie otrzyma potwiedzenia otrzymania pustego pakietu to może podejrzewać, że zerwano połączenie.

Natomiast gdy strona chce zerwać połączenie to wysyła segment z informacją o końcu, wtedy druga potwierdza i obie zamykają połączenie.

### Jaki problem rozwiązuje sterowanie przepływem (ang. flow control) implementowane przez TCP?
TCP chce uniknąć sytuacji, gdy przytłoczy odbiorcę segmentami, a ten nie nadąża z ich przetwarzaniem (co może doporowadzić do przepłnianie buforu odbiorcy). Może to też wynikać z różnych prędkości sieciowych skomunikowanych maszyn.
Posługuje się tzw. "advertised window", które dynamicznie zmienia rozmiar i określa dostępny rozmiar buforu odbiorcy danych. (rozmiar może osiągnąć 0)

## 3
![](https://i.imgur.com/HbETEly.png)

### Materiały
https://man7.org/linux/man-pages/man7/tcp.7.html
https://man7.org/linux/man-pages/man2/listen.2.html
https://man7.org/linux/man-pages/man2/accept.2.html

+ slajdy z wykładu

The Sockets Networking API - [7]

### Omów diagram [7, 4.1] komunikacji klient-serwer używającej protokołu tcp(7) przy pomocy interfejsu gniazd strumieniowych.
![](https://i.imgur.com/mX2Pikx.png)

Najpierw startuje serwer, który tworzy gniazdo.
bind łączy adres gniazda serwera (`myaddr`) z danym deskryptorem (`sockfd`)
[7, 4.2]. Następnie `listen` sprawia, że gniazdo jest pasywne a `accept` służy do akceptowania requestów.

Klient startuje, tworzy gniazdo i przy pomocy connect łączy się do wystartowanego wcześniej serwera (prośba musi zostać zatwierdzona i zwrócona).

Gdy nastąpiło połączenie jesteśmy w pętli write-read, gdzie klient wysyła żądanie, serwer je przetwarza iz wraca odpowiedź co jest kontynuowane aż do zamknięcia swojego końca połączenia przez close(), serwer po otrzymaniu informacji także zamyka swój koniec (i kończy działanie lub czeka na nowego klienta).

### W którym momencie następuje związanie gniazda z adresem lokalnym i zdalnym?
![](https://i.imgur.com/KXtufbJ.png)
wiąże adres lokalny serwera z gniazdem

![](https://i.imgur.com/mWniUwj.png)
klient nie musi wołać `bind`, podaje adres IP i port serwera w `connect`

### Która ze stron komunikacji używa portów efemerycznych (ang. ephemeral)?
**porty efemeryczne** - krótko żyjące porty, zwykle przypisane automatycznie przez protokół transportortowy. Klienta zwykle nie obchodzi wartość takiego portu, a tylko to że jest unikatowy (a to gwarantuje protokół) na hoście. 
Według IANA są wybierane z puli 49152 (3/4 * 65536) do 65535

Klienci zwykle używają portów efemerycznych, nastomiast serwer korzysta z tzw. "well-known", np. HTTP==80, HTTPS=443, SSH=22

### Co specyfikuje drugi argument wywołania systemowego listen(2)?
![](https://i.imgur.com/Vi7jvEI.png)

Specyfikuje maksymalną liczbę połączeń jakie jądro powinno kolejkować dla danego gniazda.

Konkretniej kernel ma dwie kolejki:
1) Niezakończonych połączeń (czekających na three-way handshake), w stanie SYN_RCVD
2) zakończonychh połączeń (wpis dla każdego klienta który zakończył three-way handshake) w stanie ESTABLISHED

![](https://i.imgur.com/bvylHaI.png)


### Z jakim numerem portu jest związane gniazdo przekazywane do i zwracane z accept(2)?
![](https://i.imgur.com/cAwIcDV.png)

`sockfd` to pasywne (nasłuchujące) gniazdo utworzone i przypisane (`bind`) przez serwer do lokalnego adresu i portu (zwykle `well-known`)

zwracany deskryptor odnosi się to połączenia z klientem, (więc z jego portem efemerycznym)


### Skąd serwer wie, że klient zakończył połączenie?
![](https://i.imgur.com/Zn3mLck.png)
![](https://i.imgur.com/jI2TJjc.png)

1) Jedna strona wykorzystuje `close(2)` (active close) i wysyła segment FIN.
2) Strona otrzymująca FIN wykonuje passive close. Otrzymanie tego segmentu jest tez przekazywane jako EOF do aplikacji (po wszystkich danych jeszcze w kolejce do otrzymania), ponieważ na tym połączeniu nie będzie więcej informacji.
3) Po jakimś czasie aplikacja która dostała EOF zamyka swoje gniazdo i też wysyła FIN
4) strona wykonująca active close potwierdza otrzymanie FIN (ACK)


## 4
![](https://i.imgur.com/8mzkQg5.png)

### Materiały
https://man7.org/linux/man-pages/man2/bind.2.html
https://man7.org/linux/man-pages/man7/udp.7.html
https://man7.org/linux/man-pages/man2/read.2.html
https://man7.org/linux/man-pages/man2/write.2.html
https://man7.org/linux/man-pages/man2/recvfrom.2.html
https://man7.org/linux/man-pages/man2/sendto.2.html
https://man7.org/linux/man-pages/man2/connect.2.html
https://man7.org/linux/man-pages/man2/recvmsg.2.html
https://man7.org/linux/man-pages/man2/sendmsg.2.html

[7, 8.1], [7, 8.11]

### Omów diagram [7, 8.1] komunikacji klient-serwer używającej protokołu udp(7) przy pomocy interfejsu gniazd datagramowych.
![](https://i.imgur.com/LMx4uIf.png)

Podobnie jak w zad 3, serwer startuje tworzy gniazdo, łączy z lokalnym adresem i well-known portem, ale zamiast listen wykorzystuje `recvfrom`.

Klient w kontraście do TCP nie nawiązuje połączenia z serwerem, a wysyła datagram przy pomocy funkcji `sendto`, która przyjmuje adres serwera docelowego jako argument.

Serwer zamiast akceptować połączenie, to czeka przy pomocy `recfrom` na dane od klienta (którego nie zna). `recvfrom` zwraca adres klienta, wraz z datagramem (dzięki czemu serwer może wysłać odpowiedź we właściwe miejsce)

### Czemu, w przeciwieństwie do TCP, serwer może rozpocząć pracę zaraz po wykonaniu funkcji bind(2)? 
Nie musimy nawiązywać połączenia za pomocą `listen`, `accept` i `connect`.
Wysyłamy datagram "i liczymy że dotrze".

(Nie ma też więc zamykania połączeń)

### Z jakiej przyczyny interfejs read(2) i write(2) po stronie serwera może być niewystarczający? 
UDP może natychmiastowo zmieniać wykorzystanie gniazda (tj. do jakiego serwera chcemy się łączyć oraz gniazdo serwera nie oczekuje konkretnego adresu klienta (może się łączyć wiele urządzeń)).

Read(2) i Write(2) nie pozwalają na podanie adresu docelowego.

### Przedstaw semantykę operacji recvfrom(2) i sendto(2).
na podstawie [7, 8.2]
![](https://i.imgur.com/PNQy1EQ.png)

`sockfd`, `buff`, `nbytes` -> oczywiste (tak jak read/write)
argument `to` w `sendto` oznacza strukturę adresu (IP + port) gdzie chcemy wysłać dane, rozmiar tej struktury jest przekazywany w `addrlen`.
arguemnt `from` w `recvfrom` jest wypełniany jako adres tego kto wysład datagram, a rozmiar struktury jest zapisywany w addrlen (dlatego to wskaźnik).
jeśli from jest NULL to długość powinna być pustym wskaźnikiem i to oznacza, że nie interesuje nas kto wysłał dane

dwa ostatnie argumenty `recvfrom` przypominają dwa ostatnie `accept`
dwa ostatnie argumenty `sendto` przypominają dwa ostatnie `connect`

obie funkcje zwracają długość zapisanych/wczytanych danych
datagram o długości 0 -> 8-byte UDP header + no data

obie te funkcje mogą być wykorzystywane w TCP (ale zwykle nie ma potrzeby)

### Kiedy po stronie klienta następuje związanie gniazda UDP z adresem lokalnym?
Przy połączeniu UDP jeśli lokalny port nie był jeszcze związany to wybierany jest port efemeryczny.

UDP jest bezpołączeniowe, więć by doszło do powiązania to klient musi wykorzystać `bind` (co jest rzadko używane ([7, 8.6]))

### Na podstawie [7, 8.11] zreferuj efekt jaki przynosi wykonanie connect(2) na gnieździe klienta

Nie działa to jak w TCP: nie powoduje, że zachodzi three-way handshake.
Zamiast tego jądro sprawdza natychmiastowe błędy (np. niedostępny adres docelowy), zapisuje adres i port docelowy (ze struktury podanej w `connect`) i wraca do procesu wołającego.

Mamy więc połączenie gniazdo UDP i niepołączone gniazdo UDP.

3 zmiany w porównaniu do niepołączonego:
1) zamiast `sendto` używamy write/send, co oznacza, że nie możemy specyfikować docelowego IP i portu za każdym razem, a dane są automatyczniew wysyłane do zapisanego przez `connect`. (Możemy użyć sendto ale trzeba wyzerować argumenty do struktury i jej rozmiaru)
2) zamiast `recvfrom` używamy read/recv/recvmsg, datagramy które przychodzą z nieznanego adresu nie są przekazywane do gniazda (mamy jeden-do-jeden)
3) asynchroniczne błędy są zwracane do procesu gniazda

![](https://i.imgur.com/8eqrOzP.png)


### Jakie ograniczenia poprzednio wymienionych funkcji zostały poprawione przez wywołania recvmsg(2) i sendmsg(2)?
![](https://i.imgur.com/bWxelLD.png)

`msg_iov` oraz `msg_iovlen` opisują tablicę buforów wejściowych i wyjściowych (tablicę struktur `iovec`).

Przy pomocy buforów możemy jednym wywołaniem recvmsg zapełnić wiele mniejszych buforów, gdy chcemy otrzymać więcej danych. (oszczędność syscalli przy wielokrotnym wysyłaniu mniejszych pakietów)

dodatkowo mamy dostęp do flag kontrolnych, ancillary data, i pół nagłowka pakietu.

## 6 (TODO)
![](https://i.imgur.com/2fkjVNw.png)


### Kod
```c=
#include "csapp.h"

int main(int argc, char **argv) {
  struct addrinfo *p, *listp, hints;
  char buf[MAXLINE];
  char buf2[MAXLINE]; // dodatkowy bufor na service
  int rc, flags;

  if (argc < 2 || argc > 3) // dodajemy nowy argument
    app_error("usage: %s <domain name> [<service>]\n", argv[0]);

  /* Get a list of addrinfo records */
  memset(&hints, 0, sizeof(struct addrinfo));
  // https://man7.org/linux/man-pages/man2/socket.2.html
  hints.ai_family = AF_UNSPEC; /* IPv4 & IPv6 (unspecified) */
  // tftp == trivial file transfer protocol (UDP)
  hints.ai_socktype = SOCK_STREAM; // use SOCK_DGRAM (datagrams) -> tftp
  /* Connections only */
  if ((rc = getaddrinfo(argv[1], argv[2], &hints, &listp)) != 0) // pass service as 2nd argument
    gai_error(rc, "getaddrinfo");

  /* Walk the list and display each IP address */
  flags = NI_NUMERICHOST | NI_NUMERICSERV; /* Display address string/service string instead of domain name/service name */
  for (p = listp; p; p = p->ai_next) {
    Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, buf2, MAXLINE, flags); // additionaly pass buf2 with MAXLINE
    
    if (argv[2]) {
      if(p->ai_family == AF_INET6) // IPv6 format
        printf("[%s]:%s\n", buf, buf2);
      else
        printf("%s:%s\n", buf, buf2);
    }
    else 
      printf("%s\n", buf);
  }

  /* Clean up */
  freeaddrinfo(listp);

  return EXIT_SUCCESS;
}
```