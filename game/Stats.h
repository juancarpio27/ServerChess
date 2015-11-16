//
// Created by César Millán on 11/8/15.
//

#ifndef CHESS_SOLVER_STATS_H
#define CHESS_SOLVER_STATS_H


#include <vector>
#include "../piece/Piece.h"

class Stats {



    private:
        static bool instanceFlag;


        static Stats *single;
        Stats()
        {
            //private constructor
        }
    public:

    long int whiteWins = 0;
    long int blackWins = 0;
    long int draw = 0;

    static const int WHITE_WINS = 0;
        static Stats* getInstance();
        void gameFinished(std::vector<Piece *> * pieces);
        ~Stats()
        {
            instanceFlag = false;
        }

    void printStats();


};


#endif //CHESS_SOLVER_STATS_H
