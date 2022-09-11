/*
    C++ lista 5
    Artur Jankowski
    indeks 317928
 */

// BIT ARRAY

#include <iostream>
#include "tabbit.hpp"
#include <sstream>

void pushString(const std::string& s,tab_bit& tab)
{
    std::stringstream nowy(s);
    nowy >> tab;
    std::cout << tab;
    std::cout << "\n";
}

void testMieszany()
{
    std::cout << "\n";
    std::cout << "=======TEST MIESZANY=====\n";
    tab_bit nowa(4);
    tab_bit druga(16);

    std::cout << "\n";
    pushString("1110", nowa);
    pushString("0111101101", druga);

    nowa[1] = nowa[1] & druga[1];

    std::cout << nowa;
}

void testPolecenie()
{
    std::cout << "\n";
    std::cout << "=======TEST Z POLECENIA======\n";
    tab_bit t(46);
    tab_bit u(45ull);
    tab_bit v(t);
    tab_bit w(tab_bit({1,0,1,1,0,0,0,1}));
    v[0] = 1;
    t[45] = true;
    bool b = v[1];
    u[45] = u[46] = u[63];
    std::cout << t << std::endl;
}

void testKonstruktorow()
{
    std::cout << "\n";
    std::cout << "=======TEST KONSTRUKTOROW======\n";
    std::cout << "--tab_bit(rozmiar)--\n";
    //tab_bit test3(0); exception
    tab_bit t(46);
    tab_bit t2(45ull);
    std::cout << t[45] << "\n";

    std::cout << "--tab_bit(lista inicjalizacyjna)--\n";
    tab_bit i3({1,0,0,0,1,1});
    std::cout << i3 << "\n";

    std::cout << "--tab_bit(slowo)--\n";
    unsigned long long test = 45ull;
    tab_bit i4(test);
    std::cout << i4 << "\n";

    std::cout << "--kopia--\n";
    tab_bit y3(1);
    tab_bit y1(t);
    tab_bit y2 = t;
    y3 = t;

    std::cout << "--przeniesienie--\n";
    tab_bit u2(1);
    tab_bit u1(std::move(t));
    u2 = std::move(t);
}

void testOperatorow()
{
    std::cout << "\n";
    std::cout << "=======TEST OPERATOROW []=====\n";
    tab_bit test{1,0,0,1,0,1,0};
    for(int i = 0; i < test.rozmiar(); ++i)
    {
        std::cout << test[i] << " ";
    }std::cout << "\n";
    //ref
    tab_bit test2{1,0};
    test[0] = test[0] ^ test2[0];
    std::cout << test[0] << "\n";
    //std::cout << test2[2]; //exception
    //std::cout << test[-1]; //exception

    std::cout << "\n";
    std::cout << "=======TEST OPERATOROW '<<' '>>'=====\n";
    tab_bit test3(65);
    test3[64] = 1;
    std::cout << test3 << "\n";
    pushString("11100011", test3);
    //pushString("xds123", test3); //exception - exception illegal symbols
    //pushString("111", test2);    //exception - length
}

void testOperacjeBitowe() {
    std::cout << "\n";
    std::cout << "=======TEST OPERATOROW BITOWYCH NA TABLICACH=====\n";
    tab_bit pierwsza(4);
    tab_bit druga(65);
    druga[64] = 1;
    pushString("1110", pierwsza);
    pushString("0111101101", druga);

    tab_bit andOP(65);
    andOP = pierwsza & druga;
    tab_bit orOP(65);
    orOP = pierwsza | druga;
    tab_bit xorOP(65);
    xorOP = pierwsza ^ druga;
    tab_bit negOP(65);
    negOP = !(druga);

    std::cout << "\nwynik operacji and \n";
    std::cout << andOP;
    std::cout << "\nwynik operacji or \n";
    std::cout << orOP;
    std::cout << "\nwynik operacji xor \n";
    std::cout << xorOP;
    std::cout << "\nwynik operacji neg \n";
    std::cout << negOP << "\n";


    tab_bit trzecia(66);
    tab_bit czwarta(66);
    trzecia[64] = czwarta[64] = 1;
    trzecia[65] = 0;
    czwarta[65] = 1;
    std::cout << "\nprzypadek graniczny: \n" << trzecia << "\n" << czwarta << "\n";

    std::cout << "\nand \n" << (trzecia & czwarta) << "\n";
    std::cout << "or \n" << (trzecia | czwarta) << "\n";
    std::cout << "xor \n" << (trzecia ^ czwarta) << "\n";

    trzecia |= czwarta;
    std::cout << trzecia << "\n";

    trzecia ^= czwarta;
    std::cout << trzecia << "\n";
}

void testOperacjeBitoweRef()
{
    std::cout << "\n";
    std::cout << "=======TEST OPERATOROW BITOWYCH NA KONKRETNYCH ELEMENTACH=====\n";
    tab_bit pierwsza(4);
    tab_bit druga(5);
    pushString("1100", pierwsza);
    pushString("0101", druga);

    pierwsza[0] = pierwsza[0] & druga[0];
    std::cout << "and " << pierwsza << "\n";

    pierwsza[0] = pierwsza[0] | pierwsza[1];
    std::cout << "or  " << pierwsza << "\n";

    pierwsza[0] = pierwsza[1] ^ druga[1];
    std::cout << "xor " << pierwsza << "\n";

    pierwsza[0] = !pierwsza[0];
    std::cout << "neg " << pierwsza << "\n";
}

void testFunkcjePomocnicze()
{
    std::cout << "\n";
    std::cout << "=======TEST FUNKCJI POMOCNICZYCH=====\n";
    tab_bit w(tab_bit({1,0,1,1,0,0,0,1}));
    std::cout << w.rozmiar() << "\n";   //8
    std::cout << w.toInteger() << "\n"; //141

    tab_bit zero({0});
    std::cout << zero.rozmiar() << "\n";    //1
    std::cout << zero.toInteger() << "\n";  //0
}

void testSuite()
{
    try
    {
    testPolecenie();
    testKonstruktorow();
    testOperatorow();
    testOperacjeBitowe();
    testOperacjeBitoweRef();
    testFunkcjePomocnicze();
    testMieszany();
    }
    catch(const std::exception &ex)
    {
        std::clog << ex.what() << "\n";
    }
}

int main()
{
    //w hpp mozna wyklaczyc informacje o konstruktorach
    testSuite();

    return 0;
}
