#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

double myatan(double x)
{
    if(x > 0)
        return 2 * atan(1) - atan(1/x);
    else
        return -2 * atan(1) - atan(1/x);
}

int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);

    // arctan using trig indentities
    //atan
    //tan

    std::cout << "atan(3): " << atan(3) 
              << " vs (my): " << myatan(3) << endl;

    std::cout << "atan(3): " << atan(30) 
              << " vs (my): " << myatan(30) << endl;

    std::cout << "atan(3): " << atan(-30) 
              << " vs (my): " << myatan(-30) << endl;

    return 0;
}
