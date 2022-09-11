/*
Artur Jankowski, 317928
Lista 1, zad2
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool isPrime(int n)
{
    bool prime = true;

    if(n == 1)
        return false;
    else if(n == 2)
        return true;
    else if(n % 2 ==0)
        return false;//podzielne na 2 (rozne od 2)

    for(int i = 3; i * i <= n; i += 2)
    {
        if(n % i == 0)
            return false;
    }

    return prime;
}

// smallest prime p such that m != n (mod p)
int smallestP(int m, int n)
{
    // 3 <= m < n
    int resztaM = 0;
    int resztaN = 0;
    int p = 1;
    while(resztaM == resztaN)
    {
        ++p;
        if(isPrime(p))
        {
            resztaM = m % p;
            resztaN = n % p;
        }
    }
    return p;
}

//finds m, n such that p/logn is the biggest
int main()
{
    double max = 0;
    int m, n;
    for(int i = 3; i <= 1000; ++i)
    {
        for(int j = i + 1; j <= 1000; ++j)
        {
            int currentP = smallestP(i,j);
            double currentLog = ((double)currentP)/log(j);
            if(currentLog > max)
            {
                max = currentLog;
                m = i;
                n = j;
            }
        }
    }

    printf("m-%d n-%d", m, n);
    return 0;
}
