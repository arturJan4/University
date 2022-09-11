#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>

int compare(float f, float g)
{
    uint32_t x = f;
    uint32_t y = g;

return ((x >> 31) & (y >> 31) == 0 & (x != (1 << 31) & y != 0)) 
       | (((x-y) >> 31) & ((x >> 31) == (y >> 31)));
}

int main() {
    
    printf("%d", compare(3, 2));
    
 
    return 0;
}