#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

double original_func(double x)
{
    return 4040 * (sqrt(pow(x,11) + 1) - 1)/(pow(x,11));
}

// less errors - same function
double corr_func(double x)
{
    return 4040 * 1/(sqrt(pow(x,11) + 1) + 1);
}

int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);
    // -> 2020
    cout << original_func(0.001) << endl;
    cout << corr_func(0.001) << endl;

    cout << "======================";

    for(int i = 1; i <= 10; i++)
    {
        std::cout << "10^{" << -i << "}: " << original_func(pow(10,-i)) << " vs " << corr_func(pow(10,-i)) << endl;
    }
    return 0;
}
