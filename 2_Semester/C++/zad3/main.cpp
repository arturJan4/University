/*
    C++ - zad3
    Artur Jankowski
    indeks : 317928
 */

// Converter to roman numerals

#include <iostream>
#include <string>
#include <vector>

const std::vector<std::pair<int, std::string>> rzym =
        {{1000, "M"},{900, "CM"},
         {500, "D"}, {400, "CD"},
         {100, "C"},{90, "XC"},
         {50, "L"}, {40, "XL"},
         {10, "X"},{9, "IX"},
         {5, "V"}, {4, "IV"},
         {1, "I"}};

std::string bin2rom(int x)
{
    //typedef std::vector<std::pair<int, std::string>>::iterator iter;
    std::string numberString = "";
    int currentNumber = x;
    for(auto i: rzym)
    {
        while(currentNumber >= i.first)
        {
            currentNumber -= i.first;
            numberString.append(i.second);
        }
    }
    return numberString;
}

int main(int argc, char* argv[]) {
    if(argc == 1)
    {
        std::clog << "Aby otrzymac konwersje z cyfr arabskich na rzymskie\n" <<
                     "podaj je (w zakresie 1-3999) jako argumenty wywołania programu\n";
    }
    else
    {
        for(int i = 1; i < argc; ++i)
        {
            std::string text = argv[i];
            int number;
            try
            {
                number = std::stoi(text);
                if(number < 1 || number > 3999)
                    throw std::invalid_argument("liczba poza zakresem");

                std::cout << bin2rom(number) << "\n";
            }
            catch(std::invalid_argument& error)
            {
                std::clog << "catched error: " << error.what() << "\n";
            }
        }
    }

    return 0;
}
