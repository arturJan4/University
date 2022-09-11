#include <iostream>
#include "geometria.h"

// geometry implementation

void testPunkt()
{
    try {
        std::cout << "=====TESTY KONSTRUKTOROW PUNKTU=====\n";
        punkt p1;
        std::cout << "punkt default: (" << p1.x << " , " << p1.y << ")\n";

        punkt p2(1.0, 1.0);

        std::cout << "punkt 2 (z podanym 1, 1): (" << p2.x << " , " << p2.y << ")\n";

        wektor v(2.0, 3.0);
        punkt p3(p2, v);

        std::cout << "punkt 3 (pkt2 przesuniety o [2,3]): (" << p3.x << " , " << p3.y << ")\n";

        punkt p4(p3);
        std::cout << "punkt 4 (skopiowany pkt 3): (" << p4.x << " , " << p4.y << ")\n";

        /*operator przypisania kopiujacy daje error
        punkt p5(1.0,2.0);
        p5 = p4;
        */
    }
    catch(std::invalid_argument &error)
    {
        std::cerr << "catched error: " << error.what() << "\n";
    }
}

void testWektor()
{
    try {
        std::cout << "=====TESTY KONSTRUKTOROW WEKTOROW====\n";
        wektor v1;
        std::cout << "wektor default: (" << v1.dx << " , " << v1.dy << ")\n";

        wektor v2(1.0, 1.0);
        std::cout << "wektor 2 (z podanym 1, 1): (" << v2.dx << " , " << v2.dy << ")\n";

        wektor v3(v2);
        std::cout << "wektor 3 (skopiowany wektor 2): (" << v3.dx << " , " << v3.dy << ")\n";

        /*operator przypisania kopiujacy daje error
        wektor v4;
         v4 = v3;
        */
        std::cout << "=====TESTY FUNKCJI WEKTOROW====\n";
        wektor v4 = dodaj_wektory(v2, v3);
        std::cout << "suma wektorow 2 i 3: (" << v4.dx << " , " << v4.dy << ")\n";
    }
    catch(std::invalid_argument &error)
    {
        std::cerr << "catched error: " << error.what() << "\n";
    }
}

void testProsta() {
    try {
        std::cout << "=====TESTY KONSTRUKTOROW PROSTEJ===\n";

        punkt p1(5.0, 6.0);
        punkt p2(7.0, 11.0);

        prosta prosta1(p1, p2);
        std::cout << "prosta przechodzaca przez punkty p1(5,6), p2(7,11): " << prosta1.getA() << "x + " <<
                  prosta1.getB() << "y + " <<
                  prosta1.getC() << "\n";
        //std::cout << prosta1.getA()*p1.x + prosta1.getB()*p1.y;
        //std::cout << prosta1.getA()*p2.x + prosta1.getB()*p2.y;

        wektor v1(2.0, 3.0);
        prosta prosta2(v1);
        std::cout << "prosta prostopadla do wektora (2, 3)  :" << prosta2.getA() << "x + " <<
                  prosta2.getB() << "y + " <<
                  prosta2.getC() << "\n";


        prosta prosta3(2.0, 3.0, 6.0);
        std::cout << "prosta z jawnie podanymi wspolczynnikami (2,3,6): " << prosta3.getA() << "x + " <<
                  prosta3.getB() << "y + " <<
                  prosta3.getC() << "\n";

        prosta prosta4(prosta1, v1);
        std::cout << "prosta 1 przesunieta o wektor (2,3) " << prosta4.getA() << "x + " <<
                  prosta4.getB() << "y + " <<
                  prosta4.getC() << "\n";

        prosta prosta5;
        std::cout << "prosta z konstruktorem bezparametrowym: " << prosta5.getA() << "x + " <<
                  prosta5.getB() << "y + " <<
                  prosta5.getC() << "\n";

        std::cout << "=====TESTY FUNKCJI PROSTEJ====\n";
        prosta prostaPktNal(3,-2,12);
        punkt pkt1(-4.0,0.0);
        punkt pkt2(0.0,-6.0);
        std::cout << "czy pkt (-4,0) nalezy do prostej 3x - 2y + 12 = 0: " << ((prostaPktNal.czyLezyNaProstej(pkt1)) ? "tak" : "nie") << "\n";
        std::cout << "czy pkt (0,-6) nalezy do prostej 3x - 2y + 12 = 0: " << ((prostaPktNal.czyLezyNaProstej(pkt2)) ? "tak" : "nie") << "\n";

        prosta prostaWekPr(2,1,1);
        wektor u1(2,1);
        wektor u2(3,1);
        std::cout << "czy wektor (2,1) jest prostopadly do prostej 2x + y + 1 = 0: " << ((prostaWekPr.czyProstopadly(u1)) ? "tak" : "nie") << "\n";
        std::cout << "czy wektor (3,1) jest prostopadly do prostej 2x + y + 1 = 0: " << ((prostaWekPr.czyProstopadly(u2)) ? "tak" : "nie") << "\n";

        prosta prostaWekR(2,1,1);
        wektor u3(1,-2);
        wektor u4(3,1);
        std::cout << "czy wektor (1,-2) jest rownolegly do prostej 2x + y + 1 = 0: " << ((prostaWekR.czyRownolegly(u3)) ? "tak" : "nie") << "\n";
        std::cout << "czy wektor (3,1) jest rownolegly do prostej 2x + y + 1 = 0: " << ((prostaWekR.czyRownolegly(u4)) ? "tak" : "nie") << "\n";


    }
    catch(std::invalid_argument &error)
    {
        std::cerr << "catched error: " << error.what() << "\n";
    }
}

void testGlobalnych()
{
    std::cout << "=====TESTY FUNKCJI GLOBALNYCH====\n";
    prosta prostaP1(1, 1, -4);
    prosta prostaP2(1, -2, 2);
    punkt przeciecie = punktPrzeciecia(prostaP1, prostaP2);
    std::cout << "przeciecie prostych x + y - 4 = 0 i x -2y + 2 = 0: (" << przeciecie.x << "," << przeciecie.y
              << ")\n";

    prosta prostaR1(3, -2, 2);
    prosta prostaR2(3, -2, -10);
    //prosta prostaR2(4,-2,-10);
    bool czyRownoL = czyRownolegle(prostaR1, prostaR2);
    std::cout << "czy 3x - 2y + 2 = 0 i 3x - 2y - 10 sa rownolegle: " << ((czyRownoL) ? "tak" : "nie") << "\n";

    prosta prostaPR1(1, -3, 15);
    prosta prostaPR2(-3, -1, -10);
    //prosta prostaPR2(-4,-1,-10);
    bool czyProst = czyProstopadle(prostaPR1, prostaPR2);
    std::cout << "czy x - 3y + 15 = 0 i -3x - y - 10 sa prostopadle: " << ((czyProst) ? "tak" : "nie") << "\n";

}

int main() {
    testPunkt();
    testWektor();
    testProsta();
    testGlobalnych();
    return 0;
}
