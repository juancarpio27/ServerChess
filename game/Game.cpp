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
    printf("Initial state\n");
    std::cout << *(board);
    board->execute();
    printf("Execution finished\n");
}

bool Game::init() {

    //two rooks and king vs king
    /*board = new Board(BLACK, 5);
    board->pushPiece(new Rook(7, 3, WHITE));
    board->pushPiece(new Rook(5, 2, WHITE));
    board->pushPiece(new King(5, 5, WHITE));
    board->pushPiece(new King(7, 7, BLACK));*/

    //queen and king vs king
    /*board = new Board(BLACK, 5); 
    board->pushPiece(new King(0, 4, BLACK)); 
    board->pushPiece(new Queen(1, 7, WHITE));
     board->pushPiece(new King(3, 5, WHITE));*/

    //rook and king vs king
    /*board = new Board(BLACK, 5); 
    board->pushPiece(new King(0, 4, BLACK)); 
    board->pushPiece(new Rook(1, 7, WHITE));
     board->pushPiece(new King(3, 5, WHITE));*/

    //two bishops and king vs king
    /*board = new Board(WHITE, 5);
    board->pushPiece(new Bishop(6, 2, WHITE));
    board->pushPiece(new Bishop(6, 4, WHITE));
    board->pushPiece(new King(6, 5, WHITE));
    board->pushPiece(new King(3, 3, BLACK));*/

    //knight, bishop and king vs king
    /*board = new Board(BLACK, 5);
    board->pushPiece(new Knight(4, 4, WHITE));
    board->pushPiece(new Bishop(4, 3, WHITE));
    board->pushPiece(new King(7, 5, WHITE));
    board->pushPiece(new King(2, 4, BLACK));*/

    //two knights and king vs king
    /*board = new Board(WHITE, 5);
    board->pushPiece(new Knight(4, 4, WHITE));
    board->pushPiece(new Knight(4, 3, WHITE));
    board->pushPiece(new King(7, 5, WHITE));
    board->pushPiece(new King(2, 7, BLACK));*/

    //A king and a pawn vs a king
    /*board = new Board(WHITE, 5);
    board->pushPiece(new Pawn(6, 0, WHITE));
    board->pushPiece(new King(7, 5, WHITE));
    board->pushPiece(new King(6, 3, BLACK));*/

    return true;
}

void Game::clean() {
    delete board;
}