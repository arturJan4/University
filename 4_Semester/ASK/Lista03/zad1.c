#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>

// divides by 3, round to zero
int32_t div3(int32_t n)
{
    int64_t temp = n;
    int64_t magic = 0x55555556; // (2^32 + 2)/3

    int64_t part1 = temp * magic;
    printf("part1: %ld\n", part1);    
    
    return (int32_t)((part1 >> 32) + ((n >> 31) & 0x1));
    //return (int32_t)(((temp * magic) >> 32) + ((n >> 31) & 0x1)); 
}


int32_t div3_wrong(int32_t n)
{
    int64_t temp = n;
    int64_t magic = 0x55555555; // (2^3)/3

    int64_t part1 = temp * magic;
    printf("part1: %ld\n", part1);
    return (int32_t)((part1 >> 32) + ((n >> 31) & 0x1));
    //return (int32_t)(((temp * magic) >> 32) + ((n >> 31) & 0x1)); 
}

int main() {
    int counter = 0;
    double div = 3.0;
    /*    
    for (int x = INT32_MIN; ; x++) {
        int32_t result = (int32_t)(x/div);
        if(result != div3(x))
        {
            counter++;
        }
        if (x == INT32_MAX) break;
    }
    
    printf("%d", counter);
    */

    //int32_t x = 5;
    //printf("%d", div3(x));
    int32_t number = 3;
    printf("%d\n", div3(number));
    printf("%d\n", div3_wrong(number));
    return 0;
}