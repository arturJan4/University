# SO - Lista 8

## Materiały
paper:
https://citeseerx.ist.psu.edu/viewdoc/download;jsessionid=1B87BDA68BF1D60CE0801DF2E81F4F7C?doi=10.1.1.47.275&rep=rep1&type=pdf

## 1
![](https://i.imgur.com/4dypZUO.png)


### działanie sbrk oraz pary mmap, munmap
![](https://i.imgur.com/12iYXW3.png)

`void *sbrk(intptr_t increment)`
`int brk(void *addr)`

`sbrk` powiększa/zmniejsza rozmiar sterty (heap) - konkretniej zmienia pozycję **program break**, czyli pierwszej lokacji po segemencie danych danego procesu. Zwiększanie program break jako efekt zwiększa pamięć

`sbrk(0)` -> znajduje lokalizacje program break
`sbrk(increment)` -> zwiększa o increment bajtów


```c=
void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);
int munmap(void *addr, size_t length);
```
możemy "zasugerować" adres odwzorowania w pamięci.

### Jakie są wady stosowania sbrk do zarządzania rozmiarem sterty przez biblioteczny algorytm zarządzania pamięcią malloc(3)? 
Skoro `malloc` wykorzystuje `sbrk` to działa to podobnie jak sterta -> mamy operację zdjęcia ze stery i wrzucenia na stertę (pop i push).

Powiedzmy, że zaalokowaliśmy **x** bajtów, a następnie **y** bajtów. Teraz gdy chemy zwolnić ten **x** musimy wykonać zwolnienie **y**.

Dodatkowo kolejne operacje `sbrk` powoduje wzrost sterty, więć gdy chcemy zrobić `free` na wcześniej zaalokowanej pamięci to zwolniana pamięć nie będzie ponownie wykorzystana.

### Jak można to poprawić przy pomocy mmap i munmap? 
Możemy dowolnie zwolnić pamięć a potem ją zwalaniać.

### Kiedy procedura free może zwrócić pamięć do jądra?
Pamięć jest zwalniana przy pomocy `munmap` (trzymana jest informacja, żę pamięć została zaalokowana w ten sposób), który usuwa odwzorowanie to przestrzeni adresowej procesu. 
Jądro trzyma natomiast wskaźnik do zmapowanych obszarów w RB-tree

## 2
![](https://i.imgur.com/PQejG3D.png)


### Pojęcia

#### Fragmentacja wewnętrzna
![](https://i.imgur.com/DcRPEbf.png)

Istnieje wystarczająco miejsca w bloku, ale blok jest większy niż potzeba.
"wewnętrzna" ponieważ potencjalnie marnowana pamięć znajduje się wewnątrz bloku

#### Fragmentacja zewnętrzna
![](https://i.imgur.com/LWTGoBA.png)

Sumarycznie istnieje wystarczająco bloków by zaalokować pamięć, ale ze względu na ich ułożenie nie jest możliwe umieszczenie "w całości".
Nie chcemy rodzielać większych bloków pamięci na mniejsze.

### Czemu algorytm malloc nie można stosować kompaktowania?
**Kompaktowanie** - przesuwanie zajętych bloków pamięci tak aby połączyć je w ciągły blok zajmujący jak najmniej pamięci. (przesuwamy w lewo i zamieniamy miejscami, by dopasować się do paddingu)

Jako, że w C programista powinien móc polegać na stałości wskaźników. Tj. po alokacji, w trakcie działania programu odnoszą się do tego samego obszaru.
Dodatkowo niektóre struktury danych mają wskaźniki odnoszące się zależnie do poszczególnych elementów (więc trzeba byłoby je wszystkie zaktualizować).

### Na podstawie [6, §2.3] opowiedz o dwóch głównych przyczynach występowania fragmentacji zewnętrznej.

#### powód 1 - odizolowane śmierci
![](https://i.imgur.com/9Ne27ZT.png)

Gdy tworzymy wolną przestrzeń, dla której sąsiednie przestrzenie są zajęte.
Zauważamy, że zależy to od momentu alokacji i zwolnienia przestrzeni (śmierci).
Gdyby alokator mógł przewidzieć, które bloki "żyją" w podobnym czasie to ustawiłby, by je obok siebie. Wtedy pamięć nie miała by fragmentacji bo alokowalibyśmy ciągłe obszary zawierające wiele bloków.

#### powód 2 - zachowane zależne od czasu
![](https://i.imgur.com/0yPFRoo.png)
![](https://i.imgur.com/ARSBWm5.png)

Alokator powinien starać się przewidzieć wrzozec zapisu (np. czy zapisujemy wiele dużych, albo wiele małych bloków). Dla źle przewidującego można spreparować dane w taki sposób, by fragmentacja była duża.

## 3
![](https://i.imgur.com/oU5asvY.png)

### wykres i trzy wzorce przydziału

#### wykres 1
![](https://i.imgur.com/j4SWm4u.png)

Mamy tu:
- stałe zużycie z małymi zmianami
- skokowe duże i powtarzana alokacje i dealokacje
- nieregularne duże alokacje i dealokoacje

#### wykres 2
![](https://i.imgur.com/77Lyxty.png)

zużycie stale rośnie (rampa), z "płaskimi" fragmentami
profil użycia różnego rozmiaru objektów jest podobny, ale zaczyna się w różnych punktach oraz z różną stałą

#### wykres 3
![](https://i.imgur.com/4B7XzTm.png)

alokujemy jednorazowo duże ilości danych, które nie są zwalnianie w trakcie działania programu.

Dodatkowo tworzene są duże ilości małych objektów, ale są one stosunkowo szybko zwalnianie.

### Na podstawie paragrafu zatytułowanego „Exploiting ordering and size dependencies” wyjaśnij jaki jest związek między czasem życia bloku, a jego rozmiarem?

Obiekty alokowane w tym samym (w przybliżeniu) czasie, często również giną (w przybliżeniu) w tym samym, dlatego są zwykle alokowane obok siebie. np. tablice.

Obiekty różnych rozmiarów (więc pewnie różnych typów), często giną w wiekszych odstępach czasu, więc możemy segregować ze względu na rozmiar.

### Wyjaśnij różnice między politykami znajdowania wolnych bloków: first-fit, next-fit i best-fit. Na podstawie [6, §3.4] wymień ich słabe i mocne strony.
![](https://i.imgur.com/GGjz2Ap.png)

#### first-fit
przeszukuje listę od początku i używa pierwszego wystarczająco dużego bloku do alokacji, jeśli blok jest większy niż wymagany to wykonujemy podział (splitting)

#### next-fit
optymalizujemy first-fit, zamiast zawsze przeglądać od pierwszego bloku, trzymamy wskaźnik wskazujący pozycję ostatnio zakończonego sukcesem wyszukiwania

#### best-fit
przesukujemy całą listę znajdująć najlepiej dopasowane bloki (tj. takie że po alokacji zostanie jak najmniej niewykorzystanego miejsca)

#### słabe i mocne strony
first-fit:
zalety:
- jako że adresy, które służą do wskazywania są wyrównane to mamy wolne bity w których możemy przechowywać ifnroamcję o przyleganiu wolnych bitów
- nie potrzebujemy znaczników granicznych -> mniejszy rozmiar 
wady:
- tworzy tzw. drzazgi, ponieważ większe bloki na początku listy dzielimi jako pierwsze co powoduje postwanie wielu mniejszych bloków na początku listy, a wtedy wyszukiwanie wolnego bloku musi przejść po tych małych blokach za każdym razem
- pesymistycznie liniowy czas

next-fit:
zalety:
- mniejszy średni czas wyszukiwania
- nie tworzy drzazg bo zaczyna z różnych miejsc
wady:
- wpływa na lokalnośc programu przez rozproszenie objektów po pamięci

best-fit:
zalety:
- minimalizacja marnowanej przestrzeni (zwykle trzyma małe fragmenty)

wady:
- działa wolniej (przechodzi zawsze po całej liście)
- zaelta może być wadą i stworzyć wiele obszarów tak małych (przez najlepsze dopasowanie), że nie będą one użyteczne
- im więcej wolnych bloków tym gorzej działa