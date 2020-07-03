#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_SIZE 1000001
// finds Brun's constant using twin primes

int main()
{
    bool primes[ARRAY_SIZE];

    //sito
    primes[1] = false;
    for(int i = 2; i < ARRAY_SIZE; ++i)
    {
        primes[i] = true;
    }

    for(int i = 2; i * i < ARRAY_SIZE; ++i)
    {
        if(primes[i] == true)
        {
            for(int j = 2 * i; j < ARRAY_SIZE; j += i)
            {
                primes[j] = false;
            }
        }
    }

    double constB2 = 0;

    for(int i = 3; i < ARRAY_SIZE - 2; i += 2)
    {
        if(primes[i] && primes[i + 2])
        {
            double a = i;
            double b = i + 2;
            constB2 += (a+b)/(a*b);
        }
    }

    printf("%lf", constB2);

    return 0;
}
