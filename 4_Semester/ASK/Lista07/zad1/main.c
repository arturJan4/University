/*
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>

#define A 9
#define B 5

typedef struct {
    int x[A][B];
    long y;
} str1;


int main() {
    printf("%zu", alignof(str1));
    return 0;
}
