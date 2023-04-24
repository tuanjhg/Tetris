#include "Tetromino.h"
void Tetromino::setRandom(){
    pieceType = rand() % PIECE_TYPES;
    rotation = rand() % ROTATIONS;
    x = 16/ 2 - 2;
    y = 0;
}
void Tetromino::setNewRandom(){
    pieceType = rand() % PIECE_TYPES;
    rotation = 2;
    x=24;
    y=3;
}
void Tetromino::rotate(){
    rotation = (rotation + 1) % ROTATIONS;
}
void Tetromino::move(int posX,int posY){
    x += posX;
    y += posY;
}
Tetromino::Tetromino(){
    x = 0;
    y = 0;
    pieceType = 0;
    rotation = 0;
}
void Tetromino::draw(SDL_Renderer*renderer){
    for (int i = 0; i < BLOCKS_PER_PIECE; i++) {
        drawBlock(renderer, x+tetrominoes[pieceType][rotation][i][0], y+tetrominoes[pieceType][rotation][i][1], pieceType);
    }
}

void Tetromino::drawBlock(SDL_Renderer* renderer, int x, int y, int colorIndex) {
    SDL_Rect rect = {x*BLOCK_SIZE+24, y*BLOCK_SIZE+20, BLOCK_SIZE, BLOCK_SIZE};
    SDL_SetRenderDrawColor(renderer, colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2], 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderDrawRect(renderer,&rect);
}
void Tetromino::drawnextPiece(SDL_Renderer * renderer){
    for (int i = 0; i < BLOCKS_PER_PIECE; i++) {
        drawnextBlock(renderer, x+tetrominoes[pieceType][rotation][i][0], y+tetrominoes[pieceType][rotation][i][1], pieceType);
    }
}
void Tetromino::drawnextBlock(SDL_Renderer * renderer,int x,int y ,int colorIndex){
        SDL_Rect rect = {x*BLOCK_SIZE-80,y*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
    SDL_SetRenderDrawColor(renderer, colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2], 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderDrawRect(renderer,&rect);
}
