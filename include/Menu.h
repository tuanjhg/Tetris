#pragma once

#ifndef _MENU_H_
#define _MENU_H_

#include <vector>
#include "Button.h"
#include "Sound.h"
class Menu {
    private:
        int arrowHSPos;
        int currentButtonID;
        int TOTAL_BUTTON;
        int MENU_BUTTON_WIDTH;
        int MENU_BUTTON_HEIGHT;
        int baseScrPosX;
        int baseScrPosY;
        Sound * sound =new Sound();
        Render* scoreText = nullptr;
        SDL_Texture* menuTexture;
        SDL_Texture* howToPlayTexture;
        SDL_Texture* highScoreTexture;
        std::vector<Button* > menuButton;

        bool running = false;

    public:
        int currentMenuStatus;
        std::vector<std::string>highScore;
        enum Option {RUNNING=1,PLAY_BUTTON_PRESSED,PLAY2_BUTTON_PRESSED,EXIT_BUTTON_PRESSED,HOW_TO_PLAY,HIGH_SCORES};
        SDL_Texture* loadImage(SDL_Renderer* &renderer, const std::string imgPath);
        static const bool ON = true;
        static const bool OFF = false;
        std::vector<std::string> startMenuButtonText = { "New Easy Game","New Hard Game", "How to Play","High Score", "Sound: ON", "Exit"};
        Menu(const int baseScrPosX, const int baseScrPosY, const int totalButton, const int buttonWidth, const int buttonHeight);

        ~Menu();

        void init(SDL_Renderer* &renderer, const std::string imgPath, std::vector<std::string> &buttonText);

        void render(SDL_Renderer* &renderer, std::vector<std::string> scoreData);

        void handleEvent(SDL_Event &e, SDL_Renderer* &renderer);

        int getStatus() const;

};

#endif // _MENU_H_
