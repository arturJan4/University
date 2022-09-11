#include "tests.hpp"

void testKonstruktorDomyslny() {
    try
    {
        stos* nowyStos = new stos();
        std::cout << "ilosc elementow: " << nowyStos->rozmiar() << "\n";
        std::cout << "obecna pojemnosc: " << nowyStos->getCapacity() << "\n";

        nowyStos->wloz("napis");
        std::cout << "obecna pojemnosc: " << nowyStos->getCapacity() << "\n";
        std::cout << "ilosc elementow: " << nowyStos->rozmiar() << "\n";
        std::cout << "obecny element: " << nowyStos->sciagnij() << "\n";

        //nowyStos->sprawdz();//throws excepetion

        delete nowyStos;
    }
    catch(const std::exception& e)
    {
        std::clog << e.what();
    }
}

void testKonstruktorLista() {
    try
    {
        stos* nowyStos = new stos({"pierwszy", "drugi", "trzeci", "czwarty"});
        std::cout << "obecna pojemnosc: " << nowyStos->getCapacity() << "\n";
        std::cout << "ilosc elementow: " << nowyStos->rozmiar() << "\n";
        std::cout << "obecny element: " << nowyStos->sprawdz() << "\n";

        nowyStos->sciagnij();
        nowyStos->sciagnij();
        nowyStos->sciagnij();
        std::cout << "obecna pojemnosc: " << nowyStos->getCapacity() << "\n";
        std::cout << "ilosc elementow: " << nowyStos->rozmiar() << "\n";

        delete nowyStos;
    }
    catch(const std::exception& e)
    {
        std::clog << e.what();
    }
}

void testKonstruktorPojemnosc() {
    try
    {
        stos* nowyStos = new stos(10);
        nowyStos->wloz("napis");
        for(int i = 0; i < 100; ++i)
        {
            nowyStos->wloz("42");
        }
        std::cout << "obecna pojemnosc: " << nowyStos->getCapacity() << "\n";
        for(int i = 0; i < 100; ++i)
        {
            nowyStos->sciagnij();
        }
        std::cout << "obecny element: " << nowyStos->sprawdz() << "\n";
        std::cout << nowyStos->sciagnij() << "\n";
        std::cout << "obecna pojemnosc: " << nowyStos->getCapacity() << "\n";
        //std::cout << nowyStos->sciagnij() << "\n"; // throws exception
        delete nowyStos;
    }
    catch(const std::exception& e)
    {
        std::clog << e.what();
    }
}

void testKonstruktorKopiujacy() {
    try
    {
        stos* nowyStos = new stos({"jeden","dwa","trzy"});
        stos drugiStos(*nowyStos);

        std::cout << "===pierwszy stos=== \n";
        std::cout << "obecna pojemnosc: " << nowyStos->getCapacity() << "\n";
        std::cout << "ilosc elementow: " << nowyStos->rozmiar() << "\n";
        std::cout << "obecny element: " << nowyStos->sciagnij() << "\n";

        std::cout << "===drugi stos=== \n";
        std::cout << "obecna pojemnosc: " << drugiStos.getCapacity() << "\n";
        std::cout << "ilosc elementow: " << drugiStos.rozmiar() << "\n";
        std::cout << "obecny element: " << drugiStos.sciagnij() << "\n";

        delete nowyStos;
    }
    catch(const std::exception& e)
    {
        std::clog << e.what();
    }
}

void testKonstruktorPrzenoszacy() {
    try
    {
        stos* nowyStos = new stos({"jeden","dwa","trzy"});
        stos drugiStos(std::move(*nowyStos));

        std::cout << "===pierwszy stos=== \n";
        std::cout << "obecna pojemnosc: " << nowyStos->getCapacity() << "\n";
        std::cout << "ilosc elementow: " << nowyStos->rozmiar() << "\n";
        std::cout << "obecny element zwraca blad \n";

        std::cout << "===drugi stos=== \n";
        std::cout << "obecna pojemnosc: " << drugiStos.getCapacity() << "\n";
        std::cout << "ilosc elementow: " << drugiStos.rozmiar() << "\n";
        std::cout << "obecny element: " << drugiStos.sciagnij() << "\n";

        delete nowyStos;
    }
    catch(const std::exception& e)
    {
        std::clog << e.what();
    }
}

void testOperatorKopiujacy() {
    try
    {
        stos* nowyStos = new stos({"jeden","dwa","trzy"});
        stos drugiStos;
        drugiStos = *nowyStos;

        std::cout << "===pierwszy stos=== \n";
        std::cout << "obecna pojemnosc: " << nowyStos->getCapacity() << "\n";
        std::cout << "ilosc elementow: " << nowyStos->rozmiar() << "\n";
        std::cout << "obecny element: " << nowyStos->sciagnij() << "\n";

        std::cout << "===drugi stos=== \n";
        std::cout << "obecna pojemnosc: " << drugiStos.getCapacity() << "\n";
        std::cout << "ilosc elementow: " << drugiStos.rozmiar() << "\n";
        std::cout << "obecny element: " << drugiStos.sciagnij() << "\n";

        delete nowyStos;
    }
    catch(const std::exception& e)
    {
        std::clog << e.what();
    }
}

void testOperatorPrzenoszacy() {
    try
    {
        stos* nowyStos = new stos({"jeden","dwa","trzy"});
        stos drugiStos;
        drugiStos = std::move(*nowyStos);

        std::cout << "===pierwszy stos=== \n";
        std::cout << "obecna pojemnosc: " << nowyStos->getCapacity() << "\n";
        std::cout << "ilosc elementow: " << nowyStos->rozmiar() << "\n";
        std::cout << "obecny element: zwraca blad \n";

        std::cout << "===drugi stos=== \n";
        std::cout << "obecna pojemnosc: " << drugiStos.getCapacity() << "\n";
        std::cout << "ilosc elementow: " << drugiStos.rozmiar() << "\n";
        std::cout << "obecny element: " << drugiStos.sciagnij() << "\n";

        delete nowyStos;
    }
    catch(const std::exception& e)
    {
        std::clog << e.what();
    }
}

void testMetodaOdwroc() {
    try {
        stos *pustyStos = new stos();
        stos oPustyStos(std::move(pustyStos->odwroc()));

        std::cout << "===pusty stos=== \n";
        std::cout << "obecna pojemnosc: " << oPustyStos.getCapacity() << "\n";
        std::cout << "ilosc elementow: " << oPustyStos.rozmiar() << "\n";
        //std::cout << "obecny element: " << oPustyStos.sprawdz() << "\n";//exception

        stos *liczby = new stos({"jeden", "dwa", "trzy", "cztery"});
        stos oLiczby(std::move(liczby->odwroc()));
        std::cout << "===stos 4 liczb=== \n";
        std::cout << "obecna pojemnosc: " << oLiczby.getCapacity() << "\n";
        std::cout << "ilosc elementow: " << oLiczby.rozmiar() << "\n";
        std::cout << "obecny element: " << oLiczby.sprawdz() << "\n";
    }
    catch(const std::exception& e)
    {
        std::clog << e.what();
    }
}

