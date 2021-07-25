---
tags: ASK
---
# ASK - LISTA 11

## Zad 1
**pamięć podręczna z mapowaniem bezpośrednim** - taka w której na jeden zbiór przypada tylko jeden wiersz
**adresowanie bajtowe** - takie w którym mamy dostęp do poszczególnych bajtów

a) Mamy 5 bitów na offset ($adddr_{4...0}$) w adresie a więc $2^5 = 32$ bajty do adresowania. Czyli 8 słów po 32 bity.
b) Skoro mamy 5 bitów na adresu na wybór zbioru ($adddr_{9...5}$) i po jednym wierszu na zbiór to mamy 32 wiersze
c) Metadane to tag (22 bity) i valid (1bit) . Rozmiar bloku z a) to 256 bity.
Czyli razem mamy $\frac{23}{256+23} = \frac{23}{279}$

## Zad 2
**organizacja wielodrożna sekcyjno-skojarzeniowa** (E-way Set-associative cache) - taka w której mamy macierz zbiorów, które zawierają linie (E linii na zbiór). Pozwala na wykorzystanie wielu algorytmów wymiany, ale kosztem możliwych conflict missów.

**trafienie i chybienie** - gdy pamięć pobiera z pamięci podręcznej poziom niżej to gdy dana informacja znajduje się już w pamięci podręcznej (znajdziemy pasujący tag) to mamy do czynienia z trafieniem, w p.p. z chybieniem

Szyna ma 12 bitów.
Blok ma 4 bajty, a mamy adresowanie bajtowe, potrzeba więc 2 bitów na określenie do którego bloku chcemy się odwołać. ($adddr_{1...0}$)
Mamy 4 zbiory, więc także potrzeba 2 bitów.($adddr_{3...2}$)
Pozostałe 8 bitów zostawiamy na tag (znacznik). ($adddr_{11...4}$)

Wyłuskanie adresów:
| Adres | Znacznik | Indeks | Offset |
|:-----:|:--------:|:-----:|:------:|
|  832  |   0x83   |  0x0  |  0x2   |
|  835  |   0x83   |  0x1  |  0x1   |
|  FFD  |   0xFF   |  0x3  |  0x1   |

Które wartości generują trafienie i jakie wartości czytają:
| Adres | Trafienie? | Wartość |
|:-----:|:----------:|:-------:|
|  832  |    TAK     |   CC    |
|  835  |    NIE     |    -    |
|  FFD  |    TAK     |   C0    |

## Zad 3
Polityka wymiany określa sposób wyznaczania ofiary przy chybieniach.
NRU - w pierwszej kolejności wybiera nieaktywną linię, a później nie-ostatnio używaną.
Chybienia wywołane konfliktem (conflict miss) - blok próbuje zająć już zajętą linię cache.
Chybienia przymusowe (compulsory miss) - kiedy mamy pustą linię cache i zastępujemy ją po raz pierwszy blokiem danych

Tłumaczenie operacji:
| adres | Znacznik | Index | Offset |    miss    | tag ofiary |
|:-----:|:--------:|:-----:|:------:|:----------:|:----------:|
|   0   |    0     |   0   |   0    | compulsory |    brak    |
|   4   |    0     |   1   |   0    | compulsory |    brak    |
|  10   |    1     |   0   |   0    | compulsory |    brak    |
|  84   |    8     |   1   |   0    | compulsory |    brak    |
|  3c   |    3     |   3   |   0    | compulsory |    brak    |
|  e8   |    e     |   2   |   0    | compulsory |    brak    |
|  c8c  |    c8    |   3   |   0    | compulsory |    brak    |
|  a0   |    a     |   0   |   0    |  conflict  |     0      |
|   4   |    0     |   1   |   0    |     -      |     -      |
|  400  |    4     |   0   |   0    |  conflict  |     1      |
|  84   |    8     |   1   |   0    |     -      |     -      |
|  10   |    1     |   0   |   0    |  conflict  |     a      |
|  e8   |    e     |   2   |   0    |     -      |     -      |
|  884  |    88    |   1   |   0    |  conflict  |     0      |
|  c8c  |    c8    |   3   |   0    |     -      |     -      |
|   0   |    0     |   0   |   0    |  conflict  |     4      |

Hit ratio:
$\frac{4}{7+5+4} = \frac{4}{16} = \frac{1}{4}$

przed:
| Indeks | Znacznik | Valid | 
| ------ | -------- | ----- |
| 0      | 00       | 0     |
| 0      | 00       | 0     |
| 1      | 00       | 0     |
| 1      | 00       | 0     |
| 2      | 00       | 0     |
| 2      | 00       | 0     |
| 3      | 00       | 0     |
| 3      | 00       | 0     |

po przymusowych:
| Indeks | Znacznik | Valid | 
| ------ | -------- | ----- |
| 0      | 00       | 1     |
| 0      | 01       | 1     |
| 1      | 00       | 1     |
| 1      | 08       | 1     |
| 2      | 0e       | 1     |
| 2      | 00       | 0     |
| 3      | 03       | 1     |
| 3      | c8       | 1     |

po wszystkich:
| Indeks | Znacznik | Valid | Potencjalna ofiara |
| ------ | -------- | ----- | ------------------ |
| 0      | 01       | 1     |        nie         |
| 0      | 00       | 1     |        tak         |
| 1      | 88       | 1     |        nie         |
| 1      | 08       | 1     |        tak         |
| 2      | 0e       | 1     |        nie         |
| 2      | 00       | 0     |        tak         |
| 3      | 03       | 1     |        tak         |
| 3      | c8       | 1     |        nie         |

Wystarczy jeden bit na linię oznaczający czy jest to ostatnio używany element.
NRU wybiera bloki które mają bit ustatwiony na 1.
Początkowo mamy same zera. Gdy wszystkie bloki mają zero to wszystkie bloki są ustalane na 1 i jeden z nich jest wybierany na wybrany sposób. Kiedy blok jest użyty to ustawiamy jego bit na zero.

Mamy 2 linie na zbiór. Potrzeba więc 2 bity na zbiór.

## Zad 4
**pamięć w pełni asocjacyjna** - mamy tylko jeden zbiór
8 bloków

Teraz na szynie adresowej mamy dalej 12 bitów, ale nie musimy już adresować zbioru (wystarczą 2 bity na offset). 
Więc 2 bity, które stanowiły indeks zbioru teraz są częscią tagu.

Translacja adresów:
| adres | Znacznik 11-4(hex) | Znacznik 3-2(bit) | Offset |    miss    |
|:-----:|:------------------:|:-----------------:|:------:|:----------:|
|   0   |         00         |        00         |   0    | compulsory |
|   4   |         00         |        01         |   0    | compulsory |
|  10   |         01         |        00         |   0    | compulsory |
|  84   |         08         |        01         |   0    | compulsory |
|  3c   |         03         |        11         |   0    | compulsory |
|  e8   |         0e         |        10         |   0    | compulsory |
|  c8c  |         c8         |        11         |   0    | compulsory |
|  a0   |         0a         |        00         |   0    | compulsory |
|   4   |         00         |        01         |   0    |     -      |
|  400  |         40         |        00         |   0    |  capacity  |
|  84   |         08         |        01         |   0    |     -      |
|  10   |         01         |        00         |   0    |     -      |
|  e8   |         0e         |        10         |   0    |     -      |
|  884  |         88         |        01         |   0    |  capacity  |
|  c8c  |         c8         |        11         |   0    |     -      |
|   0   |         00         |        00         |   0    |  capacity  |

przymusowe - 8 
hit ratio: $\frac{6}{8+3+5} = \frac{3}{8}$

przed:
| Numer operacji | Znacznik | Valid |
| -------------- | -------- | ----- |
| 0              | 00       | 0     |
| 0              | 00       | 0     |
| 0              | 00       | 0     |
| 0              | 00       | 0     |
| 0              | 00       | 0     |
| 0              | 00       | 0     |
| 0              | 00       | 0     |
| 0              | 00       | 0     |

compulsory:
| Numer operacji | Znacznik (hex) | Znacznik (bit) | Valid |
| -------------- | -------------- | -------------- | ----- |
| 1              | 00             | 00             | 1     |
| 2              | 00             | 01             | 1     |
| 3              | 01             | 00             | 1     |
| 4              | 08             | 01             | 1     |
| 5              | 03             | 11             | 1     |
| 6              | 0e             | 10             | 1     |
| 7              | c8             | 11             | 1     |
| 8              | 0a             | 00             | 1     |

po:
| Numer operacji | Znacznik (hex) | Znacznik (bit) | Valid |
| -------------- | -------------- | -------------- | ----- |
| 10             | 40             | 00             | 1     |
| 9 <-kolejna ofiara | 00             | 01             | 1     |
| 12             | 01             | 00             | 1     |
| 11             | 08             | 01             | 1     |
| 14             | 88             | 01             | 1     |
| 13             | 0e             | 10             | 1     |
| 15             | c8             | 11             | 1     |
| 16             | 00             | 00             | 1     |

LRU - Informację o tym który jest bit będziemy kodować przy pomocy bitów wieku (age bit). Musimy umieć zakodować tyle stanów co permutacji linii na zbiór. Tutaj mamy 8! stanów czyli wystarczy $\lceil log_{2}(8!) \rceil$ = 16  bitów na zbiór. 
Uwaga: Przy cache hit także aktualizujemy obecny element jako najnowszy.

## Zad 5
1) Czemu używamy środkowych bitów do wyboru zbioru zamiast najbardziej znaczących?
Na podstawie slajdów z wykładu:
![](https://i.imgur.com/raHRZCy.png)
Jak widać sąsiednia pamięć mapuje się do różnych zbiorów w naszym cache. Sprawia to, że przy np. czytaniu tablicy możemy zapisać pewien jej chunk wielkości rozmiaru naszego cache. Programy z dobrą lokalnością przestrzenną działają dobrze

![](https://i.imgur.com/2YNEQAa.png)
Kolejne adresy bardzo często należą do tego samego zbioru w cache co powoduje konflikty i słabą wydajność.

2) Po co procesorem odrębny cache L1 dla danych i instrukcji?
![](https://i.imgur.com/ergTMvc.png)
Instruction cache przechowuje również informacje pomocne dla dekodera.
Instruction cache jest read-only a data cache read/write, więc można w ten sposób uprościć obwód.
Można czytać jednocześnie z i-cache i d-cache czyli można wykonać 2 odczyty i 1 zapis w cyklu.
Wykorzystują odrębną lokalność dla instrukcji oraz dla danych (przykładowo: przy czytaniu tablicy: mamy kolejne bloki pamięci (lokalność przestrzenna), a takie same instrukcje które robią odczyt (lokalność czasowa))
Istnieją procesory, które oszczędzają w ten sposób energię, wyłączając nieużywane elementy powiązane z cache (np. dekodery).

## Zad 7
Do L1 trafiamy zawsze:
https://en.wikipedia.org/wiki/Average_memory_access_time

Tylko L1:
T_avg = 0.66ns + (0.08 * 70ns) = 6.26ns 
Czyli 6.26/0.66 ~ 9.48 cykli

L1 + L2:
0.66ns + (0.08 * 5.62ns) + (0.08 * 0.005 * 70ns) = 1.1376ns
Czyli 1.1376/0.66 ~ 1.72 cykli

CPI: średnia liczba cykli na instrukcję wykonywana przez procesor dla programu lub jego części. Wynika z tego, że różne typy instrukcji mogą mieć różny koszt w cyklach (np. na MIPS typ LOAD kosztuje 5 cykli, a JUMP 3). 

36% instrukcji to dostępy do pamięci, reszta jest innych (64%).
Zakładamy, że dla tych 64% CPI to 1.0. (1 cykl na 1 instrukcję)

Tylko L1:
CPI_{L1} = (0.64 * 1.0) + (0.36 * 9.48) ~ 4.05 cykli

L1 + L2:
CPI_{L1+L2} = (0.64 * 1.0) + (0.36 * 1.72) ~ 1.26 cykli
