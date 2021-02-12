#include <iostream>
#include <cmath>
#include <iomanip> 
# define M_PI           3.14159265358979323846  /* pi */

using namespace std;



double pi_appr(double howMany)
{
    double x = 2;
    for(int i = 2; i <= howMany; ++i)
    {
        double eps = pow(x/(pow(2,i-1)),2);
        double first = sqrt(1-eps);
        double second = sqrt(2 * (1 - first));
        x = pow(2,i-1) * second;
    }
    return x;
}

double pi_appr_corr(double howMany)
{
    double x = 2;
    for(int i = 2; i <= howMany; ++i)
    {
        double eps = pow(x/(pow(2,i-1)),2);
        x = pow(2,i-1) * sqrt(2 * eps/(1+sqrt(1-eps)));
    }
    return x;
}

// series that converges to PI
int main(int argc, char const *argv[])
{
    cout << setprecision(20);
    cout << M_PI << endl;
    for(int i = 20; i < 40; ++i)
    {
        cout << i << ": " << pi_appr(i) << " vs: " << pi_appr_corr(i) << endl;
    }

    cout << pi_appr_corr(400) << endl;
    cout << pi_appr_corr(500) << endl;
    cout << pi_appr_corr(600) << endl;
    return 0;
}
