#ifndef ZAD6_LICZBA_HPP
#define ZAD6_LICZBA_HPP

#include "Wyrazenie.hpp"

class Liczba : public Wyrazenie {
private:
    double val;
public:
    Liczba(double value) : val(value){};

    double oblicz() override;
    std::string opis() override;
    int getPriorytet() override;
};


#endif //ZAD6_LICZBA_HPP
