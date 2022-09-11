/*
 * UWAGA! W poniższym kodzie należy zawrzeć krótki opis metody rozwiązania
 *        zadania. Będzie on czytany przez sprawdzającego. Przed przystąpieniem
 *        do rozwiązywania zapoznaj się dokładnie z jego treścią. Poniżej należy
 *        wypełnić oświadczenie o samodzielnym wykonaniu zadania.
 *
 * Oświadczam, że zapoznałem(-am) się z regulaminem prowadzenia zajęć
 * i jestem świadomy(-a) konsekwencji niestosowania się do podanych tam zasad.
 *
 * Imię i nazwisko, numer indeksu: Artur Jankowski, 317928
 */

        .text
        .globl  addsb
        .type   addsb, @function

/*
 * W moim rozwiązaniu używam następującej techniki: wielu masek bitowych
 */
/*
=========Pomysł:==========
z listy 2 zad 4 - zapobieganie przeniesieniu przy dodowaniu upakowanych liczb
Będziemy korzystać z dwóch masek:
0x8080808080808080 - same bity znaku
0x7F7F7F7F7F7F7F7F - reszta bitów

(x & 7F7F..) + (y & 7F7F..) - add

==========================
"Flagi" z wartością logiczną na pierwszym bicie słowa (reszta zera):
(x & y)  & 8080..  - negative (wiodąca jedynka jeśli x < 0 i y < 0)
~(x | y) & 8080..  - positive
(x ^ y)  & 8080..  - different_signs
(add  & positive)  - pos_overflow (dodanie dwóch dodatnich daje ujemną)
(~add & negative)  - neg_overflow (dodanie dwóch liczb ujemnych daje dodatnią - niedomiar)
(neg_overflow | pos_overflow) - overflow (występuje nasycenie)

==========================
Budowa masek:
~((overflow) << 1 - (overflow >> 7)) - zero_on_overflow_bits_mask
tam gdzie wystąpi nasycenie będziemy mieli same zera (zanegowane jedynki), a tam gdzie nie ma przepełnienia będzie róznica 0 - 0, czyli tam będą jedynki

(pos_overflow) - ((pos_overflow) >> 7)) - pos_overflow_mask
daje 0b01111111 jeśli wystąpił nadmiar
w.p.p 0b00000000

neg_overflow == neg_overflow_mask
to już jest prawidłowa maska (tj. 0b10000000)
==========================
Niech 
(ok_val) - wartość sumy która nie przekroczy zakresu
(sat_up) - wartość która osiągnie górną granicę (127)
(sat_dn) - wartośc która osiągnie dolną granice (-128)

(ok_val)(sat_up)(sat_up)(sat_dn)(ok_val)
(1....1)(0....0)(0....0)(0....0)(1....1) - zero_on_overflow_bits_mask

Teraż żeby na ok_val stała wartość sumy robimy AND maski z wartością
OR z możliwymi maskami nadmiaru lub niedomiaru
a potem naprawiamy pierwszy znak dodawania

(ok_val)(sat_up)(sat_up)(sat_dn)(ok_val)
(1....1)(0....0)(0....0)(0....0)(1....1) - zero_on_overflow_bits_mask
(ok_val)(0....0)(0....0)(0....0)(ok_val) - & (add ^ different_signs)
(ok_val)(01...1)(01...1)(1....1)(ok_val) - | (pos_overflow_mask | neg_overflow_mask)
*/
addsb:
        movq     %rdi, %rax                  # x
        movq     %rsi, %rcx                  # y

        movq     $0x7F7F7F7F7F7F7F7F, %r8   
        andq     %r8, %rax
        andq     %r8, %rcx
        addq     %rcx, %rax                  # rax - add

        movq     $0x8080808080808080, %r8    
        movq     %rdi, %rcx
        orq      %rsi, %rcx                  # x | y
        not      %rcx
        andq     %r8,  %rcx                  # positive
        andq     %rax, %rcx                  # rcx - pos_overflow     
        movq     %rcx, %r11                  # r11 - pos_overflow
        movq     %rcx, %r9
        shr      $7, %r9
        subq     %r9, %rcx                   # rcx - pos_overflow_mask

        movq     %rdi, %rdx
        andq     %rsi, %rdx                  # x & y
        andq     %r8,  %rdx
        movq     %rax, %r10
        not      %r10
        andq     %r10, %rdx                  # rdx - neg_overflow == neg_overflow_mask

        orq      %rdx, %r11                  # - overflow
        movq     %r11, %r10          
        shr      $7, %r10
        shl      %r11
        subq     %r10, %r11                 
        not      %r11                        # r11 - zero_on_overflow_bits_mask

        orq      %rcx, %rdx
        andq     %r11, %rax
        orq      %rdx, %rax

        xorq     %rsi, %rdi                  # x ^ y
        andq     %r8,  %rdi
        xorq     %rdi, %rax                  # fix signs

        ret
        .size   addsb, .-addsb
