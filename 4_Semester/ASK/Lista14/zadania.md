---
tags: ASK
---
# ASK - LISTA 14

### 2
14 bitów adres wirtualny
12 bitów fizyczny
64 bajty na stronę -> 2^6 - 6 bitów na offset
![](https://i.imgur.com/fnjERke.png)
![](https://i.imgur.com/YJkiDep.png)

![](https://i.imgur.com/GSu94eq.png)

#### 0x027c
```
 00 0010 0111 1100
| TLBT-6 | TLBI-2 | VPO - 6|
 00 0010    01      11 1100
```
TLBI = 0x1 (indeks zbioru)
TLBT = 0x2
TLB Hit? = Y (valid = 1)
Page Fault? = N
PPN = 0x17 = 23
```
| PPN - 6 | PPO - 6 |
| 01 0111 | 11 1100 |
```
```
| CT - 6  | CI - 4 | CO - 2 |
| 01 0111 | 11 11  |   00   |
```
CI = 0xF (indeks)
CT = 0x17 (tag)
CO = 0x0 (offset)

CT: 0x17 != 0x09 -> Hit? = N
Mamy miss

#### 0x03a9
```
00 0011 1010 1001
| TLBT-6 | TLBI-2 | VPO - 6|
|00 0011 |    10  | 10 1001|
```
TLBI = 0x2
TBLT = 0x3
TLB Hit? = N

```
| VPN-8     | VPO - 6|
|0000 1110  | 10 1001|
```
VPN = 14 = 0xE
z tablicy stron: VPN:0xE -> PPN:0x11 (valid = 1)
Page Fault? = N
```
| PPN-6   | PPO - 6|
|01 0001  | 10 1001|
```
```
| CT - 6  | CI - 4 | CO - 2 |
| 01 0001 | 10 10  |   01   |
```
CI = 0xA
CT = 0x11 != 2D -> Hit? = N
Mamy miss

#### 0x0040
```
00 0000 0100 0000
| TLBT-6 | TLBI-2 | VPO - 6|
|00 0000 |  01    |00 0000 |
```
TLBI = 0x1
TLBT = 0x0
TLB Hit? = N
```
| VPN-8   | VPO - 6|
|0000 0001| 00 0000|
```
VPN = 0x1 -> tablica stron -> brak wpisu
Page Fault = Y
