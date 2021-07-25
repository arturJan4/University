/*
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>

union elem {
    struct {
        long *p;
        long y;
    } e1;
    
    struct {
        long x;
        union elem *next;
    } e2;
};

struct test{
    short a[120];
};

int main() {
    printf("%zu\n", alignof(union elem));
    printf("%ld\n", sizeof(union elem));
    printf("%ld\n", sizeof(struct test));
    return 0;
}
