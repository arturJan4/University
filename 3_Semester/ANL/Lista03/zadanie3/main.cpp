#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;
// Cardano-Tartaglii cube root formula (with errors)
double Cardano(double q, double r)
{
    double x;
    double sq = sqrt(pow(q,3) + pow(r,2));
    x = cbrt(r + sq) + cbrt(r - sq);
    std::cout << "x:" << x << endl;
}

double Cardano_popr(double q, double r)
{
    double x;
    double cb = cbrt(r + sqrt(pow(q,3) + pow(r,2)));
    x = (2 * r)/(pow(cb,2) + pow(1/cb,2) * pow(q,2) + q);
    std::cout << "x:" << x << endl;
}

int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);
    cout << " r == q " << endl;
    Cardano(10000,10000);
    Cardano_popr(10000,10000);
    
    cout << " q >> r " << endl;
    //0.031446516433224877
    Cardano(424,20);
    Cardano_popr(424,20);
    
    //0.0000000066666667
    Cardano(10000,0.0001);
    Cardano_popr(10000,0.0001);

    cout << " q << r  q ~ 0" << endl;
    //12.599202561943471808
    Cardano(0.0001, 1000);
    Cardano_popr(0.0001, 1000);     
    return 0;
}
