#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//finds such string transform that result will equal 1 or prints that it is impossible
// example
/*
3
2 2 1
result : 2 / 2 * 1
5
10 8 0 2 1
result : 10 + 8 * 0 + 2 - 1
*/

char operations[20] = "";

bool recSolution(int n, int numbers[n], int current,int wynik)
{
    if( n == current)
    {
        if(wynik == 1)
            return true;
        else
            return false;
    }

    if(recSolution(n,numbers,current + 1, wynik + numbers[current]))
    {
        operations[current] = '+';
        return true;
    }
    else if(recSolution(n,numbers,current + 1, wynik - numbers[current]))
    {
        operations[current] = '-';
        return true;
    }
    else if(recSolution(n,numbers,current + 1, wynik * numbers[current]))
    {
        operations[current] = '*';
        return true;
    }
    else if(numbers[current] != 0)
    {
        if(recSolution(n,numbers,current + 1, wynik / numbers[current]))
        {
            operations[current] = '/';
            return true;
        }
    }

    return false;
}


int main()
{
    int n;
    scanf("%d", &n);

    int numbers[n];
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &numbers[i]);
    }


    if(recSolution(n,numbers,1,numbers[0]))
    {
        printf("%d", numbers[0]);
        for(int i = 1; i < n; ++i)
        {
            printf("%c%d", operations[i], numbers[i]);
        }
    }
    else printf("nie da sie");


    return 0;
}
