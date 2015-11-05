//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_ROOK_H
#define CHESS_SOLVER_ROOK_H


#include "../Piece.h"
#include <vector>

class Rook : public Piece {
public:
    std::vector<Move *> makeMove();
};


#endif //CHESS_SOLVER_ROOK_H
