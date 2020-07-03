/*
    Artur Jankowski
    CPP - zadanie 7 - wymierne
    indeks: 317928
 */
#include <iostream>
#include <stdexcept>
#include "wymierna.hpp"

// arithmethic on ration numbers and calculating them (infinite decimals representation)

using namespace obliczenia;

void testKonstruktorow()
{
    std::cout << "\n";
    std::cout << "=======TEST KONSTRUKTOROW=====\n";
    wymierna test = wymierna(2,6);
    std::cout << test.toString() << "\n";

    wymierna test2 = wymierna(-24,36);
    std::cout << test2.toString() << "\n";

    wymierna test3 = wymierna(2,-6);
    wymierna test3_2(test3);
    std::cout << test3_2.toString() << "\n";

    wymierna test4(-2,-6);
    std::cout << test4.toString() << "\n";

    wymierna test5 = wymierna(std::numeric_limits<int>::min());
    std::cout << test5.toString() << "\n";
}

void testOperatorow()
{
    std::cout << "\n";
    std::cout << "=======TEST OPERATOROW=====\n";
    wymierna test = wymierna(1,6);
    wymierna test2 = wymierna(-2,6);
    wymierna test3 = test + test2;
    std::cout << test.toString() << " + " << test2.toString()
              << " = " << test3.toString() << "\n";

    wymierna test4 = wymierna(36,12);
    wymierna test5 = wymierna(14,100);
    wymierna test6 = test4 - test5;
    std::cout << test4.toString() << " - " << test5.toString()
              << " = " << test6.toString() << "\n";

    wymierna test7 = wymierna(42,12);
    wymierna test8 = wymierna(3,100);
    wymierna test9 = test7 * test8;
    std::cout << test7.toString() << " * " << test8.toString()
              << " = " << test9.toString() << "\n";

    wymierna test10 = wymierna(42,12);
    wymierna test11 = wymierna(3,100);
    wymierna test12 = test10 / test11;
    std::cout << test10.toString() << " / " << test11.toString()
              << " = " << test12.toString() << "\n";

    wymierna test13 = -(wymierna(5,-3));
    std::cout << "(- oper): " << test13.toString() << "\n";

    wymierna test14 = !(wymierna(-5,3));
    std::cout << "(! oper): " << test14.toString() << "\n";
}

void testStrumienia()
{
    std::cout << "\n";
    std::cout << "=======TEST STRUMIENIA (<<)=====\n";
    wymierna test(1,3);
    std::cout << test << "\n"; //0.(3)

    wymierna test2(2,3);
    std::cout << test2 << "\n"; //0.(6)

    wymierna test3(1,8);
    std::cout << test3 << "\n"; //0.125

    wymierna test4(1,-11);
    std::cout << test4 << "\n"; //-0.(09)

    wymierna test5(29,12);
    std::cout << test5 << "\n"; //2.41(6)

    wymierna test6(22,7);
    std::cout << test6 << "\n"; //pi approx

    wymierna test7(-355,-113);
    std::cout << test7 << "\n"; //better pi approx

    wymierna test8(-43,12);
    std::cout << test8 << "\n"; //-3,58(3)

    wymierna test9(1,2);
    wymierna test9_2(1,3);
    wymierna test9_3(2,2);

    std::cout << "\n";
    std::cout << "=======TEST CAST (int,double)=====\n";
    std::cout << (int)test9 <<  " " <<
                 (int)test9_2 << " " << (int)test9_3 << "\n";

    std::cout << (double)test9 <<  " " <<
              (double)test9_2 << " " << (double)test9_3 << "\n";
}

void testException()
{
    std::cout << "\n";
    std::cout << "=======TEST WYJATKOW=====\n";
    try{
        wymierna test1(-43,0);
        std::cout << test1;
    }catch(const std::exception &ex){std::clog << ex.what() << "\n";}

    try{
        wymierna test2(0,5);
        wymierna test2_2 = !test2;
        std::cout << test2_2;
    }catch(const std::exception &ex){std::clog << ex.what() << "\n";}

    try{
        wymierna test3(std::numeric_limits<int>::min());
        wymierna test3_2 = -test3;
        std::cout << test3_2;
    }catch(const std::exception &ex){std::clog << ex.what() << "\n";}

    try{
        wymierna test4(std::numeric_limits<int>::max()/2 + 1);
        wymierna test4_1(std::numeric_limits<int>::max()/2);
        wymierna test4_2 = test4 * test4_1;
    }catch(const std::exception &ex){std::clog << ex.what() << "\n";}

    try{
        wymierna test5(-1);
        wymierna test5_1(std::numeric_limits<int>::min());
        wymierna test5_2 = test5 * test5_1;
    }catch(const std::exception &ex){std::clog << ex.what() << "\n";}

    try{
        wymierna test6(std::numeric_limits<int>::max()/2 + 1);
        wymierna test6_1(std::numeric_limits<int>::max()/2 + 1);
        wymierna test6_2 = test6 + test6_1;
    }catch(const std::exception &ex){std::clog << ex.what() << "\n";}

    try{
        wymierna test7(std::numeric_limits<int>::min());
        wymierna test7_1(1);
        wymierna test7_2 = test7 - test7_1;
    }catch(const std::exception &ex){std::clog << ex.what() << "\n";}

    try{
        wymierna test8(std::numeric_limits<int>::min());
        wymierna test8_1(0);
        wymierna test8_2 = test8 / test8_1;
    }catch(const std::exception &ex){std::clog << ex.what() << "\n";}
}

void testSuite()
{
    try
    {
        testKonstruktorow();
        testOperatorow();
        testStrumienia();
        testException();
    }catch(const std::exception &ex)
    {
        std::clog << ex.what() << "\n";
    }
}
int main()
{
    testSuite();
    return 0;
}
