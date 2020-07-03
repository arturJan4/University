#include <stdio.h>
#include <stdlib.h>

struct elem
{
    int val;
    struct elem *next;
};

struct elem *utworz(int wart)
{
    struct elem *pom;
    pom = (struct elem *)malloc(sizeof(struct elem));
    pom->val = wart;
    pom->next = NULL;
    return pom;
}

void wypisz_wszystkie(struct elem* lista)
{
    while(lista != NULL)
    {
        printf("%d ", lista->val);
        lista = lista->next;
    }
    printf("\n");
}

void wypisz_dodatnie(struct elem* lista)
{
    while(lista != NULL)
    {
        if(lista->val > 0)
            printf("%d ", lista->val);
        lista = lista->next;
    }
    printf("\n");
}

//implementacja z returnem?
struct elem* dodaj_koniec(struct elem* lista, int val)
{
    struct elem* pom = lista;
    if(pom == NULL)
    {
        return utworz(val);
    }

    while(pom->next != NULL)
    {
        pom = pom->next;
    }
    struct elem *element = utworz(val);
    pom->next = element;

    return lista;
}

//co jesli 1 element //czy lista pomocnicza
struct elem* usun_koniec(struct elem* lista)
{
    if(lista == NULL)return NULL;
    if(lista->next == NULL)
    {
        free(lista);
        lista = NULL;
        return NULL;
    }

    struct elem* pom = lista;
    while(lista->next->next != NULL)
    {
        lista = lista->next;
    }

    free(lista->next);
    lista->next = NULL;
    return pom;
}

struct elem* dodaj_listy(struct elem* lista1, struct elem* lista2)
{
    if(lista1 == NULL)
        return lista2;

    struct elem* pom = lista1;
    while(lista1->next != NULL)
    {
        lista1 = lista1->next;
    }
    lista1->next = lista2;

    return pom;
}

void wypisz_odwrocone(struct elem* lista)
{
    if(lista == NULL)return;
    else
        wypisz_odwrocone(lista->next);
    printf("%d ", lista->val);
}



struct elem* usun_wart(struct elem* lista,int wartosc)
{
    if(lista == NULL)return NULL;

    while(lista != NULL && lista->val == wartosc)
    {
        struct elem* pop = lista;
        lista = lista->next;
        free(pop);
    }

    struct elem *start = lista;
    struct elem *poprzednik;

    while(lista != NULL)
    {
        poprzednik = lista;
        lista = lista->next;

        if(lista == NULL)return start;

        if(lista->val == wartosc)
        {
            poprzednik->next = lista->next;
            free(lista);
            lista = poprzednik;
        }

    }
    return start;
}

struct elem* odwroc_liste(struct elem* lista)
{
    struct elem* pop = NULL;
    struct elem* nast = NULL;

    while(lista != NULL)
    {
        nast = lista->next;
        lista->next = pop;
        pop = lista;
        lista = nast;
    }

    return pop;
}

int main()
{
    struct elem *start = NULL;
    start = dodaj_koniec(start,5);
    start = dodaj_koniec(start,1);
    start = dodaj_koniec(start,-4);
    start = dodaj_koniec(start,5);
    start = dodaj_koniec(start,5);
    start = dodaj_koniec(start,-1);

    start = odwroc_liste(start);

    wypisz_wszystkie(start);

    return 0;
}
