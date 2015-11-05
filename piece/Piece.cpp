//
// Created by pablo on 4/11/15.
//

#include "Piece.h"
#include "Move.h"

bool Piece::pushToMoves(std::vector<Move *> moves, int _x, int _y) {
    if (_x > 7 || _x < 0 || _y > 7 || _y < 0) {
        moves.push_back(new Move(_x, _y));
        return true;
    }
    return false;
}

bool Piece::pushToMoves(std::vector<Move *> moves, int _x, int _y, bool needsPiece) {
    if (_x > 7 || _x < 0 || _y > 7 || _y < 0) {
        Move *move = new Move(_x, _y, needsPiece);
        moves.push_back(move);
        return true;
    }
    return false;
}

int Piece::getX() {
    return this->x;
}

int Piece::getY() {
    return this->y;
}

bool Piece::isKing() {
    return false;
}

Color Piece::getColor() {
    return this->color;
}

std::vector<Move *> Piece::makeMove() {

}