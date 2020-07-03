/*
    C++ lista 5
    Artur Jankowski
    indeks 317928
 */

#ifndef ZAD5_TABBIT_HPP
#define ZAD5_TABBIT_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <cmath>
#include <algorithm>
#include <cstdint>

#if 1//0                          // switch between 0 and 1 ...
#define ENABLE_CTOR_DBG_PRINTs    // do testow, wyswietlanie konstruktorow
#endif                            // ... to respectively disable or enable CTOR DETECTION PRINTs

class tab_bit
{
private:
    typedef uint64_t slowo;                             //komorka w tablicy
    static const int rozmiarSlowa = sizeof(slowo) * 8;  //rozmiar slowa w bitach
    class ref;                                          //klasa pomocnicza do adresowania bitow
    //przenioslem operatorory '<<' '>>' nizej
protected:
    int dl;                                            //liczba bitow
    slowo *tab;                                        //tablia bitow
public:
    explicit tab_bit(int rozm);                        //wyzerowana tablica bitow [0...rozm]
    explicit tab_bit(slowo tb);                        //tablica bitow [0...rozmiarSlowa]
                                                       //zainicjalizowana wzorcem
    tab_bit(const std::initializer_list<bool>& list);  //lista inicjalizyjna
    tab_bit(unsigned long long rozm) : tab_bit((slowo)rozm){} //ull wrapper

    tab_bit(const tab_bit &tb);                        //konstruktor kopiujacy
    tab_bit(tab_bit &&tb) noexcept;                    //konstruktor przenoszacy
    tab_bit & operator = (const tab_bit &tb);          //przypisanie kopiujace
    tab_bit & operator = (tab_bit &&tb) noexcept;      //przypisanie przenoszace

    ~tab_bit();                                        //destruktor
private:
    bool czytaj(int i) const;                          //metoda pomocnicza do odczytu bitu
    bool pisz(int i, bool b);                          //metoda pomocnicza do zapisu bitu
    static void test();                                //metoda pomocnicza do testow
public:
    bool operator[] (int i) const;                     //indeksowanie dla stalych tablic bitowych
    ref operator[] (int i);                            //indeksowanie dla zwyklych tablica bitowych
    inline int rozmiar() const{return this->dl;}       //rozmiar tablicy w bitach

public:
    //operatory bitowe
    friend tab_bit operator|(const tab_bit &tb1, const tab_bit &tb2);//binary
    tab_bit& operator|=(const tab_bit& tb1);                         //unary

    friend tab_bit operator&(const tab_bit &tb1, const tab_bit &tb2);//binary
    tab_bit& operator&=(const tab_bit& tb1);                         //unary

    friend tab_bit operator^(const tab_bit &tb1, const tab_bit &tb2);//binary
    tab_bit& operator^=(const tab_bit& tb1);                         //unary

    friend tab_bit operator!(const tab_bit& tb1);                     //unary
public:
    //zaprzyjaznione operatory strumieniowe
    friend std::istream & operator >> (std::istream &we, tab_bit &tb);
    friend std::ostream & operator << (std::ostream &wy, const tab_bit &tb);
public:
    long long int toInteger();                                      // binary->decimal
};

class tab_bit::ref
{
    //referencja na konkretny bit
        /*pomogl mi tu z tym co trzeba zaimplmentowac kolega na Discordzie
         *bo za bardzo nie wiedzialem o co chodzi
         *konieczne do dzialania operatora ! w tej implementacji*/
private:
    int index;
    tab_bit* tabPtr;
public:
    ref(int index, tab_bit* tabPtr);
    ref & operator = (const ref& reference);
    ref & operator = (bool x);
    operator bool() const;//operator rzutowania (przy operacji!)
};

#endif //ZAD5_TABBIT_HPP
