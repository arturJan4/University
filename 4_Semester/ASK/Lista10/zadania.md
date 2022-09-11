---
tags: ASK
---
# ASK - LISTA 10

## zad 1
https://pages.cs.wisc.edu/~remzi/OSFEP/file-disks.pdf - avg seek time to 1/3
seek - ustawienie ramienia nad ścieżką (w praktyce mamy przyśpieszenie)
rotational latency - 
rotational latency - jak ramię się ustawi to dysk musi się obrócić aż trafi na pierwszy bit sektora, w najgorszym przypadku pełny obrót bo dopiero co ominął sektor
1 / RPM x 60 secs / min 
transfer time - dla sektora
1/RPM x 1/(average # sectors/track) x 60secs/min
tacces = suma średnich

## zad 2 


## zad 4
**Pamięć podręczna** - mniejsza i droższa, ale szybsza pamięć, która poprawia szybkość dostępu do informacji mogących być potrzebne w najbliższej przyszłości.

Jeśli nie znajdujemy szukanego bloku na danej wysokości hierarchi pamięcii to mamy miss i przechodzimy niżej w.p.p mamy hit.

$ns = 1/1 \ 000 \ 000 \ 000 s$
$2,5 \ GHz$ wykonuje $2 \ 500 \ 000 \ 000$ cykli na sekundę.

a) Średnia czas dostępu do pamięci:
źródło wzoru: https://en.wikipedia.org/wiki/Average_memory_access_time
gdzie u nas:
$H_1 = A(L1)$, $H_2 = A(L2)$, $H_3 = A(L3)$, $H_4 = A(DRAM)$
$MR_{1} = (1-H(L1))$, $MR_{2} = (1-H(L2))$, $MR_{3} = (1-H(L3))$

Wzór rekurencyjny rozszerzy się do:
$H_{1} + MR_{1}H_{2} + MR_{1}MR_{2}H_{3} + MR_{1}MR_{2}MR_{3}H_{4}$
Intuicyjnie: zawsze trafiamy (hit) do L1 (4 cykle), jak nie trafimy (miss) z prawdopodobieństwem 0.1 to wykonamy dodatkowe 12 cykli itd.

$4 + 0,10 * 12 + 0,10 * 0,05 * 40 + 0,10 * 0,05 * 0,02 * 200 =$
$= 4 + 1,2 + 0,2 + 0,02 = 5,42$ cykli procesora.

żeby dostać czas wykonujemy: (liczba cykli/taktowanie * liczba nanosekund w sekundzie)
$(5,42/2 \ 500 \ 000 \ 000) * 1 \ 000 \ 000 \ 000 = 2,168 \ ns$


b) Pesymistyczny czas (zawsze trafiamy do głównej pamięci DRAM) : 
$4 + 12 + 40 + 200 = 256$ cykli procesora.

$(256/2 \ 500 \ 000 \ 000) * 1 \ 000 \ 000 \ 000 = 102,4 \ ns$

## zad 6

Synchroniczna pamięć DRAM - wykonuje kolejne kroki na narastającym zboczu zegara.

![](https://i.imgur.com/b7pKv4I.png)

1) Kontroler pamięci udostępnia adres wiersza na szynie i ustawia sygnał $RAS$ na zero.
2) Po czasie $t_{RCD}$ może zostać wysłany sygnał $CAS$. Od tego czasu na szynie powinien znajdować się adres kolumny.
3) Teraz mamy zaadresowaną komórkę, i RAM potrzebuje czasu $t_{CAS}$ na przesłanie danych.
4) Kontroler może też wyspecyfikować ładowanie więcej słów (zwykle 2, 4, 8), żeby nie powtarzać całego cyklu. Może też wysyłać kolejne sygnały $CAS$, aby dostać się do innych kolumn (utrzymuje wiersz otwarty).

![](https://i.imgur.com/i66jbz2.png)
Powyższy diagram pokazuje, że przed dostępem to nowego wiersza, musimy zamknąć wiersz i wstępnie naładować nowy, musi minąć czas $t_{RP}$ od wydania polecenia ładowania ($WE$).

**Źródła opóźnień**:
$t_{CAS}$ (bramkowanie kolumny) - CL na diagramie, 
"Column Access Strobe latency. The time interval between column access command and the start of data return by the DRAM device"

$t_{RCD}$ (wybór wiersza) - 
RAS-to-CAS delay - opóźnienie pomiędzy wyborem wiersza a wyborem kolumny

$t_{RP}$ (wstępne ładowanie wiersza) - czas odświeżania pamięci przed kolejnym dostępem do wiersza

$t_{RAS}$ (bramkowanie wiersza) - występuje po sygnale $RAS$, 
czas pomiędzy dostępem do wiersza a odświeżeniem pamięci. Bank nie może być wstępnie ładowany zanim nie minie $t_{RAS}$ od poprzedniej aktywacji.