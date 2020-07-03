#ifndef ZAD7_WYJATEK_HPP
#define ZAD7_WYJATEK_HPP

#include <stdexcept>

class wyjatek_wymierny : public std::exception
{
protected:
    const char* exc;
    wyjatek_wymierny(const char *message) : exc(message){};
public:
    virtual const char * what () const throw ()
    {
        return exc;
    }
};

class dzielenie_przez_0 : public wyjatek_wymierny
{
public:
    dzielenie_przez_0(const char* message) : wyjatek_wymierny(message) {};
};

class przekroczenie_zakresu : public wyjatek_wymierny
{
public:
    przekroczenie_zakresu(const char* message) : wyjatek_wymierny(message) {};
};
#endif //ZAD7_WYJATEK_HPP
