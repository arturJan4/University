#ifndef ZAD10_OPERATORY_HPP
#define ZAD10_OPERATORY_HPP

#include <cmath>
#include <utility>
#include "operandy.hpp"

namespace Kalkulator
{
    class funkcja : public symbol
    {
    private:
        std::string symbolString;
        double arg1 = 0;
        double arg2 = 0;
        double obliczUnary();
        double obliczBinary();
    public:
        static std::map<std::string, int> reservedFunctions;  //mapa <nazwa,arnosc>
        explicit funkcja(std::string  name) : symbolString(std::move(name)){};

        std::string toString() override;
        double oblicz() override; //wybiera obliczUnary/obliczBinary na podstawie nazwy funkcji i zapisanej jej arnosci

        void setArg1(double val);
        void setArg2(double val);
        int getArity();
    };
}
#endif //ZAD10_OPERATORY_HPP
