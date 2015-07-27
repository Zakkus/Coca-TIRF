#include"Filters.hh"

void redFilter(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
    std::vector<Uint8> rgb;
    //SDL_Surface* tmp = new SDL_Surface(*image);

    
		par_dilate par = par_dilate(image, width);
        parallel_for(tbb::blocked_range<int>(0, height * width),
			par);

  //delete tmp;
}

void whiteFilter(SDL_Surface* image, int L, int l, int min_left, int min_up)
{
    int width = image->w;
    int height = image->h;
    std::vector<Uint8> rgb;
    //SDL_Surface* tmp = new SDL_Surface(*image);

    for (int i = min_left; i < min_left + L; i++)
		parallel_for(tbb::blocked_range<int>(min_up, min_up + l), par_white(image, i));
        /*for (int j = min_up; j < min_up + l; j++)
        {
            rgb = getRGB(image, i, j);
            if (rgb[1] >= 120 && rgb[2] >= 120 && rgb[0] >= 120)
                setPixel(image, i, j, SDL_MapRGB(image->format, 255, 255, 255));
        }*/
    //delete tmp;
}

//erode et dilate ont besoin d'une SDL_Surface binarisée

void erode(SDL_Surface* image, int dimx, int dimy)
{
    int width = image->w;
    int height = image->h;
    SDL_Surface* tmp = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_BlitSurface(image, NULL, tmp, NULL);
    std::vector<Uint8> rgb = std::vector<Uint8>();
        parallel_for(tbb::blocked_range<int>(0, (width - 2 * dimx) * (height - 2 * dimy)), par_setpix(tmp, image, dimx, dimy, 255, SDL_MapRGB(image->format, 255, 255, 255)));
		/*for (int i = dimx; i < width - dimx; i++)
        {
            rgb = getRGB(tmp, i, j);
            if (rgb[0] == rgb[1] && rgb[1] == rgb[2] && rgb[0] == 255)
                for (int x = -dimx; x <= dimx; x++)
					for (int y = -dimy; y <= dimy; y++)
						setPixel(image, x+i, y+j, SDL_MapRGB(image->format, 255,255,255));
	//				parallel_for (tbb::blocked_range<int>(-dimy, dimy), 
	//			par_setpix(image, x, i, j, SDL_MapRGB(image->format, 255,255,255)));
  
        }*/
 //   delete tmp;
}



void dilate(SDL_Surface* image, int dimx, int dimy)
{
    int width = image->w;
    int height = image->h;
    SDL_Surface* tmp = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_BlitSurface(image, NULL, tmp, NULL);
    std::vector<Uint8> rgb = std::vector<Uint8>();
    //for (int j = dimy; j < height - dimy; j++)
        parallel_for(tbb::blocked_range<int>(0, (width - 2 * dimx) * (height - 2 * dimy)),par_setpix(tmp, image, dimx, dimy, 0, SDL_MapRGB(image->format, 0,0,0)));
		/*for (int i = dimx; i < width - dimx; i++)
        {
            rgb = getRGB(tmp, i, j);
            if (rgb[0] == rgb[1] && rgb[1] == rgb[2] && rgb[0] == 0)
                for (int x = -dimx; x <= dimx; x++)
					for (int y = -dimy; y <= dimy; y++)
           //         parallel_for (tbb::blocked_range<int>(-dimy, dimy + 1), 
			//	par_setpix(image, x, i, j, SDL_MapRGB(image->format, 0,0,0)));
                        setPixel(image, x + i, y + j, SDL_MapRGB(image->format, 0, 0, 0));
        }*/
    //delete tmp;
}

//Image binarisée donne un numéro sur chaque composante

void MaxCompo(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
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
                    Compo_tr(image, i, j, n1, n2, n3);
                }
                else
                {
                    n2++;
                    n1 = n1 % 254;
                    if (n2 / 254 == 0)
                    {
                        Compo_tr(image, i, j, n1, n2, n3);
                    }
                    else
                    {
                        n3++;
                        n2 = n2 % 254;
                        if (n3 / 254 == 0)
                        {
                            Compo_tr(image, i, j, n1, n2, n3);
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
        }
        for (int l = i + 1; l < width && getRGB(image, l, j)[0] == 0 && getRGB(image, l, j)[1] == 0 && getRGB(image, l, j)[2] == 0; l++)
        {
            setPixel(image, l, j, SDL_MapRGB(image->format, n1, n2, n3));
            if (j - 1 >= 0)
                Compo_tb(image, l, j - 1, n1, n2, n3);
            if (j + 1 < height)
                Compo_tb(image, l, j + 1, n1, n2, n3);
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
        }
        for (int l = j + 1; l < height && getRGB(image, i, l)[0] == 0 && getRGB(image, i, l)[1] == 0 && getRGB(image, i, l)[2] == 0; l++)
        {
            setPixel(image, i, l, SDL_MapRGB(image->format, n1, n2, n3));
            if (i - 1 >= 0)
                Compo_lr(image, i - 1, l, n1, n2, n3);
            if (j + 1 < height)
                Compo_lr(image, i + 1, l, n1, n2, n3);
        }
    }
}

void Compo_tr(SDL_Surface* image, int i, int j, int n1, int n2, int n3)
{
    int width = image->w;
    int height = image->h;
    int lastx = i - 1;
    int lasty = j - 1;
    for (int k = i; k < width && getRGB(image, k, j)[0] != 255 && getRGB(image, k, j)[1] != 255 && getRGB(image, k, j)[2] != 255 &&
                    getRGB(image, k, j)[0] != n1 && getRGB(image, k, j)[1] != n2 && getRGB(image, k, j)[2] != n3; k++)
    {
        setPixel(image, k, j, SDL_MapRGB(image->format, n1, n2, n3));
        int l = j + 1;
        if (l < height && getRGB(image, k, l)[0] != 255 && getRGB(image, k, l)[1] != 255 && getRGB(image, k, l)[2] != 255 &&
            getRGB(image, k, l)[0] != n1 && getRGB(image, k, l)[1] != n2 && getRGB(image, k, l)[2] != n3)
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

std::map<int, int> ChooseCompo(SDL_Surface* img)
{
    std::map<int, int>  compos = std::map<int, int>();
    int height = img->h;
    int width = img->w;
    std::vector<Uint8> rgb = std::vector<Uint8>();
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            rgb = getRGB(img, i, j);
            if (rgb[0] != 255)
            {
                std::map<int, int>::iterator it = compos.find(rgb[2] * 1000000 + rgb[1] * 1000 + rgb[0]);
                if (it != compos.end())
                    it->second = it->second + 1;
                else
                    compos[rgb[2] * 1000000 + rgb[1] * 1000 + rgb[0]] = 1;
            }
        }
    return compos;
}

std::pair<int, int> GetMaxCompo(std::map<int, int>& compos)
{
    std::pair<int, int> max = std::make_pair(0,0);
    for (std::map<int, int>::iterator it = compos.begin(); it != compos.end(); it++)
    {
        int m = std::max(max.second, it->second);
        if (m != max.second)
            max = *it;
    }
	compos.erase(max.first);
    return max;
}

void ColorCompo(SDL_Surface* img, std::vector<int> compo)
{
    int width = img->w;
    int height = img->h;
    int c3 = compo[2];
    int c2 = compo[1];
    int c1 = compo[0];
    std::vector<Uint8> rgb = std::vector<Uint8>();
    //SDL_Surface* tmp = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    //SDL_BlitSurface(img, NULL, tmp, NULL);
	parallel_for(tbb::blocked_range<int>(0, width*height), par_color(img, width, c1,c2,c3));
    /*for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            rgb = getRGB(img,i,j);
            if (rgb[0] == c1 && rgb[1] == c2 && rgb[2] == c3)
                setPixel(img, i, j, SDL_MapRGB(img->format, 0,0,0));
            else
                setPixel(img, i, j, SDL_MapRGB(img->format, 255, 255, 255));
        }*/
    //delete tmp;
}

int CheckCompo(int l, int L)
{
    if (l == 0 || L == 0)
        return false;
    if (l > L)
        return (100 * L) / l;
    else
        return (100 * l) / L;
    return l > 10 && L > 10 && ((l * 2 >= L && l  <= L) || (L * 2 >= l && L <= l));
}

int getL(SDL_Surface* img, int &min_left)
{
    int width = img->w;
    int height = img->h;
    int Lmax = 0, xmin = width - 1;
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
                xmin = std::min(xmin, k);
            }
            else
            {
                if (getRGB(img,k,j)[0] == 0)
                {
                    L += k - i;
                    i = k;
                    xmin = std::min(xmin, k);
                }
            }
        }
        Lmax = std::max(Lmax, L);
    }
    min_left = xmin;
    return Lmax;
}

int getl(SDL_Surface* img, int &min_up)
{
    int width = img->w;
    int height = img->h;
    int lmax = 0, ymin = height - 1;
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
                ymin = std::min(ymin, j);
            }
            else
            {
                if (getRGB(img,k,j)[0] == 0)
                {
                    l += j - i;
                    i = j;
                    ymin = std::min(ymin, j);
                }
            }
        }
        lmax = std::max(lmax, l);
    }
    min_up = ymin;
    return lmax;
}


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

float CheckPercent(SDL_Surface* img, int xmin, int ymin, int l, int L)
{
    int nbwhite = 0;
    for (int i = xmin; i < xmin + L; i ++)
    {
        int tmpwhite = 0;
        int black = 0;
        for (int j = ymin; j < ymin + l; j ++)
        {
            if (black == 0 && getRGB(img,i,j)[0] != 255)
                black = 1;
            if (black == 1 && getRGB(img, i, j)[0] == 255)
                tmpwhite++;
            if (black == 1 && getRGB(img,i,j)[0] != 255)
            {
                nbwhite += tmpwhite;
                tmpwhite = 0;
            }
        }
    }

    double percent = (double)nbwhite / (double)(l * L);
    return percent;
}
