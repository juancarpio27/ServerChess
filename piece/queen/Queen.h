//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_QUEEN_H
#define CHESS_SOLVER_QUEEN_H

#define QUEEN 2

#include "../Piece.h"
#include <vector>

class Queen : public Piece {
public:
    Queen(int _x, int _y, Color _color) : Piece(_x, _y, _color, QUEEN) { }

    std::vector<Move *> *makeMove(Piece **matrix);
};


#endif //CHESS_SOLVER_QUEEN_H
