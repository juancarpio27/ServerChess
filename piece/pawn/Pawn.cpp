//
// Created by pablo on 4/11/15.
//

#include "Pawn.h"

std::vector<Move *> *Pawn::makeMove(Piece **matrix) {
    std::vector<Move *> *moves = new std::vector<Move *>();

    int factor = (color == WHITE) ? 1 : -1;

    if (matrix[(y) * 8 + (x+factor)] == nullptr)
        pushToMoves(moves, x, y+factor);

    if (matrix[(y+1) * 8 + x + factor] != nullptr)
        pushToMoves(moves, x + factor, y + 1, true);
    if (matrix[(y-1) * 8 + x + factor] != nullptr)
        pushToMoves(moves, x + factor , y - 1, true);

    return moves;
}

Piece* Pawn::newPiece() {
    return new Pawn(x,y,color);
}