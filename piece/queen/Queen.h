//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_QUEEN_H
#define CHESS_SOLVER_QUEEN_H


#include "../Piece.h"
#include <vector>
class Queen : public Piece {

public:
    Queen(int _x, int _y, Color _color) :  Piece(_x, _y, _color) { }
    std::vector<Move *> makeMove();
};


#endif //CHESS_SOLVER_QUEEN_H
