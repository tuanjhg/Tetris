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
const int GAME_SPEED=150;
const int SCREEN_WIDTH = 560;
const int SCREEN_HEIGHT = 560;
class Game
{
    public:
        Tetromino currentTetromino;
        Tetromino nextPieceTetromino;
        int board[BOARD_HEIGHT][BOARD_WIDTH];
        bool gameover;
        //SDL_Renderer* renderer;
        //SDL_Window* window;
        //int score;
        Game();
        void init();
        void update();
        bool collides();
        void checkLines();
        void draw(SDL_Renderer* renderer);
        void gamerun();
        void quit();
        void printScore();
        int score;
        SDL_Renderer* renderer;
        SDL_Window* window;
        Render* render=new Render();
};

#endif // GAME_H
