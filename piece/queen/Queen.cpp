//
// Created by pablo on 4/11/15.
//

#include "Queen.h"
#include <vector>

std::vector<Move *> *Queen::makeMove(Piece **matrix) {
    std::vector<Move *> *moves = new std::vector<Move *>();

    /** Horizontal right **/
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

    for (int i = 1; i < 7; ++i) {
        pushToMoves(moves, x - i, y - i);
        if (matrix[(y - i) * 8 + (x - i)] != nullptr)
            break;
    }

    for (int i = 1; i < 7; ++i) {
        pushToMoves(moves, x + i, y + i);
        if (matrix[(y + i) * 8 + (x + i)] != nullptr)
            break;
    }

    for (int i = 1; i < 7; ++i) {
        pushToMoves(moves, x - i, y + i);
        if (matrix[(y + i) * 8 + (x - i)] != nullptr)
            break;
    }

    for (int i = 1; i < 7; ++i) {
        pushToMoves(moves, x + i, y - i);
        if (matrix[(y - i) * 8 + (x + i)] != nullptr)
            break;
    }

    return moves;
}