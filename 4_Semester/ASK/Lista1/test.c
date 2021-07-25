#include <stdio.h>
#include <stdint.h>

int main (int argc, char *argv[]) {
    uint32_t x;

    x = 4;

    // x dla 0
    // x & (x - 1) == 0 tylko dla x = 2^y
    printf("%d\n", x && !(x & (x - 1))); // zwraca 1 gdy x jest potęgą 2

    // np: 8
    // x    = 1000
    // x-1  = 0111
    // np: 9
    // x    = 1011
    // x-1  = 1000
    // & na MSB

    return 0;
}