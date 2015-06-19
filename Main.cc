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
//	SDL_Surface* save = loadImage(argv[1]);
    //SDL_Surface* image = loadImage("D:/Work/TIRF/Coca/Coca/moins_simple/HPIM4422.JPG");
    //grayScale(image);
    //sobelFilter(image);
    //laplaceFilter(image);

    //findRectangle(image);

    //SDL_Surface* image = loadImage("D:/Work/TIRF/can.jpg");
    redFilter(image);
//    redFilter(save);

    Red_to_Black(image);
//    Red_to_Black(save);

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

    MaxCompo(image);
	std::vector<int>* compo = ChooseCompo(image);
	
/*	std::cout << compo[0] << std::endl;
	std::cout << compo[1] << std::endl;
	*/
	ColorCompo(image, *compo);
	
	//int L = getL(image);
	
	SDL_Window* window = createWindow();
	if (window == NULL)
		return 1;
    displayImage(window, image);
	SDL_Delay(3000);

    return 0;
}
