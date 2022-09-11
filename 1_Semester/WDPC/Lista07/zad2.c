#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// calculates maximum memory blocks possible to allocate using malloc
bool memAlloc(size_t memSize)
{
    void *p = malloc(memSize);
    if(p == NULL)
    {
        return false;
    }
    else
    {
        free(p);
        return true;
    }
}

size_t maxMallocSize()
{
    size_t right = SIZE_MAX;
    size_t left = 1;

    size_t mid;
    while(left <= right)// 3 3
    {
        mid = left + ((right - left) / 2); // to avoid overflow
        if(memAlloc(mid))
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left-1;
}

int main()
{
    // kilo - 1024
    const size_t  bytesInMB = 1048576;

    size_t wynik = maxMallocSize();

    printf("in  B: %zu\n", wynik);
    printf("in KB: %zu\n", wynik /1024);
    printf("in MB: %zu\n", wynik/bytesInMB);

    return 0;
}
