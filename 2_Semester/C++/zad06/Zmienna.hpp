#ifndef ZAD6_ZMIENNA_HPP
#define ZAD6_ZMIENNA_HPP

#include <string>
#include <algorithm>
#include <vector>

#include "Wyrazenie.hpp"
class Zmienna : public Wyrazenie {
private:
    static std::vector<std::pair<std::string, double>> zmienne;
    std::string symbol;
public:
    Zmienna(std::string symbol) : symbol(symbol){};

    double oblicz() override;
    std::string opis() override;
    int getPriorytet() override;

    const std::string &getSymbol() const;

    static void setValue(std::string symbol, double val);
    static bool isSet(std::string symbol);
};


#endif //ZAD6_ZMIENNA_HPP
