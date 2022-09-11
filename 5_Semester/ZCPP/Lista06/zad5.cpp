#include <iostream>

int main()
{
    // all permutations of a string;
    std::string input = "start";
    int counter = 1;

    // next_permutation returns next string lexicographically
    // so we sort to start at "lowest" position
    std::sort(input.begin(), input.end());

    std::cout << input << "\n";

    while(next_permutation(input.begin(), input.end()))
    {
        std::cout << input << "\n";
        counter++;
    }

    std::cout << counter; // len(str)!
}