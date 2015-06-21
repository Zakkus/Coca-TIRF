#include"SDL_init.hh"

SDL_Window* createWindow()
{
    SDL_Window *window;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow
        ("An SDL2 window",
         SDL_WINDOWPOS_UNDEFINED,
         SDL_WINDOWPOS_UNDEFINED,
         640,
         480,
         SDL_WINDOW_OPENGL
        );
    return window;
}

SDL_Surface* loadImage(char* path)
{
    SDL_Surface *image;
    image = IMG_Load(path);
    return image;
}

void displayImage(SDL_Window* window, SDL_Surface* image)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000);
}

Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    int bytesPerPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytesPerPixel;
    switch (bytesPerPixel)
    {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
        default:
            return 0;
    }
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bytesPerPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytesPerPixel;
    switch (bytesPerPixel)
    {
        case 1:
            *p = pixel;
            break;
        case 2:
            *(Uint16 *)p = pixel;
            break;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;
        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

std::vector<Uint8> getRGB(SDL_Surface* image, int i, int j)
{
    Uint8 r, g, b;
    std::vector<Uint8> rgb(3);
    SDL_GetRGB(getPixel(image, i, j), image->format, &r, &g, &b);
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
    return rgb;
}
