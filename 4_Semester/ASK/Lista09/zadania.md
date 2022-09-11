---
tags: ASK
---
# ASK - LISTA 9

przed readline (break *0x0000000000401d17):
```
>>> x/16xg $rsp
0x7fffffffdd90:	0x0000000000000000	0x000000000041185e
0x7fffffffdda0:	0x00007fffffffdf08	0x0000000000400488
0x7fffffffddb0:	0x0000000000402d60	0x0000000000402e00
0x7fffffffddc0:	0x0000000000000000	0x0000000000401d45 - adres powrotu do main
0x7fffffffddd0:	0x0000000000400488	0x0000000000402590
0x7fffffffdde0:	0x0000000000000000	0x0000000200000000
0x7fffffffddf0:	0x00007fffffffdf08	0x0000000000401d2c
0x7fffffffde00:	0x0000000000000000	0x0000000600000000

```
po readline (break *0x0000000000401d1f)
```
0x7fffffffdd90:	0xdec0addedec0adde	0xdec0addedec0adde
0x7fffffffdda0:	0xdec0addedec0adde	0xdec0addedec0adde
0x7fffffffddb0:	0xdec0addedec0adde	0xdec0addedec0adde
0x7fffffffddc0:	0xdec0addedec0adde==0x0000000000401d67 - adresy gadget
0x7fffffffddd0:=0x000000000040232d==0x0000000000000000 - adresy gadget
0x7fffffffdde0:	0x6e69622f7273752f	0x7461636e61796e2f
0x7fffffffddf0:	0x00007fffffff0000	0x0000000000401d2c
0x7fffffffde00:	0x0000000000000000	0x0000000600000000
```

Jak obserwować skoki?
Dajemy breakpoint na
```
0x0000000000401d2b  echo+28 retq 
```

i patrzymy na adres powrotu w 
i robimy skoki 

0x000000000040232d

## 5
gcc -c -fverbose-asm -fno-asynchronous-unwind-tables -z -S p1.c 