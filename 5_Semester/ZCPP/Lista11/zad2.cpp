#include <iostream>
#include <iomanip>

void print_examples()
{
    // decimal
    std::cout << 1 << "\n";
    std::cout << -42 << "\n";

    // floating
    std::cout << 0.0 << "\n";
    std::cout << 0.42 << "\n";
    std::cout << -221.423 << "\n";

    // money
    std::cout << std::showbase;
    std::cout << std::put_money(0.42) << "\n";
    std::cout << std::put_money(100.42) << "\n";
    std::cout << std::put_money(1337) << "\n";
    std::cout << std::put_money(100000000) << "\n";
}

int main()
{
    std::cout << "===========     english locale     ===========\n";
    std::cout.imbue(std::locale("en_US.UTF-8"));
    print_examples();

    std::cout << "===========     polish locale      ===========\n";
    std::cout.imbue(std::locale("pl_PL.UTF-8"));
    print_examples();

    std::cout << "===========     japanease locale   ===========\n";
    std::cout.imbue(std::locale("ja_JP.UTF-8"));
    print_examples();

    return 0;
}