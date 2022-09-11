#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// finds the longest snake in 2d array

struct InputData
{
    char text[2]; // P1
    int m, n; // wymiary tablicy
    int **tablica;
};

struct InputData readInput()
{
    struct InputData dane;
    scanf("%s", dane.text);

    scanf("%d %d", &dane.n, &dane.m);

    dane.tablica = malloc(sizeof(int*) * (dane.m + 1));
    for(int i = 0; i < dane.m + 1; ++i)
    {
        dane.tablica[i] = malloc(sizeof(int) * dane.n);
    }

    for(int i = 0; i < dane.n; ++i)
    {
        dane.tablica[0][i] = -1;
    }
    for(int i = 1; i < dane.m + 1; ++i)
    {
        for(int j = 0; j < dane.n; ++j)
        {
            scanf("%d", &(dane.tablica[i][j]));
        }
    }
    return dane;
}

int dynamicSolution(struct InputData dane)
{
    int m = dane.m;
    int n = dane.n;

    int max = 0;

    int dpSolution[2][n];
    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            dpSolution[i][j] = 0;
        }
    }

    for(int i = 1; i < m + 1; ++i)
    {
        int dpLeft[n]; // from right to left order
        for(int j = 0; j < n; ++j)
        {
            dpLeft[j] = 0;
        }

        //fill first column
        if(dane.tablica[i][0] != dane.tablica[i-1][0])
            dpSolution[1][0] =  dpSolution[0][0] + 1;
        else
            dpSolution[1][0] = 1;

        //fill rest of columns
        for(int j = 1; j < n; ++j)
        {
            if(dane.tablica[i][j-1] != dane.tablica[i][j])//match in row
            {
                if(dane.tablica[i-1][j] != dane.tablica[i][j])//match in column
                {
                    if(dpSolution[0][j] > dpSolution[1][j-1])
                        dpSolution[1][j] = dpSolution[0][j] + 1;
                    else
                        dpSolution[1][j] = dpSolution[1][j-1] + 1;
                }
                else
                {
                    dpSolution[1][j] = dpSolution[1][j-1] + 1;
                }
            }
            else
            {
                if(dane.tablica[i-1][j] != dane.tablica[i][j])
                    dpSolution[1][j] = dpSolution[0][j] + 1;
                else
                    dpSolution[1][j] = 1;
            }
        }

        //fill last column
        if(dane.tablica[i-1][n-1] != dane.tablica[i][n-1])
            dpLeft[n-1] = dpSolution[0][n-1] + 1;
        else
            dpLeft[n-1] = 1;

        //fill right to left
        for(int j = n-2; j >= 0; --j)
        {
            if(dane.tablica[i][j+1] != dane.tablica[i][j])//match in row
            {
                    if(dane.tablica[i-1][j] != dane.tablica[i][j])//match in column
                    {
                        if(dpLeft[j+1] > dpSolution[0][j])
                            dpLeft[j] = dpLeft[j+1] + 1;
                        else
                            dpLeft[j] = dpSolution[0][j] + 1;
                    }
                    else
                    {
                        dpLeft[j] = dpLeft[j+1] + 1;
                    }
            }
            else
            {
                if(dane.tablica[i-1][j] != dane.tablica[i][j])
                {
                    dpLeft[j] = dpSolution[0][j] + 1;
                }
                else
                {
                    dpLeft[j] = 1;
                }
            }
        }

        //pick max in row
        for(int j = 0; j < n; ++j)
        {
            dpSolution[0][j] = dpSolution[1][j];

            if(dpLeft[j] > dpSolution[1][j])
            {
                dpSolution[0][j] = dpLeft[j];
            }

            if(dpSolution[1][j] > max)
            {
                max = dpSolution[1][j];
            }

            dpSolution[1][j] = 0;
        }

    }

    return max;
}


int main()
{
    struct InputData dane = readInput();
    int x = dynamicSolution(dane);

    printf("%d", x);
    return 0;
}

