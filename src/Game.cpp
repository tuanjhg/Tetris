#include "Game.h"
Game::Game() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
        board[i][j] = -1;
    }
}
    renderer=nullptr;
    window=nullptr;
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
        }
    }
}
void Game::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    Render*render=new Render();
    render->loadbackground(renderer);
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] >= 0) {
                currentTetromino.drawBlock(renderer, j, i, board[i][j]);
            }
        }
    }
    currentTetromino.draw(renderer);
    SDL_RenderPresent(renderer);
}
void Game::gamerun(){
    Game game;
    Uint32 lastTime = SDL_GetTicks();
    while (!game.gameover) {
        SDL_Event event;
    while (SDL_PollEvent(&event)) {
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
    if (currentTime - lastTime >= GAME_SPEED){
        lastTime = currentTime;
        game.update();
        game.draw(renderer);
        }
        SDL_Delay(1);
    }
}
void Game::quit(){
    SDL_DestroyRenderer(renderer);
    renderer=nullptr;
    SDL_DestroyWindow(window);
    window=nullptr;
    SDL_Quit();
}
void Game::init(){
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
