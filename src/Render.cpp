#include "Render.h"

Render::Render()
{
    surface=nullptr;
    texture=nullptr;
    TTF_Init();
    font=TTF_OpenFont("superstar.ttf",50);
}
void Render::loadbackground(SDL_Renderer* &renderer){
surface=IMG_Load("background.png");
texture=SDL_CreateTextureFromSurface(renderer,surface);
SDL_RenderCopy(renderer,texture,nullptr,nullptr);
}
void Render::loadgameover(SDL_Renderer* &renderer){
surface=IMG_Load("gameover.png");
SDL_Rect drect;
drect.h=280;
drect.w=280;
drect.x=140;
drect.y=140;
texture=SDL_CreateTextureFromSurface(renderer,surface);
SDL_RenderCopy(renderer,texture,nullptr,&drect);
}
Render::~Render(){
SDL_FreeSurface(surface);
surface=nullptr;
SDL_DestroyTexture(texture);
texture=nullptr;
}

void Render::loadScore(std::string text, int x,int y,SDL_Renderer* &renderer){
    surface = TTF_RenderText_Solid(font, text.c_str(),textColor);
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_Rect dest;
    dest.x = x+(25*(10-text.size())/2);
    dest.y = y;
    dest.w = 25*text.size();
    dest.h = 50;
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
    SDL_DestroyTexture(texture);
 	SDL_FreeSurface(surface);
}

