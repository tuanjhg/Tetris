#ifndef GAME_H
#define GAME_H
#include <cstdlib>
#include <ctime>
#include<vector>
#include"Tetromino.h"
#include"Render.h"
#include"Button.h"
#include"Sound.h"
const int BOARD_HEIGHT = 26;
const int BOARD_WIDTH = 13;
const int GAME_SPEED = 125;
const int SCREEN_WIDTH = 560;
const int SCREEN_HEIGHT = 560;
class Game
{
    private:
        Tetromino currentTetromino;
        Tetromino nextPieceTetromino;
        Render* render=new Render(30);
        Render* playerName = new Render(20);
        std::string playername;
        int playerDecision;
        int board[BOARD_HEIGHT][BOARD_WIDTH];
        int score;
        int speed;
        int currentBut;
        int pos =-1;
        bool gameover;
        bool newRecord= true;
        bool runningEGBoard=true;
        char buffer[10];
        int level[3]={GAME_SPEED ,GAME_SPEED -25,GAME_SPEED -50 };
        enum Decision {PAUSE=1,AGAIN,QUIT,WAITING};
        SDL_Texture* egBoard;
        SDL_Texture* hsBoard;
    public:
        Game();
        Button* yesBut = new Button(50, 30, 320, 200);
        Button* noBut  = new Button(50, 30, 400, 200);
        std::vector<std::string> scoreData;
        bool exitToMenu =false;
        void update();
        bool collides();
        void checkLines();
        void draw(SDL_Renderer* &renderer);
        void gameloop(SDL_Renderer* &renderer);
        void quit(bool &exittoMenu);
        void GameScore();
        int getPlayerDecision() const;
        void reset();
        void GameEnd(bool &exitToMenu,SDL_Event &e,SDL_Renderer * &renderer,std::vector<std::string> &scoreData);
        SDL_Texture* loadImage(SDL_Renderer* &renderer, const std::string imgPath);
};

#endif // GAME_H
