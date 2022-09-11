#ifndef ZAD6_OPERATOR2ARG_HPP
#define ZAD6_OPERATOR2ARG_HPP

#include "Operator1arg.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <stdexcept>

enum priority
{
    POTEGA = 5,
    MODULO = 10,
    DZIEL = 15,
    MNOZ = 20,
    ODEJ = 25,
    DOD = 30
};

class Operator2arg : public Operator1arg{
protected:
    Wyrazenie* operandL;

public:
    Operator2arg(Wyrazenie* operandL, Wyrazenie* operandR)
    : Operator1arg(operandR), operandL(operandL){
        if(operandR == nullptr || operandL == nullptr)
            throw std::invalid_argument("null operand");
    };

    ~Operator2arg(){
        delete operandR;
        delete operandL;
        delete this;
    }
};

class Dodaj : public Operator2arg
{
public:
    Dodaj(Wyrazenie* operandL, Wyrazenie* operandR)
    :Operator2arg(operandL,operandR){};

    int getPriorytet() override;
    double oblicz() override;
    std::string opis() override;
};


class Logarytm : public Operator2arg
{
public:
    Logarytm(Wyrazenie* operandL, Wyrazenie* operandR)
            :Operator2arg(operandL,operandR){};

    int getPriorytet() override;
    double oblicz() override;
    std::string opis() override;
};

class Odejmij : public Operator2arg
{
public:
    Odejmij(Wyrazenie* operandL, Wyrazenie* operandR)
            :Operator2arg(operandL,operandR){};

    int getPriorytet() override;
    double oblicz() override;
    std::string opis() override;
};

class Modulo : public Operator2arg
{
public:
    Modulo(Wyrazenie* operandL, Wyrazenie* operandR)
            :Operator2arg(operandL,operandR){};

    int getPriorytet() override;
    double oblicz() override;
    std::string opis() override;
};

class Mnoz : public Operator2arg
{
public:
    Mnoz(Wyrazenie* operandL, Wyrazenie* operandR)
            :Operator2arg(operandL,operandR){};

    int getPriorytet() override;
    double oblicz() override;
    std::string opis() override;
};

class Potega : public Operator2arg
{
public:
    Potega(Wyrazenie* operandL, Wyrazenie* operandR)
            :Operator2arg(operandL,operandR){};

    int getPriorytet() override;
    double oblicz() override;
    std::string opis() override;
};

class Dziel : public Operator2arg
{
public:
    Dziel(Wyrazenie* operandL, Wyrazenie* operandR)
            :Operator2arg(operandL,operandR){};

    int getPriorytet() override;
    double oblicz() override;
    std::string opis() override;
};
#endif //ZAD6_OPERATOR2ARG_HPP
