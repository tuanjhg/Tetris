#pragma once
#ifndef RENDER_H
#define RENDER_H
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<iostream>
#include <SDL_ttf.h>
const SDL_Color textColor={255, 128, 204};
class Render
{
    public:
        Render(int fontsize);
        ~Render();
        void loadbackground(SDL_Renderer* &renderer,const int &GameType);
        void loadScore(std::string text,int x,int y,SDL_Renderer* &renderer);
        const std::string FONT_NAME = "superstar.ttf";
        static const int CENTER = 0;
        static const int LEFT = 1;

        void loadRenderText(SDL_Renderer* &renderer, std::string text, SDL_Color textColor);

        void renderText(SDL_Renderer* &renderer, int x, int y, const int type);

        SDL_Texture* loadImage(SDL_Renderer* &renderer, const std::string imgPath);
    private:
        SDL_Rect dsrect;

        TTF_Font*font;
        SDL_Surface* textSurface;
        SDL_Texture* textTexture;
        SDL_Surface* surface;
        SDL_Texture* texture;
};

#endif // RENDER_H
