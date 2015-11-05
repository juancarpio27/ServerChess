//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_GAME_H
#define CHESS_SOLVER_GAME_H


#include "../board/Board.h"

class Game {
private:
    bool running;
    Board *board;
public:
    Game();

    bool init();

    int execute();

    void clean();
};


#endif //CHESS_SOLVER_GAME_H
