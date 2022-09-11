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

    int **DP = (int**)malloc(sizeof(int*) * 2);   // store 2D DP solution (only need last row)
    for(int i = 0; i < 2; ++i)
    {
        DP[i] = (int*)malloc(sizeof(int) * (2 * sum + 1)); // store [-sum, ..., 0, ..., sum]
        std::fill_n(DP[i], 2 * sum + 1, -1); // fill with -1
    } 
    int up = 0, down = 1;
    int offset = sum;
    DP[0][offset] = 0; // base case
    for(int i = 0; i < n; ++i)
    {
        int element = blocks[i];
        //std::cout << element << "\n";
        for(int j = -sum + offset; j <= sum + offset; ++j)
        {   
            DP[down][j] = DP[up][j];
            if(j - element >= 0 && DP[up][j-element] != -1)
            {
                DP[down][j] = std::max(DP[down][j], DP[up][j-element] + element);
            }
            if(j + element <= sum + offset)
            {
                DP[down][j] = std::max(DP[down][j], DP[up][j+element]);
            }
        }
        std::swap(up,down);
    }

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