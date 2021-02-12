#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

// derivative approximation formula comparision
int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);

    double h = pow(10,-5);
    //cout << exp(1);
    
    // e^(2x) , x = 0.5, = e
    for(int i = 1; i <= 20; ++i)
    {
        double x = 0.5;
        x *= 2;
        double h = pow(10,-i);
        double wynik = (exp(x+h) - exp(x))/h;
        double wynikd = (exp(x+h) - exp(x-h))/(2*h);
        std::cout << i << ": " << wynik << " vs (dokladniej) " << wynikd << endl;
    }
    cout << "========================\n\n\n\n";
    
    // sinx w x = 2 (cos2) = -0.4161
    for(int i = 1; i <= 20; ++i)
    {
        double x = 2;
        double h = pow(10,-i);
        double wynik = (sin(x+h) - sin(x))/h;
        double wynikd = (sin(x + h) - sin(x-h))/(2*h);
        std::cout << i << ": " << wynik << " vs (dokladniej) " << wynikd << endl;
    }

    cout << "========================\n\n\n\n";

    // 12lnx w x = 12. = 1
    for(int i = 1; i <= 20; ++i)
    {
        double x = 12;
        double h = pow(10,-i);
        double wynik = (12*log(x+h) - 12*log(x))/h;
        double wynikd = (12*log(x + h) - 12*log(x-h))/(2*h);
        std::cout << i << ": " << wynik << " vs (dokladniej) " << wynikd << endl;
    }
    return 0;
}
