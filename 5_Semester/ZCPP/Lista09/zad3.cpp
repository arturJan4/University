#include <iostream>
#include <string>
#include <regex>
#include <cassert>

/*
 * city name:
 * without diacritics
 * sequence of words, where a word starts from upper letter and lower letter follow
 * words may be separated by whitespaces (any amount)
 * or by '-' and then there are no whitespaces around
 */

bool regex(const std::string &text)
{
    std::regex cityname_regex(
            "[A-Z][a-z]+"                      // word (one uppercase then lowercase letters)
            "((\\s+|-)([A-Z][a-z]*))*"            // zero or more words prefixed with whitespace or hyphen
    );
    return std::regex_match(text, cityname_regex);
}

void tests()
{
    // MATCHES
    assert(regex("Wroclaw"));
    assert(regex("Bielsko-Biala"));
    assert(regex("Tarnowskie Gory"));
    assert(regex("Zielona    Gora"));


    // NOT MATCHES
    assert(!regex("WARSZAWA"));
    assert(!regex("WARSZAWA  "));
    assert(!regex("Zle mieso"));
    assert(!regex("Zimna-Wodka-07"));
    assert(!regex("Zielona    Gora  "));
    assert(!regex(" Zielona    Gora"));
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