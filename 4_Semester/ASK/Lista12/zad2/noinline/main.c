#include<stdio.h>

__attribute__((noinline))
size_t my_strlen(const char *s) {
    size_t i = 0;
    while (*s++)
        i++;
    return i;
}

const char *my_index(const char *s, char v) {
    for (size_t i = 0; i < my_strlen(s); i++)
        if (s[i] == v)
            return &s[i];
    return 0;
}

int main()
{
    const char* test = "hahhahax";
    const char* out = my_index(test, 'x');
    printf("%s", out);
    return 0;
}