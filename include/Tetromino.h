#ifndef TETROMINO_H
#define TETROMINO_H
#include<Render.h>
const int PIECE_TYPES = 7;
const int ROTATIONS = 4;
const int BLOCK_SIZE = 20;
const int BLOCKS_PER_PIECE = 4;
const int tetrominoes[PIECE_TYPES][ROTATIONS][BLOCKS_PER_PIECE][2] = {
    // I
    {
        {{0,1},{1,1},{2,1},{3,1}},
        {{2,0},{2,1},{2,2},{2,3}},
        {{0,2},{1,2},{2,2},{3,2}},
        {{1,0},{1,1},{1,2},{1,3}}
    },
    // J
    {
        {{0,1},{1,1},{2,1},{2,0}},
        {{0,1},{1,1},{2,1},{0,2}},
        {{1,0},{1,1},{1,2},{2,2}},
        {{1,0},{1,1},{1,2},{0,0}}
    },
    // L
    {
        {{0,1},{1,1},{2,1},{2,2}},
        {{1,0},{1,1},{1,2},{2,0}},
        {{0,1},{1,1},{2,1},{0,0}},
        {{1,0},{1,1},{1,2},{0,2}}
    },
    // O
    {
        {{0,0},{0,1},{1,0},{1,1}},
        {{0,0},{0,1},{1,0},{1,1}},
        {{0,0},{0,1},{1,0},{1,1}},
        {{0,0},{0,1},{1,0},{1,1}}
    },
    // S
    {
        {{1,0},{2,0},{0,1},{1,1}},
        {{1,0},{1,1},{2,1},{2,2}},
        {{1,1},{2,1},{0,2},{1,2}},
        {{0,0},{0,1},{1,1},{1,2}}
    },
    // T
    {
        {{0,1},{1,1},{2,1},{1,2}},
        {{1,0},{1,1},{2,1},{1,2}},
        {{1,0},{0,1},{1,1},{2,1}},
        {{1,0},{0,1},{1,1},{1,2}}
    },
    // Z
    {
        {{0,0},{1,0},{1,1},{2,1}},
        {{2,0},{1,1},{2,1},{1,2}},
        {{0,1},{1,1},{1,2},{2,2}},
        {{1,0},{0,1},{1,1},{0,2}}
    }
};
const int colors[PIECE_TYPES+1][3] = {
// cyan
{0, 255, 255},
// blue
{0, 0, 255},
// orange
{255, 165, 0},
// yellow
{255, 255, 0},
// green
{0, 255, 0},
// purple
{128, 0, 128},
// red
{255, 0, 0},
//white
{0,0,0}
};
class Tetromino{
    public:
    int x;
    int y;
    int pieceType;
    int rotation;
    Tetromino();
    void draw(SDL_Renderer* renderer);
    void move(int posX, int posY);
    void rotate() ;
    void setRandom();
    void setNewRandom();
    void drawBlock(SDL_Renderer*renderer,int x,int y,int colorIndex);
    void drawnextPiece(SDL_Renderer * renderer);
    void drawnextBlock(SDL_Renderer * renderer,int x,int y ,int colorIndex);
};

#endif // TETROMINO_H
