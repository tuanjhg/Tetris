#ifndef RENDER_H
#define RENDER_H
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include <SDL_ttf.h>
class Render
{
    public:
        Render();
        ~Render();
        void loadbackground(SDL_Renderer* &renderer);
        void loadgameover(SDL_Renderer* &renderer);
        TTF_Font*font;
        SDL_Surface*surface;
        SDL_Texture*texture;
        SDL_Color textColor={243,156,18};
        void loadScore(std::string text,int x,int y,SDL_Renderer* &renderer);
};

#endif // RENDER_H
