#include "wyjscie.hpp"

wyjscie::wyjscie(std::string filepath)
{
    try
    {
        outputStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        outputStream.open(filepath, std::ios::binary);
    }
    catch (const std::ios_base::failure &exc)
    {
        std::cerr << exc.what() << ", path: " << filepath;
    }
}

wyjscie::~wyjscie()
{
    outputStream.close();
}

wyjscie &operator<<(wyjscie &wy, const int &in)
{
    wy.outputStream.put(in);
    return wy;
}
