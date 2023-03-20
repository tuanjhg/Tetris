#include"Game.h"
int main(int argc, char* argv[]) {
    Game* game=new Game();
    game->init();
    game->gamerun();
    game->quit();
    return 0;
}

