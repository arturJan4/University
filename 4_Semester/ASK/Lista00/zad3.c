#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t x;
    uint32_t k;

    x = 19;
    k = 1;

    // x=10011
    // k=00010

    // 1 << k
    // 000..010..000
    //       k 
    
    // wyzeruj k-ty
    printf("%d\n", x & ~(1 << k));

    // ustal k-ty
    printf("%d\n", x | ( 1 << k));

    // zaneguj k-ty
    printf("%d\n", x ^ (1 << k));
    return 0;
}