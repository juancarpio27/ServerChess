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

    Game();
public:
    Game(Board *_board);

    bool init();

    int execute();

    void clean();
};


#endif //CHESS_SOLVER_GAME_H
