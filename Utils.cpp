#include"Utils.h"

void rgb_to_hsv(float r, float g, float b, float& h, float& s, float& v)
{
	r /= 255;
	g /= 255;
	b /= 255;
	float max = std::max(std::max(r, g), b);
	float min = std::min(std::min(r, g), b);
	v = max;

	float d = max - min;
	s = max == 0 ? 0 : d / max;

	if (max == min)
		h = 0; // achromatic
	else
	{
		if (max == r)
			h = (g - b) / d + (g < b ? 6 : 0);
		else if (max == g)
			h = (b - r) / d + 2;
		else if (max == b)
			h = (r - g) / d + 4;
		h /= 6;
	}
}

void hsv_to_rgb(float h, float s, float v, float& r, float& g, float& b)
{
	int i = int(h * 6);
	float f = h * 6 - i;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);

	switch (i % 6)
	{
		case 0: r = v, g = t, b = p; break;
		case 1: r = q, g = v, b = p; break;
		case 2: r = p, g = v, b = t; break;
		case 3: r = p, g = q, b = v; break;
		case 4: r = t, g = p, b = v; break;
		case 5: r = v, g = p, b = q; break;
	}

	r *= 255;
	g *= 255;
	b *= 255;
}

void Hline(SDL_Surface* image, int x, int y, int w)
{
	SDL_Rect area;
	area.x = x;
	area.y = y;
	area.w = w;
	area.h = 5;

	SDL_FillRect(image, &area, SDL_MapRGB(image->format, 0, 0, 0));
}

void Vline(SDL_Surface* image, int x, int y, int h)
{
	SDL_Rect area;
	area.x = x;
	area.y = y;
	area.w = 5;
	area.h = h;

	SDL_FillRect(image, &area, SDL_MapRGB(image->format, 0, 0, 0));
}

void countRedWhiteRation(SDL_Surface* image)
{
	int red = 0, white = 0;
	int width = image->w;
	int height = image->h;

	Uint8 *rgb;
	for (int i = 1; i < width - 1; i++)
		for (int j = 1; j < height - 1; j++)
		{
			rgb = getRGB(image, i, j);
			if (!(rgb[1] <= 100 && rgb[2] <= 100 && rgb[0] > 100))
				red++;
			if (rgb[1] >= 200 && rgb[2] >= 200 && rgb[0] >= 200)
				white++;
		}
	std::cout << "RED : " << red << std::endl;
	std::cout << "WHITE : " << white << std::endl;
	std::cout << "RATIO : " << (100 * red) / (width * height);
}