/*
 *  Artur Jankowski
 *  C++ - Wyrazenia
 *  indeks: 317928
 */

// Arithmetic operators and calculating them

#include <iostream>
#include <iomanip>

#include "Zmienna.hpp"
#include "Stala.hpp"
#include "Liczba.hpp"
#include "Operator1arg.hpp"
#include "Operator2arg.hpp"

void test1()
{
    Wyrazenie *w = new Odejmij(
            new Pi(),
            new Dodaj(
                    new Liczba(2),
                    new Mnoz(
                            new Zmienna("x"),
                            new Liczba(7)
                            )
                    )
            );

    std::cout << w->opis() << " = " << w->oblicz() << "\n";
}

void test2()
{
    Wyrazenie *w = new Dziel(
            new Mnoz(
                    new Odejmij(
                                new Zmienna("x"),
                                new Liczba(1)
                            ),
                    new Zmienna("x")
                    ),
            new Liczba(2)
            );

    std::cout << w->opis() << " = " << w->oblicz() << "\n";
}

void test3()
{
    Wyrazenie *w = new Dziel(
            new Dodaj(
                    new Liczba(3),
                    new Liczba(5)
                    ),
            new Dodaj(
                    new Liczba(2),
                    new Mnoz(
                            new Zmienna("x"),
                            new Liczba(7)
                            )
                    )
            );

    std::cout << w->opis() << " = " << w->oblicz() << "\n";
}

void test4()
{
    Wyrazenie *w = new Odejmij(
            new Dodaj(
                        new Liczba(2),
                        new Mnoz(
                                new Zmienna("x"),
                                new Liczba(7)
                                )
                    ),
            new Dodaj(
                    new Mnoz(
                            new Zmienna("y"),
                            new Liczba(3)
                            ),
                    new Liczba(5)
                    )
            );

    std::cout << w->opis() << " = " << w->oblicz() << "\n";
}

void test5()
{
    Wyrazenie *w = new Dziel(
            new Cos(
                    new Mnoz(
                            new Dodaj(
                                    new Zmienna("x"),
                                    new Liczba(1)
                                    ),
                            new Zmienna("x")
                            )
                    ),
            new Potega(
                    new E(),
                    new Potega(
                            new Zmienna("x"),
                            new Liczba(2)
                            )
                    )
            );
    std::cout << w->opis() << " = " << w->oblicz() << "\n";
}

void testyPolecenie()
{
    std::cout << "============================\n";
    std::cout << "TESTY Z POLECENIA, DOMYSLNIE: (x = 2) (y = 1): \n";
    Zmienna::setValue("x", 2);
    Zmienna::setValue("y",1);
    test1();
    test2();
    test3();
    test4();
    test5();
}

void testStale()
{
    std::cout << "============================\n";
    std::cout << "STALE \n";
    Wyrazenie *pi = new Pi;
    std::cout << pi->opis() << " = " << pi->oblicz() << "\n";

    Wyrazenie *e = new E;
    std::cout << e->opis() << " = " << e->oblicz() << "\n";

    Wyrazenie *phi = new Fi;
    std::cout << phi->opis() << " = " << phi->oblicz() << "\n";
}

void testUnar()
{
    std::cout << "============================\n";
    std::cout << "OPERATORY UNARNE: \n";

    Wyrazenie *w = new Sin(new Liczba(1));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Bezwgl(new Liczba(-1));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Cos(new Liczba(-1));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Przeciw(new Liczba(5));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Exp(new Liczba(2));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Odwrot(new Liczba(5));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Ln(new Liczba(3.14));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";
}

void testOperatoryBianrne()
{
    std::cout << "============================\n";
    std::cout << "OPERATORY BINARYNE \n";

    Wyrazenie *w = new Dodaj(new Liczba(1), new Liczba(-1));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Logarytm(new Liczba(10), new Liczba(1000));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Odejmij(new Liczba(-1), new Liczba(1));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Modulo(new Liczba(7), new Liczba(3));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Mnoz(new Liczba(3), new Liczba(-1));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Potega(new Liczba(2), new Liczba(10));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";

    w = new Dziel(new Liczba(3), new Liczba(5));
    std::cout << w->opis() << " = " << w->oblicz() << "\n";
}

void testZmienne()
{
    std::cout << "============================\n";
    std::cout << "ZMIENNE \n";

    Wyrazenie *w = new Zmienna("x");

    std::cout << w->opis() << " = " << w->oblicz() << "\n";
    Wyrazenie *w2 = new Zmienna("x");
    Zmienna::setValue("x", 4);

    std::cout << w2->opis() << " = " << w2->oblicz() << "\n";
}


int main() {
    try {
        testyPolecenie();
        testStale();
        testUnar();
        testOperatoryBianrne();
        testZmienne();
    }catch(const std::exception &ex)
    {
        std::clog << ex.what() << "\n";
    }

    return 0;
}
