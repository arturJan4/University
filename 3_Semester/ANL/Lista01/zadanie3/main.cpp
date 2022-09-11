#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

// float vs double comparison on recursive formula
int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);

    double* x = new double[51];

    x[0] = 1;
    x[1] = -((double)1/7);
    for(int i = 2; i <= 50; ++i)
    {
        x[i] = ((double)1/7)*(69 * x[i-1] + 10*x[i-2]);
    }

    float* y = new float[51];

    y[0] = 1;
    y[1] = -((float)1/7);
    for(int i = 2; i <= 50; ++i)
    {
        y[i] = ((float)1/7)*(69 * y[i-1] + 10*y[i-2]);
    }

    for(int i = 0; i <= 50; ++i)
    {
        cout << i << "d: " << x[i] << endl;
        cout << i << "f: " << y[i] << endl;
    }
    return 0;
}
