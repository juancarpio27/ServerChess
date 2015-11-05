//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_KNIGHT_H
#define CHESS_SOLVER_KNIGHT_H


#include "../Piece.h"

class Knight : public Piece {
public:
    std::vector<Move *> makeMove();
};


#endif //CHESS_SOLVER_KNIGHT_H
