#ifndef ZAD10_TESTY_HPP
#define ZAD10_TESTY_HPP

#include <iostream>
#include "kalkulator.hpp"

using namespace Kalkulator;

void test1()
{
    std::cout << "-----PROSTE WYRAZENIA-----\n";
    wyrazenie test("2 3.5 + 5 * 1,2 +");
    test.parse();
    std::cout << test.oblicz() << "\n";

    wyrazenie test2("6 2 /"); // 6/2
    test2.parse();
    std::cout << test2.oblicz() << "\n";

    wyrazenie test3("2 3 pow"); //2 ^ 3
    test3.parse();
    std::cout << test3.oblicz() << "\n";

    wyrazenie test4("2 7 + 3 / 14 3 - 4 * + 2 /"); // z wikipedii
    test4.parse();
    std::cout << test4.oblicz() << "\n";

    wyrazenie test5("2 3 -"); // 2 - 3
    test5.parse();
    std::cout << test5.oblicz() << "\n";

    wyrazenie test6("2 2 + 2 *"); // (2+2)*2
    test6.parse();
    std::cout << test6.oblicz() << "\n";

    wyrazenie test7("2 2 3 pow pow"); //(2^2^3)== 2^8
    test7.parse();
    std::cout << test7.oblicz() << "\n";
}

void test2()
{
    std::cout << "-----ISNUMBER()-----\n";

    std::cout << isNumber("0");
    std::cout << isNumber("12000000.5");
    std::cout << isNumber("12");
    std::cout << isNumber("12,5");
    std::cout << isNumber("12.5");
    std::cout << isNumber("-12.5");

    std::cout << "\n";
    std::cout << isNumber("e");
    std::cout << isNumber("12e");
    std::cout << isNumber("12,.5");
    std::cout << isNumber("12.5213,231");
    std::cout << isNumber("func");
    std::cout << "\n";
}

void test3()
{
    std::cout << "-----STALE I ZMIENNE-----\n";
    stala x("pi");
    std::cout << x.oblicz() << "\n";

    zmienna y("y");
    zmienna::setValue("y",14);
    std::cout << y.oblicz() << "\n";

    wyrazenie test("2 3 modulo 1 min 2 max 3 log 2 pow sin sgn");
    test.parse();
    std::cout << test.oblicz() << "\n";
}

void testInter()
{
    std::cout << "-----TEST-INTERAKTYWNEGO-KALKULATORA-----\n";
    interactiveCalc calc;
    calc.assign("2 2 +", "x");
    calc.print("x");
    calc.assign("2 2 + 3 pow -120.5 +", "y");
    calc.print("y");
    calc.print("x y + abs");
    calc.print("x y + -5,5 +");
    calc.clear();
    calc.print("x y");
    calc.print("e fi +");
    std::cout << "\n";
}

void testSuite()
{
    test1();
    test2();
    test3();
    testInter();
}

#endif //ZAD10_TESTY_HPP
