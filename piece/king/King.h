//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_KING_H
#define CHESS_SOLVER_KING_H


#include "../Piece.h"

class King : public Piece {
public:
    King(int _x, int _y, Color _color) : Piece(_x, _y, _color) { }

    std::vector<Move *> makeMove();

    bool isKing();
};


#endif //CHESS_SOLVER_KING_H
