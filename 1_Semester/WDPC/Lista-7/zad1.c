#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// macro converting from hex to ascii
#define PRINTHEX(number)\
    do{\
    int length = strlen(#number);\
    int liczba = 0;\
    int rem = length % 2;\
    for(int i = 0; i < length; i++){\
        if(#number[i] >= 'A' && #number[i] <= 'F')\
            liczba  += ((int)(#number[i]-'A' + 10));\
        else\
            liczba  += ((int)(#number[i]-'0'));\
        if(i % 2 == 0 + rem)liczba *= 16;\
        if((i + rem)%2){\
            printf("%c", liczba);\
            liczba = 0;\
        }\
    }\
    }while(0)

int main()
{
    for (int i = 0; i < 10; i++)
        if (i%2)
            PRINTHEX(A);
        else
            PRINTHEX(A5564616C6F2073696521);

    return 0;
}
