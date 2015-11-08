//
// Created by pablo on 4/11/15.
//

#include <vector>
#include <stdio.h>
#include "Rook.h"

std::vector<Move *> *Rook::makeMove(Piece **matrix) {
    std::vector<Move *> *moves = new std::vector<Move *>();

    for (int i = 1; i < 8; ++i) {
        pushToMoves(moves, i + x, y);
        if (matrix[y * 8 + (i + x)] != nullptr) {
            break;
        }
    }

    /** Horizontal left **/
    for (int i = -1; i > -8; --i) {
        pushToMoves(moves, i + x, y);
        if (matrix[y * 8 + (i + x)] != nullptr) {
            break;
        }
    }

    /** Vertical down **/
    for (int i = 1; i < 8; ++i) {
        pushToMoves(moves, x, y + i);
        if (matrix[(y + i) * 8 + x] != nullptr) {
            break;
        }
    }

    /** Vertical up **/
    for (int i = -1; i > -8; --i) {
        pushToMoves(moves, x, y + i);
        if (matrix[(y + i) * 8 + x] != nullptr) {
            break;
        }
    }

    return moves;
}