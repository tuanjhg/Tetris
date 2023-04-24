#include "Game.h"
Game::Game() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = -1;
        }
    }
    speed=GAME_SPEED;
    score=0;
    currentTetromino.setRandom();
    gameover = false;
}
void Game::update() {
    if (!gameover) {
        currentTetromino.move(0, 1);
        if (collides()) {
            currentTetromino.move(0, -1);
            for (int i = 0; i < BLOCKS_PER_PIECE; i++) {
                int x = currentTetromino.x + tetrominoes[currentTetromino.pieceType][currentTetromino.rotation][i][0];
                int y = currentTetromino.y + tetrominoes[currentTetromino.pieceType][currentTetromino.rotation][i][1];
                board[y][x] = currentTetromino.pieceType;
            }
            checkLines();
            currentTetromino.setRandom();
            currentTetromino.pieceType=nextPieceTetromino.pieceType;
            nextPieceTetromino.setNewRandom();
            if (collides()) {
                gameover = true;
            }
        }
    }
}
bool Game::collides() {
    for (int i = 0; i < BLOCKS_PER_PIECE; i++) {
        int x = currentTetromino.x + tetrominoes[currentTetromino.pieceType][currentTetromino.rotation][i][0];
        int y = currentTetromino.y + tetrominoes[currentTetromino.pieceType][currentTetromino.rotation][i][1];
        if (x < 0 || x >= BOARD_WIDTH || y >= BOARD_HEIGHT || (y >= 0 && board[y][x] >= 0)) {
            return true;
        }
    }
    return false;
}
void Game::checkLines() {
    int linesCleared = 0;
    for (int i = BOARD_HEIGHT-1; i >= 0; i--) {
        bool lineFull = true;
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] == -1) {
                lineFull = false;
                break;
        }
    }
        if (lineFull) {
            linesCleared++;
            for (int k = i; k >= 1; k--) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    board[k][j] = board[k-1][j];
                }
            }
            for (int j = 0; j < BOARD_WIDTH; j++) {
                board[0][j] = -1;
                }
                i++;
                GameScore();
                }
    }
}
void Game::draw(SDL_Renderer* &renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    render->loadbackground(renderer);
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] >= 0) {
                currentTetromino.drawBlock(renderer, j, i, board[i][j]);
            }
        }
    }
    itoa(score,buffer,10);
    std::string text = std::string(buffer);
    render->loadScore(text,330,200,renderer);
    currentTetromino.draw(renderer);
    nextPieceTetromino.drawnextPiece(renderer);
    SDL_RenderPresent(renderer);
}
void Game::gameloop(SDL_Renderer*&renderer){
    Game game;
    Uint32 lastTime = SDL_GetTicks();

    while (!game.gameover) {
            SDL_Event event;
        while (SDL_PollEvent(&event)!=0) {
            if (event.type == SDL_QUIT) {
                game.gameover = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT) {
                    game.currentTetromino.move(-1, 0);
                if (game.collides()) {
                    game.currentTetromino.move(1, 0);
                }
            } else if (event.key.keysym.sym == SDLK_RIGHT) {
                    game.currentTetromino.move(1, 0);
                if (game.collides()) {
                    game.currentTetromino.move(-1, 0);
            }
            } else if (event.key.keysym.sym == SDLK_DOWN) {
                    game.currentTetromino.move(0, 1);
                if (game.collides()) {
                    game.currentTetromino.move(0, -1);
            }
            } else if (event.key.keysym.sym == SDLK_UP) {
                    game.currentTetromino.rotate();
                if (game.collides()) {
                    game.currentTetromino.rotate();
                    game.currentTetromino.rotate();
                    game.currentTetromino.rotate();
                }
            }
        }
    }
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastTime >= speed){
        lastTime = currentTime;
        game.update();
        game.draw(renderer);
        }
        SDL_Delay(10);
    }
    render->loadgameover(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(200);
}
void Game::quit(bool &exitToMenu){
    TTF_Quit();
    Mix_Quit();
    SDL_QUIT;
    exitToMenu=true;
}
void Game::GameScore(){
 if(score<=1000){
        speed=level[0];
        score+=50;
 }
    else if (score>1000 && score<=5000){
        speed=level[1];
        score+=75;
    }else{
        speed=level[2];
        score+=100;
    }
}
