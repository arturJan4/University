#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Draws an elipse on console

bool inBound(int a, int b, double x, double y)
{
    double sum = (x*x)/(a*a) + (y*y)/(b*b);
    if(sum <= 1)return true;

    return false;
}
int main()
{
    int a,b; // a - wielka, b- mala polos elipsy
    scanf("%d%d", &a, &b);

    //sprawdzaj srodki przedzialow(kratek)
    for(double y = b - 0.5; y >= -b + 0.5; --y)
    {
        for(double x = -a + 0.5; x <= a + 0.5; ++x)
        {
            if(inBound(a,b,x,y))printf("*");
            else printf(" ");
        }
        printf("\n");
    }

    return 0;
}
