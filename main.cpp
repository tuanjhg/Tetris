#include"Game.h"
#include"Menu.h"
int main(int argc,char* argv[]){
    Game* game = new Game();
    Menu*startMenu = new Menu(262, 170, 5, 320, 30);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window*window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    startMenu->init(renderer, "obj/Image/gamestart.jpg",startMenu-> startMenuButtonText);
    bool runningMenu = true;
    bool startGame ;
    bool Running=true;
    while (Running) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0 ) {
            if (e.type == SDL_QUIT) Running = false;
            else {
                if (runningMenu) {
                    startMenu->handleEvent(e, renderer);
                    switch (startMenu->getStatus()) {
                        case Menu::PLAY_BUTTON_PRESSED:
                            runningMenu = false;
                            startGame=true;
                             break;
                        case Menu::EXIT_BUTTON_PRESSED:
                            Running = false;
                             break;
                    }
                }
            }
        }
        if (!runningMenu) {
                if(startGame){
                game->gameloop(renderer);
                game->quit(runningMenu);
        }
          if (runningMenu){ startGame = false;
          startMenu->currentMenuStatus=1;
}
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if (runningMenu){
        startMenu->render(renderer, startMenu->highScore);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    renderer=nullptr;
    SDL_DestroyWindow(window);
    window=nullptr;
    SDL_Quit();
    return 0;
}
