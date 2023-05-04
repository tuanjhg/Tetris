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
    nextPieceTetromino.setNewRandom();
    playername = "Unknown";
    playerDecision = WAITING;
    currentBut=1;
}
void Game::update(const int &GameType) {
    if (!gameover) {
        currentTetromino.move(0, 1);
        if (collides(GameType)) {
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
            if (collides(GameType)) {
                gameover = true;
            }
        }
    }
}
bool Game::collides(const int &GameType) {
    for (int i = 0; i < BLOCKS_PER_PIECE; i++) {
        int x = currentTetromino.x + tetrominoes[currentTetromino.pieceType][currentTetromino.rotation][i][0];
        int y = currentTetromino.y + tetrominoes[currentTetromino.pieceType][currentTetromino.rotation][i][1];
        if (GameType==1&&(x < 0 || x >= BOARD_WIDTH || y >= BOARD_HEIGHT || (y >= 0 && board[y][x] >= 0))) {
            return true;
        }
        if(GameType==2&&(x < 0 || x >= BOARD_WIDTH || y >= BOARD_HEIGHT/2 || (y >= 0 && board[y][x] >= 0))){
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
void Game::draw(SDL_Renderer* &renderer,const int &GameType) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if(GameType==1){
            render->loadbackground(renderer);}
    else{
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer,0,280,560,280);
        SDL_RenderDrawLine(renderer,280,0,280,280);
        SDL_RenderDrawLine(renderer,280,140,560,140);
        SDL_RenderDrawLine(renderer,0,20,280,20);
    }
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
void Game::gameloop(SDL_Renderer*&renderer,const int &GameType){
    runningEGBoard=true;
    Game game;
    Uint32 lastTime = SDL_GetTicks();
    while (!game.gameover) {
            SDL_Event event;
        while (SDL_PollEvent(&event)!=0) {
            if (event.type == SDL_QUIT) {
                game.gameover = true;
                runningEGBoard=false;
                exitToMenu=true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT) {
                    game.currentTetromino.move(-1, 0);
                if (game.collides(GameType)) {
                    game.currentTetromino.move(1, 0);
                }
            } else if (event.key.keysym.sym == SDLK_RIGHT) {
                    game.currentTetromino.move(1, 0);
                if (game.collides(GameType)) {
                    game.currentTetromino.move(-1, 0);
            }
            } else if (event.key.keysym.sym == SDLK_DOWN) {
                    game.currentTetromino.move(0, 1);
                if (game.collides(GameType)) {
                    game.currentTetromino.move(0, -1);
            }
            } else if (event.key.keysym.sym == SDLK_UP) {
                    game.currentTetromino.rotate();
                if (game.collides(GameType)) {
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
        game.update(GameType);
        game.draw(renderer,GameType);
        }
        SDL_Delay(10);
    }
    SDL_Delay(100);
    }
void Game::quit(bool &exittoMenu){
    TTF_Quit();
    Mix_Quit();
    exittoMenu=exitToMenu;
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
int Game::getPlayerDecision() const{
    return playerDecision;
}
void Game::reset(){
    playerDecision = WAITING;
    pos = -1;
    yesBut->setStatus(Button::BUTTON_IN);
    noBut->setStatus(Button::BUTTON_OUT);
}
void Game::GameEnd(bool &exitToMenu,SDL_Event &e,SDL_Renderer * &renderer,std::vector<std::string> &scoreData){
    playerName->loadRenderText(renderer, playername.c_str(), {255, 255, 255, 255});
    egBoard = render->loadImage(renderer, "endgame.png");
    hsBoard = render->loadImage(renderer, "newHighscore.png");
    yesBut->loadButton(renderer, "Yes"); yesBut->setStatus(Button::BUTTON_IN);
    noBut ->loadButton(renderer, "No");  noBut ->setStatus(Button::BUTTON_OUT);
    SDL_Rect dsRect = {50, 50, 450, 350};
        for (int i = 0; i < scoreData.size(); ++i) {
                int t = 0;
                int j = 0;
                while (j < scoreData[i].length() && scoreData[i][j] != ':') ++j;
                j += 2;
                while (j < scoreData[i].length()) t = t * 10 + scoreData[i][j] - '0', ++j;
                if (score > t) {
                    newRecord = true;
                    SDL_StartTextInput();
                    pos = i;
                    break;
                }
            }
    while (runningEGBoard) {
        if (newRecord) {
            SDL_RenderCopy(renderer, hsBoard, nullptr, &dsRect);
            if (playername != "") {
                playerName->loadRenderText(renderer, playername.c_str(), {0, 0, 0, 255});
                playerName->renderText(renderer, 350, 258, Render::CENTER);
            }
        }
        else{
            SDL_RenderCopy(renderer, egBoard, nullptr, &dsRect);
            yesBut->renderButton(renderer);
            noBut ->renderButton(renderer);
        }
        SDL_Event e;
        while (SDL_PollEvent(&e)!=0) {
         if (newRecord) {
                    if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_RETURN && playername.length() > 2) {
                            SDL_StopTextInput();
                            std::string data = playername + ": " + std::to_string(score);
                            scoreData.emplace(scoreData.begin() + pos, data.c_str());
                            scoreData.pop_back();
                            newRecord = false;
                            exitToMenu=true;
                }
                    if (e.key.keysym.sym == SDLK_BACKSPACE && playername.length() > 0) {
                        playername.pop_back();
                }
                    else if (e.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL) ) {
                        SDL_SetClipboardText(playername.c_str());
                }
                    else if (e.key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL)) {
                        playername = SDL_GetClipboardText();
                }
            }
                else if (e.type == SDL_TEXTINPUT) {
                    if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) && playername.length() < 22)
                        if ((e.text.text[0] >= 'a' && e.text.text[0] <= 'z') || (e.text.text[0] >= 'A' && e.text.text[0] <= 'Z') || (e.text.text[0] >= '0' && e.text.text[0] <= '9') || e.text.text[0] == ' ')
                            playername += e.text.text;
                }
        }
        else {
                    if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) {
                        currentBut = 2;
                        noBut ->setStatus(Button::BUTTON_IN);
                        yesBut->setStatus(Button::BUTTON_OUT);
                    }
                    else if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT) {
                        currentBut = 1;
                        yesBut->setStatus(Button::BUTTON_IN);
                        noBut ->setStatus(Button::BUTTON_OUT);
                    }
                    else if (e.key.keysym.sym == SDLK_RETURN) {
                        if (currentBut == 1) {playerDecision = AGAIN;}
                        if (currentBut ==2) {playerDecision = QUIT;}
                    }
                }
        switch (getPlayerDecision()) {
                    case Game::AGAIN:
                        reset();
                        runningEGBoard=false;
                        break;
                    case Game::QUIT:
                        exitToMenu = true;
                        runningEGBoard=false;
                        break;
                }
        }
        SDL_RenderPresent(renderer);
    }

}
