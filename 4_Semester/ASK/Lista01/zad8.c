#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

void secret(uint8_t *to, uint8_t *from, size_t count) {
    size_t n = (count + 7) / 8;
    static void *labels[] = {&&l0, &&l1, &&l2, &&l3, &&l4, &&l5, &&l6, &&l7};
    
    goto *labels[count % 8];
    
    l0: *to++ = *from++;
    l7: *to++ = *from++;
    l6: *to++ = *from++;
    l5: *to++ = *from++;
    l4: *to++ = *from++;
    l3: *to++ = *from++;
    l2: *to++ = *from++;
    l1: *to++ = *from++;
    
    if (--n > 0) goto l0;
}

int main()
{
    uint8_t a[3] = {1,2,3};
    uint8_t b[3] = {42,42,42};
    secret(b + 1, a, 2);
    
    printf("%d %d %d", b[0], b[1], b[2]);

    return 0;
}