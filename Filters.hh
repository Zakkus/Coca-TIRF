#ifndef FILTERS_HH
# define FILTERS_HH
#include"Utils.hh"
#include"SDL_init.hh"
#include<list>
#include<iostream>
#include<utility>
#include<map>
#include <tbb/tbb.h>

class par_dilate{

	public:
		void operator()(const tbb::blocked_range<int>& r) const{
			for (int j = r.begin(); j != r.end(); j++)
			{
			int i = j % w;
			int k = j / w;
			std::vector<Uint8> rgb;
	        rgb = getRGB(image, i, k);
            setPixel(image, i, k, SDL_MapRGB(image->format, 255, 0, 0));
            if (!(rgb[1] <= 70 && rgb[2] <= 70 && rgb[0] > 100))
                setPixel(image, i, k, SDL_MapRGB(image->format, 255, 255, 255));
            if (rgb[1] >= 200 && rgb[2] >= 200 && rgb[0] >= 200)
                setPixel(image, i, k, SDL_MapRGB(image->format, 255, 255, 255));
            rgb = getRGB(image, i, k);
            if (rgb[1] == 0)
                setPixel(image, i, k, SDL_MapRGB(image->format, 0, 0, 0));
 			
       		}
		}

		par_dilate(SDL_Surface* img, int width): image(img), w(width)
		{
		}
	private:
		int w;
		SDL_Surface* image;
};

class par_setpix{
	public:
		void operator()(const tbb::blocked_range<int>& r) const{
		for (int k = r.begin(); k != r.end(); k++)
        {
			int i = dimx + k % (image->w - dimx);
			int j = dimy + k / (image->w - dimx);
			std::vector<Uint8> rgb;
            rgb = getRGB(tmp, i, j);
            if (rgb[0] == rgb[1] && rgb[1] == rgb[2] && rgb[0] == val)
                for (int x = -dimx; x <= dimx; x++)
					for (int y = -dimy; y <= dimy; y++)
                        setPixel(image, x + i, y + j, color);
        }
		}
		
		par_setpix(SDL_Surface* temp, SDL_Surface* img, int x, int dim, int value, Uint32 col):
		tmp(temp), image(img), color(col), dimy(dim), dimx(x), val(value)
		{
		}

	private:
		SDL_Surface* image, *tmp;
		int dimy;
		int dimx;
		int val;
		Uint32 color;
};

class par_white{
	public:
		void operator()(const tbb::blocked_range<int>& r) const{
			for (int j = r.begin(); j != r.end(); j++)
				{
					std::vector<Uint8> rgb;
					rgb = getRGB(image, i, j);
            		if (rgb[1] >= 120 && rgb[2] >= 120 && rgb[0] >= 120)
                		setPixel(image, i, j, SDL_MapRGB(image->format, 255, 255, 255));
				}
}

		par_white(SDL_Surface* img, int ii):image(img), i(ii)
			{}
		
	private:
		int i;
		SDL_Surface* image;
};

class par_color{
	public:
		void operator()(const tbb::blocked_range<int>& r) const{
			for (int l = r.begin(); l!= r.end(); l++)
			{
				int i = l % w;
				int j = l / w;
				std::vector<Uint8> rgb;
				rgb = getRGB(img,i,j);
            	if (rgb[0] == c1 && rgb[1] == c2 && rgb[2] == c3)
                	setPixel(img, i, j, SDL_MapRGB(img->format, 0,0,0));
            	else
                	setPixel(img, i, j, SDL_MapRGB(img->format, 255, 255, 255));

			}
		}

		par_color(SDL_Surface* image, int width, Uint8 c_1, Uint8 c_2, Uint8 c_3):
			img(image), w(width), c1(c_1), c2(c_2), c3(c_3)
		{}

		private:
			SDL_Surface* img;
			int w;
			Uint8 c1, c2, c3;
};


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
std::pair<int, int> GetMaxCompo(std::map<int, int>& compos);


#endif // !FILTERS_HH
