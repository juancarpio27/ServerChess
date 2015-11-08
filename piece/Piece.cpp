//
// Created by pablo on 4/11/15.
//

#include <stdio.h>
#include "Piece.h"
#include "Move.h"

bool Piece::pushToMoves(std::vector<Move *> *moves, int _x, int _y) {
    if (_x < 8 && _x >= 0 && _y < 8 && _y >= 0) {
        moves->push_back(new Move(_x, _y));
        return true;
    }
    return false;
}

bool Piece::pushToMoves(std::vector<Move *> *moves, int _x, int _y, bool needsPiece) {
    if (_x < 8 && _x >= 0 && _y < 8 && _y >= 0) {
        moves->push_back(new Move(_x, _y, needsPiece));
        return true;
    }
    return false;
}

int Piece::getType() {
    return this->type;
}

void Piece::setType(int value) {
    type = value;
}

int Piece::getX() {
    return this->x;
}

void Piece::setX(int value) {
    x = value;
}

int Piece::getY() {
    return this->y;
}

void Piece::setY(int value) {
    y = value;
}

bool Piece::isKing() {
    return false;
}

Color Piece::getColor() {
    return this->color;
}

std::vector<Move *> *Piece::makeMove(Piece **matrix) {

}