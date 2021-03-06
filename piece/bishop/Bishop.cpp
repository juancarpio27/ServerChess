//
// Created by pablo on 4/11/15.
//

#include "Bishop.h"
#include <vector>
#include <ostream>
#include <iostream>

std::vector<Move *> *Bishop::makeMove(Piece **matrix) {
    std::vector<Move *> *moves = new std::vector<Move *>();

    for (int i = 1; i < 7; ++i) {

        if (pushToMoves(moves, x - i, y - i) && matrix[(y - i) * 8 + (x - i)] != nullptr)
            break;
    }

    for (int i = 1; i < 7; ++i) {

        if (pushToMoves(moves, x + i, y + i) && matrix[(y + i) * 8 + (x + i)] != nullptr)
            break;
    }

    for (int i = 1; i < 7; ++i) {

        if (pushToMoves(moves, x - i, y + i) && matrix[(y + i) * 8 + (x - i)] != nullptr)
            break;
    }

    for (int i = 1; i < 7; ++i) {

        if (pushToMoves(moves, x + i, y - i) && matrix[(y - i) * 8 + (x + i)] != nullptr)
            break;
    }
    return moves;
}

Piece* Bishop::newPiece() {
    return new Bishop(x,y,color);
}