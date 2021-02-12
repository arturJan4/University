#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

// base a, logarithm of x
double logarithm(double x, double a)
{
    return log2(x)/log2(a);
}

double a_podpunkt(double x)
{
    return pow(x,3) - sqrt(pow(x,6) + 2020);
}

double a_podpunkt_popr(double x)
{
    return -2020/(pow(x,3) + sqrt(pow(x,6) + 2020));
}

double b_podpunkt(double x)
{
    return pow(x,-4) * (cos(x) - 1 + (pow(x,2)/2));
}

double b_podpunkt_popr(double x, int dokl)
{
    double currentx = 1;
    double fact = 24;
    double wynik = (currentx)/fact;

    for(int i = 6; i < 4 + dokl*2; i += 2)
    {
        fact = fact * i * (i-1);
        currentx = pow(x,i-4);
        if(i % 4 == 0)
            wynik += currentx/fact; 
        else
            wynik -= currentx/fact;
    }
    return wynik;
}

double c_podpunkt(double x)
{
    return logarithm(x,5) - 6;
}

double c_podpunkt_popr(double x)
{
    return logarithm(x/(pow(5,6)),5);
}

// loss of precision 
int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);

    /* -> 0
    for(int i = 500; i <= 2000; i += 100)
    {
        std::cout << i << ": " << a_podpunkt(i) << " vs " << a_podpunkt_popr(i) << endl;
    }
    */
    /* -> 1/24
    cout << "====================b===============" << endl;
    cout << b_podpunkt(0.00000001) << endl;
    cout << b_podpunkt_popr(0.00000001,3) << endl;
    for(int i = 1; i <= 10; i++)
    {
        std::cout << "10^{" << -i << "}: " << b_podpunkt(pow(10,-i)) << " vs " << b_podpunkt_popr(pow(10,-i), 3) << endl;
    }
    */
    /* -> 0
    cout << "====================c===============" << endl;
    double x = pow(5,6);
    cout << c_podpunkt(x) << endl;
    cout << c_podpunkt_popr(x) << endl;

    x += 0.0000001;
    cout << c_podpunkt(x) << endl;
    cout << c_podpunkt_popr(x) << endl;
    */
    return 0;
}
