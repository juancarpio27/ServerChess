//
// Created by pablo on 4/11/15.
//

#include "Knight.h"

std::vector<Move *> *Knight::makeMove(Piece **matrix) {
    std::vector<Move *> *moves = new std::vector<Move *>();

    pushToMoves(moves, x + 1, y + 2);
    pushToMoves(moves, x + 2, y + 1);
    pushToMoves(moves, x + 2, y - 1);
    pushToMoves(moves, x + 1, y - 2);

    pushToMoves(moves, x - 1, y - 2);
    pushToMoves(moves, x - 2, y - 1);
    pushToMoves(moves, x - 2, y + 1);
    pushToMoves(moves, x - 1, y + 2);

    return moves;
}

Piece* Knight::newPiece() {
    return new Knight(x,y,color);
}