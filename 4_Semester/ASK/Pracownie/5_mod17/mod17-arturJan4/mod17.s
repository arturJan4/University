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
        
        .data
        even_mask:    .quad 0x0F0F0F0F0F0F0F0F
        first_const:  .byte 0x88  # 136
        second_const: .byte 0x11  # 17
        .text
        .globl  mod17
        .type   mod17, @function

/*
Zadanie robiłem zgodnie ze wskazówką. Znalazłem sumę parzystych półsłów i odjąłem sumę tych na nieparzystych pozycjach. 
A gdy taka suma dalej jest większa od 17 to powtarzamy algorytm.
Problematyczne były ujemne wyniki sumy co rozwiązałem dodając najmniejszą możliwą wielokrotność 17 jeśli wynik odejmowania był ujemny (zapalała się flaga).

64 bity -> 16 hex, półbajtów
sumowanie parzystych:
0A0B0C0D0E0F0G0H

>> 8 bitów
 0A0B0C0D0E0F0G0H
+000A0B0C0D0E0F0G
 ----------------
 00FF00FF00FF00FF
 A+B C+D E+F G+H

>> 16 bitów
 00AA00BB00CC00DD
+000000AA00BB00CC
 ----------------
 00000FFF00000FFF

>> 32 bitów
W trakcie dodawania na niektórych miejscach generują sie śmieci ale luki są wystarczająco duże by pominąć maskowanie
a na koniec wynik jest na ostatnim bajcie
suma podobnie i dostajemy A + B + C + D + E + F + G + H na dolnym bajcie (max to 8 * 15 = 120)
*/

mod17:
        xorl    %eax, %eax                  # result = 0

        movq    even_mask, %r8              # parzyste w r8
        andq    %rdi, %r8                   
        
        shr     $4, %rdi                        
        andq    even_mask, %rdi             # nieparzyste w rdi
        
        movq    %r8, %rcx                   # dodowanie półbajtów przy pomocy dziel i zwyciężaj
        shrq    $8,  %r8
        addq    %r8, %rcx

        movq    %rcx, %r8
        shrq    $16,  %r8
        addq    %rcx, %r8

        movq    %r8,  %rcx
        shrq    $32,  %r8
        addb    %r8b, %cl                   # suma parzystych półbajtów 

        movq    %rdi, %rdx
        shrq    $8,   %rdx
        addq    %rdi, %rdx

        movq    %rdx, %rdi
        shrq    $16,  %rdx
        addq    %rdx, %rdi

        movq    %rdi, %rdx
        shrq    $32, %rdx
        addb    %dil, %dl                   # suma nieparzystych półbajtów

        xorl    %r9d, %r9d
        subb    %dl, %cl                    # parzyste - nieparzyste z zakresu [-120, 120] więc mieści się na bajcie i oszczędzamy instrukcje
                                            # nie chcę martwić się ujemnymi wynikami więc
        cmovs   first_const, %r9w           # if suma < 0 -> suma += 136 (najmniejsza wielokrotność 17 która da dodatnią sumę) [16, 120]
        addb    %r9b, %cl                   # 0xBA

        movb    %cl,  %r11b
        shrb    $4,   %r11b                 # 0x0B
        
        movb    $0x0F, %r10b      
        andb    %r10b, %cl                  # 0x0A
        subb    %r11b, %cl                  # (A - B) -> z zakresu [-15, 15]
        cmovs   second_const, %ax           # if suma < 0 -> suma += 17 [0, 16]

        addb    %cl, %al
        ret
        .size   mod17, .-mod17
