/*
Artur Jankowski, 317928
Lista 2, zad 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

long int sumOfDivisors(long int n)
{
    long int sum = 0;// 1 | n
    if(n > 0)sum += 1;
    for(long int i = 2; i * i <= n; ++i)
    {
        if(i*i == n) // +sqrt(n)
        {
            sum += i;
            continue;
        }
        else if(n % i == 0)
            sum += i + n/i; // i|n => (n/i)|n
    }

    return sum;
}

// finds n, m such that sum of divisors of n is m, and sum of divisors of m is n
int main()
{
    int s;
    bool found = false;
    int wynikN, wynikM;
    scanf("%d", &s);

    long int n = s;
    while(n < INT_MAX)
    {
        long int m = sumOfDivisors(n);
        if(m < 0 || n < 0 || n >= m || m > INT_MAX || n <= s)
        {
            ++n;
            continue;
        }

        if((sumOfDivisors(m) == n))
        {
            found = true;
            wynikM = m;
            wynikN = n;
            break;
        }
        else
            ++n;
    }

    if(found)
        printf("%d %d\n", wynikN, wynikM);
    else
        printf("BRAK");

    return 0;
}

