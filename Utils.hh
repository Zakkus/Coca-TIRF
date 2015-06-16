#ifndef UTILS_HH
# define UTILS_HH
#include"SDL_init.hh"
#include<algorithm>
#include<iostream>

void hsv_to_rgb(int h, int s, int v, int& r, int& g, int& b);
void rgb_to_hsv(int r, int g, int b, int& h, int& s, int& v);
void Hline(SDL_Surface* image, int x, int y, int w);
void Vline(SDL_Surface* image, int x, int y, int h);
void countRedWhiteRation(SDL_Surface* image);
#endif // !UTILS_HH
