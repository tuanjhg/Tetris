#include"Game.h"
#include"Menu.h"
int main(int argc,char* argv[]){
    Menu*startMenu = new Menu(262, 320, 5, 320, 30);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window*window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Game* game = new Game();
    startMenu->init(renderer, "obj/Image/gamestart.jpg",startMenu-> startMenuButtonText);
    freopen("score.txt", "r", stdin);
            std::string t = "";
            for (int i = 0; i < 10; ++i) {
                std::getline(std::cin, t);
                startMenu->highScore.push_back(t);
            }
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
                game->GameEnd(game->exitToMenu,e,renderer,startMenu->highScore);
                game->quit(runningMenu);
                startMenu->currentMenuStatus=1;
        }else          if (runningMenu){ startGame = false;
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
    freopen("score.txt", "w", stdout);
    for (int i = 0; i < 10; ++i) std::cout << startMenu->highScore[i] << std::endl;
    SDL_DestroyRenderer(renderer);
    renderer=nullptr;
    SDL_DestroyWindow(window);
    window=nullptr;
    SDL_Quit();
    return 0;
}
