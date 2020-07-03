#ifndef ZAD9_MANIPULATOR_HPP
#define ZAD9_MANIPULATOR_HPP
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

inline std::istream& clearline(std::istream &is)
{
    for(int x = is.get(); (x != EOF  && x != '\n'); x = is.get()){}
    return is;
}

inline std::ostream& comma(std::ostream &os)
{
    os << ", ";
    return os;
}

inline std::ostream& colon(std::ostream &os)
{
    os << ": ";
    return os;
}

class index
{
    int x;
    int w;
    friend std::ostream & operator<<(std::ostream& os, const index& ind);
public:
    index(int x, int w) : x(x), w(w){};
};

class ignore
{
    int x;
    friend std::istream & operator>>(std::istream& is, const ignore& ign);
public:
    explicit ignore(int x) : x(x){};
};

#endif //ZAD9_MANIPULATOR_HPP
