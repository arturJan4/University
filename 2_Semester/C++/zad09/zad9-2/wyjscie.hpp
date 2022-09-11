#ifndef ZAD9_2_WYJSCIE_HPP
#define ZAD9_2_WYJSCIE_HPP
#include <fstream>
#include <stdexcept>
#include <iostream>

class wyjscie
{
    std::ofstream outputStream;
public:
    wyjscie(std::string filepath);
    ~wyjscie();
    friend wyjscie& operator<<(wyjscie &wy,const int &in);
};

#endif //ZAD9_2_WYJSCIE_HPP
