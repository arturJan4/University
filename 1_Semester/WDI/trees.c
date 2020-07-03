#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define COUNT 10
typedef struct node *pnode;
typedef struct node{
    int val;
    pnode left;
    pnode right;
}snode;

void print2DUtil(pnode root, int space)
{
    if (root == NULL)
        return;

    space += COUNT;
    print2DUtil(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->val);

    print2DUtil(root->left, space);
}

void print2D(pnode root)
{
    print2DUtil(root, 0);
}


pnode utworz(int wart)
{
    pnode pom;
    pom = (pnode)malloc(sizeof(snode));
    pom->left = NULL;
    pom->right = NULL;
    pom->val = wart;
    return pom;
}

pnode insert(pnode root, int nkey)
{
    if(root == NULL)return utworz(nkey);

    if(nkey < root->val)
        root->left =  insert(root->left, nkey);
    else if(nkey > root->val)
        root->right = insert(root->right,nkey);
    return root;
}

void write(pnode root)
{
    if(root == NULL)return;

    write(root->left);
    printf("%d ", root->val);
    write(root->right);
}

//zad2
int countElements(pnode t)
{
    if(t == NULL)return 0;

    else return (countElements(t->left) + countElements(t->right) + 1);
}

//zad3
int depthOfTree(pnode t)
{
    if(t == NULL)return 0;

    int depLewe = depthOfTree(t->left);
    int depPrawe = depthOfTree(t->right);

    if(depLewe > depPrawe)
        return depLewe + 1;
    else return depPrawe + 1;
}

//zad4
void writeDod(pnode t)
{
    if(t == NULL)return;

    writeDod(t->left);
    if(t->val > 0)printf("%d", t->val);
    writeDod(t->right);
}

//zad5
//cos za proste(inna metoda?)
int last = INT_MIN;
bool isBST(pnode t)
{
    if(t == NULL)return true;

    bool isLeft = isBST(t->left);

    bool isB = (t->val > last);
    last = t->val;
    if(!isB)return false;

    bool isRight = isBST(t->right);

    return isB && isLeft && isRight;
}

//zad6
pnode zlaczDrzewa(pnode pierwsze, pnode drugie)
{
    pnode root = pierwsze;
    if(pierwsze == NULL)return drugie;

    while(pierwsze->right != NULL)
    {
        pierwsze = pierwsze->right;
    }
    pierwsze->right = drugie;

    return root;
}

//zad7
void wypiszVer1(pnode t)
{
    if(t == NULL)return;

    printf("%d ", t->val);
    wypiszVer1(t->left);
    wypiszVer1(t->right);
}

//zad8
pnode rotacja(pnode u, pnode v)
{
    if(u == NULL || v == NULL)return NULL;
    u->left = v->right;
    v->right = u;

    return v;
}

int main()
{
    pnode start = utworz(2);
    insert(start,3);
    insert(start,5);
    insert(start,-4);
    insert(start,1);
    insert(start,0);

    write(start);printf("\n");
    //printf("%d", start->right->val);

    insert(start->left->right, 2);
    print2D(start);printf("\n\n\n");
    printf("elements : %d\n", countElements(start));
    printf("depth : %d\n", depthOfTree(start));
    printf("printfVer1: \n");wypiszVer1(start);printf("\n");

    if(isBST(start))
        printf("is BST");
    else printf("not BST");

    printf("\n");



    if(isBST(start))
        printf("is BST");
    else printf("not BST");
//    pnode drugie = utworz(6);
//    insert(drugie,7);
//    insert(drugie,13);
//    insert(drugie,9);
//
//    print2D(drugie);
//    start = zlaczDrzewa(start,drugie);
//    print2D(start);
//
//    printf("\n");
//    pnode rotTest = utworz(4);
//    insert(rotTest,2);
//    insert(rotTest,6);
//    insert(rotTest,1);
//    insert(rotTest,3);
//    print2D(rotTest);
//
//    rotTest = rotacja(rotTest, rotTest->left);
//    print2D(rotTest);
    return 0;
}
