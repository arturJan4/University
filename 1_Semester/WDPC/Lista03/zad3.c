#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// PBM image compression

typedef enum State
{
    STATE_P1,
    STATE_RR,
    STATE_RS,
    STATE_RD,
    STATE_ERROR
} State;

struct InputData
{
    int n; // rows
    int m; // columns
    State stan;
};

struct InputData getInput()
{
    char buffer[3];
    fgets(buffer,3,stdin);
    State stateOfInput = STATE_ERROR;
    int n,m;

    if(strcmp(buffer, "P1") == 0)
    {
        //printf("P1");
        scanf("%d", &n); // columns
        scanf("%d", &m); // rows
        stateOfInput = STATE_P1;
    }
    else if(strcmp(buffer, "RR") == 0)
    {
        //printf("RR");
        scanf("%d", &n);
        m = n;
        stateOfInput = STATE_RR;
    }
    else if(strcmp(buffer, "RS") == 0)
    {
        //printf("RS");
        scanf("%d", &n);
        m = n;
        stateOfInput = STATE_RS;
    }
    else if(strcmp(buffer, "RD") == 0)
    {
        //printf("RD");
        scanf("%d", &n);
        m = n;
        stateOfInput = STATE_RD;
    }
    else
    {
        printf("error in input");
        stateOfInput = STATE_ERROR;
    }

    struct InputData dane;
    dane.n = n;
    dane.m = m;
    dane.stan = stateOfInput;

    return dane;
}

void createPBM(int m, int n, int table[m][n])
{
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            scanf("%d", &table[i][j]);
        }
    }
}

void createRR(int m, int n,int table[m][n])
{
    int i = 0;
    int j = 0;
    int curr_i = 0;

    bool isZero = false;
    int left = 0;
    while(curr_i < m * n)
    {
        if(left == 0)
        {
            scanf("%d", &left);
            isZero = !isZero;
        }
        else
        {
            i = curr_i / n;
            j = curr_i % n;
            if(isZero)
                table[i][j] = 0;
            else
                table[i][j] = 1;

            ++curr_i;
            --left;
        }
    }
}

void createRS(int m, int n, int table[m][n])
{
    bool isZero = false;
    bool right = true;
    int left = 0;
    int curr_i = 0;
    while(curr_i != ((m-1) * n) + n)
    {
        if(left == 0)
        {
            scanf("%d", &left);
            isZero = !isZero;
        }
        else
        {
            int i = curr_i / n;
            int j = curr_i % n;

            if(isZero)
                table[i][j] = 0;
            else
                table[i][j] = 1;

            if(right)
            {
                if(curr_i % n == n-1)//last colum
                {
                    curr_i += n;
                    right = false;
                }
                else
                    ++curr_i;
            }
            else
            {
                if(curr_i % n == 0)//first column
                {
                    curr_i += n;
                    right = true;
                }
                else
                    --curr_i;
            }

            --left;
        }
    }
}

void createRD(int m, int n, int table[m][n])
{
    bool isZero = false;
    bool goDown = false;
    bool canMoveDown = true;
    int left = 0;
    int curr_i = 0;
    while(curr_i < m*n)
    {
        if(left == 0)
        {
            scanf("%d", &left);
            isZero = !isZero;
        }
        else
        {
            int i = curr_i / n;
            int j = curr_i % n;

            if(isZero)
                table[i][j] = 0;
            else
                table[i][j] = 1;

            if(curr_i < n || curr_i >= (n * (m-1)))//first or last row
            {
                if(i == m - 1 && j == n - 1)
                {
                    curr_i += 1;
                }
                else if(curr_i % 2 == 0)
                {
                    curr_i++;
                    goDown = !goDown;
                }
                else if(goDown)
                    curr_i += (n-1);
                else if(!goDown)
                    curr_i -= (n-1);

                canMoveDown = true;
            }
            else
            {
                if((j == 0 || j == n - 1) && canMoveDown)//first or last column
                {
                    goDown = !goDown;
                    curr_i += n;
                    canMoveDown = false;
                }
                else if(goDown)
                    curr_i += (n-1);
                else if(!goDown)
                    curr_i -= (n-1);
            }
            --left;
        }
    }
}

void createTable(int m, int n, int table[m][n], State stan)
{
    switch(stan)
    {
    case STATE_P1:
        createPBM(m,n,table);
        break;
    case STATE_RR://check if 0
        createRR(m,n,table);
        break;
    case STATE_RS:
        createRS(m,n,table);
        break;
    case STATE_RD:
        createRD(m,n,table);
        break;
    case STATE_ERROR:
        printf("error in input\n");
        break;
    default:
        printf("error creating table\n");
        break;
    }

}

int sumRR(int m, int n, int table[m][n])
{
    int sum = 1;
    bool isZero = true;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(isZero)
            {
                if(table[i][j] != 0)
                {
                    isZero = false;
                    sum++;
                }
            }
            else
            {
                if(table[i][j] == 0)
                {
                    isZero = true;
                    sum++;
                }
            }
        }
    }
    return sum;
}

int sumRS(int m, int n,int table[m][n])
{
    int sum = 1;
    bool isZero = true;
    for(int i = 0; i < m ; ++i)
    {
        if(i%2)//in reverse order
        {
            for(int j = n-1; j >= 0; --j)
            {
                if(isZero)
                {
                    if(table[i][j] != 0)
                    {
                        isZero = false;
                        sum++;
                    }
                }
                else
                {
                    if(table[i][j] == 0)
                    {
                        isZero = true;
                        sum++;
                    }
                }
            }
        }
        else
        {
            for(int j = 0; j < m; ++j)
            {
                if(isZero)
                {
                    if(table[i][j] != 0)
                    {
                        isZero = false;
                        sum++;
                    }
                }
                else
                {
                    if(table[i][j] == 0)
                    {
                        isZero = true;
                        sum++;
                    }
                }
            }
        }
    }
    return sum;
}

int sumRD(int m, int n, int table[m][n])
{
    int sum = 1;
    bool isZero = true;
    bool goDown = false;
    bool canMoveDown = true;
    int curr_i = 0;
    while(curr_i < m*n)
    {
        int i = curr_i / n;
        int j = curr_i % n;

        if(isZero && table[i][j] == 1)
        {
            sum++;
            isZero = false;
        }
        else if (!isZero && table[i][j] == 0)
        {
            sum++;
            isZero = true;
        }

        if(curr_i < n || curr_i >= (n * (m-1)))//first or last row
        {
            if(i == m - 1 && j == n - 1)
            {
                curr_i += 1;
            }
            else if(curr_i % 2 == 0)
            {
                curr_i++;
                goDown = !goDown;
            }
            else if(goDown)
                curr_i += (n-1);
            else if(!goDown)
                curr_i -= (n-1);

            canMoveDown = true;
        }
        else
        {
            if((j == 0 || j == n - 1) && canMoveDown)//first or last column
            {
                goDown = !goDown;
                curr_i += n;
                canMoveDown = false;
            }
            else if(goDown)
                curr_i += (n-1);
            else if(!goDown)
                curr_i -= (n-1);
        }
    }
    return sum;
}
int main()
{
    struct InputData inputData = getInput();

    int table[inputData.m][inputData.n];

    createTable(inputData.m,inputData.n,table,inputData.stan);

    int a = sumRR(inputData.m,inputData.n,table);
    int b = sumRS(inputData.m,inputData.n,table);
    int c = sumRD(inputData.m,inputData.n,table);

    printf("%d %d %d", a, b, c);
    return 0;
}

