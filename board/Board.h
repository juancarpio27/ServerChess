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
    Piece **matrix;
    Color turn;
    Piece *whiteKing;
    Piece *blackKing;
    int turnsLeft;
    int winner;

    void removeInvalidMoves(Piece *piece, std::vector<Move *> *moves);

    void removeOverlappingPieces(Piece *piece, std::vector<Move *> *moves);

    bool isInCheckmate();

    bool isInCheckmateWithPieces(Piece *king, std::vector<Piece *> pieces);

    Piece *getWhiteKing();

    Piece *getBlackKing();

    Piece **getMatrix();

    std::vector<Piece *> getBlackPieces();

    std::vector<Piece *> getWhitePieces();

    void invalidateMatrix();

    bool isInCheckWithPieces(Piece *king, std::vector<Piece *> pieces);

    Board *createBoard(Piece *piece, Move *move, bool incheck, int turns);

    bool finalReached();

public:
    Board(Color _turn, int _turnsLeft) : turn(_turn), turnsLeft(_turnsLeft) { }

    Board(Piece *piece, std::vector<Move *> *moves);

    ~Board();

    void execute();

    bool isInCheck();

    void pushPiece(Piece *piece);

    void clean();

    friend std::ostream &operator<<(std::ostream &out, Board &board);
};


#endif //CHESS_SOLVER_BOARD_H
