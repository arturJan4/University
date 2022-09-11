//
// Created by artur on 4/23/20.
//

#include "Zmienna.hpp"
#include <stdexcept>

std::vector<std::pair<std::string, double>> Zmienna::zmienne;

double Zmienna::oblicz() {
    std::string currentSym = this->getSymbol();
    for(auto& i : zmienne)
    {
        if(i.first == currentSym)
            return i.second;
    }
    throw std::invalid_argument(symbol + " not set - err");
}

std::string Zmienna::opis() {
    return symbol;
}

int Zmienna::getPriorytet() {
    return 0;
}

const std::string &Zmienna::getSymbol() const {
    return symbol;
}

void Zmienna::setValue(std::string symbol, double val)
{
    for (auto &i : zmienne)
    {
            if (i.first == symbol)
            {
                i.second = val;
                return;
            }
        }
    //if not set then set
    zmienne.push_back(std::make_pair(symbol,val));
}

bool Zmienna::isSet(std::string symbol) {
    for(auto& i : zmienne)
    {
        if(i.first == symbol)
        {
            return  true;
        }
    }
    return  false;
}

