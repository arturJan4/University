#ifndef ZAD10_KALKULATOR_HPP
#define ZAD10_KALKULATOR_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <map>
#include <utility>
#include <algorithm>

#include "operatory.hpp"
namespace Kalkulator
{
    bool isNumber(std::string text);
    double stringToDouble(std::string text);
    std::vector<std::string> tokenize(const std::string& input, char delimiterP);

    class interactiveCalc
    {
        bool finish = false;
    public:
        interactiveCalc()= default;
        void loop();

        static void print(std::string);
        static void assign(std::string, const std::string& symbol);
        static void clear();
        void exit();
    };

    class wyrazenie
    {
        std::queue<symbol *> objects;
        std::string input;
    public:
        explicit wyrazenie(std::string input) : input(std::move(input)){};

        void parse();    // parsuje do kolejki symboli objects
        double oblicz(); // oblicza wyrazenie w kolejce przy pomocy stosu
    };
}
#endif //ZAD10_KALKULATOR_HPP
