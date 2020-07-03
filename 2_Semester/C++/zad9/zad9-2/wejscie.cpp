#include "wejscie.hpp"

wejscie::wejscie(std::string filepath)
{
    try
    {
        inputStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        inputStream.open(filepath, std::ios::binary);
    }
    catch (const std::ios_base::failure &exc)
    {
        std::cerr << exc.what() << ", path: " << filepath;
    }
}

wejscie::~wejscie()
{
    inputStream.close();
}

wejscie &operator>>(wejscie &wej, int &in)
{
    in = wej.inputStream.get();
    return wej;
}

bool wejscie::eof()
{
    return (inputStream.peek() == EOF);
}
