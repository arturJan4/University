#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);
    // pi approximation using Leibinitz (infinite sum)
    double sum = 0;
    for(int i = 0; i < 20000; ++i)
    {
        double numerator = (i%2) ? -1 : 1;
        sum += (numerator * 4)/(2*i + 1);
    }
    std::cout << sum << endl;

    // ver 2
    double sum2 = 0;
    for(int i = 0; i < 20000; ++i)
    {
        double numerator = (i%2) ? -1 : 1;
        sum2 += (numerator)/(2*i + 1);
    }
    std::cout << 4 * sum2 <<endl;
    return 0;
}
