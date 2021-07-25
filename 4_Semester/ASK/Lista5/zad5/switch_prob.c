#include <stddef.h>
#include <stdint.h>
    
long switch_prob(long x, long n)
{
    switch(n)
    {
        case 60:
        case 61:
            return 8 * x;
        case 64:
            return x >> 3;
        case 62:
            x = 15 * x; 
        case 65:
            x = x * x;
        default:
            return x + 0x4b;
    }
}