#ifndef ZAD10_OPERANDY_HPP
#define ZAD10_OPERANDY_HPP
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <utility>

//#define DEBUG

#ifdef DEBUG
#  define D(x) (x)
#else
#  define D(x) do{}while(0)
#endif // DEBUG

namespace Kalkulator
{
    class symbol
    {
    public:
        virtual std::string toString() = 0;
        virtual double oblicz() = 0;
    };

    class operand : public symbol
    {
    public:
        virtual double oblicz() = 0;
    };

    class liczba : public operand
    {
    private:
        double val;
    public:
        explicit liczba(const double& value) : val(value){};

        double oblicz() override;
        std::string toString() override;
    };

    class zmienna : public operand
    {
    private:
        std::string symbolString;
        static std::map<std::string, double> variables;
    public:
        explicit zmienna(std::string  symbol) : symbolString(std::move(symbol)){};

        double oblicz() override;
        std::string toString() override;

        static bool isSet(const std::string& symbol);
        static void setValue(const std::string& symbol,const double& value);
        static void clear();
    };

    class stala : public operand
    {
        std::string symbolString;
        static std::map<std::string, double> constants;
    public:
        explicit stala(std::string  symbol);

        double oblicz() override;
        std::string toString() override;

        static bool isSet(const std::string& symbol);
    };
}

#endif //ZAD10_OPERANDY_HPP
