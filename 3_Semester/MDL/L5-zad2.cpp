#include <algorithm> 
#include <iostream> 
#include <string> 
 
using namespace std;
 
int main() 
{ 
    int counter = 0;
    for(int i = 1; i <= 800; ++i)
    {
        if(((i % 6 == 0) || (i%8 == 0)) && (i % 7 != 0))
            counter++;
    }
    std::cout << counter;
    return 0; 
} 