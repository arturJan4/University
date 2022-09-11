#include <iostream>
#include <string>
#include <regex>
#include <cassert>

/*
 * complex number:
 * consists of two real numbers (optional fractional part after '.')
 * separated by +/- (real part can also optionally be negative)
 * second number added with lower or uppercase 'i'
 * all of it surrounded by parentheses '()'
 */

bool regex(const std::string &text)
{
    std::regex complex_regex(
            "\\("             // must escape both the backlash and the parenthesis
            "-?"                 // real part can be negative
            "(0|([1-9]\\d*))"    // integer part
            "(\\.\\d+)?"         // optional fractional part
            "[-|\\+]"
            "(0|([1-9]\\d*))"    // integer part
            "(\\.\\d+)?"         // optional fractional part
            "[iI]"
            "\\)"
    );
    return std::regex_match(text, complex_regex);
}

void tests()
{
    // MATCHES
    assert(regex("(12+3I)"));
    assert(regex("(10+30I)"));
    assert(regex("(-12+3I)"));
    assert(regex("(-12.123+3.213i)"));
    assert(regex("(7.4-0.5i)"));
    assert(regex("(2+0.01i)"));

    // NOT MATCHES
    assert(!regex("(01+30I)"));
    assert(!regex("(10+03i)"));
    assert(!regex("3+4I"));
    assert(!regex("(3,14-2,72i)"));
    assert(!regex("(5.7i)"));
    assert(!regex("42"));
    assert(!regex("(42)"));
    assert(!regex("(12 +3I)"));
    assert(!regex("(12+ 3I)"));
    assert(!regex("( 12+ 3I)"));
    assert(!regex("(12+3I )"));
    assert(!regex("it's (12+3I)"));
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