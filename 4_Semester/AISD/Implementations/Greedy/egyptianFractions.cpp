#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <ostream>

class Fraction
{
    int m_numerator;
    int m_denominator;

  public:
    Fraction(int numerator, int denominator) 
        : m_numerator{numerator}, m_denominator{denominator} {};

    std::string toString() const
    {
        return std::to_string(m_numerator) + "/" + std::to_string(m_denominator);
    }

    Fraction operator+(const Fraction& f2)
    {
        int newN = f2.m_numerator * this->m_denominator + this->m_numerator * f2.m_denominator;
        int newD = f2.m_denominator * this->m_denominator;
        int gcd = std::gcd(newN, newD);
        return Fraction(newN/gcd, newD/gcd);
    }

    Fraction operator-(const Fraction& f2)
    {
        int newN = this->m_numerator * f2.m_denominator - f2.m_numerator * this->m_denominator;
        int newD = f2.m_denominator * this->m_denominator;
        int gcd = std::gcd(newN, newD);
        return Fraction(newN/gcd, newD/gcd);
    }

    int getNumerator()
    {
        return this->m_numerator;
    }

    friend std::ostream& operator<<(std::ostream &out, const Fraction &F)
    {
        out << (F.toString());
        return out;
    }
};

/*
    Given a fraction a/b where a <= b represent it as a sum of fractions with 1
    in the numerato
    
    example:
    3/7 = 1/3 + 1/11 + 1/231
    Greedy algorithm example - and why it doesn't give optimal solution

    Idea:
    Always substract a fraction with the smalllest denominator possible
*/

void Represent(Fraction x)
{
    std::string representation = x.toString() + " = ";

    int currentDenom = 1;
    while(x.getNumerator() != 0)
    {
        Fraction temp(1, currentDenom);
        Fraction test = x - temp;
        if(test.getNumerator() >= 0)
        {
            representation += temp.toString() + " + ";
            x = test; 
        }
        else
        {
            currentDenom += 1;
        }    
    }
    std::cout << representation << "0\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    Fraction test(3, 7);
    Fraction test2(1, 3);
    Fraction test3 = test-test2;

    std::cout << Fraction(1,3) - Fraction(1,2) << "\n";
    Represent(test);

    std::cout << Fraction(1, 4) + Fraction(1, 8) + Fraction(1, 18) << "\n";
    Fraction test4(31, 72); // 1/4 + 1/8 + 1/18
    Represent(test4);
    return 0;
}