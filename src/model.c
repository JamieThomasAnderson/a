#include <stdio.h>
#include <stdlib.h>

#include "model.h"

Node *createNodeRect(int width, int height, int x, int y, int r, int g, int b, int a) 
{
    SDL_Rect rect = {x, y, width, height};
    SDL_Color color = {r, g, b, a};
    
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->component.rect = rect;
    node->color = color;
    node->type = RECT;

    node->parent = NULL;
    node->numChildren = 0;
    
    for (int i = 0; i < MAX_CHILDREN; i++) 
    {
        node->children[i] = NULL;
    }

    return node;
}

void addChild(Node* parent, Node* child) 
{
    if (child == NULL) return;

    if (parent->type != RECT)
    {
        printf(" Node has no bounding box, must be RECT! \n");
        return;
    }

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

