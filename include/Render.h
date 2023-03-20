#ifndef RENDER_H
#define RENDER_H
#include<SDL.h>
#include<SDL_image.h>

class Render
{
    public:
        Render();
        ~Render();
        void loadbackground(SDL_Renderer* &renderer);
        SDL_Surface*surface;
        SDL_Texture*texture;
};

#endif // RENDER_H
