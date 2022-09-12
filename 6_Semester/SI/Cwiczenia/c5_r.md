---
tags: sztuczna
---
# SI - Ćwiczenia 5

## 1
![](https://i.imgur.com/05nfOm3.png)

problem: klasteryzacja

### K-średnich (K-means)
![](https://i.imgur.com/VCuYSiK.png)

czyli wyliczamy średnią z punktów jako reprezentanta

![](https://i.imgur.com/TVJCMWw.png)

odległość euklidesowa!
$O(nki)$, $ki \leq n$

### K-medians
będziemy wyliczać medianę (geometrycznie środkowa wartość) punktów jako reprezentanta

![](https://i.imgur.com/9RQ5nvs.png)

![](https://i.imgur.com/QhoQeHc.png)
argmin -> wartość argumentu y która minimalizuje sumę 

Dla dużych zbiorów danych pojawiają się wartości skrajne (outliers), które mają duży wpływ na średnią, mocno przesuwając reprezentanta.
Mediana natomiast to statystyka odporna na wartości skrajne (wymaga `50`% złych danych by to nie była prawda).
np. ``[1, 2, 3, 4, 5, 6, 42000]`` -> mediana to `4`, średnia `6003`

Problematyczne jest znajdowanie geometrycznej mediany w wielu wymiarach (nie da się wskazać ogólnego wzoru) -> algorytmy, które się tym zajmują są wiec heurystyczne

odległość manhatańska!

### K-medoids
idea: dla poprzednich metod reprezentant nie jest rzeczywistym punktem z naszego zbioru danych, a chcemy by był

![](https://i.imgur.com/oIdWTVv.png)

algorytm PAM (Partitioning Around Medoids)
większa złożoność od k-means -> ok. dla mniejszych zbiorów, lub odzielonych od siebie grup
(liczy dystans miedzy parami punktów)
$O(n^2ki)$, $ki \leq n$
![](https://i.imgur.com/NL2aWf2.png)


również odporny na wartości skrajne
w przeciwieństwie do k-means, grupa nie musi być wypukła

można używać z dowolną miarą podobieństwa (nie tylko Euklidesowa lub Manhatańska)

## 2
![](https://i.imgur.com/otGRsdh.png)
![](https://i.imgur.com/ESv8FLt.png)

algorytm dla formuły $\phi$ (indukcyjny):
jeśli $\phi$ to literał:
- to go zwracamy (1 elementowa-literałowa klauzula)

jeśli $\phi$ jest postaci $A \land B$ gdzie A i B to formuły:
- rekurencyjnie wywołujemy na A i B
- zwracamy $alg(A) \land alg(B)$, bo te podformuły są już w CNF

jeśli $\phi$ jest postaci $A \lor B$ gdzie A i B to formuły:
- niech ($A_1 \land A_2 \land A_3 \cdots A_n$), oznacza wynik alg(A), gdzie $A_i$ to klauzule
- niech ($B_1 \land B_2 \land B_3 \cdots B_m$), oznacza wynik alg(B), gdzie $B_i$ to klauzule 
- wykorzystujemy prawo rozdzielności koniunkcji względem alternatywy
![](https://i.imgur.com/zsskECN.png)
- w takim razie zwracamy:
$(A_1 \lor B_1) \land (A_1 \lor B_2) \cdots (A_n \lor B_m)$

jeśli $\phi$ jest postaci $\neg \theta$:
- $\theta$ jest postaci $\neg A$ dla jakiegoś literału A -> zwracamy $\phi$ (podwójna negacja)
- $\theta$ jest postaci $\neg \delta$ -> zwracamy $alg(\delta)$
- i prawa de Morgana
- $\theta$ jest postaci $\neg (\delta \land \sigma)$ -> zwracamy $alg(\neg \delta \lor \neg \sigma))$
- $\theta$ jest postaci $\neg (\delta \lor \sigma)$ -> zwracamy $alg(\neg \delta \land \neg \sigma))$

jeśli $\phi$ jest postaci $A \implies B$:
- zwracamy $alg(\neg A \lor B)$

jeśli $\phi$ jest postaci $A \iff B$:
- zwracamy $alg((A \land \neg B) \lor (\neg A \land B))$

wykładniczy wzrost:
$$(X_1 \land Y_1) \lor (X_2 \land Y_2)$$
$\equiv$
$$(X_1 \lor X_2) \land (X_1 \lor Y_2) \land (Y_1 \lor X_2) \land (Y_1 \lor Y_2)$$

dla dowolnego n:
$$(X_1 \land Y_1) \lor (X_2 \land Y_2) \space \cdots \space (X_n \land Y_n)$$
dostaniemy $2^n$ klauzul (każda para)


## 7
![](https://i.imgur.com/5k5IWB3.png)

Filozoficzne zombie lub argument p-zombie jest eksperymentem myślowym w filozofii umysłu, który wskazuje hipotetyczną istotę, która jest fizycznie identyczna i nieodróżnialna od normalnego człowieka, ale nie posiada świadomości, ani zdolności odczuwania.
Na przykład, gdyby filozoficzne zombie zostało szturchnięte ostrym przedmiotem, nie odczuwałoby wewnętrznie żadnego bólu, ale zewnętrznie zachowywałoby się dokładnie tak, jakby ten ból odczuwało, łącznie z werbalnym wyrażaniem bólu. 

Problem: czy tak zaawanoswana sztuczna inteligencja która spełnia cechy zombie powinna mieć takie same prawa jak reszta istot samoświadomych.

Jak ocenić czy AI jest świadome? (w zasadzie cokolwiek, inni ludzie przecież mogą być zombie-solipsyzm, relatywizm postrzegania świata np. kolory) Filozoficzne zombie pokazuje, że nie wystarczy obserwować zewnątrz, nie wystarczy też zapytać. 
Czy jeśli AI zacznie zadawać pytania o swoim istnieniu to czy etyczne jest jego wyłączenie.

pragmatyczna pozycja filozoficzna jeśli nie zakładamy solipsyzmu jest taka:
- prawa oraz szacunek dla innych ludzi są przyznawane jedynie ze względu na zewnętrzne zachowania obserwowane przez przyznającego
- nie da się dowieść, że reszta ludzi to nie p-zombie
- przyznający powinien rozszerzyć to dla każdej istoty, której nie jest w stanie zakwalifikować