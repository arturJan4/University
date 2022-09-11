#include <stdio.h>
#include <stdint.h>

int main (int argc, char *argv[]) {
    int32_t x;

    x = 18;

    printf("%d\n", x - (x >> 2) - ((x | x >> 1) & 1)); // zwraca 1 gdy x jest potęgą 2
    printf("%d", (3 * x)/4);

    return 0;
}