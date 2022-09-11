#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cassert>

// detect hyperlinks <a href="..." />
// and print value of href attribute

bool regex(const std::string &text)
{
std::regex href_regex(
        "<a\\s+"                      // '<a' with following whitespace (one or more)
        "href"
        "\\s*=\\s*"                      // '=' operator can have whitespace between
        "\"([^<>\"]*)\""                 // word (captured by group, without <>") between ""
        "\\s*"                           // following possible whitespace
        "([^<>]+\\s*)*"                  // possibly more attributes followed by whitespace
        "\\/?>");                        // closing tag (/?>)

    return std::regex_match(text, href_regex);
}

void print_links(const std::vector<std::string>& lines)
{
    std::regex expression(R"lit(<a\s+href\s*=\s*"([^<>"]*)"\s*([^<>]+\s*)*\/?>)lit");
    std::smatch match;
    for (std::string line: lines)
    {
        while(std::regex_search(line, match, expression))
        {
            std::cout << match[1].str() << "\n";
            line = match.suffix().str(); // go in line "after" match
        }
    }
}

void tests()
{
    // MATCHES
    assert(regex(R"(<a href="..." />)"));
    assert(regex(R"(<a href="test" />)"));
    assert(regex(R"(<a href =  "test" />)"));
    assert(regex(R"(<a   href="..." />)"));
    assert(regex(R"(<a   href="..."    />)"));
    assert(regex(R"(<a href="/" id="logo">)"));
    assert(regex(R"(<a href="/dla-studenta">)"));
    assert(regex(R"(<a href="..." >)"));

    // NOT MATCHES
    assert(!regex(R"(<a   hef="..."    />)"));
    assert(!regex(R"(<a   href='...'    />)"));
    assert(!regex(R"(<a href="..." /)"));
    assert(!regex(R"(a href="..." /)"));
}


int main(int argc, const char *argv[])
{
    tests();
    if (argc < 2) {
        std::cout << "Pass filename to the executable as an argument!\n";
        return -1;
    }

    std::ifstream file(argv[1]);
    if (!file.good()) {
        std::cout << "Wrong file error\n";
        return -1;
    }
    std::string input;

    std::vector<std::string> lines;
    while (getline(file, input)) {
        if (!input.empty())
            lines.emplace_back(input);
    }

    print_links(lines);

    return 0;
}