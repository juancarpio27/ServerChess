//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_KING_H
#define CHESS_SOLVER_KING_H

#define KING 1

#include "../Piece.h"

class King : public Piece {
public:
    King(int _x, int _y, Color _color) : Piece(_x, _y, _color, KING) { }

    std::vector<Move *> *makeMove(Piece **matrix);

    bool isKing();
};


#endif //CHESS_SOLVER_KING_H
