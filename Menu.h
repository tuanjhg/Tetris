#pragma once

#ifndef _MENU_H_
#define _MENU_H_

#include <vector>
#include <string>
#include "Button.h"
#include"Sound.h"
class Menu {
    private:
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

        SDL_Texture* loadImage(SDL_Renderer* &renderer, const std::string imgPath);
    public:
        int currentMenuStatus;
        std::vector<std::string>highScore;
        static const int RUNNING = 1;
        static const int PLAY_BUTTON_PRESSED = 2;
        static const int EXIT_BUTTON_PRESSED = 3;
        static const int HOW_TO_PLAY = 4;
        static const int HIGH_SCORES = 5;
        static const bool ON = true;
        static const bool OFF = false;
        std::vector<std::string> startMenuButtonText = { "New Game", "How to Play","High Score", "Sound: ON", "Exit"};
        Menu(const int baseScrPosX, const int baseScrPosY, const int totalButton, const int buttonWidth, const int buttonHeight);

        ~Menu();

        void init(SDL_Renderer* &renderer, const std::string imgPath, std::vector<std::string> &buttonText);

        void render(SDL_Renderer* &renderer, std::vector<std::string> scoreData);

        void handleEvent(SDL_Event &e, SDL_Renderer* &renderer);

        int getStatus() const;

};

#endif // _MENU_H_
