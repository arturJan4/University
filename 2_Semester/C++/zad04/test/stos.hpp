#ifndef ZAD4_STOS_HPP
#define ZAD4_STOS_HPP
#include <iostream>
#include <algorithm>

class stos
{
private:
    int pojemnosc;
    int ile;
    std::string* tablica;
public:
    stos();
    explicit stos(int pojemnosc);
    stos(const std::initializer_list<std::string>& napisy);
    //Konstruktor kopiujacy
    stos(const stos &objekt);
    //Konstruktor przenoszacy
    stos(stos &&objekt);

    //Operator przypisania kopiujacego
    stos &operator= (const stos& objekt);
    //Operator przenoszący przypisania klasy
    stos &operator= (stos&& objekt);

    void wloz(const std::string& input);
    std::string sciagnij();
    std::string sprawdz();
    int rozmiar();
    int getCapacity();
    stos odwroc();
    ~stos();
};

//pojemnosc trzymamy jako wielokrotnosci 2
int findClosest2thPower(int pojemnosc);
#endif //ZAD4_STOS_HPP
