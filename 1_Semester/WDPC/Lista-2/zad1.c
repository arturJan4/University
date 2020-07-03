#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

/*
Changes letters to alternate
example : aaaaa BBbb +a cd cd cd cd; -> aAaAa BbBb +A cd CD cd CD;
*/
int main()
{
    bool wasBigger[26] = {false}; // czy poprzednio litera byla duza
    bool notFirst[26] = {false}; // czy pierwsze wystapienie

    int character;

    character = getchar();
    while(character != EOF)
    {
        if(!isalpha(character))
        {
            putchar(character);
            character = getchar();
            continue;
        }

        int index = tolower(character) - 'a';
        if(notFirst[index])
        {
            if(wasBigger[index])
                putchar(tolower(character));
            else
                putchar(toupper(character));

            wasBigger[index] = !(wasBigger[index]);
        }
        else
        {
            putchar(character);

            if(isupper(character))
                wasBigger[index] = true;
            else
                wasBigger[index] = false;
        }

        if(!notFirst[index])
            notFirst[index] = true;

        character = getchar();
    }

    return 0;
}
