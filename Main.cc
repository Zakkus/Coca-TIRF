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
	//displayImage(createWindow(), image);
	int i = 0;
	while (i < 5)
	{
		SDL_Surface* tmp = SDL_CreateRGBSurface(0,image->w,image->h,32,0,0,0,0);
        SDL_BlitSurface(image, NULL, tmp, NULL);

		std::vector<int>* compo = ChooseCompo(tmp);

		std::cout << compo->at(0) << std::endl;
		std::cout << compo->at(1) << std::endl;

		ColorCompo(tmp, *compo);

		int min_left, min_up;

		int L = getL(tmp, min_left);
		std::cout << L << std::endl;
		int l = getl(tmp, min_up);
		std::cout << l <<std::endl;

        std::cout << "coords: " << min_left << " " << min_up << std::endl;
        std::cout << CheckCompo(L, l) << std::endl;

        //frame_component(image, final_image, L, l);
        //if (CheckCompo(L,l))
            if (CheckPercent(image, min_left, min_up, l, L))
                draw_rectangle(final_image, L, l, min_left, min_up);
        SupprCompo(image, *compo);
		i++;
	}
    SDL_Window* window = createWindow();
    if (window == NULL)
        return 1;
    displayImage(window, final_image);
    SDL_Delay(1000);

    return 0;
}
