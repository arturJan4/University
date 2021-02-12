#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

// float vs double approximation errors
int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(20);

    double x = 0.001;
    double pierwiastek = sqrt(pow(x,11) + 1);
    double a = pierwiastek - 1; // dazy do 0
    cout << a << endl;
    cout << 4040 * a/pow(x,11) << endl;

    //przekształcony wzor
    std::cout << pierwiastek + 1 << endl;
    std::cout << 4040 * 1/(pierwiastek + 1);

    return 0;
}
