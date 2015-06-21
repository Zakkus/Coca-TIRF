#ifndef FILTERS_HH
# define FILTERS_HH
#include"Utils.hh"
#include"SDL_init.hh"
#include<list>
#include<iostream>
#include<utility>
#include<map>

void redFilter(SDL_Surface* image);
void whiteFilter(SDL_Surface* image, int L, int l, int min_left, int min_up);
void dilate(SDL_Surface* image, int dimx, int dimy);
void erode(SDL_Surface* image, int dimx, int dimy);
void MaxCompo(SDL_Surface* image);
void Compo(SDL_Surface* image);
std::map<int,int> ChooseCompo(SDL_Surface* image);
void ColorCompo(SDL_Surface* image, std::vector<int> compo);
int getL(SDL_Surface* img, int &min_left);
int getl(SDL_Surface* img, int &min_up);
int CheckCompo(int l, int L);
void Compo_lr(SDL_Surface* image, int i, int j, int n1, int n2, int n3);
void Compo_tb(SDL_Surface* image, int i, int j, int n1, int n2, int n3);
void Compo_tr(SDL_Surface* image, int i, int j, int n1, int n2, int n3);
void Compo_bl(SDL_Surface* image);
std::vector<std::pair<int, int> > Findall(SDL_Surface* image, int n1, int n2, int n3);
float CheckPercent(SDL_Surface* img, int xmin, int ymin, int l, int L);
std::pair<int, int> GetMaxCompo(std::map<int, int> compos);

#endif // !FILTERS_HH
