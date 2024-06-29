#ifndef MODEL_H
#define MODEL_H

#define MAX_CHILDREN 10

#include <SDL.h>

typedef struct Node 
{
    SDL_Rect rect;
    struct Node *parent;
    struct Node *children[MAX_CHILDREN];
    int numChildren;
} Node;

Node *createNode(SDL_Rect rect, Node *parent);
void addNode(Node* parent, Node* child);
void freeWM(Node *node);
#endif