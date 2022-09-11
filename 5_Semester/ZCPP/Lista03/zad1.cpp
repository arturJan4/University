#include <numeric>
#include <iostream>

int main()
{
    std::cout << "max(long long int): " << std::numeric_limits<long long int>::max() << "\n";
    std::cout << "min(long long int): " << std::numeric_limits<long long int>::min() << "\n";
    std::cout << "digits(long long int) - binary: "
              << std::numeric_limits<long long int>::digits << " (+1 for sign) \n";
    std::cout << "digits10(long long int) - decimal: "
              << std::numeric_limits<long long int>::digits10 + 1 << "\n";


    return 0;
}