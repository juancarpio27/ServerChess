//
// Created by pablo on 4/11/15.
//

#include <iostream>
#include "Game.h"
#include "../piece/bishop/Bishop.h"
#include "../piece/king/King.h"

Game::Game() {

}

int Game::execute() {
    std::cout << *board;
    //board->execute();
}

bool Game::init() {
    board = new Board();
    Bishop *bi = new Bishop(7, 5, WHITE);
    board->pushPiece(dynamic_cast<Piece*>(bi));
    board->pushPiece(new King(4, 4, WHITE));
    board->pushPiece(new King(7, 6, BLACK));
}

void Game::clean() {
    delete board;
}