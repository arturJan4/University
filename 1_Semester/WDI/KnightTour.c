#include <stdio.h>
#include <stdlib.h>

#define n 8
int board[n+4][n+4];

void init()
{
    for(int i = 0; i < n + 4; ++i)
    {
        for(int j = 0; j < n + 4; ++j)
        {
            if(j < 2 || j > n + 1 || i < 2 || i > n + 1)
                board[i][j] = 1;
            else
                board[i][j] = 0;
        }
    }
}

void printBoard()
{
    for(int i = 2; i < n + 2; ++i)
    {
        for(int j = 2; j < n + 2; ++j)
        {
            if(board[i][j] > 9)
                printf(" %d ", board[i][j]);
            else
                printf("  %d ", board[i][j]);
        }
        printf("\n");
    }
}

int xMoves[8] = {-2,-2,-1,-1,1,1,2,2};
int yMoves[8] = {-1,1,-2,2,-2,2,-1,1};

int backtrackingSolution(int move, int y, int x)
{
    if(board[y][x] != 0)
    {
        return 0;
    }
    else
        board[y][x] = move;

    if(move == n * n)
    {
        printBoard();
        return 1;
    }

    for(int i = 0; i < 8; ++i)
    {
        if(backtrackingSolution(move + 1, y + yMoves[i], x + xMoves[i]))
            return 1;
    }

    board[y][x] = 0;

    return 0;
}

int main()
{
    init();
    //printBoard();

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(backtrackingSolution(1,i + 2,j + 2))break;
        }
    }

    return 0;
}
