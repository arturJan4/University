---
tags: ASK
---

# ASK - LISTA 6

misc:
https://repzret.org/p/repzret/
https://stackoverflow.com/questions/20526361/what-does-rep-ret-mean
https://stackoverflow.com/questions/33666617/what-is-the-best-way-to-set-a-register-to-zero-in-x86-assembly-xor-mov-or-and
https://stackoverflow.com/questions/11177137/why-do-x86-64-instructions-on-32-bit-registers-zero-the-upper-part-of-the-full-6
dobre: https://stackoverflow.com/questions/840501/how-do-function-pointers-in-c-work


## 1
long puzzle(long n, long *p)

rekord aktywacji (stack frame)
rejestry zapisane przez f. wołaną (callee-saved registers)
zmienne lokalne
adres powrotu

n - %rdi
*p - %rsi

callee-saved:
%rbx, %rbp, %rsp

zmienne lokalne: 8(%rsp)

TODO:
czy push i pop przesuwa o 8 rsp - TAK
co z tym align do 32 bitów - rtn address jest w stack frame chyba
push, push, 3 + rtn - podzielne przez 16
```
puzzle:                        // stack = [rtn_addr|*|]
        push %rbp              // stack = [%rbp|*|, rtn_addr]
        xorl %eax, %eax        // result = 0
        mov  %rsi, %rbp        // %rbp = p
        push %rbx              // stack = [%rbx|*|, %rbp, , rtn_addr]
        mov  %rdi, %rbx        // %rbx = n
        sub  $24, %rsp         // stack = [|*|null, null, null, %rbx, %rbp, rtn_addr] rozszerzamy stack o 3
        test %rdi, %rdi        // bitwise-and n
        jle  .L1               // (n==0) albo (n <= 0) TODO ->  jump (ZF=1 or SF≠ OF)
        lea  8(%rsp), %rsi     // *p = &(stack + 1)
        // stack = [|*|null, temp, null, %rbx, %rbp, rtn_addr]
        lea  (%rdi, %rdi), %rdi// n = 2 * n
        call puzzle            // result = puzzle(n, *p)
        add  8(%rsp), %rax     // result += temp
        add  %rax, %rbx        // n += result
.L1:    mov  %rbx, (%rbp)      // *p = n
        add  $24, %rsp         // przywracamy stos
        pop  %rbx              // przywracamy rbx
        pop  %rbp              // przywracamy rbp
        ret
```

```c=
    long puzzle(long n, long *p)
    {
        long result = 0;
        if(n > 0)
        {
            long temp;
            result = puzzle(n * 2, &temp);
            result += temp;
            n += result;
        }
        *p = n;
        return result;
    }
```
Rekord aktywacji:
```
return address
%rbp
%rbx
null
temp
null
```

## 2
struct T puzzle8(long *a, long n)
*a - %rsi
n - %rdx

r11 - n
r10 - temp
rax - result
r8  - min
r9  - max
rcx - elem

TODO:
czemu rdx to n -> ABI
jak zwracamy (RAX:RDX?)

ABI - strona 24:
If the type has class MEMORY, then the caller provides space for the return value and passes the address of this storage in %rdi as if it were the first argument to the function. In effect, this address becomes a “hidden” first argument. This storage must not overlap any data visible to the callee through other names than this argument.

On return %rax will contain the address that has been passed in by the caller in %rdi.
```
puzzle8:
        movq  %rdx, %r11            // n  
        xorl  %r10d, %r10d          // temp = 0 (zeruje też górne bajty)
        xorl  %eax, %eax            // result = 0
        movq  $LONG_MIN, %r8        // max = LONG_MIN
        movq  $LONG_MAX, %r9        // min = LONG_MAX
.L2:    cmpq  %r11, %r10            
        jge   .L5                   // temp - n >= 0 -> jmp
        movq  (%rsi,%r10,8), %rcx   // elem = a[temp]
        cmpq  %rcx, %r9                  
        cmovg %rcx, %r9             // min = (min - elem) > 0 ? elem : min (mov if greater)
        cmpq  %rcx, %r8             
        cmovl %rcx, %r8             // max = (max - elem) < 0 ? elem : max (mov if less)
        addq  %rcx, %rax            // result += elem
        incq  %r10                  // temp++
        jmp   .L2                   
.L5:    cqto                        // convert quadword in %rax to octoword in %rdx:%rax
        movq  %r9, (%rdi)           // *a = max
        idivq %r11                  // RDX:RAX / global -> signed divide (EAX - Quotient, EDX - Remainder)
        movq  %r8, 8(%rdi)          // *(a+1) = min          
        movq  %rax, 16(%rdi)        // *(a+2) = max
        movq  %rdi, %rax            // result = a (wskaznik na poczatek struktury)
        ret
```
Dedukcja sygnatury bez sygnatury
na podstawie tego że zwracamy wskaźnik na strukturę
```
struct T* (struct T*, long, long)
```
```c=
    struct T 
    {
        long min;
        long max;
        long average;
    };

    struct T puzzle(long *a, long n) 
    {
        long sum = 0;
        long max = LONG_MIN;
        long min = LONG_MAX;
    
        for(long temp = 0; temp < n; temp++) 
        {
            long elem = a[temp];
            if (elem < min) 
                min = elem;
            if (elem > max) 
                max = elem;
            sum += elem;
        }
    
        struct T t;
        t.min = min;
        t.max = max;
        t.average = (sum / n);

        return t;
    }
```
Liczy minimum, maximum i średnią arytmetyczną ciągu liczb i przechowuje w strukturze T.

## 3
Do wyjaśnienia:
jmpq *0x4006f8(,%rsi,8)
kod samomodyfikujący się
call *(%rdi,%rsi,8) - pośrednie wywołanie procedury
## 4
M i F wzajemnie rekurencyjne

np. int (*ptr)(int, int) - pointer to a function which receives 2 ints and returns an int

long (*)(long)

Co może pójśc nie tak?
- zły adres powrotu
- nadpisane zawartości callee-saved

%rdi - argument long
```
M:
        pushq  %rdi                // zapisujemy n na stosie
        testq  %rdi, %rdi
        je     .L2                 // n == 0 -> jump, ZF = 1
        leaq   -1(%rdi), %rdi      // n = n - 1
        call   M                   // result = M(n)
        movq   %rax, %rdi          // n = result
        call   F                   // result = F(n)
        movq   (%rsp), %rdi        // n = n (ze stosu)
        subq   %rax, %rdi          // n = n - result
.L2:    movq   %rdi, %rax          // result = n
        ret
``` 
brakuje popq %rdi

%r12 = temp
```
F:      
        testq  %rdi, %rdi
        je     .L3                 // n == 0 -> jump
        movq   %rdi, %r12          // temp = n
        leaq   -1(%rdi), %rdi      // n = n - 1
        call   F                   // result = F(n)
        movq   %rax, %rdi          // n = result
        call   M                   // result = M(n)
        subq   %rax, %12           // temp = temp - result
        movq   %r12, %rax          // result = temp
        ret
.L3:    movl   $1, %eax            
        ret                        // return 1
```

%r12 jest callee-saved powinniśmy go pushować na stos jeśli chcemy go używać (bo jakaś funkcja może zakładać że %r12 zachowa wartość)
podobnie %rdi jest caller-saved więc powinien być pushowany przed  wywołaniem jeśli go potem używamy w kodzie (bo inaczej inne funkcje mogą używać %rdi)
## 5
https://man7.org/linux/man-pages/man3/alloca.3.html
Jednostka translacji - to pojedynczy plik źródłowy (po uwzględnieniu dyrektyw preprocesora: (#include) oraz tych dotyczących warunkowej kompilacji), czyli tutaj kompilujemy tylko jeden plik .c (flaga -c)

```
gcc puzzle.c -c -Og -fomit-frame-pointer -fno-stack-protector 
objdump -d puzzle.o
```
void *alloca(size_t size);
alloca(size) - alokuje w obecnym rekordzie aktywacji size bajtów, które są automatycznie zwalniane. Zwraca wskaźnik na początek tej pamięci.

alokacje pamięci to push i sub na %rsp
dealokacje to pop i add na %rsp, leave (? - przesuwa rbp na rsp, więc chyba też)

```c
long aframe(long n, long idx, long *q) {
    long i;
    long **p = alloca(n * sizeof(long *));
    p[n-1] = &i;
    for (i = 0; i < n; i++)
        p[i] = q;
    return *p[idx];
}    
```

%rdi - n
%rsi - idx
%rdx - *q
```
Disassembly of section .text:

0000000000000000 <aframe>:
   0:   f3 0f 1e fa             endbr64 
   4:   55                      push   %rbp                        // przydział
   5:   48 89 e5                mov    %rsp,%rbp
   8:   48 83 ec 10             sub    $0x10,%rsp                  // przydział
   c:   4c 8d 0c fd 00 00 00    lea    0x0(,%rdi,8),%r9
  13:   00 
  14:   49 8d 41 17             lea    0x17(%r9),%rax
  18:   48 89 c1                mov    %rax,%rcx
  1b:   48 83 e1 f0             and    $0xfffffffffffffff0,%rcx
  1f:   48 25 00 f0 ff ff       and    $0xfffffffffffff000,%rax
  25:   49 89 e2                mov    %rsp,%r10
  28:   49 29 c2                sub    %rax,%r10
  2b:   4c 89 d0                mov    %r10,%rax
  2e:   48 39 c4                cmp    %rax,%rsp    
  31:   74 12                   je     45 <aframe+0x45>
  33:   48 81 ec 00 10 00 00    sub    $0x1000,%rsp                // przydział
  3a:   48 83 8c 24 f8 0f 00    orq    $0x0,0xff8(%rsp)
  41:   00 00 
  43:   eb e9                   jmp    2e <aframe+0x2e>
  45:   48 89 c8                mov    %rcx,%rax
  48:   25 ff 0f 00 00          and    $0xfff,%eax
  4d:   48 29 c4                sub    %rax,%rsp                    // przydział
  50:   48 85 c0                test   %rax,%rax
  53:   74 06                   je     5b <aframe+0x5b>
  55:   48 83 4c 04 f8 00       orq    $0x0,-0x8(%rsp,%rax,1)
  5b:   4c 8d 44 24 0f          lea    0xf(%rsp),%r8
  60:   49 83 e0 f0             and    $0xfffffffffffffff0,%r8
  64:   4c 89 c1                mov    %r8,%rcx
  67:   48 8d 45 f8             lea    -0x8(%rbp),%rax
  6b:   4b 89 44 08 f8          mov    %rax,-0x8(%r8,%r9,1)
  70:   48 c7 45 f8 00 00 00    movq   $0x0,-0x8(%rbp)
  77:   00 
  78:   48 8b 45 f8             mov    -0x8(%rbp),%rax
  7c:   48 39 f8                cmp    %rdi,%rax
  7f:   7d 0b                   jge    8c <aframe+0x8c>
  81:   48 89 14 c1             mov    %rdx,(%rcx,%rax,8)
  85:   48 83 45 f8 01          addq   $0x1,-0x8(%rbp)
  8a:   eb ec                   jmp    78 <aframe+0x78>
  8c:   49 8b 04 f0             mov    (%r8,%rsi,8),%rax
  90:   48 8b 00                mov    (%rax),%rax
  93:   c9                      leaveq                               // przesuwa rsp na rbp wiec dealokuje
  94:   c3                      retq  
```
%rbp jest callee-saved

leave:
movq %rbp, %rsp
popq %rbp

Czyli przywraca wskaźnik z %rbp na %rsp (usuwa obecną ramkę), a następnie przywraca poprzednie %rbp ze stosu.
## 6
long puzzle5(void)

TODO:
czy call może modyfikować rsp?
czy readlong może zwracać na raxie longa?
Wracając z fukncji readlong %rsp się ustawi przy returnie bo jest callee-saved.

readlong(long *ptr) zapisuje pod przekazanym wskaźnikiem

stack_ptr = %rdi
```
puzzle5:
        subq   $24, %rsp        // alokujemy 3
        movq   %rsp, %rdi       // stack-ptr
        call   readlong         // readlong(stack) [null, null, null]
        leaq   8(%rsp), %rdi    //                 [rl1, null, null]
        call   readlong         // readlong(stack+1) [rl1, rl2, null]
        movq   (%rsp), %rax     // result = rl1
        cqto                    // rax -> rdx:rax (singed extension)
        idivq  8(%rsp)          // rax=(rdx:rax) / rl2, rdx=(rdx:rax) % rl2  
        xorl   %eax, %eax        
        testq  %rdx, %rdx
        sete   %al              // result = (rdx == 0) -> al to 0-byte %rax, set if equal/zero (ZF)
        addq   $24, %rsp        // dealokacja stosu
        ret
```

```c=
    long readlong(long *x);

    long puzzle5(void)
    {
        long a, b;
        readlong(&a);
        readlong(&b);
        return a%b == 0;
    }

```

co robi?
Zwraca czy z wczytanych dwóch kolejnych przez readlong liczb pierwsza dzieli drugą

sygnatura:
void readlong(long *x)

Rekord aktywacji: 32 bajty
rtn_addr
null
rl2
rl1

## 7
https://en.wikipedia.org/wiki/Stdarg.h

## 8