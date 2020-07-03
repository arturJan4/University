/*  C++
    Lista 4 - implementacja stosu
    Artur Jankowski
    indeks: 317928
 */

// Stack implementation

#include <iostream>
#include "stos.hpp"
#include <cstdlib>

void runTests()
{
    //Konstruktory testuja tez metody sprawdz, sciagnij, rozmiar, wloz
    //testKonstruktorDomyslny();
    //testKonstruktorLista();
    //testKonstruktorPojemnosc();
    //testKonstruktorKopiujacy();
    //testKonstruktorPrzenoszacy();

    //testOperatorKopiujacy();
    //testOperatorPrzenoszacy();

    //testMetodaOdwroc();
}

void interactiveUsage()
{
    bool exit = false;
    stos *myStack = new stos();
    while(!exit)
    {
        std::cout << "===OPCJE===\n";
        std::cout << "1.Wstaw element\n";
        std::cout << "2.Usun element\n";
        std::cout << "3.Liczba elementow\n";
        std::cout << "4.Pojemnosc stosu\n";
        std::cout << "5.Odwroc stos \n";
        std::cout << "6.Pokaz obecny top stosu\n";
        std::cout << "7.Wypisz i usun caly stos\n";
        std::cout << "8.Zamknij program\n";
        int operation = 8;
        std::string input;
        std::cin >> input;

        //!!!!!!
        //bad practice only for showcase purposes
        std::system("clear");

        try
        {
            operation = std::stoi(input);
            if(operation < 1 || operation > 8)
                throw std::invalid_argument("nie mozna wykonac takiej operacji\n");
        }
        catch(std::invalid_argument& err)
        {
            std::cerr << err.what();
        }

        switch(operation) {
            case 1:
                std::cout << "podaj tekst ktory chcesz wstawic: \n";
                std::cin >> input;
                myStack->wloz(input);
                break;
            case 2:
                std::cout << "usunieto: " << myStack->sciagnij() << "\n";
                break;
            case 3:
                std::cout << "liczba elementow : " << myStack->rozmiar() << "\n";
                break;
            case 4:
                std::cout << "pojemnosc stosu : " << myStack->getCapacity() << "\n";
                break;
            case 5:
                *myStack = std::move(myStack->odwroc());
                break;
            case 6:
                std::cout << "gora stosu: " << myStack->sprawdz() << "\n";
                break;
            case 7:
                std::cout << "usunieto: ";
                while (myStack->rozmiar() > 0) {
                    std::cout << myStack->sciagnij() << " ";
                }
                std::cout << "\n";
                *myStack = std::move(stos());
                break;
            case 8:
                exit = true;
                break;
            default:
                throw std::invalid_argument("zla operacja\n");
        }
    }
    delete myStack;
}

int main()
{
    //testy zakomentowane, bo testowalem funkcje inkrementalnie,
    //wszystkie razem sa za dlugie
    runTests();

    //dziala dobrze w terminalu Linuxa ale
    //zakomentowac linijke 46 gdyby były problemy z "czyszczeniem" ekranu
    try
    {
        interactiveUsage();
    }
    catch(const std::exception& e)
    {
        std::clog << e.what();
    }
    return 0;
}

