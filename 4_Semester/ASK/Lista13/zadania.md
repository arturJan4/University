---
tags: ASK
---
# ASK - LISTA 13


## 1
**Jak  procesor  przetwarza  skoki warunkowe? W  jakim  celu  procesor  używa predyktora  skoków?**
Instruction control unit czyta wiele instrukcji na raz. Gdy natrafiamy na branch to procesor próbuje przewidzieć w którą stronę pójdziemy (branch prediction). Procesor zaczyna wczytywać i wykonować instrukcje z miejsca gdzie przewidział skok (speculative execution), te instrukcje nie modyfikują rzeczywistych rejestrów ani pamięci do momentu potwierdzenia poprawności skoku.

**Co  musi  zrobić, jeśli  skok  zostanie  źle przewidziany?**
Execution unit wykrywa zły skok, usuwa wyniki od momentu skoku i wysyła do branch unit sygnał o złym skoku, i prawidłowym adresie skoku. Procesor ładuje wtedy instrukcje od rzeczywistego skoku. Te instrukcje muszą być zaciągnięte, zdekodowane i wysyłane do jednostek funkcyjnych co powoduje spory koszt "branch misprediction".

**Które skoki warunkowe warto zoptymalizować do instrukcji «cmov»?**
Instrukcja conditional move jest wykorzystywana do tego by obliczyć dwie gałęzie naraz pomijając możliwość wybrania złego skoku warunkowego. Jeśli skok ma jakiś regularny wzorzec, albo obieranie konkretnej ścieżki jest pewnym trendem, to prawdopodobnie predyktor poradzi sobie bardzo dobrze z przewidywaniem. Jesli natomiast warunki są nieprzewidywalne (np. zmienne losowe, znak liczby itp.) to może być warto optymalizować (to wymaga testowania konkretnej optymalizacji).

przed optymalizacją:
```c=
void merge1(long src1[], long src2[], long dest[], long n) 
{
    long i1 = 0, i2 = 0;
    while (i1 < n && i2 < n)
        *dest++ = src1[i1] < src2[i2] ? src2[i1++] : src2[i2++];
}
```
deasemblacja kompilowanego z `-O1`
```=
merge1:
        testq   %rcx, %rcx
        jle     .L1
        movl    $0, %r8d
        movl    $0, %eax
        jmp     .L5
.L3:
        addq    $1, %r8
.L4:
        addq    $8, %rdx
        movq    %r9, -8(%rdx)
        cmpq    %r8, %rax
        movq    %r8, %r9
        cmovge  %rax, %r9
        cmpq    %rcx, %r9
        jge     .L1
.L5:
        leaq    0(,%rax,8), %r10
        movq    (%rsi,%r8,8), %r9
        cmpq    %r9, (%rdi,%rax,8)
        jge     .L3
        addq    $1, %rax
        movq    (%rsi,%r10), %r9
        jmp     .L4
.L1:
        ret
```
problematyczne jest : `src2[i1++] : src2[i2++]`
dlatego, że w jednym przypadku musimy podnieść `i1` a w drugim `i2`

Skorzystamy z wartości logicznej warunku i wyliczymy wszystkie możliwości naraz.

po poprawieniu
```c=
void merge2(long src1[], long src2[], long dest[], long n) 
{
    long i1 = 0, i2 = 0;
    while (i1 < n && i2 < n)
    {
        long val1 = src1[i1];
        long val2 = src2[i2];
        long comp = src1[i1] < src2[i2];
        *dest++ = comp ? val1 : val2;
        i1 += comp;
        i2 += (1-comp);
    }
}
```

```=
merge2:
        testq   %rcx, %rcx
        jle     .L6
        pushq   %rbx
        movq    %rdi, %r10
        movq    %rsi, %r11
        movl    $0, %edi
        movl    $0, %esi
        movl    $1, %ebx
.L3:
        movq    (%r10,%rsi,8), %rax
        movq    (%r11,%rdi,8), %r8
        cmpq    %r8, %rax
        setl    %r9b
        movzbl  %r9b, %r9d
        addq    $8, %rdx
        cmpq    %r8, %rax
        cmovg   %r8, %rax
        movq    %rax, -8(%rdx)
        addq    %r9, %rsi
        movq    %rbx, %rax
        subq    %r9, %rax
        addq    %rax, %rdi
        cmpq    %rdi, %rsi
        movq    %rdi, %rax
        cmovge  %rsi, %rax
        cmpq    %rcx, %rax
        jl      .L3
        popq    %rbx
        ret
.L6:
        ret
```
Powstały program ma więcej instrukcji ale mniej skoków (pozostało wyjście z pętli while oraz z funkcji). W szczególności eliminacja skoków warunkowych zredukuje "branch misprediction ratio".

## 2
Zadanie odnosi się do zad 5 z poprzedniej listy -> wykresy, opis działania programu. Z tą różnicą że domyślna funkcja haszująca wykorzystuje dzielenie modulo.
sposób użycia gprof: `make gprof ARG1=x ARG2=y` (po wykonaniu `make dictionary-pg`)

1) najpierw `make gprof`
![](https://i.imgur.com/h4Bg7H7.png)
109 sekund, z czego 97% we funkcji `sort_words`
zmieniamy funkcję sortującą na quick-sort (wbudowany `qsort`)

2) `make gprof QUICK=1`
![](https://i.imgur.com/HHxoglP.png)
6.62 sekundy, 87% w `find_ele_rec`, czyli problemem jest skanowanie listy
parametr FIND zmienia pomiędzy `{find_ele_rec, find_ele_iter_f, find_ele_iter_r}`.
Zmieniamy wersję rekurencyjną na iteracyjną.

3) `make gprof QUICK=1 FIND=1`
![](https://i.imgur.com/INHvq9A.png)
Czas działania pogorszył się (9.13), dlatego, że `find_ele_iter_f` dodaje na początek listy, zmieniamy na `find_ele_iter_r`, który dodaje na koniec.

4) `make gprof QUICK=1 FIND=2`
![](https://i.imgur.com/6qlwrLF.png)
5.80 sekundy, czyli lepiej niż w 2), ale dalej słabo.
parametry `find_ele_fun` zależą od naszej tablicy z kubełkami.
Jak w podręczniku ustawiłem funkcję haszującą na taką wykorzystującą sumę (`HASH=1`) i zmieniłem liczbę kubeczków na 199999 i dostałem 8.20s. Robimy więc inaczej: zmieniamy tylko liczbe kubełków (HASH pozostaje 0 - czyli wersja mod).

5) `make gprof SIZE=199999 QUICK=1 FIND=2 HASH=0`
![](https://i.imgur.com/h88BQut.png)
Mamy 0.713s. Zauważamy, że teraz bottleneck to `lower1`, czyli zmieniająca na małe znaki, która woła `strlen` w każdej iteracji. Zmieniamy implementację na `lower2`.

6) `make gprof SIZE=199999 QUICK=1 FIND=2 HASH=0 LOWER=1`
![](https://i.imgur.com/hmIxiRJ.png)
Ponownie zmieniamy funkcję haszującą, teraz na taką wykorzystującą xor (tak jak w podręczniku).

7) `make gprof SIZE=199999 QUICK=1 FIND=2 HASH=2 LOWER=1`
![](https://i.imgur.com/R59nOj2.png)
Dostajemy 0.54 sekundy, które ciężko dalej optymalizować (jak widać 5 pierwszych funkcji profilu płaskiego wykonuje się w podobnym czas). 
Drobne zmiany można zaobserwować przy zmianach n, ale są one na rzędu 0.01 sekundy, więc ciężko odróżnić je od błędu pomiarowego.

## 3
`make callgrind SIZE=199999 QUICK=1 FIND=2 HASH=2 LOWER=1`

## 4
wydruk `sudo cat /proc/iomem`
```
00000000-00000fff : Reserved            // niedostępne (np. moduły zarządzania BIOS)
00001000-0009efff : System RAM          // RAM
0009f000-000fffff : Reserved            // PCI
  000a0000-000bffff : PCI Bus 0000:00      
  000e0000-000e3fff : PCI Bus 0000:00
  000e4000-000e7fff : PCI Bus 0000:00
  000e8000-000ebfff : PCI Bus 0000:00
  000ec000-000effff : PCI Bus 0000:00
  000f0000-000fffff : PCI Bus 0000:00
    000f0000-000fffff : System ROM
00100000-70717017 : System RAM
  30a00000-31800eb0 : Kernel code       // pamięć jądra
  31800eb1-3225807f : Kernel data
  32527000-329fffff : Kernel bss
70717018-70740657 : System RAM
70740658-7547afff : System RAM
7547b000-7556efff : Reserved
7556f000-75816fff : System RAM
75817000-75817fff : Reserved
75818000-787c9fff : System RAM
787ca000-798a5fff : Reserved
798a6000-79922fff : ACPI Tables         // Advanced Control and Power Interface memory
79923000-79a8bfff : ACPI Non-volatile Storage
79a8c000-7ad0dfff : Reserved
7ad0e000-7ad0efff : System RAM
7ad0f000-7fffffff : Reserved
  7c000000-7fffffff : Graphics Stolen Memory
80000000-dfffffff : PCI Bus 0000:00     // I/O
  80000000-8fffffff : 0000:00:02.0
  90000000-a1ffffff : PCI Bus 0000:01
    90000000-9fffffff : 0000:01:00.0
    a0000000-a1ffffff : 0000:01:00.0
  a2000000-a2ffffff : 0000:00:02.0
  a3000000-a40fffff : PCI Bus 0000:01
    a3000000-a3ffffff : 0000:01:00.0
    a4000000-a407ffff : 0000:01:00.0
  a4100000-a41fffff : 0000:00:1f.3
    a4100000-a41fffff : ICH HD audio
  a4200000-a42fffff : PCI Bus 0000:02
    a4200000-a423ffff : 0000:02:00.0
      a4200000-a423ffff : alx
  a4300000-a430ffff : 0000:00:14.0
    a4300000-a430ffff : xhci-hcd        // Extensible Host Controller Interface (USB controller)
  a4310000-a4313fff : 0000:00:1f.3
    a4310000-a4313fff : ICH HD audio    // karta dźwiękowa
  a4314000-a4317fff : 0000:00:14.3
    a4314000-a4317fff : iwlwifi         // lan adapter
  a4318000-a4319fff : 0000:00:17.0
    a4318000-a4319fff : ahci            // Advanced Host Controller Interface (kontroler SATA - dyski)
  a431a000-a431bfff : 0000:00:14.2
  a431c000-a431c0ff : 0000:00:1f.4
  a431d000-a431dfff : 0000:00:1e.0
    a431d000-a431d1ff : lpss_dev
      a431d000-a431d01f : serial
    a431d200-a431d2ff : lpss_priv
    a431d800-a431dfff : idma64.0
      a431d800-a431dfff : idma64.0 idma64.0
  a431e000-a431e7ff : 0000:00:17.0
    a431e000-a431e7ff : ahci
  a431f000-a431f0ff : 0000:00:17.0
    a431f000-a431f0ff : ahci
  a4320000-a4320fff : 0000:00:16.0
    a4320000-a4320fff : mei_me
  a4321000-a4321fff : 0000:00:14.2
  a4322000-a4322fff : 0000:00:12.0
    a4322000-a4322fff : Intel PCH thermal driver
e0000000-efffffff : PCI MMCONFIG 0000 [bus 00-ff]
  e0000000-efffffff : Reserved
    e0000000-efffffff : pnp 00:05
fc000000-fc00ffff : PCI Bus 0000:00
  fc000000-fc0008da : ENE0110:00
  fc0008db-fc0008dc : ENE0110:00
  fc0008dd-fc00ffff : ENE0110:00
fc800000-fe7fffff : PCI Bus 0000:00
  fd000000-fd69ffff : pnp 00:06
  fd6a0000-fd6affff : pnp 00:08
  fd6b0000-fd6bffff : pnp 00:08
  fd6c0000-fd6cffff : pnp 00:06
  fd6d0000-fd6dffff : pnp 00:08
  fd6e0000-fd6effff : pnp 00:08
  fd6f0000-fdffffff : pnp 00:06
  fe000000-fe010fff : Reserved
    fe010000-fe010fff : 0000:00:1f.5
  fe200000-fe7fffff : pnp 00:06
fec00000-fec00fff : Reserved
  fec00000-fec003ff : IOAPIC 0            // kontroler przerwań
fed00000-fed03fff : Reserved
  fed00000-fed003ff : HPET 0
    fed00000-fed003ff : PNP0103:00
fed10000-fed17fff : pnp 00:05
fed18000-fed18fff : pnp 00:05
fed19000-fed19fff : pnp 00:05
fed20000-fed3ffff : pnp 00:05
fed40000-fed44fff : MSFT0101:00
  fed40000-fed44fff : MSFT0101:00
fed45000-fed8ffff : pnp 00:05
fed90000-fed90fff : dmar0
fed91000-fed91fff : dmar1
fee00000-fee00fff : Local APIC
  fee00000-fee00fff : Reserved
ff000000-ffffffff : Reserved
  ff000000-ffffffff : pnp 00:06
100000000-47dffffff : System RAM        // RAM ~ 14GB
47e000000-47fffffff : RAM buffer

```
sudo ./pagemap2 $$ | grep stack

```
0x7ffcce6be000     : pfn 0                soft-dirty 0 file/shared 0 swapped 0 present 0 library [stack]
0x7ffcce6bf000     : pfn 0                soft-dirty 0 file/shared 0 swapped 0 present 0 library [stack]
0x7ffcce6c0000     : pfn 0                soft-dirty 0 file/shared 0 swapped 0 present 0 library [stack]
0x7ffcce6c1000     : pfn 0                soft-dirty 0 file/shared 0 swapped 0 present 0 library [stack]
0x7ffcce6c2000     : pfn 0                soft-dirty 0 file/shared 0 swapped 0 present 0 library [stack]
0x7ffcce6c3000     : pfn 1b7fcc           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6c4000     : pfn 12e356           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6c5000     : pfn 328c8f           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6c6000     : pfn 36ea71           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6c7000     : pfn 29b87a           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6c8000     : pfn 2c70db           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6c9000     : pfn 31b946           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6ca000     : pfn 2af9e0           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6cb000     : pfn 398ba4           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6cc000     : pfn 289a62           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6cd000     : pfn 2d8a12           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6ce000     : pfn 365355           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6cf000     : pfn 2b5ac6           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6d0000     : pfn 2a1414           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6d1000     : pfn 13d16b           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6d2000     : pfn 32bbb9           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6d3000     : pfn 3252da           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6d4000     : pfn 196e04           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6d5000     : pfn 26283f           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6d6000     : pfn 198e56           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6d7000     : pfn 26efe3           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6d8000     : pfn 1a0945           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6d9000     : pfn 30bf24           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6da000     : pfn 2c753f           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6db000     : pfn 145cdc           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6dc000     : pfn 30c6fe           soft-dirty 1 file/shared 0 swapped 0 present 1 library [stack]
0x7ffcce6dd000     : pfn 0                soft-dirty 0 file/shared 0 swapped 0 present 0 library [stack]

```
![](https://i.imgur.com/s95ptcD.png)

pfn - page frame number (numer ramki)

adres w pamięci fizycznej = pfn * rozmiar_strony + offset 
offset = VPO = PPO - tj. dolne 12 bitów (bo 2^12 = 4096)
rozmiar wirtualnej ramki == rozmiar fizycznej ramki
4096 - 0x1000

np:
0x7ffcce6c3000     : pfn 1b7fcc
0x1b7fcc * 0x1000 + 0x000 = 0x1b7fcc000 -> RAM

0x7ffcce6cf000     : pfn 2b5ac6
0x2b5ac6 * 0x1000 + 0x000 = 0x2b5ac6000 -> RAM

0x7ffcce6dc000     : pfn 30c6fe
0x30c6fe * 0x1000 + 0x000 = 0x30c6fe000 -> RAM


## 5
```
vmstat -a
```
```
cat /proc/meminfo
```

fragment `ps -e -o pid,rss,vsz,cmd`
```
    PID   RSS    VSZ CMD
      1 13476 169420 /sbin/init splash
      2     0      0 [kthreadd]
      3     0      0 [rcu_gp]
      4     0      0 [rcu_par_gp]
      6     0      0 [kworker/0:0H-kblockd]
      9     0      0 [mm_percpu_wq]
     33     0      0 [cpuhp/4]
     34     0      0 [idle_inject/4]
     35     0      0 [migration/4]
     36     0      0 [ksoftirqd/4]
     63     0      0 [writeback]
     64     0      0 [kcompactd0]
     65     0      0 [ksmd]
     66     0      0 [khugepaged]
    113     0      0 [kintegrityd]
    114     0      0 [kblockd]
    115     0      0 [blkcg_punt_bio]
    117     0      0 [tpm_dev_wq]
    118     0      0 [ata_sff]
    119     0      0 [md]
    120     0      0 [edac-poller]
    121     0      0 [devfreq_wq]
    123     0      0 [watchdogd]
    126     0      0 [kswapd0]
    127     0      0 [ecryptfs-kthrea]
    129     0      0 [kthrotld]
    130     0      0 [irq/123-aerdrv]
    131     0      0 [irq/123-pcie-dp]
    132     0      0 [acpi_thermal_pm]
    297     0      0 [kworker/0:1H-events_highpri]
    321 94144 173424 /lib/systemd/systemd-journald
    409     0      0 [loop25]
    411  8488  25100 /lib/systemd/systemd-udevd
    412     0      0 [loop26]
    450     0      0 [cfg80211]
   1229 13276  24156 /lib/systemd/systemd-resolved
   1235  6000  90252 /lib/systemd/systemd-timesyncd
   1249  8128 241444 /usr/lib/accountsservice/accounts-daemon

```

```
ps -e -o pid,rss,vsz,cmd | tr -s " " | cut -d" " -f4 | tail +2 | paste -sd+ | bc
suma VSS: 326674736
```

```
free
              total        used        free      shared  buff/cache   available
Mem:       16240196     5096528      919792     1390480    10223876     9423388
Swap:      15625212        2316    15622896

```
https://stackoverflow.com/questions/7880784/what-is-rss-and-vsz-in-linux-memory-management

**stronnicowanie na żądanie**
Sprowadzamy strony do pamięci tylko wtedy kiedy jest to konieczne. Dotyczy wymiany pamięci pomiędzy pamięcią operacyjną/fizyczną (I rzędzu), a masową/dyskową (II rzędu). W tablicy stron przechowujemy dodatkowy bit valid informujący o tym czy strona znajduje się w pamięci operacyjnej, czy nie i wymaga sprowadzenia z obszaru wymiany (swap space), umieszczenie w ramce i ponowne wykonanie - leniwa wymiana) (lazy swapping). Pozwala rozszerzyć wirtualną przestrzeń adresową ponad rozmiar pamięci operacyjnej kosztem złożoności zarządzania pamięcią oraz narzutem czasowym wynikającym z korzystania z wolnej pamięci.

**współdzielenie pamięci**
Ten sam obszar pamięci fizycznej, który zawiera program lub biblioteki współdzielone, może być mappowany od wielu procesów, zamiast kopiowania dla każdego programu. Przy realizacji wymaga wprowadzenia ograniczeń w dostępie. Poprawia to efektywność wykorzystania pamięci. Pozwala też na kooperację pomiedzy procesami m.in synchronizację działań, czy komunikację (współdzielenie danych).