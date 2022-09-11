#ifndef ZAD7_WYMIERNA_HPP
#define ZAD7_WYMIERNA_HPP
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <map>
#include <numeric>
#include <limits>

#include "wyjatek.hpp"
namespace obliczenia
{
    int NWD(int a, int b);
    int NWW(int a, int b);

    bool checkOverflowMult(int a, int b);
    bool checkOverflowAdd(int a, int b);

    class wymierna
    {
        int licz, mian;
        void skrocUlamek();

    public:
        wymierna(int licz, int mian);
        explicit wymierna(int liczba) : wymierna(liczba, 1)
        {};

        wymierna(const wymierna &wym) noexcept = default;
        wymierna &operator=(const wymierna &wym) noexcept= default;

        int getLicz() const noexcept;
        int getMian() const noexcept;

        std::string toString() noexcept;

        operator int() const noexcept;
        operator double() const noexcept;

        friend wymierna operator+(const wymierna &u1, const wymierna &u2);
        friend wymierna operator-(const wymierna &u1, const wymierna &u2);
        friend wymierna operator*(const wymierna &u1, const wymierna &u2);
        friend wymierna operator/(const wymierna &u1, const wymierna &u2);

        friend wymierna operator!(const wymierna &ul);
        friend wymierna operator-(const wymierna &ul);

        friend std::ostream &operator<<(std::ostream &wyj, const wymierna &w) noexcept;
    };
}

#endif //ZAD7_WYMIERNA_HPP
