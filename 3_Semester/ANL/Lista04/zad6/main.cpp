#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

// 1/sqrt(a) iteratively
double iterativeNewton(double x0, double a, int iterations)
{
    double xn = x0;
    double xn1 = 0;
    for(int i = 0; i < iterations; ++i)
    {
        double diff = 3 - a * xn * xn;
        xn1 = diff * xn * 1.0/2;
        xn = xn1;
    }
    return xn;
}

double inversesquare(double a)
{
    return 1/(sqrt(a));
}

void runner(double a, double x0)
{
    int iterations = 1;
    while(abs(inversesquare(a) - iterativeNewton(x0,a,iterations)) >= pow(10,-18))
    {
        ++iterations;
        if(iterations == 100)
            break;
    }
    std::cout << "dokladnie: " << inversesquare(a) << 
                 " przyblizone(iteracji=" << iterations << "): " 
                 << iterativeNewton(x0,a,iterations) << endl;
}

int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);
    double a = 13321;
    double x0 = (sqrt(5/(3*a)) - sqrt(1/(3*a)))/2;
    runner(a,x0);

    a = 2;
    x0 = (sqrt(5/(3*a)) - sqrt(1/(3*a)))/2; 
    runner(a,x0);
    
    return 0;
}
