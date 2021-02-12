#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

// finding roots of a polynomal using bisection method
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

double function(double x)
{
    return x - 0.49;
}

double bisection(double a, double b, int iterations)
{
    double mid = (a+b)/2;
    if(iterations == 0)
        return mid;
    if(function(mid) == 0)
        return mid;
    if(sgn(function(a)) == sgn(function(mid)))
        return bisection(mid,b,iterations-1);
    else
        return bisection(a,mid,iterations-1);
}

//błąd 0.5 - > 1
int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);

    for(int i = 1; i <= 5; i++)
    {
        double eps = pow(2,(-1)*(i+1));
        double val = bisection(0,1,i);
        std::cout << i << ": " << val << endl;
        std::cout << i << ": " << eps << " oszacowanie" << endl;
        std::cout << i << ": bład: " << abs(val-0.49) << std::endl;
    }
    return 0;
}
