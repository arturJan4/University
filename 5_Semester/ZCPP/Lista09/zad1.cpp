#include <iostream>
#include <string>
#include <regex>
#include <cassert>

/*
 * time:
 * separated by ':'
 * always display two digits
 * hour - 0-23 -> ([01][0-9]|2[0-3])
 * minutes - 0-59 -> ([0-5][0-9])
 * seconds - as above but optional
 */

bool regex(const std::string &text)
{
    std::regex time_regex(
            "([01][0-9]|2[0-3])"
            ":"
            "([0-5][0-9])"
            "(:[0-5][0-9])?"
    );
    return std::regex_match(text, time_regex);
}

void tests()
{
    // MATCHES
    assert(regex("14:17"));
    assert(regex("00:00"));
    assert(regex("00:00:00"));
    assert(regex("00:09"));
    assert(regex("09:15"));
    assert(regex("23:37:08"));

    // NOT MATCHES
    assert(!regex("0:00"));
    assert(!regex("14.16"));
    assert(!regex("24.00"));
    assert(!regex("19:5"));
    assert(!regex("21:32:07,10"));
    assert(!regex("it is 14:17"));
}

int main()
{
    std::string input;
    tests();

    while (getline(std::cin, input)) {
        std::cout << input;

        if (regex(input))
            std::cout << " matched!";
        else
            std::cout << " did not match!";

        std::cout << "\n";
    }

    return 0;
}