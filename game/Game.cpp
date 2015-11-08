//
// Created by pablo on 4/11/15.
//

#include <iostream>
#include "Game.h"
#include "../piece/bishop/Bishop.h"
#include "../piece/rook/Rook.h"
#include "../piece/king/King.h"
#include "../piece/pawn/Pawn.h"

Game::Game() {

}

int Game::execute() {
    std::cout << *board;
    board->execute();
}

bool Game::init() {
    board = new Board(WHITE, 1);
    board->pushPiece(new Rook(4, 7, WHITE));
    board->pushPiece(new Rook(4, 6, WHITE));
    board->pushPiece(new King(5, 5, WHITE));
    board->pushPiece(new King(7, 7, BLACK));
    /*CHECKMATE
     * board = new Board(WHITE, 1);
     *  board->pushPiece(new Bishop(1, 1, WHITE));
     * board->pushPiece(new King(1, 0, BLACK));
     *  board->pushPiece(new King(1, 3, WHITE));
     *  board->pushPiece(new Knight(3, 3, WHITE));*/
    /* CHECKMATE
     * board = new Board(WHITE, 1); 
     * board->pushPiece(new Rook(0, 1, WHITE));
     * board->pushPiece(new King(0, 0, BLACK)); 
     * board->pushPiece(new King(1, 1, WHITE));
     *  board->pushPiece(new Rook(1, 0, WHITE)); */
}

void Game::clean() {
    delete board;
}