
# nie zrobione - brakło czasu

jeśli na wejściu jest liczba zdenormalizowana to wynikiem jest 0
iloczyn dwóch liczb normalnych da MSB mantysy na jednej z dwóch pozycjii
najpierw sprawdzimy tę mniej znaczącą

72 bity wyniku

1.11111 × 1.11111
= 011. 11100 00001

011.1110000001 × 1.11111
= 0111. 10100 00101 11111

1.00000 × 1.00000
= 1. 00000 00000

10000000000 × 100000
= 1. 00000 00000 00000

Czyli po poniesieniu do 3 bit wiodący mantysy może być w jednym z trzech miejsc
m_msb = pozycja tej 1 względem kropki (0, 1, 2)
chcemy zrobić result << m_msb
