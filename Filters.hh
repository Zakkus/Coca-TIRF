#ifndef FILTERS_HH
# define FILTERS_HH
#include"Utils.hh"
#include"SDL_init.hh"
#include<list>
#include<iostream>

void more_frontier(SDL_Surface *image);
void redFilter(SDL_Surface* image);
void redFilter2(SDL_Surface* image);
void grayScale(SDL_Surface* image);
void sobelFilter(SDL_Surface* image);
void laplaceFilter(SDL_Surface* image);
void findRectangle(SDL_Surface* image);
void Red_to_Black(SDL_Surface* image);
void dilate(SDL_Surface* image, int dimx, int dimy);
void erode(SDL_Surface* image, int dimx, int dimy);
void MaxCompo(SDL_Surface* image);
void Compo(SDL_Surface* image, int i, int j, int num);
void TraceRekt(SDL_Surface* image);
//à suivre, détecter les blocs de texte

#endif // !FILTERS_HH
