#ifndef ZAD9_2_WEJSCIE_HPP
#define ZAD9_2_WEJSCIE_HPP
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>

class wejscie
{
    std::ifstream inputStream;
public:
    wejscie(std::string filepath);
    ~wejscie();
    bool eof();
    friend wejscie& operator>>(wejscie &wej, int &in);
};

#endif //ZAD9_2_WEJSCIE_HPP
