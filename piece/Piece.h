//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_PIECE_H
#define CHESS_SOLVER_PIECE_H

#include <vector>
#include "Color.h"
#include "Move.h"

class Piece {
protected:
    int x;
    int y;
    Color color;
public:
    Piece() { }

    Piece(int _x, int _y, Color _color) : x(_x), y(_y), color(_color) { }

    Piece(int _x, int _y) : x(_x), y(_y) { }

    virtual bool pushToMoves(std::vector<Move *> moves, int _x, int _y);

    virtual bool pushToMoves(std::vector<Move *> moves, int _x, int _y, bool needsPiece);

    virtual std::vector<Move *> makeMove();

    virtual int getX();

    virtual int getY();

    virtual bool isKing();

    virtual Color getColor();

    inline bool operator==(const Piece& rhs){ return x == rhs.x && y == rhs.y; }
};


#endif //CHESS_SOLVER_PIECE_H
