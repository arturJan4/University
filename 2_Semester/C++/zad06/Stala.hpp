#ifndef ZAD6_STALA_HPP
#define ZAD6_STALA_HPP

#include "Wyrazenie.hpp"
#include <vector>
#include <string>
#include <cmath>

class Stala : public Wyrazenie{
protected:
    std::string symbol;
    const double val;
public:
    Stala(std::string symbol, double val) : symbol(symbol), val(val){};
    int getPriorytet() override
    {
        return 0;
    }

    double oblicz() override {
        return val;
    }

    std::string opis() override {
        return symbol;
    }
};

class Pi : public Stala
{
public:
    Pi() : Stala("pi", M_PI){};
};

class E : public Stala
{
public:
    E() : Stala("e", exp(1)){};
};

class Fi : public Stala
{
public:
    Fi() : Stala("phi", (((1 + sqrt(5)) / 2))){};
};

#endif //ZAD6_STALA_HPP
