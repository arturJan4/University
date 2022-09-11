#include <stdio.h>
#include <stdlib.h>

// zad1 with different contrains (n <= 1000, numbers from [-10^3,10^3])

const int ARR_SIZE = 2000001;
const int ADD_C = 1000000;

int main()
{
    int n;
    scanf("%d", &n);
    int *tab = malloc(sizeof(int) * ARR_SIZE);

    int input1[n];
    int input[n];
    int countPos = 0;
    int countNeg = 0;

    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &input1[i]);

        if(input1[i] < 0)
            countNeg++;
        else
            countPos++;
    }

    int i = 0;
    int j = 0;
    while(countPos > 0)
    {
        if(input1[j] >= 0)
        {
            --countPos;
            input[i] = input1[j];
            ++i;
        }
        ++j;
    }
    j = 0;
    while(countNeg > 0)
    {
        if(input1[j] < 0)
        {
            --countNeg;
            input[i] = input1[j];
            ++i;
        }
        j++;
    }

    /*
    for(int i = 0; i < n; ++i)
    {
        printf("%d ", input[i]);
    }printf("\n");
    */

    for(int i = 0; i < ARR_SIZE; ++i)
    {
        tab[i] = 0;
    }
    int maxSum = 0;
    int minSum = 0;

    for(int i = 0; i < n; ++i)
    {
        if(input[i] >= 0)
        {
            maxSum += input[i];
            for(int j = maxSum + ADD_C; j >= input[i] + ADD_C; --j)
            {
                if(tab[j] < tab[j-input[i]] + 1)
                {
                    tab[j]  = tab[j-input[i]] + 1;
                }
            }
        }

        if(input[i] < 0)
        {
            minSum += input[i];
            for(int j = input[i] + ADD_C; j <= maxSum + ADD_C ; ++j)
            {
                if(j > ARR_SIZE)break;
                if(tab[j] < tab[j-input[i]] + 1)
                {
                    tab[j]  = tab[j-input[i]] + 1;
                }
            }
        }
    }

    printf("%d", tab[ADD_C]);

    return 0;
}
