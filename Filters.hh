#ifndef FILTERS_HH
# define FILTERS_HH
#include"Utils.hh"
#include"SDL_init.hh"
#include<list>
#include<iostream>

//met en noir tout ce qui n'est pas rouge ou blanc
void redFilter(SDL_Surface* image);
void grayScale(SDL_Surface* image);
void sobelFilter(SDL_Surface* image);
void laplaceFilter(SDL_Surface* image);
void findRectangle(SDL_Surface* image);
void MaxCompo(SDL_Surface* image);
void Compo(SDL_Surface* tmp, SDL_Surface* image, int i, int j, int num);
//à suivre, détecter les blocs de texte

#endif // !FILTERS_HH
