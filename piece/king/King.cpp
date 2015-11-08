//
// Created by pablo on 4/11/15.
//

#include <vector>
#include "King.h"

std::vector<Move *> *King::makeMove(Piece **matrix) {
    std::vector<Move *> *moves = new std::vector<Move *>();

    pushToMoves(moves, x + 1, y);
    pushToMoves(moves, x + 1, y + 1);
    pushToMoves(moves, x + 1, y - 1);
    pushToMoves(moves, x - 1, y);
    pushToMoves(moves, x - 1, y + 1);
    pushToMoves(moves, x - 1, y - 1);
    pushToMoves(moves, x, y);
    pushToMoves(moves, x, y + 1);
    pushToMoves(moves, x, y - 1);

    return moves;
}

bool King::isKing() {
    return true;
}