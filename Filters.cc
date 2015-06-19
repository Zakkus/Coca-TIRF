#include"Filters.hh"

void more_frontier(SDL_Surface *image)
{
    int width = image->w;
    int height = image->h;
    std::vector<Uint8> rgb1,rgb2,rgb3;
    SDL_Surface* tmp = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_BlitSurface(image, NULL, tmp, NULL);

    for (int i = 1; i < width-1; i++)
        for (int j = 1; j < height-1; j++)
        {
            rgb1 = getRGB(tmp, i, j);
            rgb2 = getRGB(tmp, i - 1, j);
            rgb3 = getRGB(tmp, i, j - 1);
            if ((rgb1[0] != rgb2[0] || rgb1[0] != rgb2[0]))
                setPixel(image, i, j, SDL_MapRGB(image->format, 0, 0, 0));
        }

}

void redFilter(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
    std::vector<Uint8> rgb;
    SDL_Surface* tmp = new SDL_Surface(*image);

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            rgb = getRGB(image, i, j);
            //if (rgb[1] <= 100 && rgb[2] <= 100 && rgb[0] > 100)
            //	setPixel(image, i, j, SDL_MapRGB(image->format, 255, 0, 0));
            if (!(rgb[1] <= 100 && rgb[2] <= 100 && rgb[0] > 100))
                setPixel(image, i, j, SDL_MapRGB(image->format, 0, 0, 0));
            if (rgb[1] >= 200 && rgb[2] >= 200 && rgb[0] >= 200)
                setPixel(image, i, j, SDL_MapRGB(image->format, 255, 255, 255));
        }
}

//Red Filter avec HSV
void redFilter2(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
    std::vector<Uint8> rgb;
    SDL_Surface* tmp = new SDL_Surface(*image);
    int h = 0, s = 0, v = 0;

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            rgb = getRGB(tmp, i, j);
            rgb_to_hsv(rgb[0], rgb[1], rgb[2], h, s, v);
            if (h < 300 && h > 60)
                s = 0;
            int r = 0;
            int g = 0;
            int b = 0;
            hsv_to_rgb(h, s, v, r, g, b);
            setPixel(image, i, j,SDL_MapRGB(image->format, (Uint8)r, (Uint8)g, (Uint8)b));
        }
}

//Passe le rouge en noir et le reste en blanc
void Red_to_Black(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
    std::vector<Uint8> rgb;
    SDL_Surface* tmp = new SDL_Surface(*image);

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            rgb = getRGB(tmp, i, j);
            if (rgb[0] == 0 || rgb[1] == 255 || rgb[2] == 255)
                setPixel(image, i, j,SDL_MapRGB(image->format, 255, 255, 255));
            else
                setPixel(image, i, j,SDL_MapRGB(image->format, 0, 0, 0));
        }
}

void grayScale(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
    double gray;
    SDL_Surface* tmp = new SDL_Surface(*image);
    std::vector<Uint8> rgb;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            rgb = getRGB(tmp, i, j);
            gray = 0.299 * rgb[0] + 0.587 * rgb[1] + 0.114 * rgb[2];
            setPixel(image, i, j, SDL_MapRGB(image->format,
                        (Uint8)gray,
                        (Uint8)gray,
                        (Uint8)gray));
        }
}

//marche pas trop mal, algo du prof
void sobelFilter(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
    short gray, sx, sy;
    SDL_Surface* tmp = new SDL_Surface(*image);

    for (int i = 1; i < width - 1; i++)
        for (int j = 1; j < height - 1; j++)
        {
            //on consid�re que l'image est en niveaux de gris

            const int x_op[3][3] = { { -1, 0, 1 },
                { -2, 0, 2 },
                { -1, 0, 1 } };

            const int y_op[3][3] = { { 1, 2, 1 },
                { 0, 0, 0 },
                { -1, -2, -1 } };
            sx = 0;
            sy = 0;
            for (short x = 0; x < 3; x++)
                for (short y = 0; y < 3; y++)
                {
                    sx += getRGB(tmp, x + i, y + j)[0] * x_op[x][y];
                    sy += getRGB(tmp, x + i, y + j)[0] * y_op[x][y];
                }

            gray = std::abs(sx) + std::abs(sy);

            /*if (gray>200)
              gray = 255;
              else if (gray<100)
              gray = 0;*/
            gray = 255 - gray;

            setPixel(image, i, j, SDL_MapRGB(image->format,
                        (Uint8)gray,
                        (Uint8)gray,
                        (Uint8)gray));
        }
}

void laplaceFilter(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
    short gray;
    SDL_Surface* tmp = new SDL_Surface(*image);

    for (int i = 1; i < width - 1; i++)
        for (int j = 1; j < height - 1; j++)
        {
            //on consid�re que l'image est en niveaux de gris

            const char x_op[3][3] = { {  0, -1,  0 },
                { -1,  5, -1 },
                {  0, -1,  0 } };

            gray = 0;
            for (short x = 0; x < 3; x++)
                for (short y = 0; y < 3; y++)
                    gray += getRGB(tmp, x + i, y + j)[0] * x_op[x][y];

            setPixel(image, i, j, SDL_MapRGB(image->format,
                        (Uint8)gray,
                        (Uint8)gray,
                        (Uint8)gray));
        }
}

void findRectangle(SDL_Surface* image)
{
    //on consid�re une image couleur pass�e en rouge
    int width = image->w;
    int height = image->h;

    std::vector<Uint8> rgb, rgb1, rgb2, rgb3, rgb4, rgb5, rgb6;
    SDL_Surface* tmp = new SDL_Surface(*image);
    std::list<int> coordsList = std::list<int>();
    for (int i = 1; i < width - 1; i++)
        for (int j = 1; j < height - 1; j++)
        {
            rgb = getRGB(tmp, i, j);
            if (rgb[1] <= 100 && rgb[2] <= 100 && rgb[0] > 100)
            {
                rgb1 = getRGB(tmp, i - 1, j - 1);
                rgb2 = getRGB(tmp, i - 1, j);
                rgb3 = getRGB(tmp, i, j - 1);
                rgb4 = getRGB(tmp, i + 1, j + 1);
                rgb5 = getRGB(tmp, i + 1, j);
                rgb6 = getRGB(tmp, i, j + 1);
                if (!(rgb1[1] <= 100 && rgb1[2] <= 100 && rgb1[0] > 100) &&
                        !(rgb2[1] <= 100 && rgb2[2] <= 100 && rgb2[0] > 100) &&
                        !(rgb3[1] <= 100 && rgb3[2] <= 100 && rgb3[0] > 100) && 
                        (rgb4[1] <= 100 && rgb4[2] <= 100 && rgb4[0] > 100) &&
                        (rgb5[1] <= 100 && rgb5[2] <= 100 && rgb5[0] > 100) &&
                        (rgb6[1] <= 100 && rgb6[2] <= 100 && rgb6[0] > 100))
                {
                    coordsList.push_back(i);
                    coordsList.push_back(j);
                    break;
                }
                if (!(rgb4[1] <= 100 && rgb4[2] <= 100 && rgb4[0] > 100) &&
                        !(rgb5[1] <= 100 && rgb5[2] <= 100 && rgb5[0] > 100) &&
                        !(rgb6[1] <= 100 && rgb6[2] <= 100 && rgb6[0] > 100)/* &&
                                                                               (rgb1[1] <= 100 && rgb1[2] <= 100 && rgb1[0] > 100) &&
                                                                               (rgb2[1] <= 100 && rgb2[2] <= 100 && rgb2[0] > 100) &&
                                                                               (rgb3[1] <= 100 && rgb3[2] <= 100 && rgb3[0] > 100)*/)
                {
                    int y = coordsList.back();
                    coordsList.pop_back();
                    int x = coordsList.back();
                    coordsList.pop_back();
                    Hline(image, x, y, j - y);
                    Vline(image, x, j, i - x);
                    Hline(image, i, j, j - y);
                    Vline(image, i, y, j - x);
                    break;
                }
            }
        }
}

//erode et dilate ont besoin d'une SDL_Surface binaris�e

void erode(SDL_Surface* image, int dimx, int dimy)
{
    int width = image->w;
    int height = image->h;
    SDL_Surface* tmp = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_BlitSurface(image, NULL, tmp, NULL);
	std::vector<Uint8> rgb = std::vector<Uint8>();
    for (int j = dimy; j < height - dimy; j++)
    {
        for (int i = dimx; i < width - dimx; i++)
        {
			rgb = getRGB(tmp, i, j);
			if (rgb[0] == rgb[1] && rgb[1] == rgb[2] && rgb[0] == 255)
			{
				//std::cout << i << j << std::endl;
				for (int x = -dimx; x <= dimx; x++)
					for (int y = -dimy; y <= dimy; y++)
					{
						setPixel(image, x + i, y + j, SDL_MapRGB(image->format, 255, 255, 255));
					}
			}
        }
    }
}

void dilate(SDL_Surface* image, int dimx, int dimy)
{
    int width = image->w;
    int height = image->h;
    SDL_Surface* tmp = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_BlitSurface(image, NULL, tmp, NULL);
	std::vector<Uint8> rgb = std::vector<Uint8>();
    for (int j = dimy; j < height - dimy; j++)
    {
        for (int i = dimx; i < width - dimx; i++)
        {
			rgb = getRGB(tmp, i, j);
            if (rgb[0] == rgb[1] && rgb[1] == rgb[2] && rgb[0] == 0)
			{
				for (int x = -dimx; x <= dimx; x++)
				{
					for (int y = -dimy; y <= dimy; y++)
					{
                        //std::cout << "in" <<std::endl;
						setPixel(image, x + i, y + j, SDL_MapRGB(image->format, 0, 0, 0));
					}
				}
			}
        }
    }
}

//Image binaris�e donne un num�ro sur chaque composante

void MaxCompo(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
    //SDL_Surface* tmp = new SDL_Surface(*image);
    int n1 = 0;
	int n2 = 0;
	int n3 = 0;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            if (getRGB(image, i, j)[0] == 0)
            {
                n1++;
				if (n1 / 254 == 0)
					Compo(image, i, j, n1, n2, n3);
				else
				{
					n2++;
					n1 = n1 % 254;
					if (n2 / 254 == 0)
						Compo(image, i, j, n1, n2, n3);
					else
					{
						n3++;
						n2 = n2 % 254;
						if (n3 / 254 == 0)
							Compo(image, i, j, n1, n2, n3);
					}
				}
            }
        }
}

//num ne peut pas passer le 253

void Compo(SDL_Surface* image, int i, int j, int n1, int n2, int n3)
{
    int width = image->w;
    int height = image->h;
	std::vector<Uint8> rgb = std::vector<Uint8>();
	rgb = getRGB(image,i,j);
    if (rgb[0] == 0 && rgb[1] == 0 && rgb[2] == 0)
    {
        setPixel(image, i, j, SDL_MapRGB(image->format, n1, n2, n3));
        if (i - 1 > 0)
            Compo(image, i -1, j, n1, n2, n3);
        if (i + 1 < width)
            Compo(image, i + 1, j, n1, n2, n3);
        if (j - 1 > 0)
            Compo(image, i, j - 1, n1, n2, n3);
        if (j + 1 < height)
            Compo(image, i, j + 1, n1, n2, n3);
    }
}

std::vector<int> ChooseCompo(SDL_Surface* img)
{
	std::vector<int> maxcompo = std::vector<int>(3,0);
	int n = 0;
	int width = img->w;
    int height = img->h;
	int c1 = 0;
	int c2 = 0;
	int c3 = 0;
	int many = 0;
	std::vector<Uint8> rgb = std::vector<Uint8>();
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			rgb = getRGB(img,i,j);
			if (rgb[0] != 255)
			{
			if (c1 != rgb[0] || c2 != rgb[1] || c3 != rgb[3] )
			{
				many = 1;
				c1 = rgb[0];
				c2 = rgb[1];
				c3 = rgb[2];
			}
			else
			{
				many++;
				if (n < many)
				{
					n = many;
					maxcompo[0] = c1;
					maxcompo[1] = c2;
					maxcompo[2] = c3;
				}
			}
			}
		}
	return maxcompo;
}

void ColorCompo(SDL_Surface* img, std::vector<int> compo)
{
	SDL_Surface* tmp = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_BlitSurface(image, NULL, tmp, NULL);
	int width = img->w;
    int height = img->h;
	int c3 = compo[2];
	int c2 = compo[1];
	int c1 = compo[0];
	std::vector<Uint8> rgb = std::vector<Uint8>();
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			rgb = getRGB(img,i,j);
			if (rgb[0] == c1 && rgb[1] == c2 && rgb[2] == c3)
				setPixel(img, i, j, SDL_MapRGB(img->format, 0,0,0));
			else
				setPixel(img, i, j, SDL_MapRGB(img->format, 255, 255, 255));
		}
}

//Dis si la composante � des dimensions qui correspondent � celle d'une canette
bool CheckCompo(int l, int L)
{
	return l * 2 <= L && l * 1.5 >= L;
}

int getL(SDL_Surface* img, int x, int y)
{
	int width = img->w;
	int i;
	for (i = 0; i + x < width; i++)
	{
		if (getRGB(img, x+i, y)[0] != 0)
			break;
	}
	return i;
}

int getl(SDL_Surface* img, int x, int y)
{
    int height = img->h;
	int j;
	for (j = 0; y + j < height; j++)
	{
		if (getRGB(img, x, y + j)[0] != 0)
			break;
	}
}

//Supposition qu'il n'y a qu'une composante affich�e et qu'elle est li�e(aucun blanc � l'int�rieur passage pr�alable d'une ouverture tr�s grande)
void TraceRekt(SDL_Surface* img)//Peut etre prendre une seconde image �tant celle de base sur laquelle tracer le rect
{
	int width = img->w;
    int height = img->h;
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			if (getRGB(img, i, j)[0] == 0)
			{
				int L = getL(img, i, j);
				int l = getl(img, i, j);
				if (CheckCompo(l, L))
				{
					Hline(img, i, j, i + l);
					Hline(img, i, j + L, l);
					Vline(img, i, j, L);
					Vline(img, i + l, j, L);
				}
				break;
			}
		}
}
