//
// Created by pablo on 4/11/15.
//

#include "Bishop.h"
#include <vector>
#include <ostream>
#include <iostream>

std::vector<Move *> Bishop::makeMove() {
    std::cout << "asd" << std::endl;
    std::vector<Move *> moves;

    for (int i = -7; i < 7; ++i) {
        /* Movimiento Diagonal */
        pushToMoves(moves, x - i, y + i);
        pushToMoves(moves, x + i, y + i);
    }

    return moves;
}