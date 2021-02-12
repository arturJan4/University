#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;
//quadratic roots numerically

double szkolna(double a, double b, double c)
{
    double x1, x2;
    double sq = sqrt(b*b - 4 * a *c);
    x1 = (-b - sq)/(2*a);
    x2 = (-b + sq)/(2*a);
    std::cout << "x1:" << x1 << " x2: " << x2 << endl;
}

double nasza(double a, double b, double c)
{
    double x1, x2;
    double sq = sqrt(b*b - 4 * a *c);
    if(b > 0)
        x1 = (-b - sq)/(2*a);
    else
        x1 = (-b + sq)/(2*a);
    x2 = c/(a * x1);
    std::cout << "x1:" << x1 << " x2: " << x2 << endl;
}

int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);
    double a,b,c;

    a = 1, b = 6, c = 9;
    szkolna(a,b,c);
    nasza(a,b,c);
    
    std::cout << "===================\n";
    // ac ~ 0 b->inf, -1*(10^6), -1*(10^{-6})
    a = pow(10,-3), b = pow(10,3), c = pow(10,-3);

    szkolna(a,b,c);
    nasza(a,b,c);

    std::cout << "===================\n";
    // ac ~ 0 b->-inf, 1*(10^{-6} 1*(10^{6})
    a = pow(10,-3), b = (-1.0) * pow(10,3), c = pow(10,-3);
    szkolna(a,b,c);
    nasza(a,b,c);
    return 0;
}
