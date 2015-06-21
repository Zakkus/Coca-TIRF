#include"Utils.hh"

void Hline(SDL_Surface* image, int x, int y, int w)
{
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.w = w;
    area.h = 10;

    SDL_FillRect(image, &area, SDL_MapRGB(image->format, 0, 255, 200));
}

void Vline(SDL_Surface* image, int x, int y, int h)
{
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.w = 10;
    area.h = h;

    SDL_FillRect(image, &area, SDL_MapRGB(image->format, 0, 255, 200));
}

void draw_rectangle(SDL_Surface *image, int largeur, int longueur, int i, int j)
{
    Hline(image, i, j, largeur);
    Vline(image, i, j, longueur);
    Hline(image, i, j + longueur, largeur);
    Vline(image, i + largeur, j, longueur);
}
