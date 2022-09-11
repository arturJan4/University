#include <iostream>
#include <fstream>
#include <random>
#include <string_view>

int main()
{
    constexpr char uni_path[] = "uniform.csv";
    constexpr char bin_path[] = "binomial.csv";
    constexpr char nor_path[] = "normal.csv";

    std::ofstream uniform_file(uni_path);
    std::ofstream binomial_file(bin_path);
    std::ofstream normal_file(nor_path);

    std::mt19937 gen {std::random_device{}()};

    // from [a, b)
    std::uniform_real_distribution<double> uniform_distribution{1, 999};
    // 50 yes/no experiments with 0.1 success probability
    std::binomial_distribution<int> binomial_distribution {50, 0.1};
    std::normal_distribution<double> normal_distribution{5, 0.7};

    for (int i = 0; i < 1000; ++i)
    {
        uniform_file << uniform_distribution(gen) << "\n";
        binomial_file << binomial_distribution(gen) << "\n";
        normal_file << normal_distribution(gen) << "\n";
    }

    uniform_file.close();
    binomial_file.close();
    normal_file.close();
    return 0;
}