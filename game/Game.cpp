//
// Created by pablo on 4/11/15.
//

#include <iostream>
#include "Game.h"
#include "Stats.h"
#include "../piece/bishop/Bishop.h"
#include "../piece/rook/Rook.h"
#include "../piece/king/King.h"
#include "../piece/pawn/Pawn.h"
#include "../piece/knight/Knight.h"
#include "../piece/queen/Queen.h"

Game::Game(Board *_board) {
    board = _board;
}

int Game::execute() {
    printf("Initial state\n");

    board->execute();

    board->getBestPath();

    Stats *s = s->getInstance();
    printf("Draws %ld\n",s->draw);
    printf("Whites %ld\n",s->whiteWins);
    printf("Blacks %ld\n",s->blackWins);

    printf("Execution finished\n");
}

bool Game::init() {

    return true;
}

void Game::clean() {

    delete board;
}