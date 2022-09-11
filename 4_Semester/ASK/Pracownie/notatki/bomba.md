
=> 0x0000555555555405 <+0>:	sub    $0x8,%rsp
   0x0000555555555409 <+4>:	lea    0x1d40(%rip),%rsi        		# 0x555555557150 - pod tym adresem jest napis, który można znaleźć też w strings
   0x0000555555555410 <+11>:	callq  0x555555555904 <strings_not_equal>	# zgodność napisów
   0x0000555555555415 <+16>:	test   %eax,%eax
   0x0000555555555417 <+18>:	jne    0x55555555541e <phase_1+25>
   0x0000555555555419 <+20>:	add    $0x8,%rsp
   0x000055555555541d <+24>:	retq   
   0x000055555555541e <+25>:	callq  0x555555555a10 <explode_bomb>
   0x0000555555555423 <+30>:	jmp    0x555555555419 <phase_1+20>

Dump of assembler code for function phase_2:
=> 0x0000555555555425 <+0>:	push   %rbp
   0x0000555555555426 <+1>:	push   %rbx
   0x0000555555555427 <+2>:	sub    $0x28,%rsp
   0x000055555555542b <+6>:	mov    %rsp,%rsi
   0x000055555555542e <+9>:	callq  0x555555555a36 <read_six_numbers>	# 1) czyta 6 liczb
   0x0000555555555433 <+14>:	cmpl   $0x0,(%rsp)				# pierwsza podana liczba > 0
   0x0000555555555437 <+18>:	js     0x555555555443 <phase_2+30>
   0x0000555555555439 <+20>:	mov    %rsp,%rbp
   0x000055555555543c <+23>:	mov    $0x1,%ebx
   0x0000555555555441 <+28>:	jmp    0x55555555545b <phase_2+54>
   0x0000555555555443 <+30>:	callq  0x555555555a10 <explode_bomb>
   0x0000555555555448 <+35>:	jmp    0x555555555439 <phase_2+20>
   0x000055555555544a <+37>:	callq  0x555555555a10 <explode_bomb>
   0x000055555555544f <+42>:	add    $0x1,%ebx				# 3) ebx = 2
   0x0000555555555452 <+45>:	add    $0x4,%rbp			 	
   0x0000555555555456 <+49>:	cmp    $0x6,%ebx
   0x0000555555555459 <+52>:	je     0x555555555467 <phase_2+66>
   0x000055555555545b <+54>:	mov    %ebx,%eax
   0x000055555555545d <+56>:	add    0x0(%rbp),%eax			  	# 2) 1 + pierwsza wartość 
   0x0000555555555460 <+59>:	cmp    %eax,0x4(%rbp)				# druga == 1 + pierwsza
   0x0000555555555463 <+62>:	je     0x55555555544f <phase_2+42>
   0x0000555555555465 <+64>:	jmp    0x55555555544a <phase_2+37>
   0x0000555555555467 <+66>:	add    $0x28,%rsp
   0x000055555555546b <+70>:	pop    %rbx
   0x000055555555546c <+71>:	pop    %rbp
   0x000055555555546d <+72>:	retq   
End of assembler dump.

1 2 4 7 11 16 - dodaje ebx czyli obecny numer argumentu
====================================================================
Dump of assembler code for function phase_3:
=> 0x000055555555546e <+0>:	sub    $0x18,%rsp
   0x0000555555555472 <+4>:	lea    0x7(%rsp),%rcx
   0x0000555555555477 <+9>:	lea    0xc(%rsp),%rdx
   0x000055555555547c <+14>:	lea    0x8(%rsp),%r8
   0x0000555555555481 <+19>:	lea    0x1d1e(%rip),%rsi        # 0x5555555571a6
   0x0000555555555488 <+26>:	mov    $0x0,%eax
   0x000055555555548d <+31>:	callq  0x555555555130 <__isoc99_sscanf@plt>
   0x0000555555555492 <+36>:	cmp    $0x2,%eax
   0x0000555555555495 <+39>:	jle    0x5555555554b6 <phase_3+72>
   0x0000555555555497 <+41>:	cmpl   $0x7,0xc(%rsp)				 	< 7
   0x000055555555549c <+46>:	ja     0x5555555555ab <phase_3+317>
   0x00005555555554a2 <+52>:	mov    0xc(%rsp),%eax
   0x00005555555554a6 <+56>:	lea    0x1d13(%rip),%rdx        # 0x5555555571c0
   0x00005555555554ad <+63>:	movslq (%rdx,%rax,4),%rax
   0x00005555555554b1 <+67>:	add    %rdx,%rax
   0x00005555555554b4 <+70>:	jmpq   *%rax						switch-case()
   0x00005555555554b6 <+72>:	callq  0x555555555a10 <explode_bomb>
   0x00005555555554bb <+77>:	jmp    0x555555555497 <phase_3+41>
   0x00005555555554bd <+79>:	mov    $0x65,%eax
   0x00005555555554c2 <+84>:	cmpl   $0x15a,0x8(%rsp)
   0x00005555555554ca <+92>:	je     0x5555555555b5 <phase_3+327>
   0x00005555555554d0 <+98>:	callq  0x555555555a10 <explode_bomb>
   0x00005555555554d5 <+103>:	mov    $0x65,%eax
   0x00005555555554da <+108>:	jmpq   0x5555555555b5 <phase_3+327>
   0x00005555555554df <+113>:	mov    $0x78,%eax
   0x00005555555554e4 <+118>:	cmpl   $0x7b,0x8(%rsp)
   0x00005555555554e9 <+123>:	je     0x5555555555b5 <phase_3+327>
   0x00005555555554ef <+129>:	callq  0x555555555a10 <explode_bomb>
   0x00005555555554f4 <+134>:	mov    $0x78,%eax
   0x00005555555554f9 <+139>:	jmpq   0x5555555555b5 <phase_3+327>
   0x00005555555554fe <+144>:	mov    $0x75,%eax
   0x0000555555555503 <+149>:	cmpl   $0x1a6,0x8(%rsp)
   0x000055555555550b <+157>:	je     0x5555555555b5 <phase_3+327>
   0x0000555555555511 <+163>:	callq  0x555555555a10 <explode_bomb>
   0x0000555555555516 <+168>:	mov    $0x75,%eax
   0x000055555555551b <+173>:	jmpq   0x5555555555b5 <phase_3+327>
   0x0000555555555520 <+178>:	mov    $0x65,%eax
   0x0000555555555525 <+183>:	cmpl   $0x24a,0x8(%rsp)
   0x000055555555552d <+191>:	je     0x5555555555b5 <phase_3+327>
   0x0000555555555533 <+197>:	callq  0x555555555a10 <explode_bomb>
   0x0000555555555538 <+202>:	mov    $0x65,%eax
   0x000055555555553d <+207>:	jmp    0x5555555555b5 <phase_3+327>
   0x000055555555553f <+209>:	mov    $0x74,%eax
   0x0000555555555544 <+214>:	cmpl   $0x1b7,0x8(%rsp)
   0x000055555555554c <+222>:	je     0x5555555555b5 <phase_3+327>
   0x000055555555554e <+224>:	callq  0x555555555a10 <explode_bomb>
   0x0000555555555553 <+229>:	mov    $0x74,%eax
   0x0000555555555558 <+234>:	jmp    0x5555555555b5 <phase_3+327>
   0x000055555555555a <+236>:	mov    $0x6b,%eax
   0x000055555555555f <+241>:	cmpl   $0x245,0x8(%rsp)
   0x0000555555555567 <+249>:	je     0x5555555555b5 <phase_3+327>
   0x0000555555555569 <+251>:	callq  0x555555555a10 <explode_bomb>
   0x000055555555556e <+256>:	mov    $0x6b,%eax
   0x0000555555555573 <+261>:	jmp    0x5555555555b5 <phase_3+327>
   0x0000555555555575 <+263>:	mov    $0x75,%eax
   0x000055555555557a <+268>:	cmpl   $0x3d7,0x8(%rsp)
   0x0000555555555582 <+276>:	je     0x5555555555b5 <phase_3+327>
   0x0000555555555584 <+278>:	callq  0x555555555a10 <explode_bomb>
   0x0000555555555589 <+283>:	mov    $0x75,%eax
   0x000055555555558e <+288>:	jmp    0x5555555555b5 <phase_3+327>
   0x0000555555555590 <+290>:	mov    $0x71,%eax
   0x0000555555555595 <+295>:	cmpl   $0x2c1,0x8(%rsp)
   0x000055555555559d <+303>:	je     0x5555555555b5 <phase_3+327>
   0x000055555555559f <+305>:	callq  0x555555555a10 <explode_bomb>
   0x00005555555555a4 <+310>:	mov    $0x71,%eax
   0x00005555555555a9 <+315>:	jmp    0x5555555555b5 <phase_3+327>
   0x00005555555555ab <+317>:	callq  0x555555555a10 <explode_bomb>
   0x00005555555555b0 <+322>:	mov    $0x67,%eax
   0x00005555555555b5 <+327>:	cmp    %al,0x7(%rsp)
   0x00005555555555b9 <+331>:	jne    0x5555555555c0 <phase_3+338>
   0x00005555555555bb <+333>:	add    $0x18,%rsp
   0x00005555555555bf <+337>:	retq   
   0x00005555555555c0 <+338>:	callq  0x555555555a10 <explode_bomb>
   0x00005555555555c5 <+343>:	jmp    0x5555555555bb <phase_3+333>
   
x/s 0x5555555571a6
0x5555555571a6:	"%d %c %d"
int char int - typ scanf
od pierwszej zależy skok < 7
potem druga wartość 0x1b7 potem w hexie 0x74 = 't'
4 t 439 - metodą prób i błędów

====================================================================
Dump of assembler code for function phase_4:
=> 0x0000555555555604 <+0>:	sub    $0x18,%rsp
   0x0000555555555608 <+4>:	lea    0x8(%rsp),%rcx
   0x000055555555560d <+9>:	lea    0xc(%rsp),%rdx
   0x0000555555555612 <+14>:	lea    0x1ce6(%rip),%rsi        # 0x5555555572ff
   0x0000555555555619 <+21>:	mov    $0x0,%eax
   0x000055555555561e <+26>:	callq  0x555555555130 <__isoc99_sscanf@plt> "%d %d"
   0x0000555555555623 <+31>:	cmp    $0x2,%eax
   0x0000555555555626 <+34>:	jne    0x55555555562f <phase_4+43>
   0x0000555555555628 <+36>:	cmpl   $0xe,0xc(%rsp)		# (rsp+12) <= 14
   0x000055555555562d <+41>:	jbe    0x555555555634 <phase_4+48>
   0x000055555555562f <+43>:	callq  0x555555555a10 <explode_bomb>
   0x0000555555555634 <+48>:	mov    $0xe,%edx		# rdx = 14
   0x0000555555555639 <+53>:	mov    $0x0,%esi		# rsi = 0
   0x000055555555563e <+58>:	mov    0xc(%rsp),%edi		# rdi = rsp + 12 - pierwszy argument
   0x0000555555555642 <+62>:	callq  0x5555555555c7 <func4>	# %rdi, %rsi, %rdx
   0x0000555555555647 <+67>:	or     0x8(%rsp),%eax		# result | (8+rsp-drugi argument) == 0
   0x000055555555564b <+71>:	je     0x555555555652 <phase_4+78>	 # ZF = 1
   0x000055555555564d <+73>:	callq  0x555555555a10 <explode_bomb>
   0x0000555555555652 <+78>:	add    $0x18,%rsp
   0x0000555555555656 <+82>:	retq   
End of assembler dump.

>>> x/xs 0x5555555572ff
0x5555555572ff:	"%d %d"
x <= 14 (rsp+12) y (rsp+8)
func4(x, 0, 14)
sprawdźmy jaki jest result 

result	| 0 | 0 |
x	| 0 | 1 | 
x = 1, y = 0

====================================================================
Dump of assembler code for function phase_5:
=> 0x0000555555555657 <+0>:	push   %rbx
   0x0000555555555658 <+1>:	sub    $0x10,%rsp
   0x000055555555565c <+5>:	mov    %rdi,%rbx
   0x000055555555565f <+8>:	callq  0x5555555558e7 <string_length>
   0x0000555555555664 <+13>:	cmp    $0x6,%eax			# czyli string długości 6 znaków
   0x0000555555555667 <+16>:	jne    0x5555555556ae <phase_5+87>
   0x0000555555555669 <+18>:	mov    $0x0,%eax
   0x000055555555566e <+23>:	lea    0x1b6b(%rip),%rcx        # 0x5555555571e0 <array.3198>
   0x0000555555555675 <+30>:	movzbl (%rbx,%rax,1),%edx
   0x0000555555555679 <+34>:	and    $0xf,%edx
   0x000055555555567c <+37>:	movzbl (%rcx,%rdx,1),%edx
   0x0000555555555680 <+41>:	mov    %dl,0x9(%rsp,%rax,1)
   0x0000555555555684 <+45>:	add    $0x1,%rax
   0x0000555555555688 <+49>:	cmp    $0x6,%rax
   0x000055555555568c <+53>:	jne    0x555555555675 <phase_5+30>
   0x000055555555568e <+55>:	movb   $0x0,0xf(%rsp)
   0x0000555555555693 <+60>:	lea    0x9(%rsp),%rdi
   0x0000555555555698 <+65>:	lea    0x1b10(%rip),%rsi        # 0x5555555571af
   0x000055555555569f <+72>:	callq  0x555555555904 <strings_not_equal>
   0x00005555555556a4 <+77>:	test   %eax,%eax
   0x00005555555556a6 <+79>:	jne    0x5555555556b5 <phase_5+94>
   0x00005555555556a8 <+81>:	add    $0x10,%rsp
   0x00005555555556ac <+85>:	pop    %rbx
   0x00005555555556ad <+86>:	retq   
   0x00005555555556ae <+87>:	callq  0x555555555a10 <explode_bomb>
   0x00005555555556b3 <+92>:	jmp    0x555555555669 <phase_5+18>
   0x00005555555556b5 <+94>:	callq  0x555555555a10 <explode_bomb>
   0x00005555555556ba <+99>:	jmp    0x5555555556a8 <phase_5+81>
   
>>> x/50xc 0x5555555571e0    	    0     1        2      3       4        5       6       7
0x5555555571e0 <array.3198>:	109 'm' 97 'a'	 100 'd' 117 'u' 105 'i' 101 'e' 114 'r' 115 's'
0x5555555571e8 <array.3198+8>: 110 'n' 102 'f' 111 'o' 116 't' 118 'v' 98 'b'  121 'y' 108 'l'

and litery z 0xF - dolny nibble
np: 74->4->tab[4] -> 'i' (105=0x69)

>>> x/xs 0x5555555571af
0x5555555571af:	"devils"
litera -> index w tablicy -> ascii
d -> 2 -> 0x62 -> b
e -> 5 -> 0x65 -> e
v -> 12 -> 0x6c -> l
i -> 4 -> 0x64 -> d
l -> 15 -> 0x6F -> o
s -> 7 -> 0x67 -> g

beldog
====================================================================
Dump of assembler code for function phase_6:
=> 0x00005555555556bc <+0>:	push   %r15
   0x00005555555556be <+2>:	push   %r14
   0x00005555555556c0 <+4>:	push   %r13
   0x00005555555556c2 <+6>:	push   %r12
   0x00005555555556c4 <+8>:	push   %rbp
   0x00005555555556c5 <+9>:	push   %rbx
   0x00005555555556c6 <+10>:	sub    $0x58,%rsp
   0x00005555555556ca <+14>:	lea    0x30(%rsp),%r14			# pierwszy argument
   0x00005555555556cf <+19>:	mov    %r14,%rsi
   0x00005555555556d2 <+22>:	callq  0x555555555a36 <read_six_numbers>
   0x00005555555556d7 <+27>:	mov    %r14,%r12
   0x00005555555556da <+30>:	mov    $0x1,%r15d
   0x00005555555556e0 <+36>:	lea    0x30(%rsp),%r13			# pierwszy argument
   0x00005555555556e5 <+41>:	jmpq   0x55555555578e <phase_6+210>
   0x00005555555556ea <+46>:	callq  0x555555555a10 <explode_bomb>
   0x00005555555556ef <+51>:	jmpq   0x5555555557a0 <phase_6+228>
   0x00005555555556f4 <+56>:	mov    %rsp,%rsi
   0x00005555555556f7 <+59>:	lea    0x18(%r12),%rdi
   0x00005555555556fc <+64>:	mov    (%r12),%ecx
   0x0000555555555700 <+68>:	mov    $0x1,%eax
   0x0000555555555705 <+73>:	lea    0x3be4(%rip),%rdx        # 0x5555555592f0 <node1>
   0x000055555555570c <+80>:	cmp    $0x1,%ecx
   0x000055555555570f <+83>:	jle    0x55555555571c <phase_6+96>
   0x0000555555555711 <+85>:	mov    0x8(%rdx),%rdx
   0x0000555555555715 <+89>:	add    $0x1,%eax
   0x0000555555555718 <+92>:	cmp    %ecx,%eax
   0x000055555555571a <+94>:	jne    0x555555555711 <phase_6+85>
   0x000055555555571c <+96>:	mov    %rdx,(%rsi)
   0x000055555555571f <+99>:	add    $0x4,%r12
   0x0000555555555723 <+103>:	add    $0x8,%rsi
   0x0000555555555727 <+107>:	cmp    %r12,%rdi
   0x000055555555572a <+110>:	jne    0x5555555556fc <phase_6+64>
   0x000055555555572c <+112>:	mov    (%rsp),%rbx
   0x0000555555555730 <+116>:	mov    0x8(%rsp),%rax
   0x0000555555555735 <+121>:	mov    %rax,0x8(%rbx)
   0x0000555555555739 <+125>:	mov    0x10(%rsp),%rdx
   0x000055555555573e <+130>:	mov    %rdx,0x8(%rax)
   0x0000555555555742 <+134>:	mov    0x18(%rsp),%rax
   0x0000555555555747 <+139>:	mov    %rax,0x8(%rdx)
   0x000055555555574b <+143>:	mov    0x20(%rsp),%rdx
   0x0000555555555750 <+148>:	mov    %rdx,0x8(%rax)
   0x0000555555555754 <+152>:	mov    0x28(%rsp),%rax
   0x0000555555555759 <+157>:	mov    %rax,0x8(%rdx)
   0x000055555555575d <+161>:	movq   $0x0,0x8(%rax)
   0x0000555555555765 <+169>:	mov    $0x5,%ebp
   0x000055555555576a <+174>:	jmp    0x5555555557b8 <phase_6+252>
   0x000055555555576c <+176>:	callq  0x555555555a10 <explode_bomb>
   0x0000555555555771 <+181>:	add    $0x1,%rbx
   0x0000555555555775 <+185>:	cmp    $0x5,%ebx
   0x0000555555555778 <+188>:	jg     0x555555555786 <phase_6+202>
   0x000055555555577a <+190>:	mov    0x0(%r13,%rbx,4),%eax
   0x000055555555577f <+195>:	cmp    %eax,0x0(%rbp)
   0x0000555555555782 <+198>:	jne    0x555555555771 <phase_6+181>
   0x0000555555555784 <+200>:	jmp    0x55555555576c <phase_6+176>
   0x0000555555555786 <+202>:	add    $0x1,%r15
   0x000055555555578a <+206>:	add    $0x4,%r14
   0x000055555555578e <+210>:	mov    %r14,%rbp
   0x0000555555555791 <+213>:	mov    (%r14),%eax
   0x0000555555555794 <+216>:	sub    $0x1,%eax			
   0x0000555555555797 <+219>:	cmp    $0x5,%eax			# czy argument < 6
   0x000055555555579a <+222>:	ja     0x5555555556ea <phase_6+46>	# jak nie to wybucha
   0x00005555555557a0 <+228>:	cmp    $0x6,%r15
   0x00005555555557a4 <+232>:	je     0x5555555556f4 <phase_6+56>
   0x00005555555557aa <+238>:	mov    %r15,%rbx
   0x00005555555557ad <+241>:	jmp    0x55555555577a <phase_6+190>
   0x00005555555557af <+243>:	mov    0x8(%rbx),%rbx
   0x00005555555557b3 <+247>:	sub    $0x1,%ebp
   0x00005555555557b6 <+250>:	je     0x5555555557c9 <phase_6+269>
   0x00005555555557b8 <+252>:	mov    0x8(%rbx),%rax
   0x00005555555557bc <+256>:	mov    (%rax),%eax
   0x00005555555557be <+258>:	cmp    %eax,(%rbx)
   0x00005555555557c0 <+260>:	jge    0x5555555557af <phase_6+243>
   0x00005555555557c2 <+262>:	callq  0x555555555a10 <explode_bomb>
   0x00005555555557c7 <+267>:	jmp    0x5555555557af <phase_6+243>
   0x00005555555557c9 <+269>:	add    $0x58,%rsp
   0x00005555555557cd <+273>:	pop    %rbx
   0x00005555555557ce <+274>:	pop    %rbp
   0x00005555555557cf <+275>:	pop    %r12
   0x00005555555557d1 <+277>:	pop    %r13
   0x00005555555557d3 <+279>:	pop    %r14
   0x00005555555557d5 <+281>:	pop    %r15
   0x00005555555557d7 <+283>:	retq   

jakaś struktura
>>> x/20xw 0x5555555592f0
0x5555555592f0 <node1>:	0x00000163	0x00000001	0x55559300	0x00005555
0x555555559300 <node2>:	0x000002cd	0x00000002	0x55559310	0x00005555
0x555555559310 <node3>:	0x00000123	0x00000003	0x55559320	0x00005555
0x555555559320 <node4>:	0x000001d6	0x00000004	0x55559330	0x00005555
0x555555559330 <node5>:	0x00000036	0x00000005	0x555591f0	0x00005555

>>> x/3xw 0x5555555591f0
0x5555555591f0 <node6>:	0x0000035e	0x00000006	0x00000000

node: wartość, numer, adres następnego node

Nie mogą sie powtarzać liczby i mają < 6
break *0x0000555555555794 - wejdzie tyle razy ile liczb
Czyli jakaś permutacja 6 liczb [1,..6]
Pierwsze sprawdzenie czyli
6 -> 2 -> 4 -> 1 -> 3 -> 5 - zadziałało w kolejności malejących wartości
====================================================================
secret phase jest wołany w phase defused

Dump of assembler code for function phase_defused:
=> 0x0000555555555bbb <+0>:	cmpl   $0x6,0x37be(%rip)        # 0x555555559380 <num_input_strings>
   0x0000555555555bc2 <+7>:	je     0x555555555bc5 <phase_defused+10>
   0x0000555555555bc4 <+9>:	retq   
   0x0000555555555bc5 <+10>:	sub    $0x68,%rsp
   0x0000555555555bc9 <+14>:	lea    0x8(%rsp),%rcx
   0x0000555555555bce <+19>:	lea    0xc(%rsp),%rdx
   0x0000555555555bd3 <+24>:	lea    0x10(%rsp),%r8
   0x0000555555555bd8 <+29>:	lea    0x176a(%rip),%rsi        # 0x555555557349
   0x0000555555555bdf <+36>:	lea    0x3cca(%rip),%rdi        # 0x5555555598b0 <input_strings+240>
   0x0000555555555be6 <+43>:	mov    $0x0,%eax
   0x0000555555555beb <+48>:	callq  0x555555555130 <__isoc99_sscanf@plt>
   0x0000555555555bf0 <+53>:	cmp    $0x3,%eax			# eax = 3
   0x0000555555555bf3 <+56>:	je     0x555555555c06 <phase_defused+75>
   0x0000555555555bf5 <+58>:	lea    0x168c(%rip),%rdi        # 0x555555557288
   0x0000555555555bfc <+65>:	callq  0x555555555060 <puts@plt>
   0x0000555555555c01 <+70>:	add    $0x68,%rsp
   0x0000555555555c05 <+74>:	retq   
   0x0000555555555c06 <+75>:	lea    0x10(%rsp),%rdi
   0x0000555555555c0b <+80>:	lea    0x1740(%rip),%rsi        # 0x555555557352
   0x0000555555555c12 <+87>:	callq  0x555555555904 <strings_not_equal>
   0x0000555555555c17 <+92>:	test   %eax,%eax
   0x0000555555555c19 <+94>:	jne    0x555555555bf5 <phase_defused+58>
   0x0000555555555c1b <+96>:	lea    0x1606(%rip),%rdi        # 0x555555557228
   0x0000555555555c22 <+103>:	callq  0x555555555060 <puts@plt>
   0x0000555555555c27 <+108>:	lea    0x1622(%rip),%rdi        # 0x555555557250
   0x0000555555555c2e <+115>:	callq  0x555555555060 <puts@plt>
   0x0000555555555c33 <+120>:	mov    $0x0,%eax
   0x0000555555555c38 <+125>:	callq  0x555555555815 <secret_phase>
   0x0000555555555c3d <+130>:	jmp    0x555555555bf5 <phase_defused+58>

x/xw 0x555555559380
0x555555559380 <num_input_strings>:	0x00000006

x/xs 0x555555557349
0x555555557349:	"%d %d %s"

x/xs 0x5555555598b0
0x5555555598b0 <input_strings+240>:	"1 0"
czyli to jest rdi do scanf i on ma mieć 3 elementy a my dajemy dwa "1 0" (argumenty 4 zadania), brakuje stringa

tu siedzi ten potrzebny string
x/xs 0x555555557352
0x555555557352:	"DrEvil"

dodajemy DrEvil do psol.txt po "1 0 DrEvil"
i jesteśmy w secret_phase

Dump of assembler code for function secret_phase:
   0x0000555555555815 <+0>:	push   %rbx
   0x0000555555555816 <+1>:	callq  0x555555555a77 <read_line>
=> 0x000055555555581b <+6>:	mov    $0xa,%edx		# rdx = 10
   0x0000555555555820 <+11>:	mov    $0x0,%esi		# rsi = 0
   0x0000555555555825 <+16>:	mov    %rax,%rdi		# rdi - tekst
   0x0000555555555828 <+19>:	callq  0x555555555110 <strtol@plt>
   0x000055555555582d <+24>:	mov    %rax,%rbx		# long
   0x0000555555555830 <+27>:	lea    -0x1(%rax),%eax		
   0x0000555555555833 <+30>:	cmp    $0x3e8,%eax		# eax < 1000
   0x0000555555555838 <+35>:	ja     0x555555555860 <secret_phase+75>
   0x000055555555583a <+37>:	mov    %ebx,%esi		 # wejście
   0x000055555555583c <+39>:	lea    0x39cd(%rip),%rdi        # 0x555555559210 <n1> # adres korzenia
   0x0000555555555843 <+46>:	callq  0x5555555557d8 <fun7>	 
   0x0000555555555848 <+51>:	cmp    $0x3,%eax		 # == 3
   0x000055555555584b <+54>:	jne    0x555555555867 <secret_phase+82>
   0x000055555555584d <+56>:	lea    0x192c(%rip),%rdi        # 0x555555557180
   0x0000555555555854 <+63>:	callq  0x555555555060 <puts@plt>
   0x0000555555555859 <+68>:	callq  0x555555555bbb <phase_defused>
   0x000055555555585e <+73>:	pop    %rbx
   0x000055555555585f <+74>:	retq   
   0x0000555555555860 <+75>:	callq  0x555555555a10 <explode_bomb>
   0x0000555555555865 <+80>:	jmp    0x55555555583a <secret_phase+37>
   0x0000555555555867 <+82>:	callq  0x555555555a10 <explode_bomb>
   0x000055555555586c <+87>:	jmp    0x55555555584d <secret_phase+56>

x/xw 0x555555559210
0x555555559210 <n1>:	0x00000024 - to jest node

fun7 przyjmuje dwa parametry (24, input)
jak zrobić input by wyjście było == 3
30 -> 0x00000000fffffff6 -10
10 -> 0x00000000fffffff2 -14
1 -> 0
2 -> 0x00000000fffffff8 - -8
3 -> 0x00000000fffffff8 - -8
4 -> 0x00000000fffffff8 - -8
5 -> 0x00000000fffffff8 - -8
6 -> 0

break *0x0000555555555848

>>> x/64xg 0x555555559210-288
0x5555555590f0 <n45>:	0x0000000000000028	0x0000000000000000
0x555555559100 <n45+16>:	0x0000000000000000	0x0000000000000000
0x555555559110 <n41>:	0x0000000000000001	0x0000000000000000
0x555555559120 <n41+16>:	0x0000000000000000	0x0000000000000000
0x555555559130 <n47>:	0x0000000000000063	0x0000000000000000
0x555555559140 <n47+16>:	0x0000000000000000	0x0000000000000000
0x555555559150 <n44>:	0x0000000000000023	0x0000000000000000
0x555555559160 <n44+16>:	0x0000000000000000	0x0000000000000000
0x555555559170 <n42>:	0x0000000000000007	0x0000000000000000
0x555555559180 <n42+16>:	0x0000000000000000	0x0000000000000000
0x555555559190 <n43>:	0x0000000000000014	0x0000000000000000
0x5555555591a0 <n43+16>:	0x0000000000000000	0x0000000000000000
0x5555555591b0 <n46>:	0x000000000000002f	0x0000000000000000
0x5555555591c0 <n46+16>:	0x0000000000000000	0x0000000000000000
0x5555555591d0 <n48>:	0x00000000000003e9	0x0000000000000000
0x5555555591e0 <n48+16>:	0x0000000000000000	0x0000000000000000
0x5555555591f0 <node6>:	0x000000060000035e	0x0000555555559300
0x555555559200 <bomb_id>:	0x0000000001a14e3f	0x0000000000000000
0x555555559210 <n1>:	0x0000000000000024	0x0000555555559230
0x555555559220 <n1+16>:	0x0000555555559250	0x0000000000000000
0x555555559230 <n21>:	0x0000000000000008	0x00005555555592b0
0x555555559240 <n21+16>:	0x0000555555559270	0x0000000000000000
0x555555559250 <n22>:	0x0000000000000032	0x0000555555559290
0x555555559260 <n22+16>:	0x00005555555592d0	0x0000000000000000
0x555555559270 <n32>:	0x0000000000000016	0x0000555555559190
0x555555559280 <n32+16>:	0x0000555555559150	0x0000000000000000
0x555555559290 <n33>:	0x000000000000002d	0x00005555555590f0
0x5555555592a0 <n33+16>:	0x00005555555591b0	0x0000000000000000
0x5555555592b0 <n31>:	0x0000000000000006	0x0000555555559110
0x5555555592c0 <n31+16>:	0x0000555555559170	0x0000000000000000
0x5555555592d0 <n34>:	0x000000000000006b	0x0000555555559130
0x5555555592e0 <n34+16>:	0x00005555555591d0	0x0000000000000000

każda komórka to - wygląda na drzewo binarne (etykiety to sugerują)
wartość | adres | adres | null (padding)
	   left    right

Przybliżony wygląd
					n1 (0x24)
		n21 (0x8)     						n22 (0x32)
 	n31 (0x6)         n32 (0x16)			n33(0x2d)  		   n34(0x6b)
 n41(0x1)   n42(0x7)  n43(0x14)   n44(0x23)	  n45(0x28)   n46(0x2f)     n47 (0x63)   n48 (0x3e9)
 
 Zajrzymy do fun7
 >>> disass fun7 
 %rdi -adres korzenia %rsi - input
Dump of assembler code for function fun7:
   0x00005555555557d8 <+0>:	test   %rdi,%rdi
   0x00005555555557db <+3>:	je     0x55555555580f <fun7+55>		# NULL -> -1
   0x00005555555557dd <+5>:	sub    $0x8,%rsp
   0x00005555555557e1 <+9>:	mov    (%rdi),%edx				# rdx - wartość node
   0x00005555555557e3 <+11>:	cmp    %esi,%edx				# wartość - input
   0x00005555555557e5 <+13>:	jg     0x5555555557f3 <fun7+27>		# wartość > input
   0x00005555555557e7 <+15>:	mov    $0x0,%eax				# result == 0
   0x00005555555557ec <+20>:	jne    0x555555555800 <fun7+40>		
   0x00005555555557ee <+22>:	add    $0x8,%rsp
   0x00005555555557f2 <+26>:	retq   
   0x00005555555557f3 <+27>:	mov    0x8(%rdi),%rdi				# ładujemy lewy adres do rdi
   0x00005555555557f7 <+31>:	callq  0x5555555557d8 <fun7>			# wołamy na dziecku
   0x00005555555557fc <+36>:	add    %eax,%eax				# result = 2 * wynik
   0x00005555555557fe <+38>:	jmp    0x5555555557ee <fun7+22>
   0x0000555555555800 <+40>:	mov    0x10(%rdi),%rdi				# ładujemy prawe
   0x0000555555555804 <+44>:	callq  0x5555555557d8 <fun7>			
   0x0000555555555809 <+49>:	lea    0x1(%rax,%rax,1),%eax			# 2 * wynik + 1 poddziecka
   0x000055555555580d <+53>:	jmp    0x5555555557ee <fun7+22>
   0x000055555555580f <+55>:	mov    $0xffffffff,%eax
   0x0000555555555814 <+60>:	retq   

Czyli jakoś tak 
fun7(node* n, int input)
{
	if(n == NULL)
		return - 1
	if(n->value < input)
	{
		result = 2 * fun7(n->left, input)
	}
	else
	{
		if(result == 0)
			return result;
		result = 2 * fun7(n->left, input)
	}
	return result;
}

czyli jeśli znajdziemy value to result == 0
co pokrywa się z tym że znajdywało dla 1 i 6

czyli chcemy result = 3
czyli n47 (0x63) bo wtedy mamy
n47 (result = 0) 
-> n34 (2 * result = 0)
-> n22 (2 * result + 1 = 1)
-> n1 (2 * result + 1 = 3)

0x63 = 99
