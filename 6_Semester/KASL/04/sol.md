# Linux - Lista 4

## Materiały
## Zad 1
### komendy
lepiej -> named file descriptor
`exec 6<test`
`./czytaj 2 <&6 & ./czytaj 1 <&6`

"If the O_APPEND flag of the file status flags is set, the file offset shall be set to the end of the file prior to each write and no intervening file modification operation shall occur between changing the file offset and the write operation."

## Zad 2

### ls
l - long listing -> kolumny
a - wszystkie pliki (. prefix)
A - a ale bez `.` i `..`
R - recursive
S - sort (--sort=none|size|time|version|extension)
t - sort by modif. time
v - natural sort of version numbers
U - do not sort
F - (classify) - dodaje identyfikatory (*, /, =, >, @, |) do wpisów (np. / na koniec katalogu, * - exec, | - FIFO, @ - link, = - socket)
b - C-style escapes for nongraphic character (np. test\ file zamiast ‘test file’)
h - (human-readable), np. rozmiary

i inne

### stat
syscall
informacje o pliku
nazwa, rozmiar, typ, numer i-węzła, liczba dowiązań twardych, uprawnienia, czas dostępu, modyfikacji (zawartość), zmiany (metadane), uid, gid.

![](https://i.imgur.com/TMbJ8b1.png)

-L - follow links
-f - filesystem status
-c - format

### realpath
syscall
resolved absolute file name
(ostatni element nie musi istnieć domyślnie)

-e - wszystkie elementy ścieżki muszą istnieć
-m - odwrotność -||-
-L - rozwiąż .. przed symlinkami
-P - (default) rozwiąż symlink jak na niego natrafisz
-q - quiet
--relative-to=DIR - resolved path relative to DIR
-s - (strip) - nie rozwiązuj symlinków

### readlink
podobnie jak realpath, róznica dotyczy paru opcji
`readlink -f` identycznie jak `realpath`

### dirname
usuwa ostatni element ze ścieżki

dirname etc/file -> etc/
dirname file -> .

### basename
usuwa katalog i sufiks ze ścieżki

-s -> usuwaj sufix

basename /usr/bin/str.h -> str.h
basename -s /usr/bin/str.h -> str

### skrypt
for IMG in *.jpg
do
convert $IMG $(basename $IMG .jpg).png
done


## Zad 3
hostname -> /etc/hostname (nazwa hosta), identyfikacja w sieci np przy ssh
machine-id(5) -> /etc/machine-id, unikalne id systemu
os-release(5) -> /etc/os-release, wersja systemu, nazwa, wersja,  i jakieś linki

## Zad 4
lsof(8) - otwarte pliki
fuser(1) - identyfikacja procesu używające plików bądź gniazd


```bash
lsof -p [pid]

lsof plik

lsof -u [user_name]
```

## Zad 5
strace

-e trace=openat,lseek
-c - zliczanie
-t - czas

## Zad 9

przekierowania sieciowe
specjalny adres: /dev/{udp|tcp}/host/port

cat </dev/tcp/time.nist.gov/13

exec {NETD}</dev/tcp/www.google.com/80
printf 'GET / HTTP/1.0\r\n\r\n' >&$NETD
cat <&$NETD

printf 'Hello world \n' >/dev/udp/127.0.0.1/2560
nc -u -l -p 2560

lsof -i -P -n
echo "test" > /dev/tcp/127.0.0.1/44125 -> sprawdzamy odpowiedz