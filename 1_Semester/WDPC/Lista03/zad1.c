#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_ARRAY 10000

// finds the longest substring palindrome

bool isPalindrome(char text[], int start, int end)
{
    int j = end;
    for(int i = start; i < j; ++i)
    {
        if(text[i] != text[j])
            return false;
        --j;
    }

    return true;
}

char input[MAX_ARRAY];

int main()
{
    fgets(input,MAX_ARRAY,stdin);
    int end = strlen(input) - 1;
    int countLongest = 0;
    int iLongest = 0;
    int jLongest = 0;

    for(int i = 0; i < end; ++i)
    {
        for(int j = i + countLongest; j < end; ++j)
        {
            if(isPalindrome(input,i,j))
            {
                if(j-i+1 > countLongest)
                {
                    countLongest = j-i +1;
                    iLongest = i;
                    jLongest = j;
                }
            }
        }
    }

    for(int i = iLongest; i <= jLongest; ++i)
    {
        printf("%c", input[i]);
    }

    return 0;
}
