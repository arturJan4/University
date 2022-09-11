#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

double function(double x)
{
    return x * x - 2 * cos(3*x + 1);
}

double bisection(double a, double b, int iterations)
{
    double mid = (a+b)/2;
    if(iterations == 0 || (function(mid) == 0))
        return mid;
    if(sgn(function(a)) == sgn(function(mid)))
        return bisection(mid,b,iterations-1);
    else
        return bisection(a,mid,iterations-1);
}

double errorApprox(double a, double b, int iterations)
{
    return pow(2,(-1)*(iterations+1)*(b-a));
}
int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);
    double a = 0, b = 1;
    int iterations = 1;
    // 0.18458647
    while(abs(errorApprox(a,b,iterations)) > pow(10,-5))
    {
        iterations++;
    }
    std::cout << "i:" << iterations << " eps: " << abs(errorApprox(a,b,iterations)) << endl;
    std::cout << bisection(a,b,iterations) << endl;
    
    std::cout << "===============\n";
    a = -1, b = 0;
    iterations = 1;
    // -0.75942615
    while(abs(errorApprox(a,b,iterations)) > pow(10,-5))
    {
        iterations++;
    }
    std::cout << "i:" << iterations << " eps: " << abs(errorApprox(a,b,iterations)) << endl;
    std::cout << bisection(a,b,iterations) << endl;
    return 0;
}
