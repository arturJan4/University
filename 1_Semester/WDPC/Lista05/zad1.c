#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// finds the longest subset that sums to zero (n <= 30, numbers from [-10^12,10^12])

int liczbaDodatnich = 0;
int maxDlugosc = 0;
int maxPostive = 0;

bool wynik[30];
bool used[30];
long long int suma = 0;
long long int numbers[30];
int dlugosc = 0;
int countPositive = 0;

void recSubsets(int n, size_t iterator)
{
    if(iterator == 0)
    {
        if(suma + numbers[0] == 0)
        {
            dlugosc += 1;
            if(numbers[iterator] > 0)
                countPositive++;
            if(dlugosc >= maxDlugosc && (dlugosc > maxDlugosc || countPositive > maxPostive))
            {
                used[0]= true;
                maxDlugosc = dlugosc;
                maxPostive = countPositive;
                memcpy(wynik,used,sizeof(bool) * n);
            }
        }
        else if(suma == 0)
        {
            if(dlugosc >= maxDlugosc && (dlugosc > maxDlugosc || countPositive > maxPostive))
            {
                used[0] = false;
                maxDlugosc = dlugosc;
                maxPostive = countPositive;
                memcpy(wynik,used,sizeof(bool) * n);
            }
        }
        return;
    }

    //nie uzywaj tego elementu
    used[iterator] = false;
    recSubsets(n,iterator-1);

    //uzyj ten element
    used[iterator] = true;
    bool positive = numbers[iterator] > 0 ? 1 : 0;

    if(positive)
        countPositive++;
    suma += numbers[iterator];
    ++dlugosc;

    recSubsets(n,iterator-1);

    suma -= numbers[iterator];
    --dlugosc;
    if(positive)
        --countPositive;
}

void printWynik(int n)
{
    for(int i = 0; i < n; ++i)
    {
        if(wynik[i])
            printf("%lld ", numbers[i]);
    }
}

int main()
{
    int n;
    if(!scanf("%d", &n))
        printf("error reading n");

    for(int i = 0; i < 30; ++i)
    {
        wynik[i] = false;
        used[i] = false;
    }

    for(int i = 0; i < n; ++i)
    {
        if(!(scanf("%lld", &numbers[i])))
            printf("error reading numbers");
    }

    recSubsets(n,n-1);
    printWynik(n);

    return 0;

}
