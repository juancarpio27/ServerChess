//
// Created by pablo on 4/11/15.
//

#include "Queen.h"
#include <vector>

std::vector<Move *> Queen::makeMove() {
    std::vector<Move *> moves;

    int i = 0;

    for (i = -7; i < 7; ++i) {
        /* Movimiento Diagonal */
        pushToMoves(moves, x - i, y + i);
        pushToMoves(moves, x + i, y + i);

        /* Movimiento Horizontal y Vertical */
        pushToMoves(moves, i + x, y);
        pushToMoves(moves, x, y + i);

    }


    return moves;
}