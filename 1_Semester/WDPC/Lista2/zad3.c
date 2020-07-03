#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// cypher and decypher function

char alphabet[64];
char table[64][64];

int returnIndexInAlphabet(char tab[], char a)
{
    int i = 0;
    while(i < 64 && a != tab[i])
    {
        ++i;
    }

    return i;
}

void matchStrings(char key[], char text[], char output[])
{
    int i = 0;
    int lengthKey = (int)strlen(key) - 1; // -1 to \n
    int lengthText = (int)strlen(text) - 1;

    while(i < lengthText && i < 256)
    {
        output[i] = key[i % lengthKey];
        ++i;
    }
    output[i] = '\0';
}

bool supportedAlphabet(char text[])
{
    bool isSupported = true;
    size_t i = 0;
    while(i + 1 < strlen(text) && i < 256)
    {
        int j = (int)text[i];
        if(
            !((j >= '0' && j <= '9')
              || (j >= 'a' && j <= 'z')
              || (j >= 'A' && j <= 'Z')
              || j == ','
              || j == ' '))
            {
            isSupported = false;
            break;
            }

        ++i;
    }
    return isSupported;
}

void encrypter(char key[], char text[], char output[])
{
    size_t len = 0;
    for(; len + 1 < strlen(text); ++len)// -1 do spr
    {
        size_t kolumna = returnIndexInAlphabet(alphabet,text[len]);
        size_t wiersz = returnIndexInAlphabet(alphabet,key[len]);
        output[len] = table[wiersz][kolumna];
    }

    output[len] = '\0';
}

void decrypter(char key[], char text[], char output[])
{
    size_t len = 0;
    for(; len + 1 < strlen(text); ++len)// -1 do spr
    {
        size_t kolumna = returnIndexInAlphabet(alphabet,text[len]);

        int j = returnIndexInAlphabet(alphabet,key[len]);
        j = returnIndexInAlphabet(alphabet,table[j][0]);

        j = ((64 - j)%64) ;

        size_t wiersz = returnIndexInAlphabet(alphabet,table[j][0]);

        output[len] = table[wiersz][kolumna];
    }
    output[len] = '\0';
}

int main()
{
    //creates an alphabet
    for(int i = 0; i < 10; ++i)
    {
        alphabet[i] = (char)(i+48);
    }
    for(int i = 10; i < 36; ++i)
    {
        alphabet[i] = (char)(i+55);
    }
    for(int i = 36; i < 63; ++i)
    {
        alphabet[i] = (char)(i+61);
    }
    alphabet[62] = ' ';
    alphabet[63] = ',';

    //check whether we want to encrypt or decrypt
    bool encrypt = false;
    char decideWay[9];
    fgets(decideWay,8,stdin);
    if(!strcmp(decideWay, "encrypt"))
        encrypt = true;
    else
        encrypt = false;

    fflush(stdin);
    //creates permutated table
    for(int i = 0; i < 64; ++i)
    {
        int perm;
        scanf("%d ", &perm);

        for(int j = 0; j < 64; ++j)
        {
            int currentLetter = (j + perm) % 64;
            table[i][j] = alphabet[currentLetter];
        }
    }

    char key[512];
    char text[512];
    char outKey[512];
    bool isSupported = true;
    fflush(stdin);
    if(fgets(key,256,stdin) == 0)isSupported = false;

    fflush(stdin);

    if(fgets(text,256,stdin) == 0)isSupported = false;

    if((!isSupported) || !(supportedAlphabet(text)) || !(supportedAlphabet(key)))
        printf("UNSUPPORTED_ALPHABET");
    else
    {
        char output[512];
        matchStrings(key,text,outKey);

        if(encrypt)
        {
            encrypter(outKey, text, output);
        }
        else
        {
            decrypter(outKey, text, output);
        }

        printf("%s", output);
    }
    return 0;
}

