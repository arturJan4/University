/*
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>

#define CNT 7

typedef struct A {
    long idx;
    long x[4];
} a_struct;

typedef struct {
    int first;
    a_struct a[CNT];
    int last;
} b_struct;

void test(long i, b_struct *bp) {
    int n = bp->first + bp->last;
    a_struct *ap = &bp->a[i];
    ap->x[ap->idx] = n;
}


int main() {
    printf("%zu\n", alignof(a_struct));
    printf("%ld\n", sizeof(a_struct));

    return 0;
}
