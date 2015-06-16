#include"SDL_init.hh"

SDL_Window* createWindow()
{
    SDL_Window *window;
    //Start SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow
        ("An SDL2 window",                  // window title
         SDL_WINDOWPOS_UNDEFINED,           // initial x position
         SDL_WINDOWPOS_UNDEFINED,           // initial y position
         640,                               // width, in pixels
         480,                               // height, in pixels
         SDL_WINDOW_OPENGL                  // flags
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

    SDL_Delay(5000);
}

//pomp� sur le site du z�ro
/*getPixel : permet de r�cup�rer la couleur d'un pixel
  Param�tres d'entr�e/sortie :
  SDL_Surface *surface : la surface sur laquelle on va r�cup�rer la couleur d'un pixel
  int x : la coordonn�e en x du pixel � r�cup�rer
  int y : la coordonn�e en y du pixel � r�cup�rer

  Uint32 resultat : la fonction renvoie le pixel aux coordonn�es (x,y) dans la surface
  */
Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    /*nbOctetsParPixel repr�sente le nombre d'octets utilis�s pour stocker un pixel.
      En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur
      de l'image : 8, 16, 24 ou 32 bits.*/
    int bytesPerPixel = surface->format->BytesPerPixel;
    /* Ici p est l'adresse du pixel que l'on veut connaitre */
    /*surface->pixels contient l'adresse du premier pixel de l'image*/
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
    //courtesy to siteduzero
    /*nbOctetsParPixel repr�sente le nombre d'octets utilis�s pour stocker un pixel.
      En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur
      de l'image : 8, 16, 24 ou 32 bits.*/
    int bytesPerPixel = surface->format->BytesPerPixel;
    /*Ici p est l'adresse du pixel que l'on veut modifier*/
    /*surface->pixels contient l'adresse du premier pixel de l'image*/
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
            /*Suivant l'architecture de la machine*/
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
