#include <iostream>
#include <complex>
#include <vector>
#include <numeric>
#include <functional>

std::complex<double> calc_polynomal(const std::vector<std::complex<double>>& coeffs, std::complex<double> at)
{
    std::complex<double> power = 1;

    return std::accumulate(
        coeffs.cbegin(),
        coeffs.cend(),
        std::complex<double>(),
        [&](std::complex<double> res, std::complex<double> cfc) mutable {
            res += cfc * power;
            power *= at;
            return res;
        }
    );
}

void test()
{
    std::vector<std::complex<double>> coeffs;
    // https://www.wolframalpha.com/input/?i=%283+%2B+4i%29x%5E2+%2B+%283%2B3i%29x+%2B+1+at+x+%3D+2+%2B+i
    coeffs.emplace_back(std::complex<double>(1.0, 0.0));
    coeffs.emplace_back(std::complex<double>(3.0, 3.0));
    coeffs.emplace_back(std::complex<double>(3.0, 4.0));

    auto at = std::complex<double>(2.0, 1);

    std::cout << calc_polynomal(coeffs, at);
}

int main()
{
    test();
    return 0;
}
