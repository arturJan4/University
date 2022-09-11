#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t x;
    uint32_t y;

    x = 29;
    y = 3;

    // x * (2^y) = 232
    printf("%d\n", x << y);

    // floor(x/2^y) = 3
    printf("%d\n", x >> y);

    // x mod 2^y = 5 (24 + 5)
    printf("%d\n", x & ((1 << y) - 1));
    // todo: przykład

    // ceil(x/2^y) = 4
    printf("%d\n", (x + (1 << y) - 1) >> y);
}