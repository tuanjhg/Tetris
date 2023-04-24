#include "Menu.h"
Menu::Menu(const int baseScrPosX, const int baseScrPosY, const int totalButton, const int buttonWidth, const int buttonHeight) {
    menuTexture  = nullptr;
    howToPlayTexture = nullptr;
    highScoreTexture = nullptr;
    TOTAL_BUTTON = totalButton;
    MENU_BUTTON_WIDTH  = buttonWidth;
    MENU_BUTTON_HEIGHT = buttonHeight;
    this->baseScrPosX  = baseScrPosX;
    this->baseScrPosY  = baseScrPosY;
    sound->init();
}

Menu::~Menu() {
    SDL_DestroyTexture(menuTexture);
    menuTexture = nullptr;
    howToPlayTexture = nullptr;
    SDL_DestroyTexture(highScoreTexture);
    highScoreTexture = nullptr;

    for (Button* button : menuButton) {
        delete button; button = nullptr;
    }
    menuButton.clear();
}
SDL_Texture* Menu::loadImage(SDL_Renderer* &renderer, const std::string imgPath) {
    SDL_Surface* Image = IMG_Load(imgPath.c_str());
    SDL_Texture* loadTexture = SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);
    return loadTexture;
}

void Menu::init(SDL_Renderer* &renderer, const std::string imgPath, std::vector<std::string>& buttonText) {
    SDL_Surface* Image = IMG_Load(imgPath.c_str());
        menuTexture = SDL_CreateTextureFromSurface(renderer, Image);
        SDL_FreeSurface(Image);
        howToPlayTexture = loadImage(renderer, "obj/Image/How to Play1.png");
        Image = IMG_Load("obj/Image/High Scores.png");
        highScoreTexture = loadImage(renderer, "obj/Image/High Scores.png");

        scoreText = new Render(28);

        for (int i = 0; i < TOTAL_BUTTON; ++i)
            menuButton.push_back(new Button(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, baseScrPosX - MENU_BUTTON_WIDTH / 2, baseScrPosY + (5 + MENU_BUTTON_HEIGHT) * (i - 1)));

        for (int i = 0; i < TOTAL_BUTTON; ++i) {
            if (buttonText[i] == "Sound: ON") {
                if (Mix_Volume(-1, -1) == 0) buttonText[i] = "Sound: OFF";
            }
            menuButton[i]->loadButton(renderer, buttonText[i]);
            menuButton[i]->setStatus(Button::BUTTON_OUT);
        }
        menuButton[0]->setStatus(Button::BUTTON_IN);
        currentButtonID = 0;
        currentMenuStatus = RUNNING;
}


void Menu::render(SDL_Renderer* &renderer,  std::vector<std::string> scoreData) {
    if (currentMenuStatus == HOW_TO_PLAY) {
        SDL_RenderCopy(renderer, howToPlayTexture, nullptr, nullptr);
    }
    else if (currentMenuStatus == HIGH_SCORES) {
        SDL_RenderCopy(renderer, highScoreTexture, nullptr, nullptr);
    }
    else {
        SDL_RenderCopy(renderer, menuTexture, nullptr, nullptr);
        for (int i = 0; i < TOTAL_BUTTON; ++i)
            menuButton[i]->renderButton(renderer);
    }
}

void Menu::handleEvent(SDL_Event &e, SDL_Renderer* &renderer) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s) {
                //sound->playButton();
                menuButton[currentButtonID]->setStatus(Button::BUTTON_OUT);
                (currentButtonID += 1) %= TOTAL_BUTTON;
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
        }
        else if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w) {
                //sound->playButton();
                menuButton[currentButtonID]->setStatus(Button::BUTTON_OUT);
                (currentButtonID += TOTAL_BUTTON - 1) %= TOTAL_BUTTON;
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
        }
        else if (e.key.keysym.sym == SDLK_RETURN) {
            if (currentMenuStatus == HOW_TO_PLAY) {
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
                currentMenuStatus = RUNNING;
            }
            else if (currentMenuStatus == HIGH_SCORES) {
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
                currentMenuStatus = RUNNING;
            }
            else {
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
                std::string menuText = menuButton[currentButtonID]->getText();
                if (menuText == "New Game") currentMenuStatus = PLAY_BUTTON_PRESSED;
                else if (menuText == "Exit") currentMenuStatus = EXIT_BUTTON_PRESSED;
                else if (menuText == "Sound: ON") {
                    menuButton[currentButtonID]->changeSoundButton(renderer);
                    Mix_Volume(-1, 0);
                }
                else if (menuText == "Sound: OFF") {
                    menuButton[currentButtonID]->changeSoundButton(renderer),
                    Mix_Volume(-1, MIX_MAX_VOLUME);
                }
                else if (menuText == "How to Play") {
                    currentMenuStatus = HOW_TO_PLAY;
                }
                else if (menuText == "High Score") {
                    currentMenuStatus = HIGH_SCORES;
                }
            }
        }
    }
}

int Menu::getStatus() const {
    return currentMenuStatus;
}
