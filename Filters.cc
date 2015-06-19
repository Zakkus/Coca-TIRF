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
            //on considère que l'image est en niveaux de gris

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
            //on considère que l'image est en niveaux de gris

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
    //on considère une image couleur passée en rouge
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

//erode et dilate ont besoin d'une SDL_Surface binarisée

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

//Image binarisée donne un numéro sur chaque composante

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
				{
					///Compo_lr(image, i, j, n1, n2, n3);
					Compo_tr(image, i, j, n1, n2, n3);
					//Compo_bl(image,i,j,n1,n2,n3);
				}
				else
				{
					n2++;
					n1 = n1 % 254;
					if (n2 / 254 == 0)
					{
						//Compo_lr(image, i, j, n1, n2, n3);
						Compo_tr(image, i, j, n1, n2, n3);
						//Compo_bl(image,i,j,n1,n2,n3);
					}
					else
					{
						n3++;
						n2 = n2 % 254;
						if (n3 / 254 == 0)
						{
							//Compo_lr(image, i, j, n1, n2, n3);
							Compo_tr(image, i, j, n1, n2, n3);
							//Compo_bl(image,i,j,n1,n2,n3);
						}
					}
				}
            }
        }
}

//num ne peut pas passer le 253

void Compo_lr(SDL_Surface* image, int i, int j, int n1, int n2, int n3)
{
    int width = image->w;
    int height = image->h;
	//std::vector<Uint8> rgb = std::vector<Uint8>();
	//rgb = getRGB(image,i,j);
	int c1 = getRGB(image,i,j)[0];
	int c2 = getRGB(image,i,j)[1];
	int c3 = getRGB(image,i,j)[2];
    if (c1 == 0 && c2 == 0 && c3 == 0)
    {
        setPixel(image, i, j, SDL_MapRGB(image->format, n1, n2, n3));
        for (int k = i - 1; k >= 0 && getRGB(image, k, j)[0] == 0 && getRGB(image, k, j)[1] == 0 && getRGB(image, k, j)[2] == 0; k--)
		{
			setPixel(image, k, j, SDL_MapRGB(image->format, n1, n2, n3));
			if (j - 1 >= 0)
				Compo_tb(image, k, j - 1, n1, n2, n3);
			if (j + 1 < height)
				Compo_tb(image, k, j + 1, n1, n2, n3);
			//Compo_tb(image, k, j, n1, n2, n3);
		}
		for (int l = i + 1; l < width && getRGB(image, l, j)[0] == 0 && getRGB(image, l, j)[1] == 0 && getRGB(image, l, j)[2] == 0; l++)
		{
			setPixel(image, l, j, SDL_MapRGB(image->format, n1, n2, n3));
			if (j - 1 >= 0)
				Compo_tb(image, l, j - 1, n1, n2, n3);
			if (j + 1 < height)
				Compo_tb(image, l, j + 1, n1, n2, n3);
			//Compo_tb(image, l, j, n1, n2, n3);
		}
    }
}

void Compo_tb(SDL_Surface* image, int i, int j, int n1, int n2, int n3)
{
	int width = image->w;
    int height = image->h;
	int c1 = getRGB(image,i,j)[0];
	int c2 = getRGB(image,i,j)[1];
	int c3 = getRGB(image,i,j)[2];
    if (c1 == 0 && c2 == 0 && c3 == 0)
    {
        setPixel(image, i, j, SDL_MapRGB(image->format, n1, n2, n3));
        for (int k = j - 1; k >= 0 && getRGB(image, i, k)[0] == 0 && getRGB(image, i, k)[1] == 0 && getRGB(image, i, k)[2] == 0; k--)
		{
			setPixel(image, i, k, SDL_MapRGB(image->format, n1, n2, n3));
			if (i - 1 >= 0)
				Compo_lr(image, i - 1, k, n1, n2, n3);
			if (i + 1 < height)
				Compo_lr(image, i + 1, k, n1, n2, n3);
			//Compo_lr(image, i, k, n1, n2, n3);
		}
		for (int l = j + 1; l < height && getRGB(image, i, l)[0] == 0 && getRGB(image, i, l)[1] == 0 && getRGB(image, i, l)[2] == 0; l++)
		{
			setPixel(image, i, l, SDL_MapRGB(image->format, n1, n2, n3));
			if (i - 1 >= 0)
				Compo_lr(image, i - 1, l, n1, n2, n3);
			if (j + 1 < height)
				Compo_lr(image, i + 1, l, n1, n2, n3);
			//Compo_lr(image, i, l, n1, n2, n3);
		}
    }
}

void Compo_tr(SDL_Surface* image, int i, int j, int n1, int n2, int n3)
{
	int width = image->w;
    int height = image->h;
	int lastx = i - 1;
	int lasty = j - 1;
	/*if (lastx >= 0 && getRGB(image, lastx, j)[0] != 255 && getRGB(image, lastx, j)[1] != 255 && getRGB(image, lastx, j)[2] != 255 && getRGB(image, lastx, j)[0] != n1 && getRGB(image, lastx, j)[1] != n2 && getRGB(image, lastx, j)[2] != n3)
		Compo_bl(image, lastx, j, n1, n2, n3);
	if (lasty >= 0 && getRGB(image, i, lasty)[0] != 255 && getRGB(image, i, lasty)[1] != 255 && getRGB(image, i, lasty)[2] != 255 && getRGB(image, i, lasty)[0] != n1 && getRGB(image, i, lasty)[1] != n2 && getRGB(image, i, lasty)[2] != n3)
		Compo_bl(image, i, lasty, n1, n2, n3);*/
	for (int k = i; k < width && getRGB(image, k, j)[0] != 255 && getRGB(image, k, j)[1] != 255 && getRGB(image, k, j)[2] != 255 && getRGB(image, k, j)[0] != n1 && getRGB(image, k, j)[1] != n2 && getRGB(image, k, j)[2] != n3;k++)
	{
		setPixel(image, k, j, SDL_MapRGB(image->format, n1, n2, n3));
		int l = j + 1;
		if (l < height && getRGB(image, k, l)[0] != 255 && getRGB(image, k, l)[1] != 255 && getRGB(image, k, l)[2] != 255 && getRGB(image, k, l)[0] != n1 && getRGB(image, k, l)[1] != n2 && getRGB(image, k, l)[2] != n3)
			Compo_tr(image, k, l, n1, n2, n3);
	}
}

void Compo_bl(SDL_Surface* image)
{
	int width = image->w;
    int height = image->h;
	std::vector<Uint8> rgb1;
	std::vector<Uint8> rgb2;
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			rgb1 = getRGB(image, i, j);
			if (rgb1[0] != 255 && rgb1[1] != 255 && rgb1[2 != 255])
			{
				if (i - 1 >= 0)
				{
					rgb2 = getRGB(image, i - 1, j);
					if (rgb2[0] != 255 && rgb2[1] != 255 && rgb2[2] != 255)
					{
						if (rgb1[0] != rgb2[0] || rgb1[1] != rgb2[1] || rgb1[2] != rgb2[2])
						{
							std::vector<std::pair<int,int> > points = Findall(image, rgb2[0], rgb2[1], rgb2[2]);
							while (points.size() > 0)
							{
								std::pair<int,int> p = points.back();
								points.pop_back();
								setPixel(image, p.first, p.second, SDL_MapRGB(image->format, rgb1[0], rgb1[1], rgb1[2]));
							}
						}
					}
				}
				if (j - 1 >= 0)
				{
					rgb2 = getRGB(image, i, j - 1);
					if (rgb2[0] != 255 && rgb2[1] != 255 && rgb2[2] != 255)
					{
						if (rgb1[0] != rgb2[0] || rgb1[1] != rgb2[1] || rgb1[2] != rgb2[2])
						{
							std::vector<std::pair<int,int> > points = Findall(image, rgb2[0], rgb2[1], rgb2[2]);
							while (points.size() > 0)
							{
								std::pair<int,int> p = points.back();
								points.pop_back();
								setPixel(image, p.first, p.second, SDL_MapRGB(image->format, rgb1[0], rgb1[1], rgb1[2]));
							}
						}
					}
				}
			}
		}
}

std::vector<int>* ChooseCompo(SDL_Surface* img)
{
	std::vector<int>* maxcompo = new std::vector<int>(3,0);
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
			if (rgb[0] != 255 && rgb[0] != 0)
			{
			if (c1 != rgb[0] || c2 != rgb[1] || c3 != rgb[2] )
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
					maxcompo->at(0) = c1;
					maxcompo->at(1) = c2;
					maxcompo->at(2) = c3;
				}
			}
			}
		}
	return maxcompo;
}

void ColorCompo(SDL_Surface* img, std::vector<int> compo)
{
	
	int width = img->w;
    int height = img->h;
	int c3 = compo[2];
	int c2 = compo[1];
	int c1 = compo[0];
	std::vector<Uint8> rgb = std::vector<Uint8>();
	SDL_Surface* tmp = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_BlitSurface(img, NULL, tmp, NULL);
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

//Dis si la composante à des dimensions qui correspondent à celle d'une canette
bool CheckCompo(int l, int L)
{
	return (l * 2 <= L && l * 1.5 >= L) || (L * 2 <= l && L * 1.5 >= l);
}

int getL(SDL_Surface* img)
{
	int width = img->w;
	int height = img->h;
	int Lmax = 0;
	for (int j = 0; j < height; j++)
	{
		int L = 0;
		int i = 0;
		for (int k = 0; k < width; k++)
		{
			if (L == 0 && getRGB(img, k,j)[0] == 0)
			{
				L++;
				i = k;
				//std::cout << i << std::endl;
			}
			else
			{
				if (getRGB(img,k,j)[0] == 0)
				{
					L += k - i;
					//std::cout << k -i << std::endl;
					i = k;
				}
			}
		}
		Lmax = std::max(Lmax, L);
	}
	return Lmax;
}

int getl(SDL_Surface* img)
{
    int width = img->w;
	int height = img->h;
	int lmax = 0;
	for (int k = 0; k < width; k++)
	{
		int l = 0;
		int i = 0;
		for (int j = 0; j < height; j++)
		{
			if (l == 0 && getRGB(img, k, j)[0] == 0)
			{
				l++;
				i = j;
			}
			else
			{
				if (getRGB(img,k,j)[0] == 0)
				{
					l += j - i;
					i = j;
				}
			}
		}
		lmax = std::max(lmax, l);
	}
	return lmax;
}

//Supposition qu'il n'y a qu'une composante affichée et qu'elle est liée(aucun blanc à l'intérieur passage préalable d'une ouverture très grande)
/*void TraceRekt(SDL_Surface* img)//Peut etre prendre une seconde image étant celle de base sur laquelle tracer le rect
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
*/

std::vector<std::pair<int, int> > Findall(SDL_Surface* img, int n1, int n2, int n3)
{
	int width = img->w;
    int height = img->h;
	std::vector<Uint8> rgb;
	std::vector<std::pair<int,int> > all = std::vector<std::pair<int,int> >();
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			rgb = getRGB(img, i, j);
			if (rgb[0] == n1 && rgb[1] == n2 && rgb[2] == n3)
			{
				all.push_back(std::make_pair(i,j));
			}
		}
	return all;
}

void Compo(SDL_Surface* image)
{
	int width = image->w;
    int height = image->h;
	std::vector<Uint8> rgbg;
	std::vector<Uint8> rgbh;
	SDL_Surface* tmp = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_BlitSurface(image, NULL, tmp, NULL);
	int k = 0;
	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	for (int j = 1; j < height; j++)
		for (int i = 1; i < width; i++)
		{
			if (getRGB(tmp, i, j)[0] == 0)
			{
			rgbh = getRGB(tmp, i, j -1);
			rgbg = getRGB(tmp, i - 1, j);
			if (rgbg[0] == 255 && rgbh[0] == 255)
			{
				n1++;
				n2 += n1 / 254;
				n3 += n2 / 254;
				n1 = n1 % 254;
				setPixel(image, i, j, SDL_MapRGB(image->format, n1, n2, n3));
			}
			else
			{
				if (rgbg[0] == 0 && rgbh[0] == 0)
				{
					std::vector<Uint8> rgb1 = getRGB(image, i - 1, j);
					std::vector<Uint8> rgb2 = getRGB(image, i ,j - 1);
					int m = std::min(rgb1[2], rgb2[2]);
					if (m == rgb1[2] && m == rgb2[2])
					{
						m = std::min(rgb1[1], rgb2[1]);
						if (m == rgb1[1] && m == rgb2[1])
						{
							m = std::min(rgb1[0], rgb2[0]);
							setPixel(image, i, j, SDL_MapRGB(image->format, m, rgb1[1], rgb1[2]));
						}
						else if (m == rgb1[1])
							setPixel(image, i, j, SDL_MapRGB(image->format, rgb1[0], rgb1[1], rgb1[2]));
						else
							setPixel(image, i, j, SDL_MapRGB(image->format, rgb2[0], rgb2[1], rgb2[2]));
					}
					else if (m == rgb1[2])
						setPixel(image, i, j, SDL_MapRGB(image->format, rgb1[0], rgb1[1], rgb1[2]));
					else
						setPixel(image, i, j, SDL_MapRGB(image->format, rgb2[0], rgb2[1], rgb2[2]));
				}
				else if (rgbg[0] == 0)
				{
					std::vector<Uint8> rgb = getRGB(image, i - 1, j);
					setPixel(image, i, j, SDL_MapRGB(image->format, rgb[0], rgb[1], rgb[2]));
				}
				else
				{
					std::vector<Uint8> rgb = getRGB(image, i, j - 1);
					setPixel(image, i, j, SDL_MapRGB(image->format, rgb[0], rgb[1], rgb[2]));
				}
			}
			}
		}
	while (k < 5)
	{
	for (int j = height - 2; j >= 0; j--)
		for (int i = width - 2; i >= 0; i--)
		{
			if (getRGB(tmp, i, j)[0] == 0)
			{
				std::vector<Uint8> rgb1 = getRGB(image, i + 1, j);
				std::vector<Uint8> rgb2 = getRGB(image, i ,j + 1);
				if (rgb1[0] != 255 && rgb2[0] != 255)
				{
				int m = std::min(rgb1[2], rgb2[2]);
					if (m == rgb1[2] && m == rgb2[2])
					{
						m = std::min(rgb1[1], rgb2[1]);
						if (m == rgb1[1] && m == rgb2[1])
						{
							m = std::min(rgb1[0], rgb2[0]);
							setPixel(image, i, j, SDL_MapRGB(image->format, m, rgb1[1], rgb1[2]));
						}
						else if (m == rgb1[1])
							setPixel(image, i, j, SDL_MapRGB(image->format, rgb1[0], rgb1[1], rgb1[2]));
						else
							setPixel(image, i, j, SDL_MapRGB(image->format, rgb2[0], rgb2[1], rgb2[2]));
					}
					else if (m == rgb1[2])
						setPixel(image, i, j, SDL_MapRGB(image->format, rgb1[0], rgb1[1], rgb1[2]));
					else
						setPixel(image, i, j, SDL_MapRGB(image->format, rgb2[0], rgb2[1], rgb2[2]));
				}
			}
		}
		
	for (int j = 1; j < height; j++)
		for (int i = 1; i < width; i++)
		{
			if (getRGB(tmp, i, j)[0] == 0)
			{
				std::vector<Uint8> rgb1 = getRGB(image, i - 1, j);
				std::vector<Uint8> rgb2 = getRGB(image, i ,j - 1);
				if (rgb1[0] != 255 && rgb2[0] != 255)
				{
				int m = std::min(rgb1[2], rgb2[2]);
					if (m == rgb1[2] && m == rgb2[2])
					{
						m = std::min(rgb1[1], rgb2[1]);
						if (m == rgb1[1] && m == rgb2[1])
						{
							m = std::min(rgb1[0], rgb2[0]);
							setPixel(image, i, j, SDL_MapRGB(image->format, m, rgb1[1], rgb1[2]));
						}
						else if (m == rgb1[1])
							setPixel(image, i, j, SDL_MapRGB(image->format, rgb1[0], rgb1[1], rgb1[2]));
						else
							setPixel(image, i, j, SDL_MapRGB(image->format, rgb2[0], rgb2[1], rgb2[2]));
					}
					else if (m == rgb1[2])
						setPixel(image, i, j, SDL_MapRGB(image->format, rgb1[0], rgb1[1], rgb1[2]));
					else
						setPixel(image, i, j, SDL_MapRGB(image->format, rgb2[0], rgb2[1], rgb2[2]));
				}
			}
		}
		k++;
	}
}