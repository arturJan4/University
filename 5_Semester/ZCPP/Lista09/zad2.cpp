#include <iostream>
#include <string>
#include <regex>
#include <cassert>

/*
 * date:
 * dd-mm-yyyy format
 * with correct day number
 * assume february has 28 days -> each month has at leas 28 days -> rest are special cases
 */

bool regex(const std::string &text)
{
    std::regex date_regex(
            "("
            "(31|29)-(0[13578]|1[02])"           // 31 day (or 29)
            "|"
            "(30|29)-(0[469]|10)"                // 30 day (or 29)
            "|"
            "([01][0-9]|2[0-8])-(0[0-9]|1[0-2])" // day-month (day <= 29)
            ")"
            "-"
            "\\d{4,4}"                           // year
    );
    return std::regex_match(text, date_regex);
}

void tests()
{
    // MATCHES
    assert(regex("15-09-1999"));
    assert(regex("05-12-2018"));
    assert(regex("28-02-2021"));
    assert(regex("29-03-2021"));
    assert(regex("31-03-2000"));
    assert(regex("31-03-0002"));


    // NOT MATCHES
    assert(!regex("03/07/1917"));
    assert(!regex("6-3-1945"));
    assert(!regex("29-02-2022"));
    assert(!regex("31-04-2000"));
    assert(!regex("31-03-20"));
    assert(!regex("31-03-20000"));
    assert(!regex("it's 15-09-1999"));
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