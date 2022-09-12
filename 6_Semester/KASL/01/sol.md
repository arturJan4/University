# Linux - Lista 1

## Materiały
`~/.bashrc` - skrypt uruchomiający się przy logowaniu (interkatywnie) umożliwiający konfigurację (kolorwanie, uzupełnianie, aliasy, funkcje itp.)

przykład aliasów:
```bash=
alias reload='source ~/.bashrc'
alias edbash='vim ~/.bashrc'
```
będziemy ich używać do edycji i odświeżenia konfiguracji

przykład funkcji:
```bash=
#Make directory & enter it
mkcd() {
   mkdir -p $1
   cd $1
}
```

uwaga co do przekazywania argumentów:
$# -	Number of arguments
$* -	All positional arguments (as a single word)
$@ -	All positional arguments (as separate strings)
$1 -	First argument
$_ - 	Last argument of the previous command

## Zad 1
![](https://i.imgur.com/fF7IiWA.png)

### Wyjaśnienie opcji ll
ls:
- `l`: (long listing format) - jedna kolumna
- `A`: (almost all) - wszystkie pliki (podobnie jak a), ale z pominięciem `.` i `..`
- `F`: (classify) - dodaje identyfikatory (`*`, `/`, `=`, `>`, `@`, `|`) do wpisów (np. `/` na koniec katalogu, `*` - exec, `|` - FIFO, `@` - link, `=` - socket)
- `b`: C-style escapes for nongraphic character (np. test\ file zamiast 'test file')
- `h`: (human-readable), np. rozmiary
- `v`: naturalne sortowanie po wersjach
- -color=always (katalog-niebieski, symlink-cyan, exec-zielony etc, czerwony z czarnym tłem-zepsuty itd.)

stronnicowanie -less:
- `X` (--no-init) - "Disables sending the termcap initialization and
              deinitialization strings to the terminal.  This is
              sometimes desirable if the deinitialization string does
              something unnecessary, like clearing the screen."
- `E` (--QUIT-AT-EOF) 
- `R` (--RAW-CONTROL-CHARS) (r - wyświetla "surowe" znaki kontrolne zamiast notacji z `^`), R robi to samo ale tylko dla znaków kontrolnych opisujących kolor

### polecenie `ll`
używam funkcji by przekazywać argumenty (ścieżki do katalogów)

:::spoiler słabe rozw.
zamieniam powrotnie na alias (przed tą zmianą `ll` nie działało)
```bash=
alias ll='function t() {
  ls $@ -lAFbhv --color=always | less -XER
};t $@'
```
:::


```bash=
function ll {
  ls $@ -lAFbhv --color=always | less -XER
}
```

### polecene `gentmp`
używam: date(1)
`date [OPTION]... [+FORMAT]`
pomocnicze polecenie `date +%Y%m%d%H%M%S`

%Y - to np. YYYY
%m - mm
%H%M%S - hhmmss

chcemy jeszcze dodać napis `tmp-`
```bash=
alias gentmp="date +%Y%m%d%H%M%S"
```

### polecenie `genpwd`
`cat /dev/urandom | head -c 32` -> czyta 32 losowe bajty (`-c` -> bajty)

użyjemy tr(1) do szukania znaków z zadanego podzbioru
- `c` - naszym zbiorem jest dopełnienie podanego
- `d` - usuń znaki z naszego zbioru (czyli z dopełnienia)

`tr -cd '3-9A-HJ-NP-Z'`

finalnie:
```bash=
 alias genpwd="cat /dev/urandom | tr -cd '3-9A-HJ-NP-Z' | head -c 32; echo"
```
(dodałem echo dla znaku nowej linii, TODO: czy jest ładniejsze rozwiązanie niż puste echo?)

## Zad 2 
![](https://i.imgur.com/Rx6qh9Q.png)

grep(1) szuka ciągu znaków pasujących do wzorca(ów) w plikach i wyświetla dopasowane linie

### składnia
```
       grep [OPTION...] PATTERNS [FILE...]
       grep [OPTION...] -e PATTERNS ... [FILE...]
       grep [OPTION...] -f PATTERN_FILE ... [FILE...]
```

jeśli FILE to `-` -> działa na stdin
jeśli żaden FILE nie jest podany -> rekurencyjnie przeszukuje katalog roboczy

### opcje
- E (extended regex - egrep)
- F (fixed string, NOT regex - fgrep)
- G (basic - default)

### opcje 2 - match
- e PATTERN (użyj PATTERN jako wzorzec) -> `grep -e 'abc' -e 'def' -e '123'`
- f FILE (j.w.)
- i (Ignore case)
- --no-ignore-case (default, ale znosi -i w skryptach, które już go używają)
- v (inVert match) - wypisze niepasujące linie
- w (Word regex) - szukamy całego słowa (nie wystarczy prefix) -> `printf "hello\nhell" | grep -w hell`
- x (line regex) - j.w. ale całej linii (podobnie jak `^()$`)

### opcje 3 - output
- c (Count) - licz wystąpienia (linie)
- -color
- l - wypisuje nazwy plików ze znalezionym wzorem (L daje przeciwny wynik)
- m NUM (max) - znajdzie tylko NUM dopasowań
- o (Only matching) - nie wypisuj całej linii, a tylko pasujący fragment
- q (quiet) - wyjdź z 0 jak znajdziemy match
- s (silent) - nic nie wypisuje dla pustych i nieistniejących plików

### opcje 4 - miscel.
- a - przetwarzanie pliku binarnego
- r (recursive)
- -line-buffered -> buforowanie na wyjściu

### regex - podstawy
Regex (regular expression) - wzorzec opisujący zbiór napisów. Budowany przy pomocy róznych operatorów.

uwaga: dla GNU grep==egrep

- podstawowy blok to znak np: `A`, `a`, `3` itp.
- `.` - dowolny znak (oprócz `\n`)
- `[ABCD]` - dowolny znak z podanego w nawiasch zbioru (`[A-D]`), znaki tracą specjalne znaczenie (`]` należy umieścić na poczatku, `-` na końcu, a `^` nie na poczatku)
- jeśli dodamy `^` to `[^ABCD]` oznacza znaki oprócz tych w nawiasie
- `\w`, `\d`, `\s` - słowo, cyfra, biały znak
- `\W`, `\D`, `\S` - NIE słowo, NIE cyfra, NIE biały znak
- dodatkowo mamy aliasy np: `[:digit:]`, `[:alnum:]`, `[:lower:]`
- `^`, `$` - początek, koniec linii
- `\<`, `\>` - pusty napis na początku/końcu słowa
- `(` i `)` grupują

powtarzanie:
       ?      The preceding item is optional and matched at most once.
       *      The preceding item will be matched zero or more times.
       +      The preceding item will be matched one or more times.
       {n}    The preceding item is matched exactly n times.
       {n,}   The preceding item is matched n or more times.
       {,m}   The preceding item is matched at most m times.  This is a
              GNU extension.
       {n,m}  The preceding item is matched at least n times, but not
              more than m times.

konkatencaja działa
alternatywa -> przy pomocy operatora `|` (`Andrzej|Dawid`)

kolejność: powtarzanie -> konkatenacja -> alternatywa (można używać nawiasów by wymusić inną)

https://cheatography.com/davechild/cheat-sheets/regular-expressions/
### przykłady
3 do 9 cyfr:
`grep -E '[[:digit:]]{3,9}' test.txt`

długie słowa:
`grep -E "[[:alpha:]]{15,}" test.txt`

alternatywa:
`grep -E 'fatal|error|critical' error.log`

opcjonalna grupa:
`grep -E '(fear)?less' test.txt`

nr karty mastercard
`^4[0-9]{12}(?:[0-9]{3})?$`
zaczyna się 4, stare karty mają 13 cyfr, nowe 16 (`?:` - non capturing group)

https://emailregex.com/
https://www.regular-expressions.info/email.html
email według RFC 5322
```bash=
(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])
```


## Zad 3
![](https://i.imgur.com/Hc0H6qp.png)
https://man7.org/linux/man-pages/man1/find.1.html

służy do wyszukiwania plików w podanych katalogach
szuka rekurencyjnie w dół drzewa katalogów

### struktura
`find [-H] [-L] [-P] [-D opcje-debugowania] [-Opoziom] [ścieżka...] [wyrażenie]`

traktowanie symlinków (nadpisują się)
- P (default - never follow symbolic links)
- L (follow symbolic link)
- H (do not follow, except while processing command-line arguments)

debugowanie find'a:
- D - debug opts po przecinku
np: 
- exec - informacje z -exec
- search - verbose tree navigation
- stat - stat na obecnie szukanych plikach
- all

optymalizacja:
-Olevel
domyślnie poziom 1 (testy -name, -regex wykonywane pierwsze bo opierają się na nazwach pliku)
poziom 2 -> po testach opartych na nazwach robimy testy `-type` nie wymagające informacji z i-węzła
poziom 3 -> tanie testy pierwsze, droższe później, najbardziej prawdopodobne do znalezienia testy wcześniej (np. `-type f` wcześniej niż `-type c`)

wyrażenie składa się z:
testów, akcjii, opcji globalnych (np. -depth), opcji pozycyjnych, operatorów (-o (or), -a (and)) 

### opcje globalne (niektóre)
- `depth` (najpierw zawartość katalogu a potem obecny katalog)
- `maxdepth levels` i `mindepth levels`
- `mount` - nie schodź do katalogów na innym systemie plików

### kryteria selekcji (niektóre)
`-empty` - pusty blik będący katalogiem lub plikiem zwyczajnym
`-name` - plik o danej nazwie (iname - case insensitive)
`-type` - o danym typie (np. `d` - katalog, `f` - plik normalny, `l` - symlink etc.)
`-group` - należy do grupy o wskazanej nazwie
`-inum` - numer i-węzła mniejszy od
`-iregex` - `regex -i`
`-path` - podobnie jak name, ale radzi sobie z `.`, `/`, `find . -path "./sr*sc"` znajdzie `./src/misc`
`-perm` - bity uprawnień
`-size` - rozmiar

### akcje (niektóre)
- delete
- exec command (TODO)
- ls
- print (default)
- quit (wyjdź po znalezieniu pierwszego pasującego)

### przykłady
symlinki zaczynając w bieżącym katalogu:
`find . -type l`

pliki z rozszerzeniem .js
`find ~ -maxdepth 4 -name '*.js'`

pliki z danymi uprawnieniami:
`find ~ -maxdepth 3 -perm 777`

pliki o danych typach
`find /tmp -type f,d,l`

pliki zmodyfikowane w ciągu ostatnich 24h:
`find $HOME -mtime 0`

usuń znalezione pliki (uwaga: bez -0 działa źle dla plików z cudzysłowem, spacjami i znakiem nowej linii)
`find -print0 | xargs -0`

uruchamia podaną komendę na znalezionych plikach:
`find . -type f -name all_perm -exec chmod 777 {}\;`

`tldr find`

## Zad 4
![](https://i.imgur.com/0Z6LmyJ.png)
https://man7.org/linux/man-pages/man1/rename.1.html

zmienia nazwy plików zmieniając pierwsze wystąpienie szukanego wyrażenia przez podany zamiennik

składnia:
`rename [options] expression replacement file...`

(zainstalowałem rename z apt)
### niektóre opcje 
- v (verbose), wypisz zmienione pliki
- n (nono), no action
- f (force), over write
- d (--nopath, --nofullpath, --filename),, do not rename directory

### przykłady
zamień rozszerzenie .html na .php:
`rename 's/\.html$/\.php/' *.html`

zamień duże na małe litery we wszystkich nazwach plików katalogu 
`rename -n 'y/A-Z/a-z/' *`

przesunięcie o 1
`rename -n 'y/A-Z/B-Z/' *`

kapitalizuj nazwy plików:
`rename 's/((^\w)|(\s\w))/\U$1/g' *` 
\U - uppercase character

usuń sufiks nazwy
`rename -n 's/LE$//' *`

y -> operator z Perl (translacja znak->znak) (też tr)
s -> operator (np. `s/new york/New York/`, `s/new york/New York/gi` - global i case-insensitive)

## Zad 6
![](https://i.imgur.com/UDXVviu.png)

### Listę wszystkich bibliotek współdzielonych zainstalowanych w Twoim systemie.
`sudo find / -regextype grep -regex ".*\.so\(\.[0-9]\+\)\?$"`

np: libhogweed.so.4, libcoreclr.so

### Listę dowiązań symbolicznych do bibliotek współdzielonych zainstalowanych w Twoim systemie.
szukamy dowiązań (flaga `-l`)
potrem robimy readlink z flagą `-f` na wynikach ({} to placeholder nazwy, + - oznacza że wykonujemy dla każdego rezultatu)

rozwiązywanie symlinków:
`find / -type l -exec readlink -f {} +`

dodajemy grep:
`sudo find / -type l -exec readlink -f {} + | grep ".*\.so\(\.[0-9]\+\)\?$"`

### Liczbę, sumaryczny rozmiar w bajtach i średni rozmiar wszystkich bibliotek współdzielonych zainstalowanych w Twoim systemie.
wykorzystyamy polecenie z pierwszego podpunktu do znajdowania plików
`sudo find / -regextype grep -regex ".*\.so\(\.[0-9]\+\)\?$"`

:::spoiler opcja I
dodajemy flagę `-printf` aby określić co wypisujemy
`-printf "%s+\n"` wypisze rozmiar pliku w bajtach i znak +
i używamy kalkulatora `bc`
:::

dodajemy flagę `-ls` do find aby wyświetlić rozmiar pliku (w bajtach) w 7 kolumnie
i używamy awk do liczenia reszty (zmienne n i sum to początkowo 0), END to co robimy na koniec
`awk '{sum += $7; n++;} END {print n, sum, sum/n;}'`

łączymy razem:
`sudo find / -regextype grep -regex ".*\.so\(\.[0-9]\+\)\?$" -ls | awk '{sum += $7; n++;} END {printf "count:%s, sum:%s, average:%s", n, sum, sum/n;}'`

`/snap/core` -> dla szybkiego testu

### Listę (uporządkowaną i bez powtórzeń) wszystkich katalogów, w których występują biblioteki współdzielone.
uporządkowana -> `sort`
bez powtórzeń -> `uniq`

chcemy uciąć nazwę pliku ze ścieżki podawanej przez:
`sudo find / -regextype grep -regex ".*\.so\(\.[0-9]\+\)\?$"`
użyjemy `dirname` (konkretniej `xargs dirname`)

`sudo find / -regextype grep -regex ".*\.so\(\.[0-9]\+\)\?$" | xargs dirname | sort | uniq`

### Listę (uporządkowaną i bez powtórzeń) wszystkich katalogów, w których występują dowiązania symboliczne do bibliotek współdzielonych zainstalowanych w Twoim systemie.
uporządkowana -> `sort`
bez powtórzeń -> `uniq`

na podtawie poprzednich podpunktów:
`sudo find / -type l -exec readlink -f {} + | grep ".*\.so\(\.[0-9]\+\)\?$" | xargs dirname | sort | uniq`


## Zad 7
![](https://i.imgur.com/826JvqP.png)

/usr/share/locale
### Listę wszystkich nazw języków, dla których istnieje plik MO co najmniej jednego programu.
np:
/usr/share/locale/zu/LC_MESSAGES/iso_3166.mo
->
/usr/share/locale/*/LC_MESSAGES/*
chcemy `zu`

`find /usr/share/locale/*/LC_MESSAGES  -name *.mo`
`sed -nr 's#locale/(.*)/LC_MESSAGES#\1#p'` -> matchuje za dużo
rozbijam na 2
`sed -r 's#/usr/share/locale/##'`
`sed -r 's#/.*##'`

na końcu `sort` i `uniq`

`find /usr/share/locale/*/LC_MESSAGES  -name *.mo | sed -r 's#/usr/share/locale/##' | sed -r 's#/.*##' | sort | uniq`
### Listę wszystkich nazw języków, dla których istnieją komunikaty programu dpkg.
analogicznie jak wyżej

`find /usr/share/locale/*/LC_MESSAGES  -name *dpkg.mo | sed -r 's#/usr/share/locale/##' | sed -r 's#/.*##' | sort | uniq`

### Listę wszystkich programów posiadających komunikaty w języku pl.
szukamy w `/usr/share/locale/pl/LC_MESSAGES`
`basename absolute_path suffix` zwraca nazwę pliku bez suffixu

`find /usr/share/locale/pl/LC_MESSAGES -name *.mo -exec basename {} .mo \;`

### Dla każdego z ośmiu rozdziałów podręcznika listę wszystkich nazw języków, dla których istnieje co najmniej jedna strona dokumentacji w danym języku i w danym rozdziale.
/usr/share/man
Pamiętaj że zamiast katalogu en/man1 mamy katalog man1/ itd.

przechodzimy po manach dla różnych locale i wypisujemy numer rozdziału:
`for (( i=1; i<=8; i++ )); do echo; echo "man$i"; find /usr/share/man/*/man$i/ -name *.$i* 2>/dev/null; done`
po man dla eng:
`find /usr/share/man/man$i`

wycinanie języka z locale:
`sed 's#/.*/man/##' | sed 's#/.*##'`

dla en osobno (quit znajduje 1 wystąpienie):
`find /usr/share/man/man$i -name *.$i* -printf 'en\n' -quit`

`for (( i=1; i<=8; i++ )); do echo; echo "man$i"; find /usr/share/man/*/man$i/ -name *.$i* 2>/dev/null | sed 's#/.*/man/##' | sed 's#/.*##' | sort | uniq; find /usr/share/man/man$i -name *.$i* -printf 'en\n' -quit; done`

### Dla każdego z ośmiu rozdziałów podręcznika listę wszystkich stron podręcznika w języku pl
przeglądanie polskich podręczników (błędy do nulla):
`for i in {1..8}; do find /usr/share/man/pl/man$i/ -name *.$i* 2> /dev/null; done`

wycinamy nazwę:
`for i in {1..8}; do find /usr/share/man/pl/man$i/ -name *.$i* 2> /dev/null | sed 's#/.*/##' | sort | uniq; done`

## Zad 9
![](https://i.imgur.com/V9lWlIx.png)

sed(1) - stream editor
filtrowanie i zamiana tekstu

### składnia
można używać innych separatorów zamiast `/` (np. `#`, `|`)

- e (wiele poleceń)
- f (wczytanie skryptu z pliku)
- n (tylko linie wybrane do wypiswania są wypisywane - opcja `/p`, "suppress the default output")
- i edycja pliku in-place

komendy w sed:
- `p` - print
- `d` - delete
- `s` - search and replace (`&` -> match)

### przykłady
wypisz 1 linię
`sed -n '1p' file`

wypisz 5 linii
`sed -n '1,5p' file`

wypisz co 2 linię
`sed -n '1~2p' file`

usuń co 2 linię
`sed '1~2d' file`

dodaj nową linię pomiedzy każdą obecną linią:
`sed 'G' file`

dodaj numer pomiedzy każdą obecną linią:
`sed '=' file`

zamienia 3 pierwsze linie na hello world:
`sed '1,3s/.*/hello world/' file`

zamienia pierwszą instancję w każdej linii:
`sed 's/find/replace' < infile > outfile`

zamienia każdą instancję w każdej linii:
`sed 's/find/replace/g' < infile > outfile`

sed szuka stringów nie słów:
`echo "red is tired" | sed 's/red/green/g'`

usuń linie pasujące do wzorca:
`sed '/pattern/d' file`

kapitalizacja słowa is:
`sed ‘s/is/\U&/’ file`

wiele podstawień:
`sed -e 'comand' -e 'command'` 

usuń spacje na końcu linii:
`sed -i 's/ *$//' file`
tabów:
`sed -i 's/[[:space:]]*$//' file`

zamień 3 na 4 w każdej linii zaczynającej się od 2
`sed '/^2/s/3/4/g' file`

## Zad 10
![](https://i.imgur.com/3WEov3y.png)

skrypt dla sed'a
`sed -f <filename> <data>`

```bash=
sed -e ':loop' -e 't/' -e 't loop'
```