#include <stdio.h>
#include <stdint.h>
#include <stdalign.h>

struct test {
    char a;
    char b;
    char c;
};

struct C {
    char a;
};

typedef struct A {
    int8_t a; // 1B
    int32_t b; // 4B
    int8_t c; // 1B
    int16_t d; // 2B    a---bbbbc-dd czyli 12B
} A;

struct betterA {
    void *b; // 4B
    int16_t d; // 2B
    int8_t a; // 1B
    int8_t c; // 1B    bbbbddac czyli 8B
};

struct B {
    uint16_t a; // 2B
    double b; // 8B
    uint32_t c; // 4B    aa------bbbbbbbbcccc---- czyli 24B
};

typedef struct betterB {
    double b; // 8B
    uint32_t c; // 4B
    uint16_t a; // 2B    bbbbbbbbccccaa-- czyli 16B
} By;

int main() {
    printf("%ld\n", sizeof(struct test));
    printf("%ld\n", sizeof(struct A));
    printf("%ld\n", sizeof(struct betterA));
    printf("%ld\n", sizeof(struct B));
    printf("%ld\n", sizeof(struct betterB));
    printf("%ld\n", sizeof(void *));
    printf("Alignment of char = %zu\n", alignof(struct A));
    
    By x;   
    By * y = &x;
    
    printf("%p\n", y);
    printf("%p\n", &(y->b));
    printf("%p\n", &(y->c));
    printf("%p\n", &(y->a));
    return 0;
}