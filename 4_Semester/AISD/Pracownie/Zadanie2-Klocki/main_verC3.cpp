#include <cstdio>
#include <cstring>
#include <algorithm>

int DP[2][1000003];
int blocks[2000];

int main()
{
    // TODO readline ?
    // TODO - symmetric?
    // TODO - minimal block for min difference ?

    int n;
    scanf("%d", &n);
    
    int sum = 0;
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &blocks[i]);
        sum += blocks[i];
    }
    std::sort(blocks, blocks + n);
    sum >>= 1;
    int howMany = 2 * sum + 2;
    memset(DP[0], -1, howMany * sizeof(DP[0][0]));
    memset(DP[1], -1, howMany * sizeof(DP[1][0]));
    
    const int offset = sum;
    const int start = -sum + offset;
    const int end = sum + offset;
    
    int currentSum = 0;
    int up = 0, down = 1;
    DP[0][offset] = 0; // base case
    for(int i = 0; i < n; ++i)
    {
        int element = blocks[i];
        currentSum += element;
        //std::cout << element << "\n";
        int finish = std::min(currentSum + offset, end);
        for(int j = std::max(-currentSum + offset, start); j <= finish; ++j)
        {   
            int maximum = DP[up][j];
            //printf("%d ", maximum);
            if(j - element >= 0 && DP[up][j-element] != -1)
            {
                maximum = std::max(maximum, DP[up][j-element] + element);
            }
            if(j + element <= finish)
            {
                maximum = std::max(maximum, DP[up][j+element]);
            }
            DP[down][j] = maximum;
        }
        std::swap(up,down);
    }

    /*   
    for(int i = start; i <= end; ++i)
    {
        printf("%d:%d ", i, DP[up][i]);
    }
    */

    if(DP[up][offset] > 0)
    {
        printf("TAK\n");
        printf("%d", DP[up][offset]); // up because of last swap
    }
    else
    {
        /*
        int min = sum + 1;        
        for(int i = -sum + offset; i <= sum + offset; ++i)
        {
            std::cout << i - offset << ":" << DP[up][i] << " ";
            if(i != offset && (i-offset) > 1 && DP[up][i] > 0)      // TODO: not sure if that if is correct
            {                                                       // Check if it finds minimum height
                min = std::min(min, abs(i-offset));
            }
        }
        */
        // TOOD: przechodzi a nie powinno
        // find two closests heights (does it work?)
        int minimum =  blocks[1] - blocks[0];
        for(int i = 2; i < n; ++i)
        {
            minimum = std::min(minimum, blocks[i] - blocks[i-1]);
        }

        for(int i = start; i <= end; ++i)
        {
            if(DP[up][i] != abs(i - offset) && DP[up][i] > 1)
            {   
                minimum = std::min(minimum, abs(i - offset));
            }
        }
        
        printf("NIE\n");
        printf("%d", minimum); 
    }
    return 0;
}