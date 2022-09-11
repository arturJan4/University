#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// bit knitter
// transforming multi-dimensional array into linear array

void intToBinary(int a, int binaryRep[16])
{
    //najmniej znaczacy jest pierwszy
    int i = 0;
    while(a > 0)
    {
        binaryRep[i] = a % 2;
        a /= 2;
        ++i;
    }
    while(i < 16)
    {
        binaryRep[i] = 0;
        ++i;
    }
}

long long int binaryToInt(int n, int binaryRep[n])
{
    long long int sum = 0;
    long long int pot = 1;
    int i = 0;
    while(i < n)
    {
        if(binaryRep[i] == 1)
        {
            sum += pot;
        }
        ++i;
        pot *= 2;
    }

    return sum;
}
int asciiToInt(char c)
{
    return (int)(c) - 48;
}

struct ConditionalNegation
{
    char negateThis[2];
    char ifThisEquals[2];
    int valueToCompare;
};

struct Input
{
    bool encode;
    char sygnatura[4096];
    int y;  // if decode y == x
    int x;
    struct ConditionalNegation negacje[32];
    int ileNegacji;
};

struct Input readInput()
{
    struct Input data;
    data.encode = false;
    data.ileNegacji = 0;
    char input[4096];
    fgets(input,100,stdin);

    if(!(strcmp(input, "encode\n")))
        data.encode = true;
    else
        data.encode = false;

    fgets(input,4095,stdin);

    int i = 1;
    int j = 0;
    while((input[i] != '\0' || input[i] != '\n') && input[i] != ']')
    {
        if(input[i] != ' ')
        {
            data.sygnatura[j] = input[i];
            ++j;
        }
        ++i;
    }
    data.sygnatura[j] = '\0';

    i += 5;
    j = -1;
    while(input[i] != '\n')
    {
        if(input[i] == 'c')
        {
            ++j;
            data.negacje[j].negateThis[0] = input[i+3];
            data.negacje[j].negateThis[1] = input[i+4];
            data.negacje[j].ifThisEquals[0] = input[i+6];
            data.negacje[j].ifThisEquals[1] = input[i+7];
            data.negacje[j].valueToCompare = asciiToInt(input[i+9]);
            data.ileNegacji++;
        }
        ++i;
    }

    if(data.encode)
    {
        char para[20];
        fgets(para,19,stdin);
        if(para[1] == 'y')
        {
            data.y = asciiToInt(para[7]);
            data.x = asciiToInt(para[9]);
        }
        else
        {
            data.x = asciiToInt(para[7]);
            data.y = asciiToInt(para[9]);
        }
    }
    else
    {
        int n;
        scanf("%d", &n);
        data.x = n;
        data.y = n;
    }

    return data;
}

void printData(struct Input input)
{
    printf("\n========\n");
    if(input.encode)
        printf("encode\n");
    else
        printf("decode\n");

    printf("%s", input.sygnatura);
    printf("para(y,x): %d %d", input.y, input.x);
    printf("\n");
}

void testBintoInt()
{/*
    int binaryrep1[16] = {1,0,0};
    //int wynik1 = binaryToInt(binaryrep1,16);

    int binaryrep2[16] = {1,1,0};
    //int wynik2 = binaryToInt(binaryrep2,16);

    int binaryrep3[16];
    for(int i = 0; i < 16; ++i)
    {
        binaryrep3[i] = 1;
    }
    //int wynik3 = binaryToInt(binaryrep3,16);

    //printf("expected 1: value: %d\n", wynik1);
    printf("expected 3: value: %d\n", wynik2);
    printf("expected : value: %d\n", wynik3);

    intToBinary(wynik1,binaryrep1);
    intToBinary(wynik2,binaryrep2);
    intToBinary(wynik3,binaryrep3);

    printf("===W DRUGA STRONE===\n");
    for(int i = 0; i < 16; ++i)
    {
        printf("%d ", binaryrep1[i]);
    }
    printf("\n");

    for(int i = 0; i < 16; ++i)
    {
        printf("%d ", binaryrep2[i]);
    }
    printf("\n");

    for(int i = 0; i < 16; ++i)
    {
        printf("%d ", binaryrep3[i]);
    }
    printf("\n");
*/
}

void testNegations(struct Input dane)
{
    for(int i = 0; i < dane.ileNegacji; ++i)
    {
        printf("negate:%c%c\n",dane.negacje[i].negateThis[0],dane.negacje[i].negateThis[1]);
        printf("if:%c%c equals %d\n",dane.negacje[i].ifThisEquals[0],dane.negacje[i].ifThisEquals[1],dane.negacje[i].valueToCompare);

    }
}

void reverseArray(int n, int array[n])
{
    int temp[n];
    for(int i = 0; i < n; ++i)
    {
        temp[i] = array[i];
    }
    int j = 0;
    for(int i = n-1; i >= 0; --i)
    {
        array[j] = temp[i];
        ++j;
    }
}

int returnIndex(char b)
{
    int index = asciiToInt(b);

    if(!(index >= 0 && index <= 9))
    {
        switch(b)
        {
        case 'A':
            index = 10;
            break;
        case 'B':
            index = 11;
            break;
        case 'C':
            index = 12;
            break;
        case 'D':
            index = 13;
            break;
        case 'E':
            index = 14;
            break;
        case 'F':
            index = 15;
            break;
        default:
            index = -1;
            break;
        }
    }
    return index;
}
void signatureToBinary(int wynik[32], struct Input dane)
{
    int xBinary[16] = {0};
    int yBinary[16] = {0};

    intToBinary(dane.x,xBinary);
    intToBinary(dane.y,yBinary);

    int rozmiarWyniku = 0;
    for(int i = 0; dane.sygnatura[i] != '\0'; i += 2)
    {
        rozmiarWyniku++;
        int j = i/2;
        int index = returnIndex(dane.sygnatura[i+1]);

        if(dane.sygnatura[i] == 'y')
        {
            wynik[j] = yBinary[index];
        }
        else
        {
            wynik[j] = xBinary[index];
        }
    }

    reverseArray(rozmiarWyniku,wynik);

    for(int z = 0; z < dane.ileNegacji; ++z)
    {
        //find if is certain value
        for(int i = 0; dane.sygnatura[i] != '\0'; i += 2)
        {
            if((dane.negacje[z].ifThisEquals[0] == dane.sygnatura[i])
                    && (dane.negacje[z].ifThisEquals[1] == dane.sygnatura[i+1]))
            {
                int j = rozmiarWyniku -1 - (i/2);
                if(wynik[j] == dane.negacje[z].valueToCompare)
                {
                    for(int k = 0; dane.sygnatura[k] !='\0'; k += 2)
                    {
                        if((dane.negacje[z].negateThis[0] == dane.sygnatura[k])
                                && (dane.negacje[z].negateThis[1] == dane.sygnatura[k+1]))
                        {
                            int m = rozmiarWyniku - 1 - (k/2);
                            if(wynik[m] == 1)
                                wynik[m] = 0;
                            else
                                wynik[m] = 1;
                        }
                    }
                }
            }
        }

    }

}

void fromSignature(struct Input dane, int wynik[32])
{
    intToBinary(dane.x, wynik);

    int rozmiarWyniku = 0;
    for(int i = 0; dane.sygnatura[i] != '\0'; i += 2)
    {
        rozmiarWyniku++;
    }
    reverseArray(rozmiarWyniku,wynik);

    for(int z = dane.ileNegacji - 1; z >= 0; --z)
    {
        //find if is certain value
        for(int i = 0; dane.sygnatura[i] != '\0'; i += 2)
        {
            if((dane.negacje[z].ifThisEquals[0] == dane.sygnatura[i])
                    && (dane.negacje[z].ifThisEquals[1] == dane.sygnatura[i+1]))
            {
                int j = i/2;
                if(wynik[j] == dane.negacje[z].valueToCompare)
                {
                    for(int k = 0; dane.sygnatura[k] !='\0'; k += 2)
                    {
                        if(dane.negacje[z].negateThis[0] == dane.sygnatura[k]
                                && dane.negacje[z].negateThis[1] == dane.sygnatura[k+1])
                        {
                            int m = (k/2);
                            if(wynik[m] == 0)
                                wynik[m] = 1;
                            else
                                wynik[m] = 0;
                        }
                    }
                }
            }
        }
    }

    int xBinary[16] = {0};
    int yBinary[16] = {0};
    for(int i = 0; dane.sygnatura[i] != '\0'; i += 2)
    {
        int j = i/2;
        if(dane.sygnatura[i] == 'y')
        {
            int index  = returnIndex(dane.sygnatura[i+1]);
            if(wynik[j] == 1)
                yBinary[index] = 1;
        }
        else
        {
            int index  = returnIndex(dane.sygnatura[i+1]);
            if(wynik[j] == 1)
                xBinary[index] = 1;
        }
    }
    int x = binaryToInt(16,xBinary);
    int y = binaryToInt(16,yBinary);
    printf("(y,x)=(%d,%d)",y,x);
}
int main()
{
    struct Input dane = readInput();

    // printData(dane);
    //testBintoInt();

    //od bitu najmniej znaczacego do najbardziej czyli x0 = a[0]

    int wynik[32] = {0};
    if(dane.encode)
    {
        signatureToBinary(wynik,dane);
        printf("%lld", binaryToInt(32,wynik));
    }
    else
    {
        fromSignature(dane,wynik);
    }

    return 0;
}

