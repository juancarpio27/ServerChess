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
    int type;
    int x;
    int y;
    Color color;
    int weight;

public:
    Piece() { }

    Piece(int _x, int _y, Color _color, int _type) : x(_x), y(_y), color(_color), type(_type) { }

    Piece(int _x, int _y) : x(_x), y(_y) { }

    Piece(Piece *old_piece, Move* move);

    Piece(Piece *old_piece);

    virtual bool pushToMoves(std::vector<Move *> *moves, int _x, int _y);

    virtual bool pushToMoves(std::vector<Move *> *moves, int _x, int _y, bool needsPiece);

    virtual std::vector<Move *> *makeMove(Piece **matrix);

    virtual Piece *newPiece();

    int getType();

    void setType(int value);

    int getX();

    void setX(int value);

    int getY();

    void setY(int value);

    int getWeight();

    void setWeight(int value);

    virtual bool isKing();

    virtual Color getColor();

    inline bool operator==(const Piece &rhs) { return x == rhs.x && y == rhs.y; }
};


#endif //CHESS_SOLVER_PIECE_H
