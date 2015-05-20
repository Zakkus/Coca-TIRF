#ifndef FILTERS_H
# define FILTERS_H
#include"Utils.h"
#include"SDL_init.h"
#include<list>
#include<iostream>

//met en noir tout ce qui n'est pas rouge ou blanc
void redFilter(SDL_Surface* image);
void grayScale(SDL_Surface* image);
void sobelFilter(SDL_Surface* image);
void laplaceFilter(SDL_Surface* image);
void findRectangle(SDL_Surface* image);
//à suivre, détecter les blocs de texte

#endif // !FILTERS_H