#include <iostream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <numeric>
#include <cmath>

// calculate the average of numbers in a vector
template <typename T>
T average_vector(const std::vector<T> &vec)
{
    if (vec.empty())
        return 0;

    auto const count = static_cast<double>(vec.size());
    return std::reduce(vec.begin(), vec.end()) / count;
}

// calculate standard deviation of numbers in a vector
template <typename T>
T stddev_vector(const std::vector<T> &vec)
{
    if (vec.empty())
        return 0;

    auto const count = static_cast<double>(vec.size());
    auto const average = average_vector(vec);
    auto const sum = std::accumulate(vec.begin(), vec.end(), 0.0,
            [&] (T acc, T elem) {return acc += std::pow((elem - average), 2);});

    return std::sqrt(sum/count);
}

int main()
{
    std::vector<double> numbers;

    std::istream_iterator<double> doubleReader(std::cin);
    std::istream_iterator<double> doubleReaderEOF;
    // read from stdin using stream iterator
    while(doubleReader != doubleReaderEOF)
    {
        numbers.emplace_back(*doubleReader);
        ++doubleReader;
    }

    // save and set new precision value
    std::streamsize ss = std::cout.precision();
    std::cout << std::fixed << std::setprecision(3);
    /*
    for (double d : numbers)
    {
        std::cout << d;
    }
    */
    std::cout << "average: " << average_vector(numbers) << "\n";
    std::cout << "stddev:  " << stddev_vector(numbers) << "\n";


    std::cout << std::setprecision(ss);
    return 0;
}
