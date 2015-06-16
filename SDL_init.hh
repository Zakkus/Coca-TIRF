#ifndef SDL_INIT_HH
# define SDL_INIT_HH

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<cstdio>
#include<vector>

SDL_Window* createWindow();
SDL_Surface* loadImage(char* path);
void displayImage(SDL_Window* window, SDL_Surface* image);
Uint32 getPixel(SDL_Surface *surface, int x, int y);
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
std::vector<Uint8> getRGB(SDL_Surface* image, int i, int j);

#endif // !SDL_INIT_HH
