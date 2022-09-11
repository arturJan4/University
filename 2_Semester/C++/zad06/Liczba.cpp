#include "Liczba.hpp"

double Liczba::oblicz() {
    return val;
}

std::string Liczba::opis() {
    return std::to_string(val);
}

int Liczba::getPriorytet() {
    return 0;
}
