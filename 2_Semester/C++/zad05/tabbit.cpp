/*
    C++ lista 5
    Artur Jankowski
    indeks 317928
 */

#include "tabbit.hpp"

void dbgCtorSize() {
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] size \n";
#endif
}

void dbgCtorPattern() {
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] pattern \n";
#endif
}

void dbgCtorList() {
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] initializer list \n";
#endif
}

void dbgCtorCopy() {
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] copy\n";
#endif
}

void dbgCtorMove() {
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] move\n";
#endif
}

void dbgCtorAssigCopy() {
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] copy - assignment\n";
#endif
}

void dbgCtorAssignMove() {
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] move - assignment \n";
#endif
}
//------------------------------------------------------------------------
tab_bit::tab_bit(int rozm) : dl(rozm)
{
    dbgCtorSize();
    if(rozm < 1)
        throw std::invalid_argument("nieprawidlowy rozmiar tablicy");

    int sizeOfArray = std::ceil(static_cast<double>(rozm)/tab_bit::rozmiarSlowa);
    tab = new slowo[sizeOfArray];
    test();
}

tab_bit::tab_bit(tab_bit::slowo tb)
{
    dbgCtorPattern();
    dl = tab_bit::rozmiarSlowa;
    tab = new slowo[1];
    tab[0] = tb;
}

tab_bit::tab_bit(const std::initializer_list<bool>& list) : dl(list.size())
{
    dbgCtorList();

    if(list.size() == 0)
        throw std::invalid_argument("lista inicjalizacyjna musi byc niepusta\n");

    dl = list.size();
    int sizeOfArray = std::ceil(static_cast<double>(dl)/rozmiarSlowa);
    tab = new slowo[sizeOfArray];

    std::initializer_list<bool>::iterator it;
    int i = 0;
    for(it = list.begin(); it != list.end(); ++it)
    {
        pisz(i,*it);
        ++i;
    }
}

tab_bit::tab_bit(const tab_bit &tb) //konstruktor kopiujacy
        :dl(tb.dl)
{
    dbgCtorCopy();
    size_t sizeOfArray = std::ceil(static_cast<double>(tb.rozmiar())/tab_bit::rozmiarSlowa);
    this->tab = ((sizeOfArray == 0) ? nullptr : new slowo[sizeOfArray]);
    if(sizeOfArray)
    {
        std::copy(tb.tab,tb.tab + sizeOfArray,this->tab);
    }
}

tab_bit& tab_bit::operator=(const tab_bit &tb)  //przypisanie kopiujace
{
    dbgCtorAssigCopy();
    //przypisanie do samego siebie
    if(&tb == this)
        return *this;

    delete[] tab;

    this->dl = tb.dl;
    size_t sizeOfArray = std::ceil(static_cast<double>(tb.rozmiar())/tab_bit::rozmiarSlowa);
    tab = new slowo[sizeOfArray];
    if(sizeOfArray)
    {
        std::copy(tb.tab,tb.tab + sizeOfArray,this->tab);
    }

    return *this;
}

tab_bit::tab_bit(tab_bit &&tb) noexcept  //konstruktor przenoszacy
        :dl(tb.dl), tab(tb.tab)
{
    dbgCtorMove();
    tb.tab = nullptr;
}

tab_bit &tab_bit::operator=(tab_bit &&tb) noexcept //przypisanie przenoszace
{
    dbgCtorAssignMove();
    //przypisanie do samego siebie
    if(&tb == this)
        return *this;

    delete[] this->tab;

    this->tab = tb.tab;
    this->dl = tb.dl;

    tb.tab = nullptr;

    return *this;
}

tab_bit::~tab_bit()
{
    delete[] tab;
}
//------------------------------------------------------------------------
//pomocnicze
bool tab_bit::czytaj(int i) const  //tablice indeksowane 0 - 63
{
    if(i < 0 || i >= rozmiar())// >= ?
    {
        std::cerr << i;
        throw std::invalid_argument("indeks poza tablica (przy czytaniu)");
    }
    size_t whichArray = i/rozmiarSlowa;
    int currBit = i % rozmiarSlowa;
    unsigned long long shiftedBit = 1ull << currBit;
    return static_cast<bool>(tab[whichArray] & shiftedBit);
}

bool tab_bit::pisz(int i, bool b)
{
    if(i < 0 || i >= rozmiar())// >= ?
    {
        throw std::invalid_argument("indeks poza tablica (przy pisaniu)");
    }
    size_t whichArray = i/rozmiarSlowa;
    int currBit = i % rozmiarSlowa;
    unsigned long long shiftedBit = 1ull << currBit; //maska z tylko jednym zapalonym bitem na indeksie i
    auto newB = static_cast<unsigned long long>(b);
    tab[whichArray] = ((tab[whichArray]  & (~shiftedBit)) | ((newB << i) & shiftedBit));
    return b;
}

void tab_bit::test()
{
   // std::cout << rozmiar();
}
//------------------------------------------------------------------------
//operatory indeksowania(tablica indeksowana [0-63] ale x[1] ma dac pierwszy element czyli tab[0]
bool tab_bit::operator[](int i) const
{
    if(i < 0 || i >= this->rozmiar())
        throw std::invalid_argument("indeks poza tablica []");

    return czytaj(i);
}

tab_bit::ref tab_bit::operator[](int i)
{
    if(i < 0 || i >= this->rozmiar())
        throw std::invalid_argument("indeks poza tablica [](ref)");

    return tab_bit::ref(i, this);
}

//------------------------------------------------------------------------
//operatory bitowe
tab_bit operator|(const tab_bit &tb1, const tab_bit &tb2)
{
    //element neutralny 0, dopelniamy do dluzszej tablicy
    tab_bit answer(static_cast<int>(std::max(tb1.dl,tb2.dl)));
    if(tb1.dl < tb2.dl)
    {
            for(int i = 0; i < tb1.dl; ++i)
            {
                bool inter = tb1.czytaj(i) | tb2.czytaj(i);
                answer.pisz(i,(tb1,inter));
            }
            for(int j = tb1.dl; j < tb2.dl; ++j)
            {
                answer.pisz(j,tb2.czytaj(j));
            }
    }
    else
    {
        for(int i = 0; i < tb2.dl; ++i)
        {
            bool inter = tb1.czytaj(i) | tb2.czytaj(i);
            answer.pisz(i,(tb2,inter));
        }
        for(int j = tb2.dl; j < tb1.dl; ++j)
        {
            answer.pisz(j,tb1.czytaj(j));
        }
    }
    return answer;
}

tab_bit &tab_bit::operator|=(const tab_bit& tb1)
{
    tab_bit temp = (*this | tb1);
    *this = std::move(temp);

    return *this;
}

tab_bit operator&(const tab_bit &tb1, const tab_bit &tb2)
{
        //element neutralny 1, dopelniamy do dluzszej tablicy
        tab_bit answer(static_cast<int>(std::max(tb1.dl,tb2.dl)));
        if(tb1.dl < tb2.dl)
        {
            for(int i = 0; i < tb1.dl; ++i)
            {
                bool inter = tb1.czytaj(i) & tb2.czytaj(i);
                answer.pisz(i,(tb1,inter));
            }
            for(int j = tb1.dl; j < tb2.dl; ++j)
            {
                answer.pisz(j,tb2.czytaj(j));
            }
        }
        else
        {
            for(int i = 0; i < tb2.dl; ++i)
            {
                bool inter = tb1.czytaj(i) & tb2.czytaj(i);
                answer.pisz(i,(tb2,inter));
            }
            for(int j = tb2.dl; j < tb1.dl; ++j)
            {
                answer.pisz(j,tb1.czytaj(j));
            }
        }
        return answer;
}

tab_bit &tab_bit::operator&=(const tab_bit& tb1)
{
    tab_bit temp = (*this & tb1);
    *this = std::move(temp);

    return *this;
}

tab_bit operator^(const tab_bit &tb1, const tab_bit &tb2)
{
    //element neutralny 0, dopelniamy do dluzszej tablicy
    tab_bit answer(static_cast<int>(std::max(tb1.dl,tb2.dl)));
    if(tb1.dl < tb2.dl)
    {
        for(int i = 0; i < tb1.dl; ++i)
        {
            bool inter = tb1.czytaj(i) ^ tb2.czytaj(i);
            answer.pisz(i,(tb1,inter));
        }
        for(int j = tb1.dl; j < tb2.dl; ++j)
        {
            answer.pisz(j,tb2.czytaj(j));
        }
    }
    else
    {
        for(int i = 0; i < tb2.dl; ++i)
        {
            bool inter = tb1.czytaj(i) ^ tb2.czytaj(i);
            answer.pisz(i,(tb2,inter));
        }
        for(int j = tb2.dl; j < tb1.dl; ++j)
        {
            answer.pisz(j,tb1.czytaj(j));
        }
    }
    return answer;
}

tab_bit &tab_bit::operator^=(const tab_bit& tb1)
{
    tab_bit temp = (*this ^ tb1);
    *this = std::move(temp);

    return *this;
}

tab_bit operator!(const tab_bit& tb1)
{
    tab_bit answer(tb1);

    int sizeOfArray = std::ceil(static_cast<double>(tb1.rozmiar()/tab_bit::rozmiarSlowa));
    for(int i = 0; i <= sizeOfArray; ++i)
    {
        answer.tab[i] = ~(tb1.tab[i]);
    }

    return answer;
}
//------------------------------------------------------------------------
//zaprzyjaznione operatory strumieniowe
std::istream &operator>>(std::istream &we, tab_bit &tb)
{
    std::string input;
    we >> input;

    if(input.length() > tb.dl)
        throw std::invalid_argument("za duzo znakow na wejsciu");

    for(int i = 0; i < tb.dl; ++i)
    {
        if(i < input.length())
        {
            if(input[i] == '1')
                tb.pisz(i,true);
            else if(input[i] == '0')
                tb.pisz(i,false);
            else
                throw std::invalid_argument("nieprawidlowe znaki na wejsciu, podaj ciag (0,1)");
        }
        else
            return we;
    }
    return we;
}

std::ostream &operator<<(std::ostream &wy, const tab_bit &tb)
{
    for(int i = 0; i < tb.dl; ++i)
    {
        wy << tb.czytaj(i) <<  " ";
    }
    return wy;
}
//------------------------------------------------------------------------
//klasa ref
tab_bit::ref::ref(int index, tab_bit *tabPtr)
{
    this->index = index;
    this->tabPtr = tabPtr;
}

tab_bit::ref &tab_bit::ref::operator=(const tab_bit::ref &reference)
{
    if(&reference == this)
        return *this;
    tabPtr->pisz(this->index, reference);
    return *this;
}

tab_bit::ref::operator bool() const
{
    return tabPtr->czytaj(this->index);
}

tab_bit::ref &tab_bit::ref::operator=(bool x)
{
    tabPtr->pisz(this->index,x);
    return *this;
}
//------------------------------------------------------------------------
//pomocnicze
long long int tab_bit::toInteger()
{
    if(dl == 0)
        throw std::invalid_argument("no number to convert");
    long long answer = 0;
    long long temp = 1;
    for(int i = 0; i < this->dl; ++i)
    {
        if(this->czytaj(i))
            answer += temp;
        temp *= 2;
    }
    if(answer < 0)
        std::clog << "przekroczono zakres long long\n";
    return answer;
}


