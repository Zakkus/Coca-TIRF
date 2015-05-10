#include<Filters.h>

void redFilter(SDL_Surface* image)
{
	int width = image->w;
	int height = image->h;
	Uint8 r, g, b;

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			SDL_GetRGB(getPixel(image, i, j), image->format, &r, &g, &b);
			if (!(g <= 100 && b <= 100 && r > 100))
			{
				//std::cout << "red: " << r << " green: " << g << " blue: " << b << std::endl;
				setPixel(image, i, j, SDL_MapRGB(image->format, 255, 255, 255));
			}
		}
}