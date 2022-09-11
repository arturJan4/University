#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 1000000

// sorting using a trie tree

struct Node;
struct Node
{
    int count;
    struct Node* edges[26];
}Node;

void printTrie(struct Node* wsk)
{
    if(wsk == NULL)return;

    for(int i = 0; i < 26; ++i)
    {
        if(wsk->edges[i] != NULL)
        {
            printf("(%c : %d)", i + 'a', wsk->edges[i]->count);
            printTrie(wsk->edges[i]);
        }
    }
}

void addToTrie(struct Node *wsk, char *napis, unsigned int i)
{
    if(strlen(napis) == i)return;
    char curCh = napis[i];

    if(wsk->edges[curCh - 'a'] == NULL)
        wsk->edges[curCh - 'a'] = (struct Node*)calloc(sizeof(Node),1);

    if(strlen(napis) - 1 == i)
        (wsk->edges[curCh - 'a']->count) += 1;

    addToTrie(wsk->edges[napis[i] - 'a'],napis,i+1);
}

char napis[MAX_SIZE];
char input[MAX_SIZE];

void recursiveSearch(struct Node *wsk, char* napis, int curI)
{
    if(wsk->count > 0)
    {
        for(int i = 0; i < wsk->count; ++i)
        {
            printf("%s\n", napis);
        }
    }

    for(int i = 0; i < 26; ++i)
    {
        if(wsk->edges[i] != NULL)
        {
           napis[curI] = (char)(i +'a');
           recursiveSearch(wsk->edges[i],napis, curI + 1);
           napis[curI] = ' ';
        }
    }
}

int main()
{
    struct Node *root = (struct Node*)calloc(sizeof(Node),1);

    while(fgets(input, MAX_SIZE, stdin))
    {
        input[strlen(input)-1] = 0;
        addToTrie(root,input,0);

        //printf("%s", input);
    }
    printf("\n");
    recursiveSearch(root,napis,0);

    //printTrie(root);
    return 0;
}
