# Sieci- Warsztaty - random notes

## przed
setup maszyna wirtualna

viribian, schowek etc.

## 1
`ip link`
`ip addr`
`dhclient -v enp0s3`
`host -t a example.org`
`systemctl start ssh`
`telnet`
`ping`
`netstat`
`traceroute`
`nc`
`ethtool enp0s3`
`ip link set up dev enp0s3`
`ip addr add 192.168.0.1/24 dev enp0s3`
`ip addr flush dev enp0s3`
`ip link set down dev enp0s3`

## 2
`ip link set enpx sy name enp-rem`
`ip route`
`route -n`
`ping -b`

różnica między komunikatami (adres rozgłoszeniowy, adres sieci, adres poza siecią)

`sudo ip link set enp0s3 name enp-loc`
`sudo sysctl net.ipv4.ip_forward`

`sudo ip route add 192.168.12.0/24 via 172.16.0.2`

`ip route add default via 192.168.12.1`

### wyzwanie
- konfig maszyn
- nazywanie: `sudo ip link set enp0s3 name enp-loc`
- aktywowanie `sudo ip link set up dev enp0s3`
- przypisanie: `sudo ip addr add 192.168.0.1/24 dev enp0s3`

routing:
- V0: `sudo ip route add 192.168.1.0/24 via 192.168.0.2`
- V1: `sudo ip route add default via 192.168.0.1` -> dodanie bramki domyślnej
- V2: `sudo ip route add default via 192.168.1.1`

te pytania na koniec? TODO
to jak działa NAT i 10.0.2.15

https://www.thomas-krenn.com/en/wiki/Network_Configuration_in_VirtualBox

## 3

### przed
zrobiłem migawkę -> czy działa??

### tutorial 1
czy na koniec powinno być każdy z każdym?

`sudo !!`

### tutorial 2
analogiczne

V1 -> 2, 3
V4 -> 1, 2

stworzenie plików:
`
V2#> touch /etc/quagga/ripd.conf
V2#> touch /etc/quagga/zebra.conf
V2#> touch /etc/quagga/vtysh.conf
`
`sudo systemctl start ripd`
vtysh (exit -> end)
configure terminal -> router rip -> version 2 -> network ...
(`no network`)
`show ip rip`
`show running-config`

### Wyzwanie
analogicznie

default gateway:
na V1
`sudo ip route add default via 192.168.0.2`
na V5
`sudo ip route add default via 192.168.4.4`

przykład na V2:
```
sudo ip addr add 192.168.0.2/24 dev enp-loc0
sudo ip addr add 192.168.1.2/24 dev enp-loc1
sudo ip addr add 192.168.2.2/24 dev enp-loc2
```

network w vtysh odpowiada sieciom podłączonym bezpośrednio do obecnej maszyny

### z zajęć
uwaga na promiscous mode

## 4
### przed
- nazywanie: `sudo ip link set enp0s3 name enp-loc`
- aktywowanie `sudo ip link set up dev enp0s3`
- przypisanie: `sudo ip addr add 192.168.0.1/24 dev enp0s3`

wireshark
ip route
+ migawka
### tutorial 1
dla V1:
`sudo ip route add default via 192.168.1.2`
V2:
`sudo ip route add default via 192.168.2.3`
V3:
`sudo ip route add default via 192.168.3.4`
V4
`sudo ip route add default via 192.168.4.1`

V1: traceroute 192.168.3.3

Czy zawsze suma tych ścieżek daje pełny cykl? Dlaczego?

O co chodzi z tym cyklem?
TODO

`sudo ip route del default`
### tutorial 2
```
cd /etc/quagga/
sudo touch ospfd.conf
sudo touch zebra.conf
sudo touch vtysh.conf
sudo systemctl start ospfd
sudo systemctl status ospfd
```

`sudo vtysh`

```=
virbian# configure terminal
virbian(config)# router ospf
virbian(config-router)# network 192.168.x.0/24 area 0
virbian(config-router)# network 192.168.y.0/24 area 0
no network adres sieci area 0
end
show running-config
```

Czy protokół OSPF korzysta z warstwy transportowej czy też jest osadzony bezpośrednio w pakietach IP?

Jaka jest obliczona długość najdłuższej trasy? Dokąd prowadzi?

`sudo ip link set up dev enp-all`
`sudo ip addr add 172.16.16.x/16 dev enp-all` (x-numer maszyny)

```=
sudo vtysh
configure terminal
router ospf
network 172.16.0.0/16 area 0
```
### wyzwanie
V1
local0
V2
local0
V3
local0
local1
V4
local1

V1:
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 192.168.1.1/24 dev enp0
```

V2:
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 192.168.1.2/24 dev enp0
```

V3:
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 192.168.1.3/24 dev enp0
sudo ip link set enp0s8 name enp1
sudo ip link set up dev enp1
sudo ip addr add 192.168.2.1/24 dev enp1
```

V4:
```
sudo ip link set enp0s3 name enp-out
sudo ip link set up dev enp-out
sudo ip addr add 192.168.2.2/24 dev enp-out
```

na V1:
ping 192.168.1.2, 192.168.1.3

na V3:
ping 192.168.1.1, 192.168.1.2
ping 192.168.2.2

dla V1:
`sudo ip route add default via 192.168.1.2`
V2:
`sudo ip route add default via 192.168.1.3`
V4
`sudo ip route add default via 192.168.2.1`

## 5

### przed
V0 -> NAT
sudo ip link set enp0s3 name enp0

V1-V4 -> local0

`sudo ip link set enp0s3 name enp0`
`sudo ip link set up dev enp0`
### 1

wireshark + 
ip addr
`sudo dhclient enp0`

odpalamy klienta, serwer jest na virtualbox

Jakie komunikaty zostają wymienione pomiędzy Twoim komputerem a serwerem DHCP?
Zauważ, że DHCP posługuje się protokołami UDP i IP. Jaki jest źródłowy adres IP
wysyłanego pakietu, skoro w momencie jego wysyłania Virbian0 nie ma jeszcze IP?

jest UDP port:
`cat /etc/services | less`
bootps, następcą jest DHCP (protokół komunikacyjny typu UDP umożliwiający komputerom w sieci uzyskanie od serwera danych konfiguracyjnych)

Dynamic host configuration protocol
unikatowy adres ip dla hostów
https://pl.wikipedia.org/wiki/Dynamic_Host_Configuration_Protocol

DHCP Discover -> na broadcast (szuka serwera DHCP)
DHCP Offer -> serwer wysyła propozycje wszędzie
DHCP Request -> potwierdzenie do serwera
DHCP ACK -> ip, subnet mask, default gateaway, dns server, lease time

jak wygaśnie lease -> DHCPREQUEST z tym samy adresem i może dostać DHCPNACK

`sudo dhclient -r enp0`
DHCP Release

`sudo ip link set down dev enp0`
`sudo ip addr flush dev enp0`

### 2
wireshark na obu 

V1:
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 192.168.0.1/24 dev enp0
```

V2:
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 192.168.0.2/24 dev enp0
```

`ip link` na obu -> MAC kart sieciowych przy enp0
po co rozgłoszeniowy?
adres zródłowy ramki: nasz MAC
docelowy: skąd (?)

`ping 192.168.0.2`

zaglądamy do Ethernet ramek (łącze danych)
-> 3 bajty producenta, 3 unikatowe
dla źródła i dla docelowego
pakiet (warstwa sieciowa):
docelowy, źródłowy, TTL, checskum etc.

jest jeszcze fizyczna ale nie zobaczymy

`ping 192.168.0.255 -b`
teraz jest na broadcast i adres MAC też jest rozgłoszeniowy
a źródłowy taki sam

#### ARP - address resolution protocol
zapytania: kto ma dany IP?
odpowiada jeden komputer
wszyscy odczytują i zapisuja na pewien czas w tablicy

co jeśli mamy dwie różne sieci IP w tej samej sieci warstwy fizycznej?

`ip neigh`
`ip neigh flush all`

1 pytanie ping jest wolniejsze bo trzeba zrobić ARP

`arp-scan`
(uwaga: na ping nie trzeba odpowiadać, a na to tak)

#### kont.
V1: `ip neigh`

`man ip-neighbour`
nud { permanent | noarp | stale | reachable} - stan NUD (ang. Neighbour Unreachability Detection, który ma zostać nadany wpisowi. Możliwe wartości stanów NUD:
permanent - wpis jest poprawny na zawsze, nie ulega przeterminowaniu, może zostać tylko usunięty administracyjnie (np. za pomocą polecenia `ip neigh del ...`).
noarp - wpis jest poprawny, nie będzie weryfikowana jego poprawność, jednak zostanie skasowany automatycznie, jeżeli jego czas życia wygaśnie.
reacheable - wpis jest poprawny do czasu aż czas życia wygaśnie.
stale - wpis jest poprawny, ale podejrzany
failed - wpis nie jest poprawny
delay 

teraz usuwamy (zrestartuj wiresharka wcześniej)
`sudo ip neigh flush all` na obu

znowu `ping -c 1 192.168.0.2`

te ARP wysyłają się co jakiś czas
źródłowy robi na broadcast MAC zapytanie o to kto ma dany adres IP
maszyna która ma ten adres odpowiada jakie ma IP

i widać że to też sprawia że druga maszyna robi podobne zapytanie
(gdyby robić `ip neigh` to widać że DELAY zmienia się w REACHABLE)

`cat /proc/sys/net/ipv4/neigh/enp0/gc_stale_time` -> 60 sekund

. Co jest danymi ramki w przypadku zapytań ARP?
Adres, o który się pytamy oraz adres na który ma odpowiedzieć
. Czy zapytania ARP są wysyłane do konkretnego komputera czy na adres rozgłoszeniowy?
Rozgłoszeniowy
. Czy odpowiedzi ARP są wysyłane do konkretnego komputera czy na adres rozgłoszeniowy?
Do konkretnego komputera

z wykładu wspomniany program: `sudo arp-scan --localnet`

### 3
V1:
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 192.168.0.1/24 dev enp0
```

V2:
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 192.168.0.2/24 dev enp0
```

gdy błąd:
`sudo ip link set down dev enp0`
`sudo ip addr flush dev enp0`

`sudo ip`
`ping 192.168.0.2`
`sudo ip addr del 192.168.0.2/24 dev enp0 && sudo ip addr add 192.168.0.123/24 dev enp0`

reszta to polecenie

V1: `sudo ip addr del 192.168.0.1/24 dev enp0`
V2: `sudo ip addr del 192.168.0.123/24 dev enp0`

### wyzwanie
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add IP dev enp0
    
Virbian1 : 192.168.1.1/24
Virbian2 : 192.168.1.2/25
Virbian3 : 192.168.1.129/24
Virbian4 : 192.168.1.130/25

V1:
192.168.1.0-192.168.1.255 (ostatni rozgłoszeniowy)

V2:
192.168.1.0-192.168.1.127 

V3:
192.168.1.0-192.168.1.255

V4: 
192.168.1.128-192.168.1.255

1   - 0b0 0000001
2   - 0b0 0000010
130 - 0b1 0000010
129 - 0b1 0000001
        |
       25 bit (128)
V1: 
`sudo ip addr add 192.168.1.1/24 dev enp0`
   
V2: 
```
sudo ip addr add 192.168.1.2/25 dev enp0
```

V3:
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 192.168.1.129/24 dev enp0
```

V4:
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 192.168.1.130/25 dev enp0
```

Z maszyny Virbian1 pingnij jej adres rozgłoszeniowy, a następnie odpowiedz na następujące pytania:
+ wiresharki na any
`ping -c 1 192.168.1.255 -b`

Które maszyny otrzymały komunikat ICMP echo request? Które nie otrzymały i
dlaczego?
wszystkie otrzymują bo tamte adresy to podzbbiór
(ta sama sieć i podsieci)
a dostają na MAC rozgłoszeniowy

Które maszyny wysłały w odpowiedzi komunikat ICMP echo reply? Które nie wysłały i dlaczego?
V1 odsyła, ale na warstwie łącza loopback
V2 nie bo ma inny broadcast (inna podsieć)
V3 odsyła (zgodny broadcast, i jest w podsieci)
V4 nie bo nie wie jak odesłać do nadawcy -> `ip route`

Które odpowiedzi dotarły do maszyny Virbian1 ? Które nie dotarły i dlaczego?
wszystkie dotarły

I Wykonaj powyższy punkt, ale z maszyny Virbian2, z maszyny Virbian3, a na końcu
z maszyny Virbian4.

#### z V2
`ping -c 1 192.168.1.127 -b`
Które maszyny otrzymały komunikat ICMP echo request? Które nie otrzymały i
dlaczego?
Wszystkie otrzymują

Które maszyny wysłały w odpowiedzi komunikat ICMP echo reply? Które nie wysłały i dlaczego?
tylko V2 do siebie na loopback (`ip route show table local`) -> reszta jest w innych podsieciach

Które odpowiedzi dotarły do maszyny Virbian1 ? Które nie dotarły i dlaczego?
wszystkie dotarły
Dotarły wszystkie czyli żadna (oprócz lo)

#### z V3
`ping -c 1 192.168.1.255 -b`
Które maszyny otrzymały komunikat ICMP echo request? Które nie otrzymały i
dlaczego?
Wszystkie otrzymują

Które maszyny wysłały w odpowiedzi komunikat ICMP echo reply? Które nie wysłały i dlaczego?
V1 odsyła (ten sam adres rozgłoszeniowy)
V2 nie (inna podsieć)
V3 odsyła (przez loopback)
V4 odsyła bo mimo bycia w innej podsieci adres komputera pingującego (tj. .129 jest w zakresie V4: 192.168.1.128-192.168.1.255)

Wszystkie wysłane dotarły

#### z V4
`ping -c 1 192.168.1.255 -b`
Które maszyny otrzymały komunikat ICMP echo request? Które nie otrzymały i
dlaczego?
wszystkie otrzymują

Które maszyny wysłały w odpowiedzi komunikat ICMP echo reply? Które nie wysłały i dlaczego?
V1 tak, bo ten sam adres rozgłoszeniowy
V2 nie bo ma inny broadcast (inna podsieć -> `ip route`
V3 odsyła (ten sam rozgłoszeniowy)
V4 odsyła bo loopback

Które odpowiedzi dotarły do maszyny Virbian1 ? Które nie dotarły i dlaczego?
wszystkie docierają przy czym trzeba zwrócić uwagę że V3 wysyła do V1 zamiast bezpośednio przez local0 do V4

I Zdekonfiguruj interfejsy enp0 i wyłącz wszystkie maszyny

`sudo ip link set down dev enp0`
`sudo ip addr flush dev enp0`

## 6

### przed
```
sudo ip link set enp0s3 name enp0
sudo dhclient -v enp0
```

### 1
`dig www.debian.org` -> 130.89.148.77
`su -` -> root
`(while true; do netstat -tan | grep 130.89.148.77; done) | tee tcp_log`
`wget http://130.89.148.77/`

Proto Recv-Q Send-Q Local Address           Foreign Address         State 

https://en.wikipedia.org/wiki/File:Tcp_state_diagram.png
wireshark (tcp_log po wysłaniu i zatrzymaniu drugiego terminala)
+github

### 2
`dig www.cs.uni.wroc.pl @198.41.0.4` -> np. 194.181.87.156
`dig www.cs.uni.wroc.pl @194.181.87.156`
https://pl.wikipedia.org/wiki/Domain_Name_System -> refresh, typy rekordów
etc.
https://en.wikipedia.org/wiki/List_of_DNS_record_types
`dig www.cs.uni.wroc.pl @bilbo.nask.org.pl`
`dig www.cs.uni.wroc.pl @hera.math.uni.wroc.pl`
`dig cs.uni.wroc.pl @198.41.0.4`

`dig +trace www.cs.uni.wroc.pl @198.41.0.4` + wireshark

`dig -t a ii.uni.wroc.pl` (t to type)
`dig -t ns ii.uni.wroc.pl`
`dig -t mx ii.uni.wroc.pl`

`dig -t ptr 11.4.17.156.in-addr.arpa` -> reverse DNS lookup

### 3
`nc -u -l -p 10053`
`dig -p 10053 www.wikipedia.pl @127.0.0.1 +tries=1` -> drugie okno
`nc -u -l -p 10053 | tee dns_request`
`hexdump -C dns_request` -> to co w wireshark
`nc -q 1 -u 8.8.8.8 53 < dns_request` -> i fajnie w wiresharku widać

### Wyzwanie
`systemctl start hyderpark`
`systemctl status hydepark`

wyłącz force-https:
dom.security.https_first_pbm

`nc -q 3 virbian 8080 < http_request`
proxy
nowy komunikat -> wating for (bo request jest przechwytywany przez proxy 8888)
htt_request -> cat


``:set nolist`
`tail -n +15 http_request | wc -c  `
`tail -n +15 http_request | awk '{$1=$1;print}' | wc -c`
`nc -q 3 virbian 8080 < http_request`


## 7

### 1
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 10.0.0.1/8 dev enp0
```
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 10.0.0.2/8 dev enp0
```
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 10.0.0.3/8 dev enp0
```

sudo vim
/etc/hosts:
10.0.0.1 mail.example.com

V1:
```
systemctl start postfix
systemctl start dovecot
```

```
student2@mail.example.com
```

```
openssl s_client -quiet -connect mail.example.com:25 -starttls smtp
```

### 2
->NAT
```
sudo dhclient -v enp0
```



### Wyzwanie
```
sudo ip addr flush dev enp0
ip sudo link set down dev enp0
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 10.0.0.2/8 dev enp0
```