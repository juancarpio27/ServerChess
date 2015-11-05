//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_BISHOP_H
#define CHESS_SOLVER_BISHOP_H


#include <vector>
#include "../Piece.h"

class Bishop : public Piece {
public:
    Bishop(int _x, int _y, Color _color) :  Piece(_x, _y, _color) { }

    std::vector<Move *> makeMove();
};


#endif //CHESS_SOLVER_BISHOP_H
