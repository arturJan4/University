#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t x; // little-endian (32b = 4B)
    uint32_t byte0, byte1, byte2, byte3; // podzielone na 4 bajty

    x = 0x456789ab;
    printf("%x\n", x);

    byte3 = x << 24;
    byte2 = (x & 0x0000ff00) << 8;
    byte1 = (x & 0x00ff0000) >> 8;
    byte0 = x >> 24;
    x = (byte3 | byte2 | byte1 | byte0); // big-endian

    printf("%x\n", x);

    /*
    byte3 = (x & 0x000000ff) << 24;
    byte2 = (x & 0x0000ff00) << 8;
    byte1 = (x & 0x00ff0000) >> 8;
    byte0 = (x & 0xff000000) >> 24;
    */
}