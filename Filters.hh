#ifndef FILTERS_HH
# define FILTERS_HH
#include"Utils.hh"
#include"SDL_init.hh"
#include<list>
#include<iostream>

//met en noir tout ce qui n'est pas rouge ou blanc
void redFilter(SDL_Surface* image);
void redFilter2(SDL_Surface* image);
void grayScale(SDL_Surface* image);
void sobelFilter(SDL_Surface* image);
void laplaceFilter(SDL_Surface* image);
void findRectangle(SDL_Surface* image);
void Red_to_Black(SDL_Surface* image);
void erode(SDL_Surface* image, int dim);
void dilate(SDL_Surface* image, int dim);
void MaxCompo(SDL_Surface* image);
void Compo(SDL_Surface* tmp, SDL_Surface* image, int i, int j, int num);
void TraceRekt(SDL_Surface* image);
//� suivre, d�tecter les blocs de texte

#endif // !FILTERS_HH
