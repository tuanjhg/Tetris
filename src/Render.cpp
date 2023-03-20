#include "Render.h"

Render::Render()
{
    surface=nullptr;
    texture=nullptr;
}
void Render::loadbackground(SDL_Renderer* &renderer){
surface=IMG_Load("background.png");
texture=SDL_CreateTextureFromSurface(renderer,surface);
SDL_RenderCopy(renderer,texture,nullptr,nullptr);
}
Render::~Render(){
SDL_FreeSurface(surface);
surface=nullptr;
SDL_DestroyTexture(texture);
texture=nullptr;
}
