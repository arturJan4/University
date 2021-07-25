---
tags: ASK
---

# ASK - LISTA 7

## 1
![](https://i.imgur.com/d6JrZ0w.png)

```
    movslq 8(%rsi), %rax     // dostęp do str2->t
    addq   32(%rsi), %rax    // dostęp do str2->u
    movq   %rax, 184(%rdi)   // dostęp do str1->y
```

z 1 linii:
W str2 mamy long'a więc alignof(str2) to przynajmniej 8.
Więc jeśli t jest na 8 bajcie to array[B] jest wcześniej, czyli $4 \lt B \leq 8$.
Oraz struktura jest paddowana do wielokrotności 8.

z 2 linii:
t zajmuje 8 i 9 bajt. 10 i 11 - padding t
na 32 bajcie zaczyna się u 
-> bajty od 12 do 31 to short s[A] z czego przynajmniej do 24 jest rzeczywista tablica (reszta może być paddingiem)
short ma 2 bajty
czyli $6 \lt A \leq 10$

z 3 linii:
A * B * 4 + offset (7 bajtów maksymalnie) = 184
$177 \leq A \times B \times 4 \leq 184$
$44.25 \lt 45 \leq AB \leq46$
$45 = 3^2 \times 5$
$46 = 2 \times 23$
oraz
$4 \lt B \leq 8$
$6 \lt A \leq 10$
$A = 9$, $B = 5$

## 2
![](https://i.imgur.com/whEWn7p.png)

%rdi - i
%rsi - j
%rdx - k
%rcx - *dest
```
store_elem:
        leaq (%rsi,%rsi,2),%rax     // rax = 3j
        leaq (%rsi,%rax,4),%rax     // rax = j + 4 * 3j = 13j
        movq %rdi,%rsi              // rsi = i
        salq $6,%rsi                // rsi = 64*i
        addq %rsi,%rdi              // rdi = i + 64i = 65i
        addq %rax,%rdi              // rdi = 65i + 13j
        addq %rdi,%rdx              // rdx = k + 65i + 13j
        movq A(,%rdx,8),%rax        // rax = A + 8 * (k + 65i + 13j)
        movq %rax,(%rcx)            // *dest = rax
        movq $3640,%rax             // rax += 3640
    ret
```

3640 to sizeof(A) czyli tablica A ma 3640 bajtów to jest 3640/8 = 455 komórek
$R \times S \times T = 455$

8 - long
jak dostać się do A[i][j][k] rozmiaru $R \times S \times T$
$A[i] = A + 8 \times i \times S \times T$
$A[i][j] = A + 8 \times i \times S \times T + 8 \times j \times T$
$A[i][j][k] = A + 8 \times i \times S \times T + 8 \times j \times T + 8 \times k$ 
Grupujemy:
$$A[i][j][k] = A + 8 \times (i \times S \times T + \times j \times T + 8 \times k$ $

u nas mamy $A + 8 \times (65i + 13j + k)$
czyli: $S = \frac{65}{13} = 5$, $T = 13$
$R = \frac{455}{13 * 5} = 7$

## 3
![](https://i.imgur.com/IKN04yH.png)

%rdi - i
%rsi - *bp
```
test:
    movl   0x120(%rsi),%ecx         // ecx = bp + 288 (bp.last)
    addl   (%rsi),%ecx              // ecx += bp.first
    leaq   (%rdi, %rdi, 4),%rax     // rax = 5i
    leaq   (%rsi, %rax, 8),%rax     // rax = bp + 8*5i = bp + 40i // &bp->a[i] - 8
    movq   0x8(%rax),%rdx           // rdx = *[(bp + 40i) + 8] // ap->idx (+8 to int + padding, wartość to pierwszy element a_struct czyli idx)
    movslq %ecx,%rcx                // rcx = sign extend: ecx
    movq   %rcx,0x10(%rax, %rdx, 8) // (bp + 40i + 8) + 8 * (ap->idx) + 8 = rcx // ap->x
    retq
```

```
elementy bp
|(first) 4 | 4 | a_struct a[7] (280) | 4 | last |

elementy a:
| idx (0) | x[4] (+8) | idx (+40) | x[4] (+48) | 

wtedy ap = &bp->a[i] to: bp + 8 + 40i 
i ap->idx:  bp + 8 + 40i 
a ap->x:    bp + 8 + 40i + 8
a ap->x[j]: bp + 8 + 40i + 8 * j
```

Przesuwamy wskaźnik o 288 bajtów, gdzie 4 bajty zostawiamy na int, zostają więc nam 284 bajty na struktury.
Chcąc dostać się do elementu tablicy-struktury, mnożymy $i$ przez 40. Stąd wynika, że struktura ta zawiera 40 bajtów.
Musimy jeszcze zostawić 4 bajty na padding.
Więc $CNT = 280 / 40 = 7$.
Z kodu C można również wywnioskować, że struktura ta zawiera liczbę oraz tablicę.
Tablica będzie typu long, ponieważ wkładamy do niej liczbę $n$ rozszerzoną do 64-bitów, czyli tyle ile ma long. W takim razie będziemy mieli $40/8 = 5$ elementów. Jednak chcemy przechowywać jeszcze liczbę na początku, na która musimy przeznaczyć 8 bajtów.
Tak węc finalnie otrzymamy 8 bajtów na $idx$ oraz 32 bajty na tablicę, więc będzie ona zawierała 4 elementy.

$CNT = 7$

```c=
typedef struct A {
    long idx;
    long x[4];
} a_struct;
```

## 4
![](https://i.imgur.com/nU8KJJU.png)


```c=
union elem {
    struct {
        long *p;
        long y;
    } e1;
    
    struct {
        long x;
        union elem *next;
    } e2;
};
```

Unia ma 16 bajtów bo największy element ma 16 bajtów

```=
proc(union elem *)
proc:
    movq 8(%rdi),%rax    res = next (wskaźnik na union elem) (w e2)
    movq (%rax),%rdx     tmp = *res (union elem)
    movq (%rdx),%rdx     tmp = *p   (wartość, bo pierwszy element)
    subq 8(%rax),%rdx    tmp = tmp - *(next + 8)
    movq %rdx,(%rdi)     tmp2 = tmp
    
    ret
```

```c=
union elem* proc(union elem *x)
{
    union elem *next = x->e2.next;        // 3
    long p_val = *(next->e1.p);           // 4 i 5
    p_val = p_val - next->e1.y;           // 6
    x->e2.x = p_val;                      // 7
    return next;
}

```
## 5
![](https://i.imgur.com/q9Xua8o.png)

%rdi - x
%rsi - y
%rdx - z

%rsp - wskaźnik stosu
```
wrap:
    subq $72, %rsp        // alokujemy 9 8bajtowych miejsc na stosie
    movq %rdx, (%rsp)     // z na dół stosu
    movq %rsp, %rdx       // k = koniecStosu
    leaq 8(%rsp), %rax    // %rax - adres przedostatnia zalokowana komórka
    pushq %rdx             
    pushq %rsi
    pushq %rdi            
    movq %rax, %rdi       // %rdi - adres przedostatnia zalokowana komórka
    call eval             // wołamy eval
    movq 40(%rsp), %rax   // result = x - z
    addq 32(%rsp), %rax   // result += z*x (górne bity)
    imulq 48(%rsp), %rax  // result *= (x-y)
    addq $96, %rsp        // dealokujemy 96 (72 + 24 (z 3 pop))
    
    ret
```


Rekord aktywacji w momencie wołania eval
|         |                   |         |
| ------- | ----------------- | ------- |
| 1       |                   |         |
| 2       |                   |         |
| 3       |                   |         |
| 4       |                   |         |
| 5       |                   |         |
| 6       |                   |         |
| 7       |                   |         |
| 8       |                   |         |
| 9       | z                 | <- %rdx |
| ---     | ---               | ---     |
| 10      | koniec stosu %rdx |         |
| 11      | y                 |         |
| 12      | x                 |         |
| rtn_add |                   |         |


![](https://i.imgur.com/df4brXQ.png)


```
eval:
    movq %rdi, %rax        // rax = adres 8 komórki
    movq 16(%rsp), %rcx    // rcx = y ze stosu  // u[1] z SA
    movq 24(%rsp), %rdx    // rdx = koniec stosu z wrap (k) //&z // wskaźnik v z SA
    movq (%rdx), %rsi      // rsi = z // (*k) // *v z SA
    movq %rcx, %rdx        // rdx = y
    imulq %rsi, %rdx       // rdx = y * z
    movq %rdx, (%rdi)      // zapisujemy rdx w 8 komórce // p[0] z SB
    movq 8(%rsp), %rdx     // rdx = x ze stosu    // u[0] z SA
    movq %rdx, %rdi        // rdi = x
    subq %rsi, %rdi        // rdi = x - z
    movq %rdi, 8(%rax)     // zapisujemy rdi w 7 komórce // p[1] z SB
    subq %rcx, %rdx        // rdx = x - y
    movq %rdx, 16(%rax)    // zapisujemy rdx w 6 komórce // q z SB
    
    ret
```

|     |              |         |
| --- | ------------ | ------- |
| 1   |              |         |
| 2   |              |         |
| 3   |              |         |
| 4   |              |         |
| 5   |              |         |
| 6   | x-y          |         |
| 7   | x-z          |         |
| 8   | z\*x         |         |
| 9   | z            | <- %rdx |
| --- | ---          | ---     |
| 10  | koniec stosu |         |
| 11  | y            |         |
| 12  | x            |         |

```c=
typedef struct A {
    long u[2];
    long *v;
} SA;
typedef struct B {
    long p[2];
    long q;
} SB;

```

```c=
    SB eval(SA s)
    {
        long x=s.u[0], y=s.u[1], z=*s.v; 
        SB result = {
            .p[0] = z * x,
            .p[1] = x - z,
            .q = x - y
        };
        return result;
    }
    
    long wrap(long x, long y, long z)
    {
        SA temp = {
            .u[1] = y,
            .v = &z,
            .u[0] = x
        };
        
        SB sb = eval(temp);
        
        return (sb.p[1] + sb.p[0]) * sb.q;
    }
```


## 6
![](https://i.imgur.com/Oj3y0GX.png)

128 bitów - 4 floaty

```=
puzzle6:
    movq        (%rdi), %rdx                  // pierwsze pole struct
    leaq        8(%rdi), %rcx                 // drugie do rcx
    xorl        %eax, %eax                    // zerujemy raxa
    vxorps      %xmm1, %xmm1, %xmm1           // zerowanie xmm1
    vmovss      .LC1(%rip), %xmm2             // 1.0
.L2: 
    cmpq        %rdx, %rax                    // sprawdzenie czy i >= n
    jge         .L5
    vfmadd231ss (%rcx,%rax,4), %xmm2, %xmm1   // kolejne pole tablicy floatow
    incq        %rax                          // zwiekszamy licznik
    vmulss      %xmm0, %xmm2, %xmm2           // xmm2 = xmm2 * xmm0
    jmp         .L2
.L5: 
    vmovaps     %xmm1, %xmm0                  // xmm0 zwraca 
    ret

.LC1: .long 0x3f800000                        // 0011 1111 1 -> 01111111
                                              // bias = 127 -> 127 - 127 -> 2^0 = 1
```

```c=
struct P
{
    long n;
    float* y;
};


float puzzle6(struct P *s, float b)
{
    long n = s->n;
    float* tab = s->y;
    
    float sum = 0.0;
    float number = 1.0;
    for(long i=0; i<n; i++)
    {
        sum = sum + (tab[i] * number);
        number = number * b;
    }
    return sum;
}

```

$\sum_{i=0}^{n} y[i]*b^i$


- vfmadd231ss a b c => c = c + (a*b)
- vmulss  a b c => c = a*b