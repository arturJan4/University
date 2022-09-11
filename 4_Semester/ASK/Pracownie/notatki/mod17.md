mamy po 8 nibbli
każdy ma max 15 więc wynik z zakresu [-120, 120]
Dodajemy najmniejszą wielokrotność 17 tak by wskoczyło na dodatnie -> 17 * 8 = 136 -> [16, 256]
Mamy teraz 0xABC, robimy f = (A + C) - B i to jest zakresu [-15, 15]
jeśli f < 0 to można cmovem dodać 17

rax​, ​%rcx​, ​%rdx​, ​%rdi​, ​%rsi​, ​%rsp​, and ​%r8-r11

64 bity -> 16 hex
sumowanie parzystych:
0A0B0C0D0E0F0G0H

0A0B0C0D0E0F0G0H
>> 8 bitów
0A0B0C0D0E0F0G0H
000A0B0C0D0E0F0G
00FF00FF00FF00FF
 A+B C+D E+F G+H

>> 16 bitów
00AA00BB00CC00DD
000000AA00BB00CC
00000FFF00000FFF

>> 32 bitów
suma

sumowanie nieparzystych:
A0B0C0D0E0F0G0H0 >> 4
0A0B0C0D0E0F0G0H

>> 8 bitów
0A0B0C0D0E0F0G0H
000A0B0C0D0E0F0G
00FF00FF00FF00FF
 A+B C+D E+F G+H

>> 16 bitów

>> 32 bitów

suma - suma + 136

0xABC
x = C - B + A
-15 <= x <= 15

if x < 0:
    x += 17

41 instrukcji
3.86 IPC
10.63 CPI

        TODO:
                - sufiksy i rozmiary rejestrów (to może pomóc z ilością instrukcji)
                - .data
                - cmov -> opt
                - optymalizacja wykorzystanych rejestrów
                - wykorzystwać jeden rejestr?
        Pomysły:
                - najpierw parzyste -> nieparzyste -> oszczędzamy andowanie
                - zmieścić wyniki pośrednie "w lukach"
