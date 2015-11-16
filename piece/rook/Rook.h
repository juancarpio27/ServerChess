//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_ROOK_H
#define CHESS_SOLVER_ROOK_H

#define ROOK 3

#include "../Piece.h"
#include <vector>

class Rook : public Piece {
public:
    Rook(int _x, int _y, Color _color) : Piece(_x, _y, _color, ROOK) { weight = 5; }

    Piece* newPiece();

    std::vector<Move *> *makeMove(Piece **matrix);
};


#endif //CHESS_SOLVER_ROOK_H
