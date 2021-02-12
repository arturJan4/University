#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

// integrals using recursive formula
int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);
    double *I = new double[21];
    I[0] = log((double)2021/2020);
    for(int i = 1; i <= 20; ++i)
    {
        I[i] = (double)1.0/i - 2020 * I[i-1];
        std::cout << i << ": " << I[i] << endl;
    }
    return 0;
}
