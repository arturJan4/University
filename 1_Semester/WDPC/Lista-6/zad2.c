#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

// finding solution(minimal amount of moves) for flood game
/* example:
4 5
aaaa
bbbb
ccaa
dddd
eecc
result : 4
*/


bool znaki[30];
int minMoves;

void printArray(int m, int n, char** tab)
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            printf("%c", tab[i][j]);
        }
        printf("\n");
    }
}

void readArray(int m, int n, char** tab)
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            scanf(" %c", &tab[i][j]);
        }
    }
}

void readChars(int m, int n, char** tab)
{
    memset(znaki,false,sizeof(bool)*30);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            znaki[(int)(tab[i][j] - 97)] = true;
        }
    }
}

bool inBound(int m, int n, char** tab, int curI, int curJ, char curChar, char chosen)
{
    if(curI < n && curI >= 0 && curJ < m && curJ >= 0)
    {
        if(tab[curI][curJ] == curChar && tab[curI][curJ] != chosen)
        {
            return true;
        }
    }
    return false;
}

void fill(int m, int n, char** tab, int curI, int curJ, char curChar, char chosen)//fills array recursively with chosen
{
    if(inBound(m,n,tab,curI,curJ,curChar,chosen))
    {
        tab[curI][curJ] = chosen;

        curI++;
        if(inBound(m,n,tab,curI,curJ,curChar,chosen))
        {
            fill(m,n,tab,curI,curJ,curChar,chosen);
        }
        curI -=2;
        if(inBound(m,n,tab,curI,curJ,curChar,chosen))
        {
            fill(m,n,tab,curI,curJ,curChar,chosen);
        }
        curI++;
        curJ++;
        if(inBound(m,n,tab,curI,curJ,curChar,chosen))
        {
            fill(m,n,tab,curI,curJ,curChar,chosen);
        }
        curJ -=2;
        if(inBound(m,n,tab,curI,curJ,curChar,chosen))
        {
            fill(m,n,tab,curI,curJ,curChar,chosen);
        }
        curJ++;
    }
}

bool isSolved(int m, int n, char** tab)
{
    char znak = tab[0][0];
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(znak != tab[i][j])
                return false;
        }
    }
    return true;
}

void recSol(int m, int n, char** tab, int curMoves)
{
    if(curMoves >= minMoves)    //break if can't do better
        return;

    if(isSolved(m,n,tab))
    {
        if(curMoves < minMoves)
            minMoves = curMoves;
        return;
    }

    for(int k = 0; k < 26; ++k)
    {
        if(znaki[k])    //if the char is used in table
        {
            char fillWithChar = (char)(k + 97);

            for(int i = 0; i < n; ++i)
            {
                for(int j = 0; j < m; ++j)
                {
                    char beginningChar = tab[i][j];
                    if(beginningChar == fillWithChar)continue;

                    if(inBound(m,n,tab,i,j,beginningChar,fillWithChar)) // checks if tab[i][j] is valid(not out-of-bounds or different from beginningChar)
                    {
                        char** temp = malloc(sizeof(char*) * (n)); // temporary table of chars
                        for(int l = 0; l < n; ++l)
                        {
                            temp[l] = malloc(sizeof(char) * m);
                        }
                        for(int ax = 0; ax < n; ++ax)
                        {
                            memcpy(temp[ax],tab[ax],sizeof(char)*m);
                        }

                        fill(m,n,temp,i,j,beginningChar,fillWithChar); // fills all elements that are same as beginning char with fillWith
                        recSol(m,n,temp,curMoves + 1);

                        for(int ax = 0; ax < n; ++ax)
                        {
                            free(temp[ax]);
                        }
                        free(temp);
                    }

                }
            }
        }
    }
}

int main()
{
    int m, n;
    if(scanf("%d%d", &m, &n)){};

    char** tab = malloc(sizeof(char*) * (n));
    for(int i = 0; i < n; ++i)
    {
        tab[i] = malloc(sizeof(char) * m);
    }

    minMoves = m*n -1;
    readArray(m,n,tab);
    readChars(m,n,tab); // into boolean table

    recSol(m,n,tab,0);
    //printArray(m,n,tab);

    printf("%d", minMoves);
    //free memory
    return 0;
}
