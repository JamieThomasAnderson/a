#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include "model.h"

void renderNode(SDL_Renderer* renderer, Node* node);
void renderWM(SDL_Renderer* renderer, Node* root);

#endif