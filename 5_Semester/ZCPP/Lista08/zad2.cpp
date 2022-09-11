#include <iostream>
#include <complex>

std::complex<double> gamma_approx(std::complex<double> z, uint iterations)
{
    std::complex<double> result = 1.0 / z;

    // identity element of multiplication is 1
    for (int i = 1; i < iterations; ++i)
    {
        auto n = static_cast<double>(i);
        std::complex<double> num = std::pow(1.0 + 1.0/n, z);
        std::complex<double> den = 1.0 + z / n;
        result *= (num / den);
    }

    return result;
}

constexpr double EULER_MASCHERONI = 0.5772156649;

std::complex<double> inv_gamma_approx(std::complex<double> z, uint iterations)
{
    std::complex<double> result = z * std::exp(EULER_MASCHERONI * z);

    // identity element of multiplication is 1
    for (int i = 1; i < iterations; ++i)
    {
        auto n = static_cast<double>(i);
        std::complex<double> zn = z / n;
        std::complex<double> left = (1.0 + zn);
        std::complex<double> right = std::exp(-zn);

        result *= left * right;
    }

    return result;
}

void test_gamma(double real, double imag, uint precision)
{
    std::complex<double> num(real, imag);
    std::complex<double> gamma = gamma_approx(num, precision);
    std::complex<double> inv = inv_gamma_approx(num, precision);


    std::cout << "gamma(" << num.real() << "+" << num.imag() << "i): " << gamma.real() << " + " << gamma.imag() << "i\n";
    std::cout << "inv_g(" << num.real() << "+" << num.imag() << "i): " << inv.real() << " + " << inv.imag() << "i\n";
}

int main()
{
    test_gamma(1., 2, 1000000);
    // based on: keisan.casio.com
    // expected: gamma (gamma)         -> 0.151904002 + 0.0198048801i
    // expected: inv (Reciprocal gamma)-> 6.473073626 - 0.8439438407i


    return 0;
}
