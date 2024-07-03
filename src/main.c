/*
 * Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include <SDL.h>
#include <SDL_ttf.h>

#include "model.h"
#include "render.h"


// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600
#define LINE_HEIGHT     20

void init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized!\n"
                "SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        printf("SDL can not disable compositor bypass!\n");
        SDL_Quit();
        return;
    }
#endif
}

SDL_Window * createWindow(int width, int height, const char* name)
{
  SDL_Window *window = SDL_CreateWindow(
    name,
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    width,
    height,
    SDL_WINDOW_SHOWN
  );

  if ( !window )
  {
    printf("Window could not be created!\n"
           "SDL_Error: %s\n", SDL_GetError()
    );
    SDL_Quit();
    return NULL;
  }

  return window;
}

void renderText(SDL_Renderer* ren, TTF_Font* font, const char* text) {
    SDL_Color color = {255, 255, 255, 255};
    int y = 0;

    char* textCopy = strdup(text);
    char* line = strtok(textCopy, "\n");

    while (line) {
        printf("%ld\n", strlen(line));
        SDL_Surface* surface = TTF_RenderText_Blended(font, line, color);
        if (surface == NULL) {
            printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
            free(textCopy);
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
        SDL_FreeSurface(surface);
        if (texture == NULL) {
            printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
            free(textCopy);
            return;
        }

        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

        SDL_Rect dst;
        dst.x = 0;
        dst.y = y;
        dst.w = texW;
        dst.h = texH;

        SDL_RenderCopy(ren, texture, NULL, &dst);
        SDL_DestroyTexture(texture);

        y += LINE_HEIGHT; // Move down for the next line
        line = strtok(NULL, "\n");
    }

    free(textCopy);
}

void loadFile(const char* filename, char* buffer, size_t bufferSize) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file: %s\n", filename);
        return;
    }

    size_t bytesRead = fread(buffer, 1, bufferSize - 1, file);
    buffer[bytesRead] = '\0'; // Null-terminate the string
    fclose(file);
}

int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;

    init();

    SDL_Window* window = createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "a - Text Editor");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        printf("Renderer could not be created!\n"
                "SDL_Error: %s\n", SDL_GetError());
    }

    bool running = true;
    // FONT STUFF
    if (TTF_Init() == -1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("../fonts/Consolas.ttf", 16);
    if (font == NULL) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_StartTextInput();

    char text[1024 * 10] = "";
    loadFile("../fonts/test.txt", text, sizeof(text));
    SDL_Event e;
    
    // Node* root = createNodeRect(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 255, 0, 255);
    // Node* child = createNodeRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, 255, 0, 0, 255);
    // Node* childchild = createNodeRect((SCREEN_WIDTH / 2) - 100, (SCREEN_HEIGHT /2)-100, 0, 0, 0, 0, 255, 255);
    // addChild(root, child);
    // addChild(root, childchild);
    



    while (running)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_TEXTINPUT) {
                strcat(text, e.text.text); // Append new text
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(text) > 0) {
                    text[strlen(text) - 1] = '\0'; // Remove last character
                } else if (e.key.keysym.sym == SDLK_RETURN) {
                    strcat(text, "\n"); // Add a newline character
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(renderer);
        // renderWM(renderer, root);
        renderText(renderer, font, text);

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //freeWM(root);
    return 0;
}
