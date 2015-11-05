//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_QUEEN_H
#define CHESS_SOLVER_QUEEN_H


#include "../Piece.h"
#include <vector>
class Queen : public Piece {
public:
    std::vector<Move *> makeMove();
};


#endif //CHESS_SOLVER_QUEEN_H
