#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

double funkcjad(double x)
{
    return 12120 * ((double)(x - sin(x)))/pow(x,3);
}

float funkcjaf(float x)
{
    return 12120 * ((float)(x - sin(x)))/pow(x,3);
}

// float vs double approximation errors
int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);

    double x;

    for(int i = 0; i <= 20; ++i)
    {
        cout << i << "float: " << funkcjaf(pow(10,-(i))) << endl;
        cout << i << "double: " << funkcjad(pow(10,-(i))) << endl;
    }
    return 0;
}
