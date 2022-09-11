#include "operatory.hpp"
using namespace Kalkulator;
//mapa par <"nazwa funkcji, "arnosc funkcji">
std::map<std::string,int> funkcja::reservedFunctions =
        {{"+", 2}, {"-", 2}, {"*", 2}, {"/", 2},
         {"modulo", 2}, {"min", 2}, {"max", 2}, {"log", 2}, {"pow", 2},
         {"abs", 1}, {"sgn", 1}, {"floor", 1}, {"ceil", 1}, {"frac", 1},
         {"sin", 1}, {"cos", 1}, {"atan", 1}, {"acot", 1}, {"ln", 1}, {"exp", 1}};

//https://stackoverflow.com/questions/650162/why-the-switch-statement-cannot-be-applied-on-string
constexpr unsigned int hash(const char *s, int off = 0) {
    return !s[off] ? 5381 : (hash(s, off+1)*33) ^ s[off];
}

std::string funkcja::toString()
{
    return symbolString;
}

double funkcja::oblicz()
{
    int arity = getArity();
    if(arity == 1)
        return obliczUnary();
    else if(arity == 2)
        return obliczBinary();
    else
    {
        throw std::invalid_argument("nieprawidlowa arnosc funkcji: " + symbolString + "\n");
        return -1;
    }
}

void funkcja::setArg1(double val)
{
    arg1 = val;
}

void funkcja::setArg2(double val)
{
    arg2 = val;
}

int funkcja::getArity()
{
    auto it = reservedFunctions.find(symbolString);
    if(it != reservedFunctions.end())// var doesn't exist
        return it->second;
    else
        throw std::invalid_argument("nie znaleziono funkcji o symbolu:" + symbolString +"\n");
}

double funkcja::obliczUnary()
{
    switch (hash(symbolString.c_str()))
    {
        case hash("abs"):
            return fabs(arg1);
        case hash("sgn"):
            return (arg1 > 0) ? 1 : ((arg1 < 0) ? -1 : 0);
        case hash("floor"):
            return floor(arg1);
        case hash("ceil"):
            return ceil(arg1);
        case hash("frac"):
            return modf(arg1, &arg2);
        case hash("sin"):
            return sin(arg1);
        case hash("cos"):
            return cos(arg1);
        case hash("atan"):
            return atan(arg1);
        case hash("acot"):
            return M_PI/2 - atan(arg1);
        case hash("ln"):
            return log(arg1);
        case hash("exp"):
            return exp(arg1);
        default:
            throw std::invalid_argument("error unary: " + symbolString + "\n");
    }
}

double funkcja::obliczBinary()
{
    switch (hash(symbolString.c_str()))
    {
        case hash("+"):
            return (arg1 + arg2);
        case hash("-"):
            return (arg1 - arg2);
        case hash("*"):
            return (arg1 * arg2);
        case hash("/"):
            return (arg1 / arg2);
        case hash("modulo"):
            return ((int)arg1 % (int)arg2); // modulo działa na całkowitych
        case hash("min"):
            return std::min(arg1,arg2);
        case hash("max"):
            return std::max(arg1,arg2);
        case hash("log"):
            return log(arg2)/log(arg1);
        case hash("pow"):
            return pow(arg1,arg2);
        default:
            throw std::invalid_argument("error binary: " + symbolString + "\n");
    }
}