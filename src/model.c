#include <stdio.h>
#include <stdlib.h>

#include "model.h"

Node *createNode(SDL_Rect rect, Node *parent) 
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->rect = rect;
    node->parent = parent;
    node->numChildren = 0;
    for (int i = 0; i < MAX_CHILDREN; i++) 
    {
        node->children[i] = NULL;
    }

    return node;
}

void addNode(Node* parent, Node* child) 
{
    if (parent->numChildren < MAX_CHILDREN) 
    {
        parent->children[parent->numChildren] = child;
        parent->numChildren++;
    }

    else 
    {
        printf("Parent node is full!\n");
    }
}

void freeWM(Node *node) 
{
    if (node == NULL) return;
    for (int i = 0; i < node->numChildren; i++)
    {
        freeWM(node->children[i]);
    } 
    free(node);
}