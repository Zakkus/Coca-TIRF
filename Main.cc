#include"SDL_init.hh"
#include"Filters.hh"
#include"Utils.hh"
#include<cstdlib>
int main(int argc, char* argv[])
{
    //SDL_Surface* image = loadImage("C:/Users/Zakaria/Pictures/molester-man.jpg");
    //SDL_Surface* image = loadImage("D:/Work/TIRF/Coca/Coca/simple/HPIM4430.JPG");
    //SDL_Surface* image = loadImage("D:/Work/TIRF/Coca/Coca/simple/HPIM4433.JPG");
    SDL_Surface* image = loadImage(argv[1]);
    SDL_Surface* final_image = loadImage(argv[1]);
    SDL_Surface* white_image = loadImage(argv[1]);
    //	SDL_Surface* save = loadImage(argv[1]);
    //SDL_Surface* image = loadImage("D:/Work/TIRF/Coca/Coca/moins_simple/HPIM4422.JPG");
    //grayScale(image);
    //sobelFilter(image);
    //laplaceFilter(image);

    //findRectangle(image);

    //SDL_Surface* image = loadImage("D:/Work/TIRF/can.jpg");
    redFilter(image);
    //    redFilter(save);

    //   Red_to_Black(image);
    //    Red_to_Black(save);

    dilate(image,2,0);
    erode(image, 0,4);
    dilate(image, 0,4);
    erode(image, 4,0);
    dilate(image, 4,0);
    erode(image, 3,3);
    dilate(image, 3,3);

    dilate(image,5,0);
    erode(image,5,0);
    //    more_frontier(image);
    //

    //MaxCompo(image);
    Compo(image);
   // displayImage(createWindow(), image);
    int i = 0;
    bool done = false;
    std::vector<std::tuple<int,float, int,int,int,int> > percents;
	std::map<int, int> compos = ChooseCompo(image);
    while (i < 10)
    {
		SDL_Surface* tmp = SDL_CreateRGBSurface(0,image->w,image->h,32,0,0,0,0);
		SDL_BlitSurface(image, NULL, tmp, NULL);
		std::pair<int,int> p = GetMaxCompo(compos);

        //std::cout << compo->at(0) << std::endl;
        //std::cout << compo->at(1) << std::endl;
		std::vector<int> compo = std::vector<int>();
		std::cout << "pfirst: " << p.first << std::endl;
		int c1 = p.first % 1000;
		std::cout << "c1: " << c1 << std::endl;
		int c2 = (p.first / 1000) % 1000;
		std::cout << "c2: " << c2 << std::endl;
		int c3 = p.first / 1000000;
		std::cout << "c3: " << c3 << std::endl;
		compo.push_back(p.first % 1000);
		compo.push_back((p.first / 1000) % 1000);
		compo.push_back(p.first / 1000000);
        ColorCompo(tmp, compo);
	//	displayImage(createWindow(), tmp);
        int min_left, min_up;

        int L = getL(tmp, min_left);
        std::cout << L << std::endl;
        int l = getl(tmp, min_up);
        std::cout << l <<std::endl;

        std::cout << "coords: " << min_left << " " << min_up << std::endl;
        std::cout << CheckCompo(L, l) << std::endl;

        //frame_component(image, final_image, L, l);
        int com = CheckCompo(L,l);
        whiteFilter(white_image, L, l, min_left, min_up);
        float white = CheckPercent(white_image, min_left, min_up, l, L);
        percents.push_back(std::make_tuple(com,white,L,l,min_left,min_up));
		displayImage(createWindow(), white_image);

      /*      {
                draw_rectangle(final_image, L, l, min_left, min_up);
                break;
            }*/
        compos.erase(p.first);
        i++;
    }

    for (i = 0; i < percents.size(); i++)
    {
        float white = std::get<1>(percents[i]);
        int proportion = std::get<0>(percents[i]);
        int L = std::get<2>(percents[i]), l = std::get<3>(percents[i]);
        int min_left = std::get<4>(percents[i]), min_up = std::get<5>(percents[i]);
        if (white <= 0.25 && white > 0.1)
        {
            if (proportion <= 65 && proportion >= 55)
            {
                draw_rectangle(final_image, L, l, min_left, min_up);
                done = true;
                break;
            }
        }
        else
        {
            percents.erase(percents.begin()+i);
            i--;
        }
    }

    if (!done && !percents.empty())
    {
        std::sort(begin(percents), end(percents),
                [](std::tuple<int,float,int,int,int,int> const &t1,
                   std::tuple<int,float,int,int,int,int> const &t2)
                {
                    return std::abs(std::get<2>(t1) - 60) >
                           std::abs(std::get<2>(t2) - 60);
                });

        float white = std::get<1>(percents[0]);
        int proportion = std::get<0>(percents[0]);
        int L = std::get<2>(percents[0]), l = std::get<3>(percents[0]);
        int min_left = std::get<4>(percents[0]), min_up = std::get<5>(percents[0]);
        if (proportion <= 85 && proportion >= 51)
            draw_rectangle(final_image, L, l, min_left, min_up);
    }


    SDL_Window* window = createWindow();
    if (window == NULL)
        return 1;
    displayImage(window, final_image);
    SDL_Delay(5000);

    return 0;
}
