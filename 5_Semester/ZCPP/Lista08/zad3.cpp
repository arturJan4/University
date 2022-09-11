#include <iostream>
#include <fstream>
#include <complex>
#include <vector>

std::complex<double> zeta_approx(std::complex<double> z, uint iterations)
{
    // assumes real > 1 to be convergent

    if (iterations < 1)
        throw std::invalid_argument("dzeta needs at least one iteration");

    std::complex<double> result = 0.0;
    // identity element of multiplication is 1
    for (int i = 1; i < iterations; ++i)
    {
        auto n = static_cast<double>(i);
        result += std::pow(1.0 / n, z);
    }

    return result;
}

// using Dirichlet series
// https://en.wikipedia.org/wiki/Riemann_zeta_function
std::complex<double> zeta_approx_2(std::complex<double> z, uint iterations)
{
    // assumes real > 0 to be convergent
    if (iterations < 1)
        throw std::invalid_argument("dzeta needs at least one iteration");

    std::complex<double> result = 1.0 / (z - 1.0);

    std::complex<double> sum = 0;
    for (int i = 1; i < iterations; ++i)
    {
        auto n = static_cast<double>(i);
        sum += (n / std::pow(n+1, z)) - ((n-z) / std::pow(n, z));
    }

    return result * sum;
}


void test_zetta(double real, double imag, uint precision)
{
    std::complex<double> num(real, imag);
    std::complex<double> zeta = zeta_approx(num, precision);
    std::complex<double> zeta2 = zeta_approx_2(num, precision);


    std::cout << "zeta (" << num.real() << "+" << num.imag() << "i): " <<zeta.real() << " + " << zeta.imag() << "i\n";
    std::cout << "zeta2(" << num.real() << "+" << num.imag() << "i): " <<zeta2.real() << " + " << zeta2.imag() << "i\n";

}

std::vector<std::pair<double, std::complex<double>>> calc_critical_strip(double start, double end, double step, uint iterations)
{
    std::vector<std::pair<double, std::complex<double>>> val_points;
    int num_points = std::floor((end - start) / step);
    val_points.reserve(num_points);

    double val = start;
    while(val <= end)
    {
        auto result = zeta_approx_2({0.5, val}, iterations);
        val_points.emplace_back(val, result);

        val += step;
    }

    return val_points;
}

int main()
{
    std::string filepath = "results.csv";

    test_zetta(1.2, 2, 1000000);
    // std::complex<double> temp(1.2, 2);
    // std::riemann_zeta(temp);
    // according to wolframalpha.com
    // expected: 0.662651- 0.351463i

    test_zetta(5, 3, 1000000);
    // 0.980428670505787441767956 - 0.025411901380637479902748i

    std::ofstream output_file;
    output_file.open(filepath);
    if (output_file.fail())
    {
        std::cerr << "Failure opening the file: "  << filepath << "\n";
        return EXIT_FAILURE;
    }

    auto points = calc_critical_strip(-50, 50, 0.1, 10000);

    for (auto [val, p] : points)
    {
        output_file << val << "; " << p.real() << "; " << p.imag() << "\n";
    }

    output_file.close();

    return 0;
}
