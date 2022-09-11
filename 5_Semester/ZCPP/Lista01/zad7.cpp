#include <iostream>
#include <vector>
#include <string>

// expected format DD.MM.YYYY
std::vector<std::string> get_month(std::string date)
{
    std::string delim = ".";

    size_t pos = 0;
    std::vector<std::string> tokens;

    while ((pos = date.find(delim)) != std::string::npos) {
        tokens.push_back(date.substr(0, pos));
        date.erase(0, pos + delim.length());
    }

    tokens.push_back(date.substr(0, pos));
    return tokens;
}

void print_date(const std::string& date)
{
    std::vector<std::string> tokens = get_month(date);
    std::cout << tokens[0];

    switch (int month = stoi(tokens[1]); month)
    {
        case 1:
            std::cout << " stycznia ";
            break;
        case 2:
            std::cout << " lutego ";
            break;
        case 3:
            std::cout << " marca ";
            break;
        case 4:
            std::cout << " kwietnia ";
            break;
        case 5:
            std::cout << " maja ";
            break;
        case 6:
            std::cout << " czerwca ";
            break;
        case 7:
            std::cout << " lipca ";
            break;
        case 8:
            std::cout << " sierpnia ";
            break;
        case 9:
            std::cout << " września ";
            break;
        case 10:
            std::cout << " października ";
            break;
        case 11:
            std::cout << " listopada ";
            break;
        case 12:
            std::cout << " grudnia ";
            break;
        default:
            std::cout << "wrong month err";
    }
    std::cout << tokens[2] << "\n";
}

int main()
{
    print_date("12.01.2021");
    print_date("12.09.2021");
    print_date("28.02.2021");
    print_date("13.12.1975");
    return 0;
}