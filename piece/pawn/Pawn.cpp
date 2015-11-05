//
// Created by pablo on 4/11/15.
//

#include "Pawn.h"

std::vector<Move *> Pawn::makeMove() {
	std::vector<Move *> moves;
	
	int factor = (color == WHITE) ? 1 : -1;
    pushToMoves(moves, x , y + factor);
    pushToMoves(moves, x + 1 , y + factor, true);
    pushToMoves(moves, x - 1 , y + factor, true);

    return moves;
}