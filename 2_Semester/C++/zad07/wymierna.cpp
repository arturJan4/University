#include <map>
#include "wymierna.hpp"
namespace obliczenia
{
    int NWD(int a, int b)
    {
        if (b == 0)return a;
        else return NWD(b, a % b);
    }

    int NWW(int a, int b)
    {
        int NWD1 = NWD(a, b);
        return (a * b) / NWD1;
    }

    wymierna::wymierna(int licz, int mian) : licz(licz), mian(mian)
    {
        if (mian == 0)
            throw dzielenie_przez_0("mianownik rowny zero! (konstruktor)");
        skrocUlamek();
    }

    int wymierna::getLicz() const noexcept
    {
        return licz;
    }

    int wymierna::getMian() const noexcept
    {
        return mian;
    }

    void wymierna::skrocUlamek()
    {
        bool isPositive = true;
        if ((licz < 0) != (mian < 0))//xor
        {
            isPositive = false;
        }

        if(isPositive && (licz == std::numeric_limits<int>::min()))
            throw przekroczenie_zakresu("przekroczono zakresy przy operacji skracania");

        licz = abs(licz);
        mian = abs(mian);

        int nwd = NWD(licz, mian);
        licz /= nwd;
        mian /= nwd;

        if (!isPositive) {
            licz *= -1;
        }
    }

    wymierna::operator int() const noexcept
    {
        return static_cast<int>(round((double)licz / mian));
    }

    wymierna::operator double() const noexcept
    {
        return static_cast<double>(licz)/mian;
    }

    wymierna operator+(const wymierna &u1, const wymierna &u2)
    {
        if(checkOverflowMult(u1.mian,u2.mian))
            throw przekroczenie_zakresu("przekroczenie gornego zakresu, przy liczeniu NWD");
        int wspolnaWiel = NWW(u1.mian, u2.mian);

        int mianownik = wspolnaWiel;
        if(checkOverflowAdd(u1.licz * (wspolnaWiel / u1.mian),u2.licz * (wspolnaWiel / u2.mian)))
            throw przekroczenie_zakresu("przekroczenie zakresu podczas operacji +");

        int licznik = u1.licz * (wspolnaWiel / u1.mian) + u2.licz * (wspolnaWiel / u2.mian);

        return wymierna(licznik, mianownik);
    }

    wymierna operator-(const wymierna &u1, const wymierna &u2)
    {
        return u1 + (-u2);
    }

    wymierna operator*(const wymierna &u1, const wymierna &u2)
    {
        if(checkOverflowMult(u1.licz,u2.licz) || checkOverflowMult(u1.mian,u2.mian))
            throw przekroczenie_zakresu("przekroczenie zakresu podczas operacji *");

        return wymierna(u1.licz * u2.licz, u1.mian * u2.mian);
    }

    wymierna operator/(const wymierna &u1, const wymierna &u2)
    {
        if (u2.licz == 0)
            throw dzielenie_przez_0("licznik u2 rowny zero! (operacja /)");
        if(checkOverflowMult(u1.licz,u2.mian) || checkOverflowMult(u1.mian,u2.licz))
            throw przekroczenie_zakresu("przekroczenie zakresu podczas operacji /");

        return wymierna(u1.licz * u2.mian, u1.mian * u2.licz);
    }

    wymierna operator!(const wymierna &ul)
    {
        if (ul.licz == 0)
            throw dzielenie_przez_0("licznik ulamka rowny zero (operacja !)");
        return wymierna(ul.mian, ul.licz);
    }

    wymierna operator-(const wymierna &ul)
    {
        if(ul.licz < -(std::numeric_limits<int>::max()))
            throw przekroczenie_zakresu("przekroczenie zakresu podczas operacji -");
        return wymierna(-ul.licz, ul.mian);
    }

    std::ostream &operator<<(std::ostream &wyj, const wymierna &w) noexcept
    {
        std::string wynik = (w.licz >= 0) ? " " : "-";
        wynik += std::to_string(abs(w.licz) / w.mian);//wartosc bezwgledna z czesci calkowitej

        int licznik = abs(w.licz);
        int mianownik = abs(w.mian);
        int reszta = licznik % mianownik;

        if(reszta == 0)//brak reszty -> nie ma nic po przecinku
        {
            wyj << wynik;
            return wyj;
        }

        wynik += ",";//separator dziesietny
        std::map<int,int> mapRem;//mapuje <reszta, index>, gdy klucz 'reszta' sie powtarza to powtarza się tez czesc ulamkowa
        while(reszta != 0)
        {
            auto it = mapRem.find(reszta);
            if(it != mapRem.end())
            {
                wynik.insert(static_cast<unsigned long>(mapRem[reszta]), "(");
                wynik += ")...";
                break;
            }

            mapRem[reszta] = static_cast<int>(wynik.length());//indeks string

            //operacje podobne do wykonywanyvh podczas dzielenia pisemnego
            reszta *= 10;
            wynik += std::to_string(reszta/mianownik);
            reszta = reszta % mianownik;
        }

        wyj << wynik;
        return wyj;
    }

    std::string wymierna::toString() noexcept
    {
        return std::to_string(licz) + "/" + std::to_string(mian);
    }

    bool checkOverflowMult(int a, int b)
    {
        if((a == std::numeric_limits<int>::min()) && b == -1)
            return true;
        if((b == std::numeric_limits<int>::min()) && a == -1)
            return true;
        if(a > ((std::numeric_limits<int>::max())/b))
            return true;
        return a < ((std::numeric_limits<int>::min()) / b);

    }

    bool checkOverflowAdd(int a, int b)
    {
        int wynik = a + b;
        if(a > 0 && b > 0 && wynik < 0)
            return true;
        return a < 0 && b < 0 && wynik > 0;

    }
}