#include <iostream>
#include <random>
#include <array>


template <typename T, size_t n>
void shuffle_elements(T (&arr)[n])
{
    static std::mt19937 gen {std::random_device{}()};

    size_t arr_size = sizeof(arr)/sizeof(arr[0]);

    std::uniform_int_distribution<size_t> uniform_dist{0, arr_size};
    for (size_t i = 0; i < arr_size-1; ++i)
    {
        // to keep uniformity (analogical to std's shuffle)
        uniform_dist = std::uniform_int_distribution<size_t>{0, arr_size-1};
        size_t idx = uniform_dist(gen);
        std::swap(arr[i], arr[idx]);
    }
}


int main()
{
    std::string strs[] = {"a", "b", "c", "dd", "ee"};
    int numbers[] = {0, 1, 2, 3, 4, 5};

    shuffle_elements(strs);
    for (auto& elem : strs)
        std::cout << elem << " ";
    std::cout << "\n";

    shuffle_elements(numbers);
    for (auto& elem : numbers)
        std::cout << elem << " ";
    std::cout << "\n";

    return 0;
}
