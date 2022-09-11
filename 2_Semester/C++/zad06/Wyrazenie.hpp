#ifndef ZAD6_WYRAZENIE_HPP
#define ZAD6_WYRAZENIE_HPP
#include <string>
#include <stdexcept>
class Wyrazenie{
public:
    virtual double oblicz() = 0;
    virtual std::string opis() = 0;
    virtual int getPriorytet() = 0;
    virtual ~Wyrazenie() = default;
};


#endif //ZAD6_WYRAZENIE_HPP
