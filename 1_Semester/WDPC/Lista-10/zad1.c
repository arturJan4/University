#include <stdio.h>
#include <stdlib.h>

// cyphers a file in argv[1] using XOR algorithm and our own progam as a key

long long int getFileSize(FILE *file)
{
    fseek(file,0,SEEK_END);
    long int Size = ftell(file);
    rewind(file);

    return Size;
}

int main(int argc, char *argv[])
{
    long long int chunkSize = 100000;
    //printf("%s", argv[0]);//path to file
    FILE* inputFILE;
    FILE* outputFILE;
    inputFILE = fopen(argv[0],"rb");
    outputFILE = fopen(argv[1], "r+b");
    if(inputFILE == NULL)
        printf("error opening input file");
    if(outputFILE == NULL)
        printf("eroor opening output file");

    long long int inputSize = getFileSize(inputFILE);
    long long int outputSize = getFileSize(outputFILE);

    char* bufferIn = malloc(sizeof(char)*inputSize);
    fread(bufferIn,sizeof(char),inputSize,inputFILE);

    long long int left = outputSize;
    long long int currentSize = 0;
    long long int currI = 0;
    rewind(outputFILE);
    rewind(inputFILE);

    while(left > 0)
    {
        if(left < chunkSize)
        {
            currentSize = left;
            left = 0;
        }
        else
        {
            currentSize = chunkSize;
            left -= chunkSize;
        }

        char* bufferOut = malloc(sizeof(char)*currentSize);
        fread(bufferOut,sizeof(char),currentSize,outputFILE);

        rewind(outputFILE);
        fseek(outputFILE,currI,SEEK_SET);

        for(int i = 0; i < currentSize; ++i)
        {
            bufferOut[i] = bufferOut[i] ^ bufferIn[(currI%inputSize)];
            currI++;
        }

        fwrite(bufferOut,sizeof(char),currentSize,outputFILE);
    }

    fclose(inputFILE);
    fclose(outputFILE);
    return 0;
}
