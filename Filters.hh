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
//à suivre, détecter les blocs de texte

#endif // !FILTERS_HH
