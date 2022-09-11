#include <stddef.h>
#include <stdint.h>
    
int puzzle(long x, unsigned n)
{
    int result = 0;             // eax
    for(int i = 0; i != n; ++i) // i == edx
    {
        result += (x & 0x1);
        x >>= 0x1 ;
    }
    return result;
}