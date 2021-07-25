#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int compare(float f, float g)
{
    uint32_t x = *((int*)&f);
    uint32_t y = *((int*)&g);
    return (((x & ~y) >> 31) & ((x | y) != 0x80000000)) 
           | (((x-y) & ~(x | y)) >> 31)
           | (((y-x) & x & y) >> 31);
}

/*
return ((x >> 31) == 1 & (y >> 31) == 0 & (x != 0x80000000 & y != 0)) 
        | (((x-y) & 0x80000000) & (x ^ y >> 31));
*/

int main (int argc, char *argv[]) {
    float x = 3;
    float y = 5;
    printf("%d\n", compare(x, y));
    x = -25;
    y = 250;
    printf("%d\n", compare(x, y));
    
    for(float i = -1000.0; i < 1000.0; ++i)
    {
        for(float j = -1000.0; j < 1000.0; ++j)
        {
            float k = i;
            float l = j;
            if(compare(k,l) != (i < j))
            {
                printf("error: %f \t %f\n", i, j);
            }
        }
    }
    
    return 0;
}