#ifndef ZAD8_LIST_HPP
#define ZAD8_LIST_HPP

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <type_traits>

#if 0//1                          // switch between 0 and 1 ...
#define ENABLE_CTOR_DBG_PRINTs    // do testow, wyswietlanie konstruktorow
#endif                            // ... to respectively disable or enable CTOR DETECTION PRINTs
void dbgCtorList();
void dbgCtorCopy();
void dbgCtorMove();
void dbgCtorAssigCopy();
void dbgCtorAssignMove();

class Base
{
public:
    virtual ~Base() {};
};

template <class T>
class List : public Base               //aby korzystac w run-time z polymorfizmu
{
private:
    class Node
    {
        T val;
        Node *next;
    public:
        Node() : next(nullptr){};
        explicit Node(const T &value) : val(value), next(nullptr){};
        T getValue() {return val;}

        Node* getNext() {return next;}
        void setNext(Node* ptrNext) {this->next = ptrNext;}
    };
    Node* root;
public:
    List(): root(nullptr){};
    List(const std::initializer_list<T> & list);
    List(const List &ls);                        //konstruktor kopiujacy
    List(List &&ls) noexcept;                    //konstruktor przenoszacy
    List& operator=(const List &ls);             //przypisanie kopiujace
    List& operator=(List &&ls) noexcept;         //przypisanie przenoszace
    ~List();

    /* operacje na liscie */
    void insertBack(const T &val);
    void insertFront(const T &val);
    T popBack();
    T popFront();
    //usuwa wszystkie elementy poczawszy od current (wlacznie)
    void insert(const T &value, size_t index);   //wstawia element na list[index] = val, indeksujemy od zera
    void remove(const T &value);                 //usuwa pierwszy w kolejnosci element o podanej wartosci z listy

    std::string toString() const;               //konwersja na std::string
    std::vector<T> toVector() const;            //konwersja na std::vector<T>
    Node* getNode() const;                      //zwraca wskaznik na glowe listy

    /* zapytania */
    bool isEmpty() const;
    int findElem(const T &value) const;         //zwraca indeks pierwszego wystapienia elementu o podanej wartosci
                                                //-1 gdy nie nie ma go w liscie
    size_t countElements() const;               //zwraca liczbe elementow listy

    /* operatory zaprzyjaznione (<<) */
    template<class T1>
    friend std::ostream& operator<<(std::ostream &wyj, const List<T1> &w);
};
/* konstruktory */
template<class T>
List<T>::List(const std::initializer_list<T> &list)
{
    dbgCtorList();
    root = nullptr;
    typename std::initializer_list<T>::iterator it;
    for(it = list.end() - 1; it != list.begin() - 1; --it)// w odwrotnej kolejnosci
    {
        this->insertFront(*it);
    }
}

template<class T>
List<T>::List(const List &ls)
{
    dbgCtorCopy();
    if(ls.root == nullptr)
    {
        root = nullptr;
        return;
    }

    Node *lsIterator = ls.root;
    Node *rootIter;
    root = nullptr;
    Node *prev = nullptr;
    while(lsIterator != nullptr)
    {
        rootIter = new Node(lsIterator->getValue());
        if(root == nullptr)
            root = rootIter;

        if(prev != nullptr)
            prev->setNext(rootIter);

        prev = rootIter;
        lsIterator = lsIterator->getNext();
    }
}

template<class T>
List<T> &List<T>::operator=(const List &ls)
{
    dbgCtorAssigCopy();
    if(&ls == this)
        return *this;
    if(ls.root == nullptr)
    {
        root = nullptr;
        return *this;
    }

    Node *lsIterator = ls.root;
    Node *rootIter;
    root = nullptr;
    Node *prev = nullptr;
    while(lsIterator != nullptr)
    {
        rootIter = new Node(lsIterator->getValue());
        if(root == nullptr)
        {
            root = rootIter;
        }
        if(prev != nullptr)
            prev->setNext(rootIter);

        prev = rootIter;
        lsIterator = lsIterator->getNext();
    }

    return *this;
}

template<class T>
List<T>::List(List &&ls) noexcept
{
    dbgCtorMove();
    root = ls.root;
    ls.root = nullptr;
}

template<class T>
List<T> &List<T>::operator=(List &&ls) noexcept
{
    dbgCtorAssignMove();
    if(&ls == this)
        return *this;

    this->root = ls.root;
    ls.root = nullptr;

    return *this;
}

template<class T>
List<T>::~List()
{
    Node *tempNext;
    for(Node* temp = root; temp != nullptr; temp = tempNext)
    {
        tempNext = temp->getNext();
        delete temp;
    }
}

/* operacje na liscie */
template<class T>
void List<T>::insertBack(const T &val)
{
    Node* newNode = new Node(val);
    Node* iterator = root;
    if(root == nullptr)
        root = newNode;
    else
    {
        while(iterator->getNext() != nullptr)
        {
            iterator = iterator->getNext();
        }
        iterator->setNext(newNode);
    }
}

template<class T>
void List<T>::insertFront(const T &val)
{
    Node* newNode = new Node(val);
    if(root == nullptr)
        root = newNode;
    else
    {
        newNode->setNext(root);
        root = newNode;
    }
}

template<class T>
T List<T>::popFront()
{
    if(root == nullptr)
        throw std::invalid_argument("error - lista jest pusta");
    else if(root->getNext() == nullptr)
    {
        return popBack();
    }
    T value = root->getValue();
    Node *temp = root;
    root = root->getNext();
    delete temp;
    return value;
}

template<class T>
T List<T>::popBack()
{
    Node* iterator = root;
    if(root == nullptr)
        throw std::invalid_argument("error - lista jest pusta");
    else if(root->getNext() == nullptr)
    {
        T value = root->getValue();
        delete iterator;
        root = nullptr;
        return value;
    }
    else
    {
        while(iterator->getNext()->getNext() != nullptr)
        {
            iterator = iterator->getNext();
        }
        T value = iterator->getNext()->getValue();
        delete iterator->getNext();
        iterator->setNext(nullptr);
        return value;
    }
}

template<class T>
void List<T>::insert(const T &value, size_t index)
{
    if(index < 0)
        throw std::invalid_argument("error - indeks musi byc dodatni");
    if(index == 0)
    {
        insertFront(value);
        return;
    }

    Node *iterator = root;
    for(size_t i = 0;  i < index - 1; ++i)
    {
        if(iterator == nullptr)
            throw std::invalid_argument("error - wyjscie poza liste");
        iterator = iterator->getNext();
    }
    if(iterator == nullptr)
        throw std::invalid_argument("error - wyjscie poza liste");

    Node *newNode = new Node(value);
    if(iterator->getNext() != nullptr)
        newNode->setNext(iterator->getNext()->getNext());
    iterator->setNext(newNode);
}

template<class T>
void List<T>::remove(const T &value)
{
    Node* iterator = root;
    if(iterator->getValue() == value)
    {
        popFront();
        return;
    }
    else if(iterator->getNext() == nullptr)
    {
        throw std::invalid_argument("error - brak wartosci do usuniecia");
    }

    while(iterator->getNext()->getValue() != value)
    {
        iterator = iterator->getNext();
        if(iterator->getNext() == nullptr)
        {
            throw std::invalid_argument("error - brak wartosci do usuniecia");
        }
    }
    Node *deleted = iterator->getNext();
    iterator->setNext(deleted->getNext());//przepinamy nastepnik elementu o wartosci val
    delete deleted;
}

template<class T>
std::string List<T>::toString() const
{
    if(this->root == nullptr)
        return "";

    Node* newNode = root;
    std::ostringstream stream;
    while(newNode != nullptr)
    {
        stream << newNode->getValue() << " ";
        newNode = newNode->getNext();
    }
    std::string out = stream.str();
    if(out.length() > 0)
        out.pop_back();
    return out;
}

template<class T>
std::vector<T> List<T>::toVector() const
{
    size_t count = this->countElements();
    std::vector<T> vct;
    vct.reserve(count);

    Node* newNode = root;
    while(newNode != nullptr)
    {
        vct.push_back(newNode->getValue());
        newNode = newNode->getNext();
    }

    return vct;
}

template<class T>
typename List<T>::Node* List<T>::getNode() const
{
    return root;
}

/* zapytania */
template<class T>
bool List<T>::isEmpty() const
{
    return (root == nullptr);
}

template<class T>
int List<T>::findElem(const T &value) const
{
    size_t index = 0;
    Node* iterator = root;
    while(iterator->getValue() != value)
    {
        iterator = iterator->getNext();
        if(iterator == nullptr)
            return -1;
        ++index;
    }
    return static_cast<int>(index);
}

template<class T>
size_t List<T>::countElements() const
{
    size_t count = 0;
    Node* iterator = root;
    while(iterator != nullptr)
    {
        iterator = iterator->getNext();
        ++count;
    }
    return count;
}

template<class T1>
std::ostream &operator<<(std::ostream &wyj, const List<T1> &w)
{
    std::string out = "LIST: [";
    if(w.root != nullptr)
        out += w.toString();

    out += "]";
    wyj << out;
    return wyj;
}
#endif //ZAD8_LIST_HPP
