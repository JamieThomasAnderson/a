

#include "render.h"
#include "model.h"

#include <SDL.h>

void renderNode(SDL_Renderer* renderer, Node* node)
{
    if (node == NULL) return;

    switch (node->type)
    {
        case RECT:
            SDL_SetRenderDrawColor(renderer, node->color.r, node->color.g, node->color.b, node->color.a);
            SDL_RenderFillRect(renderer, (SDL_Rect*)&node->component.rect);
            break;
        case TEXTURE:
            SDL_RenderCopy(renderer, node->component.texture, NULL, &node->component.rect);
            break;
        case SURFACE:
            // SDL_BlitSurface(node->component.surface, NULL, SDL_GetWindowSurface(SDL_GetRendererOutput(renderer)), &node->component.rect);
            break;
        case COLOR:
            SDL_SetRenderDrawColor(renderer, node->component.color.r, node->component.color.g, node->component.color.b, node->component.color.a);
            SDL_RenderClear(renderer);
            break;
        default:
            printf("Unknown type\n");
            break;
    }

    for (int i = 0; i < node->numChildren; i++)
    {
        renderNode(renderer, node->children[i]);
    }
}

void renderWM(SDL_Renderer* renderer, Node* root)
{
    if (root == NULL) return;

    renderNode(renderer, root);

    for (int i = 0; i < root->numChildren; i++)
    {
        renderWM(renderer, root->children[i]);
    }
}