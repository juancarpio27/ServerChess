//
// Created by pablo on 4/11/15.
//

#include <vector>
#include "Rook.h"

std::vector<Move *> Rook::makeMove() {
    std::vector<Move *> moves;
    int i = 0;

    /* Movimiento Horizontal y Vertical */
    for (i = -7; i < 7; ++i) {
        pushToMoves(moves, i + x, y);
        pushToMoves(moves, x, y + i);
    }

    return moves;
}