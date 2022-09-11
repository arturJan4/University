#include <iostream>
#include <iomanip>
#include <ctime>

void print_date()
{
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    std::cout << std::put_time(&tm, "%c %Z") << "\n";
}

int main()
{
    std::cout << "===========     english locale     ===========\n";
    std::cout.imbue(std::locale("en_US.UTF-8"));
    print_date();

    std::cout << "===========     polish locale      ===========\n";
    std::cout.imbue(std::locale("pl_PL.UTF-8"));
    print_date();

    std::cout << "===========     japanease locale   ===========\n";
    std::cout.imbue(std::locale("ja_JP.UTF-8"));
    print_date();

    return 0;
}