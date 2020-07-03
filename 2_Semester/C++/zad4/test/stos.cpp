#include "stos.hpp"

stos::stos() {
    this->pojemnosc = 1;
    tablica = new std::string[this->pojemnosc];
    ile = 0;
    std::cerr << "Wywolano domyslny konstruktor\n";
}

stos::stos(int pojemnosc) : stos()
{
    if(pojemnosc < 1 || pojemnosc > 100)
        throw std::invalid_argument("pojemnosc musi byc dododatnia i nie wieksza od 100\n");

    this->pojemnosc = findClosest2thPower(pojemnosc);
    tablica = new std::string[this->pojemnosc];
    std::cerr << "Wywolano konstruktor z podana pojemnoscia\n";
}

stos::stos(const std::initializer_list<std::string> &napisy) : stos(static_cast<int>(napisy.size()))
{
    if(napisy.size() == 0)
        throw std::invalid_argument("lista inicjalizacyjna musi byc niepusta\n");

    std::initializer_list<std::string>::iterator it;
    for(it = napisy.begin(); it != napisy.end(); ++it)
    {
        this->wloz(*it);
    }
    std::cerr << "Wywolano konstruktor z lista inicjalizacyjna\n";
}

stos::stos(const stos &objekt)
        : tablica(objekt.pojemnosc ? (new std::string[objekt.pojemnosc]) : nullptr),
          ile(objekt.ile),
          pojemnosc(objekt.pojemnosc)
{
    if(tablica)
    {
        std::copy(objekt.tablica,objekt.tablica + ile,tablica);
    }
    std::cerr << "Wywolano konstruktor kopiujacy\n";
}

stos &stos::operator=(const stos &objekt) {
    //przypisanie do samego sieibe
    if(&objekt == this)
        return *this;

    tablica = new std::string[objekt.pojemnosc];
    ile = objekt.ile;
    pojemnosc = objekt.pojemnosc;
    std::cerr << "Wywolano operator przypisania kopiujacego\n";
    return *this;
}

stos::stos(stos &&objekt) : tablica(objekt.tablica), ile(objekt.ile), pojemnosc(objekt.pojemnosc)
{
    objekt.tablica = nullptr;
    std::cerr << "Wywolano konstruktor przenoszacy \n";
}

stos &stos::operator=(stos &&objekt) {
    //przypisanie do samego sieibe
    if(&objekt == this)
        return *this;

    delete[] this->tablica;
    tablica = objekt.tablica;
    ile = objekt.ile;
    pojemnosc = objekt.pojemnosc;
    objekt.tablica = nullptr;

    std::cerr << "Wywolano operator przypisania przenoszacego\n";
    return *this;
}

void stos::wloz(const std::string &input) {
    if(ile == pojemnosc)//grow array
    {
        pojemnosc *= 2;
        auto newArray = new std::string[pojemnosc];
        std::copy(tablica,tablica + ile, newArray);
        delete[] tablica;
        tablica = newArray;
    }
    ++ile;
    tablica[ile-1] = input;
}

std::string stos::sciagnij() {
    if(ile == 0)
        throw std::invalid_argument("stos jest pusty\n");
    if(ile <= pojemnosc/2)//shrink array
    {
        pojemnosc /= 2;
        //przypadek gdy mamy duzy array  po uzyciu stos(capacity) i sciagamy
        while(ile <= (pojemnosc/2))
        {
            pojemnosc /= 2;
        }
        auto newArray = new std::string[pojemnosc];
        std::copy(tablica,tablica + ile, newArray);
        delete[] tablica;
        tablica = newArray;
    }
    --ile;
    return tablica[ile];
}

std::string stos::sprawdz() {
    if(ile == 0)
        throw std::invalid_argument("stos jest pusty\n");

    return tablica[ile-1];
}

int stos::rozmiar() {
    return ile;
}

int stos::getCapacity() {
    return this->pojemnosc;
}

stos stos::odwroc() {
    stos nowyStos = stos(this->pojemnosc);
    int iterator = ile;
    while(iterator > 0)
    {
        nowyStos.wloz(this->tablica[iterator-1]);
        --iterator;
    }

    return nowyStos;
}

stos::~stos() {
    std::cerr << "Wywolano destruktor stosu\n";
    if(this != nullptr)
        delete[] tablica;
}

int findClosest2thPower(int pojemnosc) {
    int i = 1;

    while(i < pojemnosc)
    {
        i *= 2;
    }
    return i;
}
