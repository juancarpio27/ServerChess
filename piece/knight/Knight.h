//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_KNIGHT_H
#define CHESS_SOLVER_KNIGHT_H

#define KNIGHT 0

#include "../Piece.h"

class Knight : public Piece {
public:
    Knight(int _x, int _y, Color _color) : Piece(_x, _y, _color, KNIGHT) { }

    std::vector<Move *> *makeMove(Piece **matrix);

    Piece* newPiece();
};


#endif //CHESS_SOLVER_KNIGHT_H
