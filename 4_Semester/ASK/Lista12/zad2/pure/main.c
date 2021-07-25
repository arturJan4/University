#include "index.h"

int main()
{
    const char* test = "hahhahax";
    const char* out = my_index(test, 'x');
    printf("%s", out);
    return 0;
}