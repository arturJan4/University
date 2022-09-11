/*
 *      Artur Jankowski
 *      CPP - zadanie 8
 *      indeks: 317928
 */
#include <iostream>
#include "list.hpp"
#include "funkcje.hpp"
#include  <stdlib.h>

// list using generics

void testKonstruktorow()
{
    std::cout << "\n";
    std::cout << "=======TEST KONSTRUKTOROW======\n";
    std::cout << "--Lista()--\n";
    List<int> defaultL;
    std::cout << defaultL << "\n";

    std::cout << "--Lista(lista inicjalizacyjna)--\n";
    List<char> i1({'a','b'});
    std::cout << i1 << "\n";

    List<int> i2({1,0,0,0,1,1});
    std::cout << i2 << "\n";

    List<const char*> stringLiteral({"abc","dba","vfx"});
    std::cout << stringLiteral << "\n";

    std::cout << "--kopia--\n";
    List<int> i3({1,2});
    List<int> c1(i3);
    std::cout << c1 << "\n";

    List<int> c2 = i3;
    std::cout << c2 << "\n";

    List<int> c3;
    c3 = i3;
    std::cout << c3 << "\n";

    std::cout << "--przeniesienie--\n";
    List<double> i4({1.2,2.3,3.4});
    List<double> m1(std::move(i4));
    std::cout << m1 << "\n";
    List<double> m2 = std::move(m1);
    std::cout << m2 << "\n";
    std::cout << "poprzednia liste jest pusta - " << m1 << "\n";
}

void testOperacjiNaLiscie()
{
    std::cout << "\n";
    std::cout << "=======TEST OPERACJI======\n";
    std::cout << "--pop(front i back),insert(index),remove(value)--\n";
    List<int> t1;
    t1.insertFront(2);
    t1.popBack();
    t1.insertBack(3);
    t1.popFront();
    std::cout << t1 << "\n";


    t1.insertFront(1);
    t1.insertFront(2);
    t1.insertFront(3);
    t1.insertFront(4);
    t1.insertFront(5);
    t1.insertFront(6);
    t1.insertFront(7);

    std::cout << t1 << "\n";

    t1.popFront();
    std::cout << t1 << "\n";

    t1.popBack();
    std::cout << t1 << "\n";

    t1.remove(6); //front
    std::cout << t1 << "\n";

    t1.remove(3); //mid
    std::cout << t1 << "\n";

    t1.remove(2); //back
    std::cout << t1 << "\n";

    t1.remove(5); //one element
    t1.remove(4); //last element
    std::cout << t1 << "\n";

    //tworzenie listy przy pomocy insert
    t1.insert(0,0);
    t1.insert(1,1);
    t1.insert(2,2);
    std::cout << t1 << "\n";

    std::cout << "--findElement,CountElements--\n";
    List<std::string> t2({"abc","def","ghe"});
    std::cout << t2 << "\n";
    std::cout << "liczba elementow: " << t2.countElements() << "\n";
    std::cout << "indeks elementu 'abc': " << t2.findElem("abc") << "\n";
    std::cout << "indeks elementu 'def': " << t2.findElem("def") << "\n";
    std::cout << "indeks elementu 'ghe': " << t2.findElem("ghe") << "\n";
    std::cout << "indeks elementu 'xyz': " << t2.findElem("xyz") << "\n";
}

void testObslugiBledow()
{
    std::cout << "\n";
    std::cout << "=======TEST OBSLUGI BLEDOW======\n";
    List<int> pusta;
    try{
        pusta.popFront();
    }
    catch (const std::exception &ex) {
        std::clog << ex.what() << "\n";
    }
    try{
        pusta.popBack();
    }
    catch (const std::exception &ex) {
        std::clog << ex.what() << "\n";
    }
    try{
        pusta.insert(42,1);
    }
    catch (const std::exception &ex) {
        std::clog << ex.what() << "\n";
    }
    try{
        pusta.insertFront(1);
        pusta.insertFront(2);
        pusta.insertFront(3);
        pusta.remove(4);
    }
    catch (const std::exception &ex) {
        std::clog << ex.what() << "\n";
    }
}

void testFunkcji()
{
    std::cout << "\n";
    std::cout << "=======TEST FUNKCJI======\n";
    std::cout << "--sort i check(<=)--\n";
    List<double> t1{1.3,6.0,4.0,2.2,3.14,2.84};
    std::cout << t1 << "\n";
    std::cout << "sorted? : " << ((check(t1)) ? "true" : "false") << "\n";
    sort(t1);
    std::cout << t1 << "\n";
    std::cout << "sorted? : " << ((check(t1)) ? "true" : "false") << "\n";

    List<const char*> t2{"abe", "abf", "nba", "zus", "csi", "ksi"};
    std::cout << t2 << "\n";
    std::cout << "sorted? : " << ((check(t2)) ? "true" : "false") << "\n";
    sort(t2);
    std::cout << t2 << "\n";
    std::cout << "sorted? : " << ((check(t2)) ? "true" : "false") << "\n";

    std::cout << "--SORT I CHECK (>=)--\n";
    List<char> t3{'a','b','f','g','l','a','c'};
    std::cout << t3 << "\n";
    std::cout << "sorted? : " << ((check<char,porRev<char>>(t3)) ? "true" : "false") << "\n";
    sort<char,porRev<char>>(t3);
    std::cout << t3 << "\n";
    std::cout << "sorted? : " << ((check<char,porRev<char>>(t3)) ? "true" : "false") << "\n";
}

template<class T>
void testInterOperation()
{
    List<T> *myList = new List<T>();
    bool choosed = false;

    while (!choosed)
    {
        system("CLS");              //windows
        //std::cout << "\033[2J\033[1;1H";   //linux

    std::cout << "Wybierz operacje (wpisz liczbe):\n";
    std::cout << "0. dodaj element na przod listy\n";
    std::cout << "1. dodaj element na tyl listy\n";
    std::cout << "2. usun element z przodu listy\n";
    std::cout << "3. usun element z tylu listy \n";
    std::cout << "4. dodaj element na dany indeks\n";
    std::cout << "5. usun pierwszy element o podanej wartosci\n";
    std::cout << "6. wyszukaj pierwszy element o podanej wartosci\n";
    std::cout << "7. sprawdz czy lista jest posortowana malejaco\n";
    std::cout << "8. sprawdz czy lista jest posortowana rosnaco\n";
    std::cout << "9. posortuj malejaco\n";
    std::cout << "10. posortuj rosnaco\n";
    std::cout << "11. wyjdz\n";
    std::cout << "obecna lista: " << *myList << "\n";

    int option,option2;
    size_t optionIndex;
    T optionInput;

        std::string input;
        std::cin >> input;

        try
        {
            option = std::stoi(input);
            if(option < 0 || option > 11)
                throw std::invalid_argument("nie mozna wykonac takiej operacji\n");
        }
        catch(std::invalid_argument& err)
        {
            std::cerr << err.what();
        }

        switch (option)
        {
            case 0:
                std::cout << "podaj argument: \n";
                std::cin >> optionInput;
                myList->insertFront(optionInput);
                break;
            case 1:
                std::cout << "podaj argument: \n";
                std::cin >> optionInput;
                myList->insertBack(optionInput);
                break;
            case 2: break;
                std::cout << "usunieto: " << myList->popFront() << "\n";
                break;
            case 3:
                std::cout << "usunieto: " << myList->popBack() << "\n";
                break;
            case 4:
                std::cout << "podaj indeks: \n";
                std::cin >> optionIndex;
                std::cout << "podaj argument: \n";
                std::cin >> optionInput;
                myList->insert(optionInput,optionIndex);
                break;
            case 5:
                std::cout << "podaj wartosc: \n";
                std::cin >> optionInput;
                myList->remove(optionInput);
                break;
            case 6:
                std::cout << "podaj wartosc: \n";
                std::cin >> optionInput;
                std::cout << "znaleziono na indeksie: " <<myList->findElem(optionInput) << "\n";
                break;
            case 7:
                std::cout << "sorted? : " << ((check<T,porRev<T>>(*myList)) ? "true" : "false") << "\n";
                break;
            case 8:
                std::cout << "sorted? : " << ((check(*myList)) ? "true" : "false") << "\n";
                break;
            case 9:
                sort<T,porRev<T>>(*myList);
                break;
            case 10:
                sort(*myList);
                break;
            case 11: choosed = true; delete myList; return; break;
            default: std::cout << "Wprowadzano niepoprawna liczbe, sprobuj ponownie \n";
                break;
        }
    }
    delete myList;
}

void testInterchooseClass()
{
    int option;
    std::cout << "Wybierz typ Klasy (wpisz liczbe):\n";
    std::cout << "0. int\n";
    std::cout << "1. double\n";
    std::cout << "2. char\n";
    std::cout << "3. std::string\n";

    bool choosed = false;
    while (!choosed)
    {

    std::string input;
    std::cin >> input;

        try
        {
            option = std::stoi(input);
            if(option < 0 || option > 3)
                throw std::invalid_argument("nie mozna wykonac takiej operacji\n");
        }
        catch(std::invalid_argument& err)
        {
            std::cerr << err.what();
        }

        switch (option)
    {
        case 0:
            testInterOperation<int>();
            choosed = true; break;
        case 1:
            testInterOperation<double>();
            choosed = true; break;
        case 2:
            testInterOperation<char>();
            choosed = true; break;
        case 3:
            testInterOperation<std::string>();
            choosed = true; break;
        default: std::cout << "Wprowadzano niepoprawna cyfre, sprobuj ponownie \n";
            break;
    }
    }
}

void testInteraktywny()
{
    testInterchooseClass();
}

void testSuite()
{
    testKonstruktorow();
    testOperacjiNaLiscie();
    testFunkcji();
    testObslugiBledow();
};

int main()
{
    testSuite();
    //testInteraktywny();
    return 0;
}
