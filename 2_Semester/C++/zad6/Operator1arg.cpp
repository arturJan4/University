#include "Operator1arg.hpp"
#include <cmath>

double Sin::oblicz() {
    return std::sin(operandR->oblicz());
}

std::string Sin::opis() {
    return std::string ("sin") + "(" + operandR->opis() + ")";
}

double Bezwgl::oblicz() {
    return std::abs(operandR->oblicz());
}

std::string Bezwgl::opis() {
    return std::string("|") + operandR->opis() + "|";
}

double Cos::oblicz() {
    return std::cos(operandR->oblicz());
}

std::string Cos::opis() {
    return std::string("cos") + "(" + operandR->opis() + ")";
}

double Przeciw::oblicz() {
    return -(operandR->oblicz());
}

std::string Przeciw::opis() {
    return std::string("-") + "(" + operandR->opis() + ")";//TODO
}

double Exp::oblicz() {
    return std::exp(operandR->oblicz());
}

std::string Exp::opis() {
    return std::string("exp") + "(" + operandR->opis() + ")";
}

double Odwrot::oblicz() {
    double den = operandR->oblicz();
    if(den == 0)
        throw std::invalid_argument("Division by zero");
    return 1/(operandR->oblicz());
}

std::string Odwrot::opis() {
    return std::string("1/") + operandR->opis();
}

double Ln::oblicz() {
    return std::log(operandR->oblicz());
}

std::string Ln::opis() {
    return std::string("ln") + "(" + operandR->opis() + ")";
}
