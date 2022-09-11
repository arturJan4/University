#include <iostream>
#include <fstream>
#include <random>
#include <unordered_map>

// could be made constexpr (but with more extra not that readable code)
std::unordered_map<char, double> freq_map{
        {'a', 14810},
        {'b', 2715},
        {'c', 4943},
        {'d', 7874},
        {'e', 21912},
        {'f', 4200},
        {'g', 3693},
        {'h', 10795},
        {'i', 13318},
        {'j', 188},
        {'k', 1257},
        {'l', 7253},
        {'m', 4761},
        {'n', 12666},
        {'o', 14003},
        {'p', 3316},
        {'q', 205},
        {'r', 10977},
        {'s', 11450},
        {'t', 16587},
        {'u', 5246},
        {'v', 2019},
        {'w', 3819},
        {'x', 315},
        {'y', 3853},
        {'z', 128},
};

int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " [text length] [filepath]\n";
        return EXIT_FAILURE;
    }

    // based on http://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
    // first 26 letters of english alphabet, starting from a to z
    std::discrete_distribution<int> letter_distr{freq_map['a'], freq_map['b'], freq_map['c'], freq_map['d'], freq_map['e'],
                                                freq_map['f'], freq_map['g'], freq_map['h'], freq_map['i'], freq_map['j'],
                                                freq_map['k'], freq_map['l'], freq_map['m'], freq_map['n'], freq_map['o'],
                                                freq_map['p'], freq_map['q'], freq_map['r'], freq_map['s'], freq_map['t'],
                                                freq_map['u'], freq_map['v'], freq_map['w'], freq_map['x'], freq_map['y'],
                                                freq_map['z']};


    std::mt19937 gen {std::random_device{}()};
    // throw coin 11 times
    std::binomial_distribution<> binomial_distribution(11, 0.5);

    std::ofstream output_file;
    output_file.open(argv[2]);
    if (output_file.fail())
    {
        std::cerr << "Failure opening the file: "  << argv[2] << "\n";
        return EXIT_FAILURE;
    }
    uint num_words = std::atoi(argv[1]);

    for (int i = 0; i < num_words; ++i)
    {
        uint num_letters = binomial_distribution(gen) + 1;

        for (int j = 0; j < num_letters; ++j)
        {
            output_file << static_cast<char>(letter_distr(gen) + 'a');
        }

        if (i != num_words - 1)
            output_file << " ";
    }

    output_file.close();

    return 0;
}
