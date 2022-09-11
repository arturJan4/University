#include <iostream>
#include <set>

using string_set = std::set<std::string>;

int main()
{
    const string_set example{"jeden", "dwa", "trzy", "cztery"};

    for (const auto &str : example) {
        std::cout << str << " ";
    }

    return 0;
}