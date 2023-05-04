#include "Render.h"

Render::Render(int fontsize)
{

    TTF_Init();
    font=TTF_OpenFont(FONT_NAME.c_str(),fontsize);
    textSurface=nullptr;
    textTexture=nullptr;
    surface=nullptr;
    texture=nullptr;
}
void Render::loadbackground(SDL_Renderer* &renderer){
    surface=IMG_Load("obj/Image/background.png");
    texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_RenderCopy(renderer,texture,nullptr,nullptr);
}
SDL_Texture* Render::loadImage(SDL_Renderer* &renderer, const std::string imgPath) {
    SDL_Surface* surface = IMG_Load(imgPath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return texture;
}
Render::~Render(){
    if (font != nullptr) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    if (textTexture != nullptr) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }

    if (textSurface != nullptr) {
        SDL_FreeSurface(textSurface);
        textSurface = nullptr;
    }
     if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    if (surface != nullptr) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
}

void Render::loadScore(std::string text, int x,int y,SDL_Renderer* &renderer){
    font=TTF_OpenFont("superstar.ttf",30);
    SDL_Surface* surface1 = TTF_RenderText_Solid(font, text.c_str(),textColor);
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer,surface1);
    SDL_Rect dest;
    dest.x = x+(25*(10-text.size())/2);
    dest.y = y;
    dest.w = 20*text.size();
    dest.h = 40;
    SDL_RenderCopy(renderer, texture1, nullptr,&dest);
    SDL_FreeSurface(surface1);
    SDL_DestroyTexture(texture1);

}
void Render::loadRenderText(SDL_Renderer* &renderer, std::string text, SDL_Color textColor) {
    if (textSurface != nullptr) SDL_FreeSurface(textSurface);
    textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    if (textTexture != nullptr) SDL_DestroyTexture(textTexture);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
}

void Render::renderText(SDL_Renderer* &renderer, int scrPosX, int scrPosY, const int type) {
    dsrect = {scrPosX, scrPosY, textSurface->w, textSurface->h};
    if (type == CENTER) {
        dsrect.x = scrPosX - textSurface->w / 2;
        dsrect.y = scrPosY - textSurface->h / 2;
    }
    if(type == LEFT){
        dsrect.x = scrPosX - textSurface->w -25;
        dsrect.y = scrPosY - textSurface->h / 3;
    }
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsrect);
}
