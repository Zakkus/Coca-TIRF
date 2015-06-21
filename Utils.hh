#ifndef UTILS_HH
# define UTILS_HH
#include"SDL_init.hh"
#include<algorithm>
#include<iostream>
#include<tuple>

void Hline(SDL_Surface* image, int x, int y, int w);
void Vline(SDL_Surface* image, int x, int y, int h);
void draw_rectangle(SDL_Surface *image, int largeur, int longueur, int i, int j);
#endif // !UTILS_HH
