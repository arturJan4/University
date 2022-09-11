#include <numeric>
#include <iostream>

int main()
{
    std::cout << "positive closest to 0 in float (denormalized):"
              << std::numeric_limits<float>::denorm_min()
              << "\n";
    std::cout << "positive closest to 0 in double (denormalized):"
              << std::numeric_limits<double>::denorm_min()
              << "\n";

    std::cout << "max for float:"
              << std::numeric_limits<float>::max()
              << "\n";
    std::cout << "max for double:"
              << std::numeric_limits<double>::max()
              << "\n";

    std::cout << "difference between 1 and smallest float > 1:"
              << std::numeric_limits<float>::epsilon()
              << "\n";
    std::cout << "difference between 1 and smallest float > 1:"
              << std::numeric_limits<double>::epsilon()
              << "\n";
    return 0;
}