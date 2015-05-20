#ifndef SDL_INIT_H
# define SDL_INIT_H

#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>

SDL_Window* createWindow();
SDL_Surface* loadImage(char* path);
void displayImage(SDL_Window* window, SDL_Surface* image);
Uint32 getPixel(SDL_Surface *surface, int x, int y);
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint8* getRGB(SDL_Surface* image, int i, int j);

#endif // !SDL_INIT_H