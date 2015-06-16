#include"Utils.hh"

void rgb_to_hsv(int r, int g, int b, int& h, int& s, int& v)
{
    float rbis = r/255, bbis = b/255, gbis = g/255;
    float hbis = h, sbis = s, vbis = v;
    float max = std::max(std::max(rbis, gbis), bbis);
    float min = std::min(std::min(rbis, gbis), bbis);
    vbis = max;

    float d = max - min;
    sbis = max == 0 ? 0 : d / max;

    if (max == min)
        hbis = 0; // achromatic
    else
    {
        if (max == rbis)
            hbis = (gbis - bbis) / d + (gbis < bbis ? 6 : 0);
        else if (max == gbis)
            hbis = (bbis - rbis) / d + 2;
        else if (max == bbis)
            hbis = (rbis - gbis) / d + 4;
        hbis /= 6;
    }
    s = (int)sbis, h = (int)hbis, v = (int)vbis;
}

void hsv_to_rgb(int h, int s, int v, int& r, int& g, int& b)
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

    std::vector<Uint8> rgb;
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
