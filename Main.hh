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


class par_2{
	public:
		void operator()(const tbb::blocked_range<int>& r)const
		{
			for (int i = r.begin(); i != r.end(); i++)
			{
				std::pair<float,float> white = std::get<1>((*percents)[i]);
				int proportion = std::get<0>((*percents)[i]);
				int L = std::get<2>((*percents)[i]), l = std::get<3>((*percents)[i]);
				int min_left = std::get<4>((*percents)[i]), min_up = std::get<5>((*percents)[i]);
				if ((white.second <= 0.271 && white.second > 0.1 && white.first < 0.34 && white.first > 0.1) ||
						(white.first <= 0.271 && white.first > 0.12 && white.second > 0.05))
				{
					if (proportion <= 65 && proportion >= 55)
					{
						draw_rectangle(final_image, L, l, min_left, min_up);
						*done = true;
						break;
					}
				}
                else
                    std::get<0>((*percents)[i]) = 0;
				/*else
				{
					percents->erase(percents->begin()+i);
					i--;
				}*/
			}
		}
		
		par_2(SDL_Surface* img, bool *d,
			std::vector<std::tuple<int,std::pair<float,float>, int,int,int,int> >* p):
		final_image(img), percents(p), done(d)
		{}

	private:
		SDL_Surface* final_image;
		std::vector<std::tuple<int,std::pair<float,float>, int,int,int,int> >* percents;
		bool *done;
};
#endif
