#include <iostream>
#include <cmath>
#include <iomanip> 

# define M_PI           3.14159265358979323846  /* pi */

using namespace std;

double arcctg(double x)
{
    return(atan((double)1/x));
}

double a_podpunkt(double x)
{
    return 4 * pow(cos(x),2) - 3;
}

double a_podpunkt_popr(double x)
{
    return cos(3*x)/cos(x);
}

double b_podpunkt(double x)
{
    return (M_PI/2 - x - arcctg(x))/(pow(x,3));
}

double b_podpunkt_popr(double x, int howMany)
{
    double current = 1;
    double suma = 0;
    for(int i = 1; i <= howMany; i++)
    {
        double k = 2 * i + 1;
        double wyraz = (i % 2) ? -(current)/k : current/k;
        //std::cout << "znak:" << ((i%2) ? '-' : '+') << " current: " << current << " k: " << k << endl; 
        suma += wyraz;
        current = current * x * x;
    }
    return suma;
}

int main(int argc, char const *argv[])
{
    cout << setprecision(20);
    //a
    cout << "-PI/6: " << a_podpunkt(M_PI/(-6)) << " vs (popr): " << a_podpunkt_popr(M_PI/(-6)) << endl;
    cout << "PI/6: "  << a_podpunkt(M_PI/6)  << " vs (popr): " << a_podpunkt_popr(M_PI/6)  << endl;
    cout << "PI/6 + 20000PI: " << a_podpunkt(M_PI/6 + 10000 * 2 * M_PI) << " vs (popr): " << a_podpunkt_popr(M_PI/6 + 10000 * 2 * M_PI) << endl;
    //b
    cout << "====================b===============" << endl;

    cout << b_podpunkt(0) << endl;
    cout << b_podpunkt_popr(0,5) << endl;
    return 0;
}
