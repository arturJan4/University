#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

double a_func(double x)
{
    return pow(x,3) - pow(x,2) + 1;
}
// pierwsza pochodna
double a_der(double x)
{
    return 3 * pow(x,2) - (2 * x);
}
// druga pochodna
double a_der2(double x)
{
    return 6 * x - 2;
}

double a_newton(double x0, int iterations)
{
    double xn = x0;
    for(int i = 0; i < iterations; ++i)
    {
        xn = xn - a_func(xn)/a_der(xn);
    }
    return xn;
}

double a_olver(double x0, int iterations)
{
    double xn = x0;
    for(int i = 0; i < iterations; ++i)
    {
        double f = a_func(xn);
        double d = a_der(xn);
        double d2= a_der2(xn);

        xn = xn - (f/d) - 0.5 * (d2/d) * pow((f/d),2);
    }
    return xn;
}

void runner(double exact, double x0)
{
    int iterations = 1;
    int iterationsO = 1;
    while(abs((exact - a_newton(x0,iterations))/exact) >= pow(10,-18))
    {
        ++iterations;
        if(iterations == 100)
            break;
    }
    while(abs((exact - a_olver(x0,iterationsO))/exact) >= pow(10,-18))
    {
        ++iterationsO;
        if(iterationsO == 100)
            break;
    }
    std::cout << "dokladnie: " << exact << endl << 
                 "przyblizone-newton(iteracji=" << iterations << "): " 
                 << a_newton(x0,iterations) << endl << 
                 "przyblizone-olver(iteracji=" << iterationsO << "): " 
                 << a_olver(x0,iterations) << endl;
}

// przybliżenie p
double approx_conver(double x0)
{
    for(int i = 1; i < 10; ++i)
    {
        double a = a_olver(x0, i); //n-2
        double b = a_olver(x0, i + 1); // n - 1
        double c = a_olver(x0, i + 2); // n
        double d = a_olver(x0, i + 3); // n + 1
        
        if(d/c == 1)
            break;

        double rate = log(abs((d-c)/(c-b))) / log(abs((c-b)/(b-a)));
        std::cout << "n: " << i + 2 << " p ~" << rate << endl;
    }
}

int main()
{
    std::cout << std::setprecision(16);

    // x≈-0.754877666246692760049508896358528691894606618
    // x^3 - x^2 + 1 = 0
    // f'(x) = 3x^2-2x
    // f''(x) = 6x - 2
    // to jest przykład dla którego dobrze działa
    // trzeba zrobić więcej testów, dla różnych funkcji, by mieć większą pewność
    runner(-0.7548776662466927, -10);
    approx_conver(3);
    return 0;
}
