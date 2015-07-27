#ifndef MAIN_HH
#define MAIN_HH

#include"SDL_init.hh"
#include"Filters.hh"
#include"Utils.hh"
#include<cstdlib>

class par_1{

	public:
		void operator()(const tbb::blocked_range<int>& r)const
		{
			for (int i = r.begin(); i != r.end(); i++)
			{
				SDL_Surface* tmp = SDL_CreateRGBSurface(0,image->w,image->h,32,0,0,0,0);
				SDL_BlitSurface(image, NULL, tmp, NULL);
				std::pair<int,int> p = GetMaxCompo(*compos);

				std::vector<int> compo = std::vector<int>();
				compo.push_back(p.first % 1000);
				compo.push_back((p.first / 1000) % 1000);
				compo.push_back(p.first / 1000000);
				ColorCompo(tmp, compo);
				int min_left, min_up;

				int L = getL(tmp, min_left);
				int l = getl(tmp, min_up);

				int com = CheckCompo(L,l);
				whiteFilter(white_image, L, l, min_left, min_up);
				float white2 = CheckPercent(white_image, min_left, min_up, l, L);
				float white1 = CheckPercent(tmp, min_left, min_up, l, L);
				percents->push_back(std::make_tuple(com,std::make_pair(white1,white2),
							L,l,min_left,min_up));
			}
		}
		

		par_1(SDL_Surface* img, SDL_Surface* wimg, std::map<int, int>* m, 
			std::vector<std::tuple<int,std::pair<float,float>, int,int,int,int> >* p):
		image(img), white_image(wimg), compos(m), percents(p)
		{}

	private:
		SDL_Surface* image;
		SDL_Surface* white_image;
		std::map<int, int>* compos;
		std::vector<std::tuple<int,std::pair<float,float>, int,int,int,int> >* percents;
};

#endif
