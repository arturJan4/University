#include "manipulator.hpp"

//index
std::ostream &operator<<(std::ostream &os, const index &ind)
{
    os << "[";
    std::string text = std::to_string(ind.x);
    int widthText = text.length();
    int pad = ind.w - widthText;
    while(pad > 0)
    {
        os << " ";
        --pad;
    }
    os << text;
    os << "]";
    return os;
}

//ignore
std::istream &operator>>(std::istream &is, const ignore &ign)
{
    is.ignore(ign.x, '\n');
    return is;
}
