#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// draws a histogram of letters
#define MAX_SIZE 256 // wielkosc wejscia

const int STRIPE_SIZE = 10; // dlugosc paska

int main()
{
    char buffer[MAX_SIZE];
    fgets(buffer,MAX_SIZE,stdin);

    int countChars[256] = {0};
    int sumOfChars = 0;

    for(size_t i = 0; i < strlen(buffer); ++i)
    {
        if(isgraph(buffer[i]))
        {
            countChars[(int)buffer[i]]++;
            sumOfChars++;
        }
    }
    for(int i = 0; i < 256; ++i)
    {
        if(isgraph(i) && countChars[i] > 0)
        {
            double percentage = ((double)countChars[i]/sumOfChars);
            double share = round(percentage*STRIPE_SIZE);
            //printf("%c: %d %lf \n", i, countChars[i], share);

            printf("%c [", i);
            for(int i = 0; i < STRIPE_SIZE; ++i)
            {
                if(share > 0)
                {
                    printf("*");
                    --share;
                }
                else
                    printf(" ");
            }
            printf("]\n");
        }
    }
    return 0;
}
