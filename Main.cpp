#include"SDL_init.h"
#include"Filters.h"
#include"Utils.h"
#include<cstdlib>
int main(int argc, char* args[])
{
	//SDL_Surface* image = loadImage("C:/Users/Zakaria/Pictures/molester-man.jpg");
	//SDL_Surface* image = loadImage("D:/Work/TIRF/Coca/Coca/simple/HPIM4430.JPG");
	SDL_Surface* image = loadImage("D:/Work/TIRF/Coca/Coca/simple/HPIM4433.JPG");
	//SDL_Surface* image = loadImage("D:/Work/TIRF/Coca/Coca/moins_simple/HPIM4422.JPG");
	//grayScale(image);
	//sobelFilter(image);
	//laplaceFilter(image);

	//findRectangle(image);

	//SDL_Surface* image = loadImage("D:/Work/TIRF/can.jpg");
	redFilter(image);

	countRedWhiteRation(image);
	displayImage(createWindow(), image);

	return 0;
}