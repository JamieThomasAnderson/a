#ifndef MODEL_H
#define MODEL_H

#define MAX_CHILDREN 10

#include <SDL.h>

typedef enum 
{
    RECT,
    TEXTURE,
    SURFACE,
    COLOR
} SDLType;

typedef union SDLComponent
{
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Color color;
} SDLComponent;


typedef struct Node 
{
    SDLComponent component;
    SDL_Color color;
    SDLType type;

    struct Node *parent;
    struct Node *children[MAX_CHILDREN];
    int numChildren;
} Node;

Node *createNodeRect(int width, int height, int x, int y, int r, int g, int b, int a); 
void addChild(Node* parent, Node* child);
void freeWM(Node *node);
#endif