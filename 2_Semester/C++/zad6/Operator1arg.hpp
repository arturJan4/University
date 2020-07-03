#ifndef ZAD6_OPERATOR1ARG_HPP
#define ZAD6_OPERATOR1ARG_HPP

#include "Wyrazenie.hpp"
#include <string>

class Operator1arg : public Wyrazenie {
protected:
    Wyrazenie* operandR;
public:
    Operator1arg(Wyrazenie* operand) : operandR(operand){
        if(operandR == nullptr)
            throw std::invalid_argument("null operand");
    };

    ~Operator1arg() override{
        delete operandR;
        delete this;
    }

    int getPriorytet() override {
        return 0;
    }
};

class Sin : public Operator1arg
{
public:
    Sin(Wyrazenie* wyrazenie) : Operator1arg(wyrazenie){};

    double oblicz() override;
    std::string opis() override;
};

class Bezwgl : public Operator1arg
{
public:
    Bezwgl(Wyrazenie* wyrazenie) : Operator1arg(wyrazenie){};

    double oblicz() override;
    std::string opis() override;
};

class Cos : public Operator1arg
{
public:
    Cos(Wyrazenie* wyrazenie) : Operator1arg(wyrazenie){};

    double oblicz() override;
    std::string opis() override;
};

class Przeciw : public Operator1arg
{
public:
    Przeciw(Wyrazenie* wyrazenie) : Operator1arg(wyrazenie){};

    double oblicz() override;
    std::string opis() override;
};

class Exp : public Operator1arg
{
public:
    Exp(Wyrazenie* wyrazenie) : Operator1arg(wyrazenie){};

    double oblicz() override;
    std::string opis() override;
};

class Odwrot : public Operator1arg
{
public:
    Odwrot(Wyrazenie* wyrazenie) : Operator1arg(wyrazenie){};

    double oblicz() override;
    std::string opis() override;
};

class Ln : public Operator1arg
{
public:
    Ln(Wyrazenie* wyrazenie) : Operator1arg(wyrazenie){};

    double oblicz() override;
    std::string opis() override;
};
#endif //ZAD6_OPERATOR1ARG_HPP
