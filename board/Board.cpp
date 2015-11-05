//
// Created by pablo on 4/11/15.
//

#include <iostream>
#include "Board.h"
#include "../Helper.h"
#include "../piece/bishop/Bishop.h"

Board::Board(Piece *piece, std::vector<Move *> moves) {
    if (turn == WHITE) {
        turn = BLACK;
    } else {
        turn = WHITE;
    }

    removeInvalidMoves(piece, moves);
    removeOverlappingPieces(piece, moves);
    if (isInCheck()) {
        std::cout << "in check moder focker" << std::endl;
    } else {
        execute();
    }
    //isInCheckmate();
}

void Board::execute() {
    std::vector<Piece *> pieces;
    if (turn == WHITE) {
        pieces = whitePieces;
    } else {
        pieces = blackPieces;
    }

    for (std::vector<Piece *>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
        std::vector<Move *> moves = (*it)->makeMove();
    }
}

void Board::pushPiece(Piece *piece) {
    if (piece->getColor() == WHITE) {
        whitePieces.push_back(piece);
    } else {
        blackPieces.push_back(piece);
    }
}

void Board::clean() {

}

Piece *Board::getMatrix() {
    if (matrix == nullptr) {
        matrix = new Piece[64];
        //std::fill(matrix, matrix + sizeof(matrix), 0);
        for (std::vector<Piece *>::iterator it = whitePieces.begin(); it != whitePieces.end(); ++it) {
            Piece * piece = matrix + (*it)->getX() * 8 + (*it)->getY();
            *piece = **it;
        }

        for (std::vector<Piece *>::iterator it = blackPieces.begin(); it != blackPieces.end(); ++it) {
            Piece * piece = matrix + (*it)->getX() * 8 + (*it)->getY();
            *piece = **it;
        }
    }
    return matrix;
}

Piece *Board::getWhiteKing() {
    //TODO change to separate function
    if (whiteKing == nullptr) {
        for (std::vector<Piece *>::iterator it = whitePieces.begin(); it != whitePieces.end(); ++it) {
            Piece *piece = *it;
            if (piece->isKing() && piece->getColor() == WHITE) {
                whiteKing = piece;
                break;
            }
        }
    }

    return whiteKing;
}

Piece *Board::getBlackKing() {
    //TODO change to separate function
    if (blackKing == nullptr) {
        for (std::vector<Piece *>::iterator it = blackPieces.begin(); it != blackPieces.end(); ++it) {
            Piece *piece = *it;
            if (piece->isKing() && piece->getColor() == BLACK) {
                blackKing = piece;
                break;
            }
        }
    }

    return blackKing;
}

void Board::removeInvalidMoves(Piece *piece, std::vector<Move *> moves) {
    removeOverlappingPieces(piece, moves);
    removeCheckMoves(moves);
}

void Board::removeOverlappingPieces(Piece *piece, std::vector<Move *> moves) {
    Piece *matrix = getMatrix();
    for (std::vector<Move *>::iterator it = moves.begin(); it != moves.end(); ++it) {
        Move *move = *it;
        Piece *otherPiece = matrix + move->getY() * 8 + move->getX();
        if (otherPiece != nullptr) {
            if (piece->getColor() == otherPiece->getColor()) {
                moves.erase(it);
            }
        } else {
            if (otherPiece->getColor() == WHITE) {
                remove(blackPieces, otherPiece);
            } else {
                remove(whitePieces, otherPiece);
            }
        }
    }
}

bool Board::isInCheck() {
    isInCheck(getBlackKing());
    isInCheck(getWhiteKing());
}

bool Board::isInCheck(Piece *king) {
    Piece *matrix = getMatrix();

    isInCheckWithPieces(king, whitePieces);
    isInCheckWithPieces(king, blackPieces);

    return false;
}

bool Board::isInCheckWithPieces(Piece *king, std::vector<Piece *> pieces) {
    Piece *matrix = getMatrix();

    for (std::vector<Piece *>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
        std::vector<Move *> moves = (*it)->makeMove();
        for (std::vector<Move *>::iterator move = moves.begin(); move != moves.end(); ++move) {
            if (matrix + (*move)->getY() * 8 + (*move)->getX() == king) {
                return true;
            }
        }
    }

    return false;
}

bool Board::isInCheckmate() {

    return false;
}


void Board::removeCheckMoves(std::vector<Move *> moves) {

}

void  Board::removePieceEatingMoves(std::vector<Move *> moves) {

}

std::ostream &operator<<(std::ostream &out, Board &board) {
    Piece *matrix = board.getMatrix();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int num = matrix + j * 8 + i == NULL ? 1 : 0;
            out << num;
        }
        out << std::endl;
    }

    return out;
}