#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// simple directory structure simulation

typedef struct Node
{
    char* name;
    int used;
    struct Node* children[256];
    struct Node* parent;
}Node;

Node* doesExist(Node* parent, char* searchedName)
{
    for(int i = 0; i < parent->used; ++i)
    {
        if(!(strcmp(searchedName,parent->children[i]->name)))
            return parent->children[i];
    }

    return NULL;
}

Node* createNode(Node* current, char* name)
{
    if(doesExist(current,name) != NULL)
        return NULL;
    if(current->used >= 256)return NULL;

    Node* newNode = malloc(sizeof(Node));

    newNode->used = 0;

    newNode->name = malloc(sizeof(name));
    strcpy(newNode->name,name);

    current->children[current->used] = newNode;
    (current->used)++;

    newNode->parent = current;
    return newNode;
}

void printDirectory(Node *current)
{
    if(current == NULL)
    {
        return;
    }

    printDirectory(current->parent);
    printf("%s/",current->name);
}

Node* changeDirectory(Node* current, char* command)
{
    if(!strcmp(command,".."))
    {
        if(current->parent != NULL)
            return current->parent;
        else return current;
    }

    Node* newDir = doesExist(current,command);
    if(newDir == NULL)return current;
    else return newDir;
}

void printNode(Node* current)
{
    printf("name:<%s>\n", current->name);
    printf("used:<%d>\n", current->used);
    (current->parent != NULL) ? printf("parentName:<%s>\n", current->parent->name) : printf("null parent\n");
}

void readInput(Node* root)
{
    char command[512];
    char argument[512];
    while((scanf("%s", command)) != EOF)
    {
        if((strcmp("pwd",command)))
        {
            if(scanf("%s", argument) == EOF)return;
            if(!(strcmp("cd",command)))
            {
                root = changeDirectory(root,argument);
            }
            else if(!(strcmp("mkdir",command)))
            {
                createNode(root,argument);
            }
        }
        else
        {
            printDirectory(root);
            printf("\n");
        }
    }
}
/*
void testCreateNode(Node* root)
{
    Node* node1 = createNode(root,"ab");
    printNode(node1);
    printNode(root);
}

void testPrintDirectory(Node *root)
{
    Node* node1 = createNode(root,"ab");
    Node* node2 = createNode(node1,"c");
    Node* node3 = createNode(node2,"d");
    Node* node4 = createNode(node2,"e");

    printDirectory(root);
    printf("\n=========\n");
    printDirectory(node2);
    printf("\n=========\n");
    printDirectory(node3);
    printf("\n=========\n");
    printDirectory(node4);
    Node* node5 = createNode(node2,"e");
}

void testMult(Node* root)
{
    printDirectory(root);
    printf("\n");
    createNode(root,"home");
    root = changeDirectory(root,"home");
    printDirectory(root);
    printf("\n");
}
*/
int main(void)
{
    Node* root = malloc(sizeof(Node));
    root->used = 0;
    root->name = "";
    root->parent = NULL;

    //testCreateNode(root);
    //testPrintDirectory(root);
    //changeDirectory(root,"..");
    //testMult(root);
    readInput(root);
    return 0;
}

