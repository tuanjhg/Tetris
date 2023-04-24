#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include"Tetromino.h"
#include"Render.h"
const int BOARD_HEIGHT = 26;
const int BOARD_WIDTH = 13;
const int GAME_SPEED = 125;
const int SCREEN_WIDTH = 560;
const int SCREEN_HEIGHT = 560;
class Game
{
    public:
        Tetromino currentTetromino;
        Tetromino nextPieceTetromino;
        int board[BOARD_HEIGHT][BOARD_WIDTH];
        bool gameover;
        char buffer[10];
        int level[3]={GAME_SPEED ,GAME_SPEED -25,GAME_SPEED -50 };
        Game();
        void update();
        bool collides();
        void checkLines();
        void draw(SDL_Renderer* &renderer);
        void gameloop(SDL_Renderer* &renderer);
        void quit(bool &exitToMenu);
        void GameScore();
        int score;
        int speed;
        Render* render=new Render(30);
};

#endif // GAME_H
