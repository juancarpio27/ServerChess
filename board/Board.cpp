//
// Created by pablo on 4/11/15.
//

#include <iostream>
#include "Board.h"
#include "../Helper.h"

/*Board::Board(Piece *piece, std::vector<Move *> moves) {
    //isInCheckmate();
}*/

Board *Board::createBoard(Piece *piece, Move *move) {
    Color turnColor = turn == WHITE ? BLACK : WHITE;

    Board *board = new Board(turnColor, turnsLeft - 1);

    for (std::vector<Piece *>::iterator it = whitePieces.begin(); it != whitePieces.end(); ++it) {
        Piece *newPiece = new Piece();
        *newPiece = **it;
        board->pushPiece(newPiece);
    }

    for (std::vector<Piece *>::iterator it = blackPieces.begin(); it != blackPieces.end(); ++it) {
        Piece *newPiece = new Piece();
        *newPiece = **it;
        if (*it == piece) {
            newPiece->setX(move->getX());
            newPiece->setY(move->getY());
        }
        board->pushPiece(newPiece);
    }

    return board;
}

void Board::execute() {
    if (isInCheck()) {
        printf("The board is in check\n");
    }
    else {
        printf("The board is not in check\n");
    }

    if (isInCheckmate()) {
        printf("The board is in checkmate\n");
        std::cout << *(this);
    }
    else {
        printf("The board is not in checkmate\n");
        std::cout << *(this);
    }
    std::vector<Piece *> pieces;
    if (turn == WHITE) {
        pieces = whitePieces;
    } else {
        pieces = blackPieces;
    }

    for (std::vector<Piece *>::iterator pieceIt = pieces.begin(); pieceIt != pieces.end(); ++pieceIt) {
        std::vector<Move *> *moves = (*pieceIt)->makeMove(getMatrix());
        //removeInvalidMoves(*pieceIt, moves);
        for (std::vector<Move *>::iterator moveIt = moves->begin(); moveIt != moves->end(); ++moveIt) {
            Board *board = createBoard(*pieceIt, *moveIt);
            //board->execute();
        }
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

Piece **Board::getMatrix() {
    if (matrix == nullptr) {
        matrix = new Piece *[64];
        for (std::vector<Piece *>::iterator it = whitePieces.begin(); it != whitePieces.end(); ++it) {
            matrix[(*it)->getY() * 8 + (*it)->getX()] = *it;
        }

        for (std::vector<Piece *>::iterator it = blackPieces.begin(); it != blackPieces.end(); ++it) {
            matrix[(*it)->getY() * 8 + (*it)->getX()] = *it;
        }
    }
    return matrix;
}


void Board::invalidateMatrix() {
    if (matrix != nullptr) {
        delete matrix;
        matrix = nullptr;
    }
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

void Board::removeInvalidMoves(Piece *piece, std::vector<Move *> *moves) {
    removeOverlappingPieces(piece, moves);
    removeCheckMoves(moves);
}

void Board::removeOverlappingPieces(Piece *piece, std::vector<Move *> *moves) {
    Piece **matrix = getMatrix();
    for (std::vector<Move *>::iterator it = moves->begin(); it != moves->end(); ++it) {
        Move *move = *it;
        Piece *otherPiece = matrix[move->getY() * 8 + move->getX()];
        if (otherPiece != nullptr) {
            if (piece->getColor() == otherPiece->getColor()) {
                moves->erase(it);
                --it;
            } else {
                if (otherPiece->getColor() == WHITE) {
                    remove(blackPieces, otherPiece);
                } else {
                    remove(whitePieces, otherPiece);
                }
            }
        }
    }
}

bool Board::isInCheck() {
    bool inCheck = false;
    inCheck = inCheck || isInCheckWithPieces(getBlackKing(), whitePieces);
    inCheck = inCheck || isInCheckWithPieces(getWhiteKing(), blackPieces);
    return inCheck;
}

bool Board::isInCheckWithPieces(Piece *king, std::vector<Piece *> pieces) {
    Piece **matrix = getMatrix();
    for (std::vector<Piece *>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
        std::vector<Move *> *moves = (*it)->makeMove(getMatrix());
        removeInvalidMoves(*it, moves);
        for (std::vector<Move *>::iterator move = moves->begin(); move != moves->end(); ++move) {
            printf("Move %d/%d\n",(*move)->getX(),(*move)->getY());
            if (king->getX() == (*move)->getX() && king->getY() == (*move)->getY()) {
                return true;
            }
        }
        delete moves;
    }

    return false;
}

bool Board::isInCheckmate() {
    bool inCheck = true;
    inCheck = isInCheckmateWithPieces(getBlackKing(), whitePieces);
    //inCheck = inCheck || isInCheckmateWithPieces(getWhiteKing(), blackPieces);
    return inCheck && isInCheck();
}

bool Board::isInCheckmateWithPieces(Piece *king, std::vector<Piece *> pieces) {
    std::vector<Move *> *moves = king->makeMove(getMatrix());
    removeInvalidMoves(king, moves);
    for (std::vector<Move *>::iterator move = moves->begin(); move != moves->end(); ++move) {
        //invalidateMatrix();
        int x = king->getX();
        int y = king->getY();
        king->setX((*move)->getX());
        king->setY((*move)->getY());
        *(matrix + y * 8 + x) = nullptr;
        printf("Checking the king in %d/%d\n",king->getX(),king->getY());
        bool inCheck = isInCheckWithPieces(king, pieces);
        king->setX(x);
        king->setY(y);
        *(matrix + y * 8 + x) = king;

        if (!inCheck) {
            return false;
        }
    }
    return true;
}

void Board::removeCheckMoves(std::vector<Move *> *moves) {

}

void  Board::removePieceEatingMoves(std::vector<Move *> *moves) {

}

std::ostream &operator<<(std::ostream &out, Board &board) {
    Piece **matrix = board.getMatrix();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int num = *(matrix + j * 8 + i) == nullptr ? 1 : 0;
            out << num;
        }
        out << std::endl;
    }

    return out;
}