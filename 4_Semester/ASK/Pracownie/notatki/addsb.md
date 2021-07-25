(x & 7F7F) + (y & 7F7F) - addo
(x & y) & 8080 - negative
~(x | y) - positive
(~(addo) & negative) - neg_overflow
(addo & positive) & 8080 - pos_overflow
neg_overflow | pos_overflow - overflow
(~((x & y) | positive) & 8080) - different_signs
(pos_overflow) - ((pos_overflow) >> 7)) - pos_overflow_mask
~((overflow << 1) - (overflow >> 7)) - zero_on_overflow_bits

Można używać łatwo:


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

ver1
CPI: 9.36
IPC: 3.85

ver2
CPI: 9.1
IPC: 3.85

