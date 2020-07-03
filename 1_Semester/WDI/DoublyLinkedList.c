#include <stdio.h>
#include <stdlib.h>

struct elem
{
    int val;
    struct elem *next;
    struct elem *prev;
};

struct elem *utworz(int wart)
{
    struct elem *pom;
    pom = (struct elem *)malloc(sizeof(struct elem));
    pom->val = wart;
    pom->next = NULL;
    pom->prev = NULL;

    return pom;
}

struct elem* dodaj_koniec(struct elem *kolejka, int wart)
{
    struct elem *start = kolejka;
    struct elem *nowy = utworz(wart);

    if(kolejka == NULL)
        return nowy;

    while(kolejka->next != NULL)
    {
        kolejka = kolejka->next;
    }
    kolejka->next = nowy;
    nowy->prev = kolejka;

    return start;
}

struct elem* usun_pocz(struct elem *kolejka)
{
    struct elem *start = kolejka;

    if(kolejka == NULL)
        return NULL;

    while(kolejka->prev != NULL)
    {
        kolejka = kolejka->prev;
    }
    start = kolejka->next;

    if(kolejka->next != NULL)
        kolejka->next->prev = NULL;

    free(kolejka);

    return start;
}

void wypisz(struct elem* kolejka)
{
    while(kolejka != NULL)
    {
        printf("%d ", kolejka->val);
        kolejka = kolejka->next;
    }
}

int main()
{
    struct elem* start = utworz(2);
    start = dodaj_koniec(start,2);
    start = dodaj_koniec(start,5);
    start = dodaj_koniec(start,-2);
    start = dodaj_koniec(start,3);
    start = dodaj_koniec(start,4);

    start = usun_pocz(start->next->next);
    start = usun_pocz(start->next->next);
    start = usun_pocz(start->next->next);
    start = usun_pocz(start);
    start = usun_pocz(start);
    start = usun_pocz(start);

    start = dodaj_koniec(start,2);

    wypisz(start);
    return 0;
}
