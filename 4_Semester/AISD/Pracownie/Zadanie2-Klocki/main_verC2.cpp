#include <stdio.h>
#include <algorithm>
#include <vector>

int main()
{
    // TODO cin, cout -> scanf, printf
    // TODO MLE optimizations -> solve from right?
    // TODO readline ?
    
    int n;
    scanf("%d", &n);
    int *blocks = (int*)malloc(n * sizeof(int)); // store heights
  
    int sum = 0;
    for(int i = 0; i < n; ++i)
    {
        int temp;
        scanf("%d", &temp);
        blocks[i] = temp;
        sum += temp;
    }

    int *DP = (int*)(malloc(sizeof(int) * (2 * sum + 1)));
    std::fill_n(DP, 2 * sum + 1, -1); // fill with -1
    
    int offset = sum;
    DP[offset] = 0; // base case
    for(int i = 0; i < n; ++i)
    {
        int element = blocks[i];
        //std::cout << element << "\n";
        for(int j = sum + offset; j >= -sum + offset; --j)
        {   
            DP[j] = DP[j];
            if(j - element >= 0 && DP[j-element] != -1)
            {
                DP[j] = std::max(DP[j], DP[j-element] + element);
            }
            if(j + element <= sum + offset)
            {
                DP[j] = std::max(DP[j], DP[j+element]);
            }
        }
    }

    if(DP[offset] > 0)
    {
        printf("TAK\n");
        printf("%d", DP[offset]); // up because of last swap
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
        // find two closests heights (does it work?)
        std::sort(blocks, blocks + n);
        int minimum =  blocks[1] - blocks[0];
        for(int i = 2; i < n; ++i)
        {
            minimum = std::min(minimum, blocks[i] - blocks[i-1]);
        }
        printf("NIE\n");
        printf("%d", minimum); 
    }
    return 0;
}