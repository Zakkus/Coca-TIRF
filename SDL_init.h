#ifndef SDL_INIT_H
# define SDL_INIT_H

#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>

SDL_Window* create_window();
SDL_Surface* load_image(char* path);
void display_image(SDL_Window* window, SDL_Surface* image);
Uint32 getPixel(SDL_Surface *surface, int x, int y);
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

#endif // !SDL_INIT_H