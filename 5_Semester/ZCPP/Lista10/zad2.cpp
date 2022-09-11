#include <iostream>
#include <numeric>
#include <cassert>
#include <vector>
#include <fstream>
#include <iterator>

// Euler's totient
// count of positive numbers less then or equal n (k <= n),
// which are coprime to n (gcd is 1)
uint64_t totient(uint64_t n)
{
    uint64_t sum = 0;

    for (uint64_t k = 1; k <= n; ++k)
    {
        if(std::gcd(k, n) == 1)
            ++sum;
    }

    return sum;
}

void test_totient()
{
    assert(totient(1) == 1);
    assert(totient(2) == 1);
    assert(totient(3) == 2);
    assert(totient(11) == 10);
    assert(totient(12) == 4);
}

int main()
{
    test_totient();

    uint64_t k;
    std::cin >> k;

    // populate vector with k totient values
    std::vector<uint64_t> totient_vals;
    for(int i = 1; (i <= k || i < 1); ++i)
        totient_vals.emplace_back(totient(i));

    // try to open the file
    std::string filepath = "phi.txt";
    std::ofstream output_file;
    output_file.open(filepath);
    if (output_file.fail())
    {
        std::cerr << "Failure opening the file: "  << filepath << "\n";
        return EXIT_FAILURE;
    }

    // write totient values to the file
    std::copy(totient_vals.cbegin(),
              totient_vals.cend(),
              std::ostream_iterator<uint64_t>(output_file, "; "));

    return 0;
}
