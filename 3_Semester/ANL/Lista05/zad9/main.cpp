#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

double p_finder(double r0, double r1, double r2, double r3)
{
    int p = 1;
    double iloczynL = r2;
    double iloczynR = r1;

    double left = (r3/iloczynL);
    double right = (r2/iloczynR);
    
    while(abs(left - right) > pow(10,-1))
    {
        iloczynL *= r2;
        iloczynR *= r1;
        left = (r3/iloczynL);
        right = (r2/iloczynR);
        ++p;
        if(p == 100 )
        {
            std::cout << left << " " << right;
            return -1;
        }   
    }
    return p;
}

int main(int argc, char const *argv[])
{
    std::cout << "r: " << p_finder(0.763907023, 0.543852762, 0.196247370, 0.009220859) << endl;
    std::cout << "g: " << p_finder(0.605426053, 0.055322784, 0.004819076, 0.000399783) << endl;

    return 0;
}
