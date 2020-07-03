#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// racket notation to infix c-like notation
/*
example 
(+ 1234567891011121314151617181920212223   (  * 1 1 1 1))
+(1234567891011121314151617181920212223, *(1, 1, 1, 1))
*/
char output[10000];
char c;
char current = ',';
int outputIterator = 0;

void inside(char c)
{
        if(c == '(')current = '(';
        else if(c == ' ')
        {
            output[outputIterator] = current;
            printf("%c", output[outputIterator++]);

            if(current == ',')
            {
                output[outputIterator] = ' ';
                printf("%c", output[outputIterator]);
            }
            current = ',';
        }
        else
        {
            output[outputIterator] = c;
            printf("%c", output[outputIterator++]);
        }
}
int main()
{
    while((c = getchar()))
    {
        if(c == '\n')break;
        inside(c);

        if(c == ' ')//nadmiarowe spacje
        {
            while((c = getchar()) && c == ' ')++outputIterator;
            if(c == '\n')break;// end of input

            inside(c);
        }
    }
    return 0;
}

