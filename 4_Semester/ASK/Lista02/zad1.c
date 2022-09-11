#include <stdio.h>
#include <stdint.h>

int main() {
    int32_t x = -2;
    int32_t y = 3;

    int test = x * ~y + (uint32_t)y * (uint32_t)x == -x;
    for(int8_t x = INT8_MIN; x < INT8_MAX; ++x)
    {
        for(int8_t y = INT8_MIN; y < INT8_MAX; ++y)
        {
            int test = x * ~y + (uint32_t)y * (uint32_t)x == -x;
            if(!test)
            {
                printf("%d", test);
            }
        }
    }
    return 0;
}