#include <iostream>
#include <string>
#include <cmath>
#include <vector>

// finds prime factors of a number

int64_t stringToInt64(std::string input)
{
    int negative = 0;//bool
    int64_t strLen = input.length();

    if(strLen == 0)
        throw std::invalid_argument("pusty napis");

    if(input[0] == '-')
        negative = 1;

    if(input[negative] == '0' && strLen > 1)//number starting with zeros
    {
        throw::std::invalid_argument("nieprawidlowa liczba (zaczynajaca sie od zer)");
    }

    if (strLen >= 19 + negative || strLen == negative)
    {
        if (strLen == 19 + negative)
        {
            std::string sub = input.substr(negative,19 + negative);//without minus sign
            if(sub > "9223372036854775808" || (!negative && sub > "9223372036854775783"))
            {
                throw std::invalid_argument("Przekroczono zakres (na ostatniej cyfrze)");
            }
        }
        else
            throw std::invalid_argument("Przekroczono zakres (lub podano tylko minus)");
    }

    int64_t number = 0;
    int64_t powerOf10 = 1;
    for(int64_t i = strLen-1; i >= 0 + negative; --i)
    {
        if(input[i] < '0' || input[i] > '9')
            throw std::invalid_argument("Blad - podano znak nie-liczbowy");
        number += (input[i]-48) * powerOf10;
        powerOf10 *= 10;
    }

    if(negative)
    {
        number *= -1;
    }

    return number;
}

bool isPrime(int64_t number)
{
    if(number == 2 || number == 3)return true;
    if(number == 1 || number % 2 == 0 || number % 3 == 0)return false;

    for(int i = 5; i * i <= number; i += 6)//6k+1, 6k-1 (rozpoczecie od 6 daje zly wynik dla 25)
    {
        if(i < 5)break;
        if((number % i == 0) || number % (i + 2) == 0)
            return false;
    }
    return true;
}

std::vector<int64_t> factorize(int64_t numberFrom)
{
    std::vector<int64_t> factors;
    int64_t number = numberFrom;
    const int64_t MIN = -9223372036854775808;

    if (number == -1 || number == 0 || number == 1) {
        factors.push_back(number);
        return factors;
    }

    if(number < 0)
    {
        factors.push_back(-1);
        if (number == MIN)//avoid overflow
        {
            number = -4611686018427387904;
            factors.push_back(2);
        }
        number *= -1;
    }
    else
        factors.push_back(1);

    if(isPrime(number))
    {
        factors.push_back(number);
        return factors;
    }
    while(number != 1)
    {
        if(number % 2 == 0)
        {
            number /= 2;
            factors.push_back(2);
        }
        else if(number % 3 == 0)
        {
            factors.push_back(3);
            number /= 3;
        }
        else
            break;
    }

    int64_t divideBy = 5;
    while(number != 1 && divideBy > 0 && divideBy * divideBy <= number)
    {
        if(number % divideBy == 0)
        {
            number /= divideBy;
            factors.push_back(divideBy);
        }
        else if(number % (divideBy + 2) == 0)
        {
            number /= divideBy + 2;
            factors.push_back(divideBy + 2);
        }
        else
        {
            divideBy += 6;
        }
    }

    if(number != 1)//prime
    {
        factors.push_back(number);
    }

    return factors;
}

void printFactors(int64_t number)
{
    std::vector<int64_t> factors = factorize(number);
    std::cout << number << " = ";
    for(auto& i: factors)
    {
        std::cout << i;
        if(&i != &factors.back())
            std::cout << "*";
    }
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    if(argc == 1)
    {
        std::cerr << "Aby otrzymac rozklad na czynniki pierwsze podaj liczby\n"
                  << "jako argumenty (liczby całkowite) przy wywolaniu programu\n";
    }
    else
    {
        for(int i = 1; i < argc; ++i)
        {
            std::string text = argv[i];
            int64_t number;
            try
            {
                number = stringToInt64(text);
                printFactors(number);
            }
            catch(std::invalid_argument& error)
            {
                std::cerr << "catched error: " << error.what() << "\n";
            }
        }
    }

    return 0;
}
