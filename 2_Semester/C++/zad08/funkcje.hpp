#ifndef ZAD8_FUNKCJE_HPP
#define ZAD8_FUNKCJE_HPP
#include <cstring>
#include "list.hpp"

template<class T> class por;
template<class T> class porRev;

template<class T, class C = por<T>>
bool check(const List<T> &list)
{
    //lista zero lub jedno elementowa jest posortowana
    if(list.getNode() == nullptr)
    {
        return true;
    }
    List<T> temp = list;
    T valPrev = temp.popFront();
    while(!temp.isEmpty())
    {
        T val = temp.popFront();
        if(C::lt(val,valPrev))
            return false;
        valPrev = val;
    }
    return true;
}
template<class T, class C = por<T>>
void sort(List<T> &list)
{
    //operacje na list są kosztowne a std::sort szybki więc
    // tworzymy wektor elementów z listy i pushujemy je na nową listę którą potem przenosimy
    List<T> temp;
    std::vector<T> vct = list.toVector();
    size_t count = vct.size();
    std::sort(vct.begin(),vct.end(),//sort in reverse order (because pushing reverses it again)
            [ ]( const T& left, const T& right ){return !(C::lt(left,right));});//lambda c++11

    for(int i = 0; i < count; ++i)
    {
        temp.insertFront(vct[i]);
    }
    list = (std::move(temp));
}

//implementuje <=
template<class T>
class por{
public:
    static bool eq (T a, T b) {return a == b;}
    static bool lt (T a, T b) {return a < b;}
};
//czesciowa specjalizacja
template<class T>
class por<T*>
{
public:
    static bool eq (T *a, T *b) {return *a == *b;}
    static bool lt (T *a, T *b) {return *a < *b;}
};
//pelna specjalizacja dla const char*
template<>
class por<const char *>{
public:
    static bool eq (const char  *a, const char  *b) {return !strcmp(a,b);}
    static bool lt (const char  *a, const char  *b) {return (strcmp(a, b) < 0);}
};

//implementuje >=
template<class T>
class porRev{
public:
    static bool eq (T a, T b) {return a == b;}
    static bool lt (T a, T b) {return a > b;}
};


#endif //ZAD8_FUNKCJE_HPP
