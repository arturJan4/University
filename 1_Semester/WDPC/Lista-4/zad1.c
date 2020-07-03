#include <stdio.h>
#include <stdlib.h>

// changes all bits in bit representation so that if there are three zeroes 
// before a 1 then a 1 is changed into a 0
int main()
{
    int c = getchar();
    int countOfZero = 0;
    while(c != EOF)
    {
        for (int i = 0; i < 8; ++i)
        {
            int temp = ((c << i) & 128) ? 1 : 0;

            if(temp == 0)
                countOfZero++;
            else
            {
                if(countOfZero >= 3)
                {
                    countOfZero = 0;
                    //c = (c & ((~128) >> i));
                    c ^= 128 >> i;
                }
            }
        }
        printf("%c", c);

        c = getchar();
    }
    return 0;
}
