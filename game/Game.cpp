//
// Created by pablo on 4/11/15.
//

#include <iostream>
#include "Game.h"
#include "../piece/bishop/Bishop.h"
#include "../piece/rook/Rook.h"
#include "../piece/king/King.h"
#include "../piece/pawn/Pawn.h"
#include "../piece/knight/Knight.h"
#include "../piece/queen/Queen.h"

Game::Game() {

}

int Game::execute() {
    std::cout << *board;
    board->execute();
}

bool Game::init() {
    board = new Board(BLACK, 40);
    board->pushPiece(new Rook(7, 6, WHITE));
    board->pushPiece(new Rook(5, 2, WHITE));
    board->pushPiece(new King(5, 5, WHITE));
    board->pushPiece(new King(7, 7, BLACK));
    //CHECKMATE
     /*board = new Board(WHITE, 1);
      board->pushPiece(new Bishop(1, 1, WHITE));
     board->pushPiece(new King(1, 0, BLACK));
      board->pushPiece(new King(1, 3, WHITE));
      board->pushPiece(new Knight(3, 3, WHITE));*/
     //CHECKMATE
     /*board = new Board(WHITE, 1); 
     board->pushPiece(new Rook(0, 1, WHITE));
     board->pushPiece(new King(0, 0, BLACK)); 
     board->pushPiece(new King(1, 1, WHITE));
      board->pushPiece(new Rook(1, 0, WHITE));*/
    /*board = new Board(WHITE, 1); 
    board->pushPiece(new King(0, 0, BLACK)); 
    board->pushPiece(new King(2, 1, WHITE));
     board->pushPiece(new Knight(2, 0, WHITE));
     board->pushPiece(new Bishop(6, 4, WHITE));*/
    /*board = new Board(WHITE, 1); 
    board->pushPiece(new King(0, 4, BLACK)); 
    board->pushPiece(new King(2, 4, WHITE));
     board->pushPiece(new Rook(0, 7, WHITE));*/
    /*board = new Board(WHITE, 1); 
    board->pushPiece(new King(0, 4, BLACK)); 
    board->pushPiece(new Queen(1, 4, WHITE));
     board->pushPiece(new King(2, 5, WHITE));*/

    return true;
}

void Game::clean() {
    delete board;
}