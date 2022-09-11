#include "operandy.hpp"

#include <utility>
using namespace Kalkulator;

double liczba::oblicz()
{
    return val;
}

std::string liczba::toString()
{
    return std::to_string(val);
}

double zmienna::oblicz()
{
    auto iter = variables.find(symbolString);
    if(iter == variables.end())
        throw std::invalid_argument("can't find variable" + symbolString);

    return iter->second;
}

std::string zmienna::toString()
{
    return symbolString;
}

bool zmienna::isSet(const std::string& symbol)
{
    return zmienna::variables.find(symbol) != zmienna::variables.end();
}

void zmienna::setValue(const std::string& symbol,const double& value)
{
    auto it = variables.find(symbol);
    if(it == variables.end())// var doesn't exist
    {
        D(std::cout << "var: " << symbol << "doesn't exist\n");
        variables.insert(std::make_pair(symbol,value));
    }
    else
    {
        it->second = value;
    }
}

void zmienna::clear()
{
    variables.clear();
}

stala::stala(std::string  symbol) : symbolString(std::move(symbol))
{
    if(constants.empty())
    {
        constants.insert(std::make_pair("e",2.718281828459));
        constants.insert(std::make_pair("pi", 3.141592653589));
        constants.insert(std::make_pair("fi",1.61803398875));
    }
}

double stala::oblicz()
{
    auto iter = constants.find(symbolString);
    return iter->second;
}

std::string stala::toString()
{
    return symbolString;
}

bool stala::isSet(const std::string& symbol)
{
    return stala::constants.find(symbol) != stala::constants.end();
}