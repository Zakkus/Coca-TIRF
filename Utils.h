#ifndef UTILS_H
# define UTILS_H
#include"SDL_init.h"
#include<algorithm>
#include<iostream>

void hsv_to_rgb(float h, float s, float v, float& r, float& g, float& b);
void rgb_to_hsv(float r, float g, float b, float& h, float& s, float& v);
void Hline(SDL_Surface* image, int x, int y, int w);
void Vline(SDL_Surface* image, int x, int y, int h);
void countRedWhiteRation(SDL_Surface* image);
#endif // !UTILS_H