//
// Created by pablo on 4/11/15.
//

#include "Pawn.h"

std::vector<Move *> *Pawn::makeMove(Piece **matrix) {
    std::vector<Move *> *moves = new std::vector<Move *>();

    int factor = (color == WHITE) ? 1 : -1;

    if (matrix[(y + factor) * 8 + x] == nullptr)
        pushToMoves(moves, x, y + factor);

    if (matrix[(y + factor) * 8 + x + 1] != nullptr)
        pushToMoves(moves, x + 1, y + factor, true);
    if (matrix[(y + factor) * 8 + x - 1] != nullptr)
        pushToMoves(moves, x - 1, y + factor, true);


    return moves;
}