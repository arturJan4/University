#include "Operator2arg.hpp"

int Dodaj::getPriorytet() {
    return DOD;
}

double Dodaj::oblicz() {
    return operandL->oblicz() + operandR->oblicz();
}

std::string Dodaj::opis() {
    std::string left = operandL->opis();
    std::string right = operandR->opis();
    //if prior >= encapsulate in ()
    if(operandL->getPriorytet() >= ODEJ)
    {
        std::string temp = std::string("(") + left + ")";
        left = temp;
    }
    if(operandR->getPriorytet() >= ODEJ)
    {
        std::string temp = std::string("(") + right + ")";
        right = temp;
    }
    return left + " + " + right;
}

int Logarytm::getPriorytet() {
    return 0;//function
}

double Logarytm::oblicz() {
    try {
        return (std::log(operandR->oblicz())/std::log(operandL->oblicz()));
    }
    catch(const std::exception &ex)
    {
        std::clog << ex.what() << "\n";
    }
}

std::string Logarytm::opis() {
    return std::string ("log_") + "{" + operandL->opis() + "}"
            + "^{" + operandR->opis() + "}";
}

int Odejmij::getPriorytet() {
    return ODEJ;
}

double Odejmij::oblicz() {
    return operandL->oblicz() - operandR->oblicz();
}

std::string Odejmij::opis() {
    std::string left = operandL->opis();
    std::string right = operandR->opis();
    if(operandL->getPriorytet() >= ODEJ)
    {
        std::string temp = std::string("(") + left + ")";
        left = temp;
    }
    if(operandR->getPriorytet() >= ODEJ)
    {
        std::string temp = std::string("(") + right + ")";
        right = temp;
    }
    return left + " - " + right;
}

int Modulo::getPriorytet() {
    return MODULO;
}

double Modulo::oblicz() {
    double prawy = operandR->oblicz();
    if(prawy == 0)
        throw std::invalid_argument("Division by zero - modulo");

    return std::fmod(operandL->oblicz(),prawy);
}

std::string Modulo::opis() {
    std::string left = operandL->opis();
    std::string right = operandR->opis();
    //if prior >= encapsulate in ()
    if(operandL->getPriorytet() >= MODULO)
    {
        std::string temp = std::string("(") + left + ")";
        left = temp;
    }
    if(operandR->getPriorytet() >= MODULO)
    {
        std::string temp = std::string("(") + right + ")";
        right = temp;
    }
    return left + " % " + right;
}

int Mnoz::getPriorytet() {
    return MNOZ;
}

double Mnoz::oblicz() {
    return operandL->oblicz() * operandR->oblicz();
}

std::string Mnoz::opis() {
    std::string left = operandL->opis();
    std::string right = operandR->opis();
    //if prior >= encapsulate in ()
    if(operandL->getPriorytet() >= DZIEL)
    {
        std::string temp = std::string("(") + left + ")";
        left = temp;
    }
    if(operandR->getPriorytet() >= DZIEL)
    {
        std::string temp = std::string("(") + right + ")";
        right = temp;
    }
    return left + " * " + right;
}

int Potega::getPriorytet() {
    return POTEGA;
}

double Potega::oblicz() {
    return std::pow(operandL->oblicz(),operandR->oblicz());
}

std::string Potega::opis() {
    std::string left = operandL->opis();
    std::string right = operandR->opis();
    //if prior >= encapsulate in ()
    if(operandL->getPriorytet() >= POTEGA)
    {
        std::string temp = std::string("(") + left + ")";
        left = temp;
    }
    if(operandR->getPriorytet() >= POTEGA)
    {
        std::string temp = std::string("(") + right + ")";
        right = temp;
    }
    return left + " ^ " + right;
}

int Dziel::getPriorytet() {
    return DZIEL;
}

double Dziel::oblicz() {
    double den = operandR->oblicz();
    if(den == 0)
        throw std::invalid_argument("Division by zero - div operation");

    return operandL->oblicz()/den;
}

std::string Dziel::opis() {
    std::string left = operandL->opis();
    std::string right = operandR->opis();
    //if prior >= encapsulate in ()
    if(operandL->getPriorytet() >= DZIEL)
    {
        std::string temp = std::string("(") + left + ")";
        left = temp;
    }
    if(operandR->getPriorytet() >= DZIEL)
    {
        std::string temp = std::string("(") + right + ")";
        right = temp;
    }
    return left + " / " + right;
}
