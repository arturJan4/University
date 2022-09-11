#include <iostream>
#include <fstream>
#include <iomanip>

const uint ALPHABET_SIZE = 26;

int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Pass filename to the executable\n";
        return -1;
    }

    std::ifstream file(argv[1]);
    if(!file.good())
    {
        std::cout << "Wrong file error\n";
        return -1;
    }
    std::stringstream buf;

    buf << file.rdbuf();
    std::string input = buf.str();

    uint64_t letters_all = 0;
    uint64_t letters_freq[ALPHABET_SIZE] = {};

    for (const auto& letter : input)
    {
        if (letter >= 'a' && letter <= 'z')
        {
            letters_freq[(int)letter - (int)'a']++;
            letters_all++;
        }
        else if (letter >= 'A' && letter <= 'Z')
        {
            letters_freq[(int)letter - (int)'A']++;
            letters_all++;
        }
    }

    // Draw histogram

    const uint hist_points = 50;
    const char hist_letter = '=';
    const uint end_point = 25;
    for (char i = 'a'; i <= 'z'; i++)
    {
        double freq = (double)letters_freq[(int)i-(int)'a']/letters_all * 100;
        if (freq >= 10.0)
            std::cout << std::setprecision(2);
        else
            std::cout << std::setprecision(3);

        std::cout << i << "(" << std::fixed << freq << "%):|";

        double imm_val = (double)end_point/hist_points;
        while (freq > imm_val)
        {
            std::cout << hist_letter;
            freq -= imm_val;
        }

        std::cout << "\n";
    }

    std::cout << "           ";
    for (int i = 0; i < hist_points; i++)
    {
        if (((i+1) % (int)(hist_points/4+1)) == (int)(hist_points/4))
            std::cout << "*";
        else
            std::cout << "=";
    }
    std::cout << end_point << "%\n";
}

