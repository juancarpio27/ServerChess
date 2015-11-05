//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_MOVE_H
#define CHESS_SOLVER_MOVE_H


class Move {
private:
    int x;
    int y;
    bool needsPiece;
public:
    Move(int _x, int _y) : x(_x), y(_y), needsPiece(false) {}
    Move(int _x, int _y, bool _needsPiece) : x(_x), y(_y), needsPiece(_needsPiece) {}

    int getX();

    int getY();

    int getNeedsPiece();
};


#endif //CHESS_SOLVER_MOVE_H
