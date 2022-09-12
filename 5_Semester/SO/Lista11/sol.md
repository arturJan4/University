# SO - Lista 11

## Materiały
https://www.nongnu.org/ext2-doc/ext2.html

## 2
![](https://i.imgur.com/9Rlz9eY.png)

### Pojęcia
![](https://i.imgur.com/LXXlq5n.png)
![](https://i.imgur.com/dDiW7TU.png)


#### Superblok (superblock)
Przechowuje najważniejsze właściwości systemu plików.

zawiera m.in:
- rozmiar bloków -> konkretniej s_log_block_size
- rozmiar inode (doskonała potęga 2, ale mniej lub równa rozmiarowi bloku)
- liczbę inode (wolnych i używanych w systemie plików)
- liczbę bloków (wolnych, używanych i zarezerwowanych)
- liczbę bloków zarezerwowanych dla super-user'a (np. gdy z jakiegoś powodu zapełni się reszta przestrzeni: błąd albo atak to warto zostawić przestrzeń dla edycji/naprawy plików konfiguracyjnych)
- liczbę wolnych bloków (zawiera zarezerwowane) (suma dla wszystkich grup bloków)
- liczbą bloków na grupę
- liczbą inode na grupę (definiuje dodatkowo rozmiar bitmapy)
- czas ostatniego zamontowania
- czas ostatniego zapisu
- stan systemu plików
i wiele innych (ale według mnie mniej interesujących)

Podstawowa kopia jest przechowywana na offsecie 1024 bajtów od początku. Dodatkowo mamy kopie zapasowe wewnątrz systemu plików (revision >= 1 -> grupy: 0, 1 i potęgi 3, 5, 7)

pola przechowywane są w formacie little-endian

#### Blok (block)
Grupa sektorów na która została podzielona partycja/dysk/plik/urządzenie blokowe sformatowane przy pomocy EXT2

częste rozmiary bloków: 1KiB, 2KiB, 4KiB and 8KiB, ale superblok zezwala na `1024 * (2^31)-1`

#### Grupa bloków (block group)
Bloki są łączone w grupy by zmniejszyć fragmentację i zminimalizować sumaryczyny seek-time dla głowicy.
Dwa bloki blisko staru każdej grupy są zarezerwowane dla bitmapy opisującej zużyte bloki i bitmapy opisującej i-węzły. Maksymalny rozmiar to 8 * (rozmiar bloku). Po tych bitmpaach mamy tablicę i-wezłów i bloki danych. 

#### Tablica deskryptorów grup bloków (block group descriptor table)
Znajduję się zaraz po superbloku, opisuje grupę bloków (położenie i rozmiar bitmapy bloków i i-węzłów każdej grupy).

### Korzystając z pól superbloku (ang. superblock) podaj wzór na wyliczenie wartości: rozmiaru bloku, liczby i-węzłów i bloków przechowywanych w grupie bloków (ang. block group), liczby wpisów tablicy deskryptorów grup bloków (ang. block group descriptor table). 

#### rozmiar bloku: 
na podstawie pola `s_log_block_size`
> **s_log_block_size**
The block size is computed using this 32bit value as the number of bits to shift left the value 1024. This value may only be non-negative.

`block size = 1024 << s_log_block_size;`

#### liczba i-węzłów i bloków
> **s_inodes_per_group**
32bit value indicating the total number of inodes per group. This is also used to determine the size of the inode bitmap of each block group. Note that you cannot have more than (block size in bytes * 8) inodes per group as the inode bitmap must fit within a single block. This value must be a perfect multiple of the number of inodes that can fit in a block ((1024<<s_log_block_size)/s_inode_size). 

> **s_blocks_per_group**
32bit value indicating the total number of blocks per group. This value in combination with s_first_data_block can be used to determine the block groups boundaries. Due to volume size boundaries, the last block group might have a smaller number of blocks than what is specified in this field. 

#### liczba wpisów tablicy deskryptorów grup bloków
Deskryptorów grup bloków jest tyle samo co grup bloków ("For each block group in the file system, such a group_desc is created. ") 

Liczbę tą można policzyć w następujący sposób:
`s_blocks_count / s_blocks_per_group`

### Wymień składowe należące do grupy bloków oraz podaj ich rozmiar w blokach. 
![](https://i.imgur.com/CHuVqYl.png)

Kopia superbloku (lub nie) -> 1 blok
Kopia deskryptorów grupy (tam gdzie jest też superblok) -> rozmiar (w blokach) zależy od ilości grup (`s_blocks_count / s_blocks_per_group`)
bg_block_bitmap (data bitmap na grafice) - 1 bit opisuje 1 blok w obecnej grupie (used/free) -> zawsze 1 blok (czyli max ROZMIAR BLOKU * 8 bitów do wykorzystania w bitmapie)
bg_inode_bitmap (inode bitmap) - 1 bit opisuje inode w inode table -> 1 blok
tablica i-węzłów - 1 na grupę bloków, `s_inodes_per_group` i-węzłów na grupę w tej tablicy
bloki danych


### Które grupy bloków przechowują kopie zapasową superbloku i tablicy deskryptorów grup bloków?
>The first version of ext2 (revision 0) stores a copy at the start of every block group, along with backups of the group descriptor block(s). Because this can consume a considerable amount of space for large filesystems, later revisions can optionally reduce the number of backup copies by only putting backups in specific groups (this is the sparse superblock feature). The groups chosen are 0, 1 and powers of 3, 5 and 7. 

## 3
![](https://i.imgur.com/71lp1M7.png)

### Pojęcia
![](https://i.imgur.com/dDiW7TU.png)

#### Blok pośredni (indirect blok)
![](https://i.imgur.com/FwJFej8.png)

Sposób na zawarcie większej ilości danych w i-węźle (większe pliki) poprzez wykorzystanie wielopoziomowych struktur ze wskaźnikami na kolejne aż do direct bloku.

#### Zapis synchroniczny
wymuszamy czekanie na zakończenie operacji IO przed kontynuacją pracy, nie buforujemy operacji.

#### Spójność systemu plików
stan zachowujący sensowną strukturę wewnętrzną systemu plików (katalogi, i-węzły, mapy wolnych bloków itd.), czyli np. poprawnie zaincjalizowane struktury, brak konfliktów (dwa pliki korzystają w jednym momecnie z tego samego bloku), brak wiszących zasobów (niezaalokowany, a używany blok).

Chcemy aby po awarii (np. brak zasilania) system plików zachował spójność.

### Lista kroków niezbędnych do realizacji funkcji dopisującej n bloków na koniec pliku.
Uwaga: Zakładamy, że poszczególne kroki funkcji są zawsze wdrażane synchronicznie. 
Uwaga: Funkcje nie powinny powodować naruszenia spójności systemu plików w przypadku awarii zasilania.
Uwaga: Dopuszczamy powstawanie wycieków pamięci.

![](https://i.imgur.com/c7TFFm4.png)

- znajdź wolny blok
- oznacz go jako zaalokowany w data bitmap
- zapisz do niego dane
- dodaj blok do i-węzła docelowego pliku
	- dodaj do bloków bezpośrednich jeśli jest miejsce
	- w.p.p. dodaj do bloków pośrednich jeśli jest miejsce
	- w.p.p. zaalokuj nowe bloki w drzewie bloków pośrednich
		- od liścia w górę by zachować spójność
		- dopisujemy nową gałąź do i-węzła pliku docelowego
- zaaktualizuj metadane (wskaźniki na bloki, rozmiar, ilość używanych bloków, timestamp)
- powtórz dla kolejnego z n bloków


## 4
![](https://i.imgur.com/uQqLymN.png)

### Pojęcia
#### Operacja atomowa
Operacja, która nie jest podzielna na mniejsze operacje, możemy założyć, że np. w przypadku awarii, nie wykona się tylko jej część.

### Czemu «rename» zakończy się błędem «EXDEV» kiedy próbujemy przenieść plik do innego systemu plików?
#### rename(2)
https://man7.org/linux/man-pages/man2/rename.2.html
![](https://i.imgur.com/USUFj4d.png)

#### exdev
![](https://i.imgur.com/Fz1K1nE.png)

`rename()` jest atomowy, ale przenoszenie pliku pomiędzy różnymi systemami plików już nie (zamiast tego można użyć `mv()`, który najpierw zawoła `rename` a jeśli dostanie error skopiuje pliki i usunie oryginalne)

### Powtórz polecenia z zadania 3 dla funkcji przenoszącej plik między dwoma różnymi katalogami w obrębie tego samego systemu plików.
Uwaga: Zakładamy, że w katalogu docelowym jest wystarczająco dużo miejsca na dodanie wpisu.
Uwaga: Wpis katalogu nie może przecinać granicy między blokami.

![](https://i.imgur.com/0fDvPhb.png)

Nie musimy przepisywać bloków z danymi.

- Wstawiamy rekord katalogu opisujący obecny plik do pliku katalogu, do którego przenosimy. (jest tam miejsce), dbając o to by nie przekroczyć granicy między blokami.
	- jeśli w nowym katalogu wpis już istnieje -> co jeśli reference zejdzie do zera? (mogą dalej istnieć deskryptory wskazujące na plik)
- Zwiększamy reference count przenoszonego pliku o 1
- Zmniejszamy odległość do kolejnego rekordu w poprzednim rekordzie katalogu względem nowego rekordu.
- Zwiększamy odległość do kolejnego rekordu w starym katalogu usuwając efektywnie wpis
	- jeśli jest to pierwszy wpis w katalogu to ustawiamy i-node number 0 (pusty wpis do przeskoczenia)
- Zmniejszamy reference count przenoszonego pliku o 1 (powinno być teraz tyle ile przed przeniesieniem)


## 5 (TODO)
![](https://i.imgur.com/TyxQX2w.png)

### unlink(2)
https://man7.org/linux/man-pages/man2/unlink.2.html
![](https://i.imgur.com/DEOsZf1.png)
![](https://i.imgur.com/ozMJCtO.png)

### Powtórz polecenia z zadania 3 dla funkcji usuwającej plik zwykły z katalogu.
Uwaga: Zakładamy, że w katalogu docelowym jest wystarczająco dużo miejsca na dodanie wpisu.
Uwaga: Wpis katalogu nie może przecinać granicy między blokami.


- usuwamy wpis z katalogu poprzez przepięcie sąsiadów
- obniżamy reference_count w i-węźle
	- jeśli wynosi 0 to zwalniamy i-węzeł oraz bloki
- jeśli istnieją deskryptory
### Kiedy możliwe jest odwrócenie operacji usunięcia pliku tj. odkasowania (ang. undelete)?
Odkasowanie danych należących do pliku jest możliwe do momentu nadpisania zawartości jego inode'a, jednak nie mamy niestety gwarancji, że będzie to jego całość.
Poszczególne bloki mogą zostać nadpisane nową zawartością, a nie wiemy które, ponieważ wygaszona flaga zajętości bloku niekoniecznie oznacza, że nie został on w międyczasie zmodyfikowany a następnie zwolniony.

### Zauważ, że usunięcie pliku nie odbiera procesom możliwości czytania jego zawartości, o ile go otworzyły przed wywołaniem unlink(2).Kiedy w takim razie plik zostanie faktycznie usunięty z dysku?
Pliki zostają całkowicie skasowane w momencie, gdy ich dane zostaną nadpisane innymi plikami .

## 6
![](https://i.imgur.com/eVr5obk.png)

### Pojęcia
#### dowiązanie twarde (hard link)
wskaźnik na i-węzeł pliku (różne nazwy tego samego pliku w obrębie jednego systemu plików).

#### dowiązanie symboliczne (symbolic link)
specjalny rodzaj pliku, wskazuje on za pomocą nazwy dowolny inny plik lub katalog (który może nie istnieć w danym momencie) w dowolnym systemie plików (w przeciwieństwie do hard linków).

System nie sprawdza ścieżki, co za tym idzie może dojść do zapętlenia.
`ln -s existing link`

### Wyjaśnij co robi system plików ext2 przy tworzeniu dowiązania twardego (ang. hard link) i symbolicznego (ang. symbolic link). 
![](https://i.imgur.com/Xfkpz8s.png)
![](https://i.imgur.com/Eb5x5CL.png)


Przy dowiązaniu twardym we wpisie katalogu mamy skojarzenie nazwy z odpowiednim i-węzłem. 
W pliku do którego tworzymy dowiązanie twarde, jest zwiększany reference counter. (w konsekwencji plik może zostać usunięty dopiero gdy reference counter osiągnie 0, czyli plik nie jest wykorzystywany w żadnym miejscu naszego systemu plików).

Przy dowiązaniu symbolicznym powstaje nowy plik, który odnosi się do tego z którym tworzymy dowiązanie.

### Gdzie jest przechowywana zawartość dowiązania symbolicznego?
Tworzony jest nowy plik (czyli i-węzeł) zawierający ścieżkę i nazwę do pliku do którego dowiązujemy z flagą we wpisie katalogu mówiącą, że to symlink.

### Jak za pomocą dowiązania symbolicznego stworzyć w systemie plików pętlę?
`mkdir test`
`cd test`
`ln -s file $(pwd)`
`ls -al`
`cd file`

Czyli file to nazwa pliku w obecnym folderze do którego dowiązujemy, ALE to też nazwa tego symlinka -> mamy pętlę.

`bash: cd: file: Too many levels of symbolic links`

### Kiedy jądro systemu operacyjnego ją wykryje i zwróci błąd «ELOOP»?
![](https://i.imgur.com/TbVtGXa.png)


### Czemu pętli nie da się zrobić z użyciem dowiązania twardego?
Ponieważ nie można tworzyć dowiązań twardych do katalogów, a drzewiasta, skierowana struktura systemu plików bez tego na to nie pozwala. (graf acykliczny, skierowany pomiędzy i-węzłami)

Dowiązania twarde do katalogów umożliwiałyby np. posiadanie wielu rodziców (problem z `..`)

## 8
![](https://i.imgur.com/KJKLj6E.png)

### debugfs(8)
https://man7.org/linux/man-pages/man8/debugfs.8.html

flagi `-w`, `-R`, `-n` etc. 

### polecenia
`fdisk -l` -> partycje (`sudo lsblk`)

`sudo debugfs /dev/sdb5` -> przejście do debuggera
#### fragmentację systemu plików (freefrag) 
`freefrag` - pokazuje blocksize, total blocks, free blocks
zakresy i ile mają wolnych bloków

![](https://i.imgur.com/xRQrcR1.png)

podanie opcji `[-c chunk_kb]` pokazuje ile jest wolnych fragmentów o podanym rozmiarze (potędze 2)

#### informacje o grupach bloków (stats)
`stats` - zawartość superbloku oraz informacje o grupach (pozycja bitmap, tabeli, # wolnych bloków, # wolnych i-node, checksum)
(g GG)

![](https://i.imgur.com/b6PPaTW.png)
`stats -h` -> sam superblok

#### zakresy bloków z których składa się wybrany duży plik (extents),
`fallocate -l 5GB largefile`
`sudo debugfs /dev/sdb5`
`dump_extents largefile`

![](https://i.imgur.com/k1GpRXF.png)
z flagą `-n` tylko wewnętrzne węzły w drzewie przydziałów
z flaga `-l` tylko węzły liści w drzewie przydziałów

#### że dowiązanie symboliczne może być przechowywane w i-węźle (idump)
`sudo ln -s /media/artur/ link`
`sudo debugfs /dev/sdb5`
`inode_dump link`

![](https://i.imgur.com/7St5Rsu.png)
z flagą `-b` tylko i_blocks
z flagą `-x` extra inode space and extended attributes

#### do jakiego pliku należy wybrany blok (blocks, icheck, ncheck)
wybieramy plik np: 
`blocks /bin/systemctl` -> dostajemy numery bloków
wybieramy jakiś nr bloku
`icheck <nr bloku>` -> dostajemy parę block-inode
`nchceck <i-node number>` -> dostajemy parę inode-pathname

![](https://i.imgur.com/fYmjHY3.png)

#### reprezentację liniową małego katalogu (bdump)
`blocks /usr/games/` -> nr bloku (3153954)
`block_dump 3153954` -> 
![](https://i.imgur.com/Ovel855.png)