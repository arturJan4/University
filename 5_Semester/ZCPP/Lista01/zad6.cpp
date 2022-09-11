#include <iostream>
#include <cmath>
#include <complex>

const double precision = 0.000001;

bool close_enough(double expected, double actual, double precision)
{
    return abs(actual - expected) < precision;
}

void delta_calc(double a, double b, double c)
{
    if (a == 0)
        throw std::invalid_argument(" a !=0 for quadratic equations");

    if (double delta = b*b - (4.0 * a * c); close_enough(0, delta, precision))
    {
        double zero = -b / (2.0 * a);

        std::cout << "double root: " << zero << "\n";
    }
    else if (delta > 0)
    {
        double x0 = (-b - sqrt(delta))/ (2.0 * a);
        double x1 = (-b + sqrt(delta))/ (2.0 * a);

        std::cout << "1st root: " << x0 << ", 2nd root: " << x1 << "\n";
    }
    else
    {
        double real_part = -b / (2.0 * a);
        double img_part = (sqrt(-delta))/(2.0 * a);

        std::complex<double> x0  = real_part;
        std::complex<double> x1  = real_part;

        x0.imag(img_part);
        x1.imag(-img_part);

        std::cout << "1st (complex) root: " << x0 << ", 2nd (complex) root: " << x1 << "\n";
    }
}

int main()
{
    // x^2 - 3x -> 0, 3
    delta_calc(1, -3, 0);

    // 5x^2 + 2x + 1 -> -0.2 ± 0.4i
    delta_calc(5, 2, 1);

    // y = (x-1)^2 = x^2 - 2x + 1
    delta_calc(1, -2, 1);

    return 0;
}
