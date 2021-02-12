#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;
// Newton's method
// 1/R iteratively
double approx(double x0, double R, int iterations)
{
    double xn = x0;
    for(int i = 0; i < iterations; ++i)
    {
        xn = x0 * (2-x0*R);
        x0 = xn;
    }
    return xn;
}

double inverse(double R)
{
    return 1.0/R;
}

void runner(double R, double x0)
{
    int iterations = 1;
    while(abs(inverse(R) - approx(x0,R,iterations)) >= pow(10,-18))
    {
        ++iterations;
        if(iterations == 100)
            break;
    }
    std::cout << "dokladnie: " << inverse(R) << 
                 " przyblizone(iteracji=" << iterations << "): " 
                 << approx(x0,R,iterations) << endl;
}
int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);
    double R = 1.0/2;
    int iterations = 35;
    //double x0 = 1.0/R;
    double x0 = 0.000001;
    runner(R,x0);

    R = 1.0/sqrt(2);
    runner(R,x0);
    
    R = 1.0/pow(42,2);
    runner(R,x0);

    R = 123456;
    runner(R,x0);

    runner(R,x0);
    x0 = 10.0/R;
    runner(R,x0);
    return 0;
}
