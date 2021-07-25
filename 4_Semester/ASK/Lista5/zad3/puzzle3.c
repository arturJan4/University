#include <stddef.h>
#include <stdint.h>
    
uint32_t puzzle3(uint32_t n, uint32_t d)
{
    int64_t n_reg = n;
    const int64_t d_shift = (int64_t)d << 32;
    uint32_t result = 0;
    
    for(uint32_t mask = 0x80000000; mask != 0; mask >>= 1)
    {
        n_reg <<= 1;
        int64_t r = n_reg - d_shift;
        if(r >= 0)
        {
            result |= mask;
            n_reg = r;
        }
    }
    return result;
}