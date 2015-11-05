//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_BOARD_H
#define CHESS_SOLVER_BOARD_H

#include <iostream>
#include "../piece/Piece.h"
#include "../piece/Move.h"

class Board {
private:
    std::vector<Piece *> whitePieces;
    std::vector<Piece *> blackPieces;
    Piece *matrix;
    Color turn;
    Move *moves;
    Piece *whiteKing;
    Piece *blackKing;

    void removeInvalidMoves(Piece *piece, std::vector<Move *> moves);

    void removeOverlappingPieces(Piece *piece, std::vector<Move *> moves);

    void removeCheckMoves(std::vector<Move *> moves);

    void removePieceEatingMoves(std::vector<Move *> moves);

    bool isInCheck();

    bool isInCheckmate();

    bool isInCheck(Piece *king);

    Piece *getWhiteKing();

    Piece *getBlackKing();

    Piece *getMatrix();

    bool isInCheckWithPieces(Piece *king, std::vector<Piece *> pieces);

public:
    Board() : turn(WHITE) { }

    Board(Piece *piece, std::vector<Move *> moves);

    void execute();

    void pushPiece(Piece *piece);

    void clean();

    friend std::ostream &operator<<(std::ostream &out, Board &board);
};


#endif //CHESS_SOLVER_BOARD_H
