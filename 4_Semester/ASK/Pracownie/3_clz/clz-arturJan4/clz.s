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
        .globl  clz
        .type   clz, @function

/*
 * W moim rozwiązaniu używam następującej techniki: dziel i zwyciężaj dla popcount
 * oraz uzupełniania jedynkami
 */

/*
=========Pomysł==========
Posłużę się rozwiązaniem zad2 z listy 1, gdzie należało w O(logn) policzyć popcount.
Konkretniej wskazywanym na ćwiczeniach krótszym rozwiązaniem z: https://en.wikipedia.org/wiki/Hamming_weight

"Rozsmarowujemy" pierwszą napotkaną jedynkę idąc od lewej strony na bity po prawej.
Potem wykorzystujemy popcount do policzenia pozycji tej jedynki. 

=========================
np:
0000 0000 0101 1011 
0000 0000 0111 1111

Wtedy mamy:
liczba zapalonych bitów - p (7)
długośc słowa - n (16)
liczba wiodących zer - (n - p) (9)

=========================
Jak "rozsmarować" tę jedynkę?
- przy pomocy przesunięć 
t = t | t >> 1
t = t | t >> 2
t = t | t >> 4
t = t | t >> 8
t = t | t >> 16
t = t | t >> 32
W najgorszym przypadku '1' bedzie wędrować z 64 bitu do 64 -> 63 -> 61 -> 57 -> 49 -> 33 -> 1 do 1 bitu.
*/

# TODO: można lepsze IPC wycisnąć z tego
clz:
        movq     %rdi, %rax
        shr      $1,   %rax
        orq      %rax, %rdi

        movq     %rdi, %rax
        shr      $2,   %rax
        orq      %rax, %rdi

        movq     %rdi, %rax
        shr      $4,   %rax
        orq      %rax, %rdi

        movq     %rdi, %rax
        shr      $8,   %rax
        orq      %rax, %rdi

        movq     %rdi, %rax
        shr      $16,  %rax
        orq      %rax, %rdi

        movq     %rdi, %rax
        shr      $32,  %rax
        orq      %rax, %rdi

        movq     $0x5555555555555555, %rsi
        movq     %rdi, %rcx
        shr      $1  , %rcx
        andq     %rsi, %rcx
        subq     %rcx, %rdi

        movq     $0x3333333333333333, %rsi
        movq     %rdi, %rcx
        shr      $2  , %rcx
        andq     %rsi, %rcx
        andq     %rsi, %rdi
        addq     %rcx, %rdi

        movq     $0x0F0F0F0F0F0F0F0F, %rsi
        movq     %rdi, %rcx
        shr      $4  , %rcx
        addq     %rcx, %rdi
        andq     %rsi, %rdi

        movq     %rdi, %rcx
        shr      $8  , %rcx
        addq     %rcx, %rdi

        movq     %rdi, %rcx
        shr      $16 , %rcx
        addq     %rcx, %rdi  

        movq     %rdi, %rcx
        shr      $32 , %rcx
        addq     %rcx, %rdi  

        movq     $64, %rax
        subq     %rdi, %rax
        andq     $0x7F, %rax
        
        ret

        .size   clz, .-clz
