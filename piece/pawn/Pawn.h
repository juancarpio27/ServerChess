//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_PAWN_H
#define CHESS_SOLVER_PAWN_H

#define PAWN 5 

#include "../Piece.h"

class Pawn : public Piece {
public:
    Pawn(int _x, int _y, Color _color) : Piece(_x, _y, _color, PAWN) { }

    Piece* newPiece();

    std::vector<Move *> *makeMove(Piece **matrix);
};


#endif //CHESS_SOLVER_PAWN_H
