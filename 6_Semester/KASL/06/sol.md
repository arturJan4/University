# Lista 6
## 1
1.sudo adduser jantest -> cat /etc/passwd

2. sudo usermod -a -gG cdrom,video,audio,bluetooth jantest

audiopulse -> https://dhole.github.io/post/pulseaudio_multiple_users/

`systemctl status bluetooth`
3.
w /etc/sudoers (sudo visudo)
jantest ALL=(root) NOPASSWD: /bin/ip

4.
sudo groupadd projekt
sudo adduser artur projekt
sudo adduser jantest projekt

touch opis.txt
ew. chgrp projekt opis.txt
sudo chown :projekt opis.txt
chmod 770 opis.txt 

5.
groups {artur,jantest}

6.
jantest ALL=(artur) /usr/bin/whoami

7.
CHFN_RESTRICT dodajemy f w /etc/login.defs
chfn -f [imie i nazwisko] [user] na jantest by zmienić
cat /etc/passwd

## 4
sudo chmod 0600 users.txt 
sudo newusers users.txt

## 7
jak na SK
TODO: poczytaj o reszcie
spróbuj zrobić netcat i łapać pakiety
(tekstowy wireshark??)

Korzystam z maszyn wirtualnych, jako że niestety nigdzie nie mam kabla Ethernet, ale to akurat nie zmienia wiele w rozwiązaniu zadania. W obu maszynach ustawiam po jednym interfejsie sieci wewnętrznej nazwane local, jako że z innych nie będziemy korzystać. Na początek warto wypisać wszystkie dostępne interfejsy, służy do tego polecenie ip link, nas szczególnie interesować będzie enp0s3, jako że lo (loopback) to interfejs wirtualny, przez który nie możemy połączyć dwóch maszyn.

Jeśli chcemy połączyć dwie maszyny, należy przypisać każdej z nich jakiś adres IP oraz maskę, wybrałem w tym celu adresy 10.0.1.1/16 oraz 10.0.1.2/16, a następnie uruchomić interfejsy obu maszyn. Wpisuję kolejno polecenia:

`ip addr add 192.168.0.1/24 dev enp0s3`
`ip addr flush dev enp0s3`
`ip link set down dev enp0s3`
`ip link set enpx sy name enp-rem`

VM1# ip addr add 10.0.42.1/16 dev enp0s8
VM1# ip link set enp0s8 up

VM2# ip addr add 10.0.42.2/16 dev enp0s8
VM2# ip link set enp0s8 up

tshark

printf 'Hello world \n' >/dev/udp/10.0.42.1/2560
nc -u -l -p 2560

Poleceniem ip addr add/del [address/mask] dev [device] możemy dodać/usunąć przypisany adres IP do/z wybranego interfejsu, wtedy pingując dowolny z istniejących adresów IP przypisanych do tego interfejsu uzyskamy odpowiedź. Poleceniem ip addr flush dev [device] możemy usunąć całą konfigurację wybranego interfejsu.

Oczywiście ip addr show dev [device] pokazuje właściwości wybranego interfejsu.