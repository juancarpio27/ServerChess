//
// Created by pablo on 4/11/15.
//

#include <iostream>
#include "Board.h"
#include "../Helper.h"

/**
 * Function to create a board, with a new piece, the new move and a boolean to check if the previous state was check
 */
Board *Board::createBoard(Piece *piece, Move *move, bool incheck, int turns) {
    Color turnColor = turn == WHITE ? BLACK : WHITE;

    Board *board = new Board(turnColor, turns);

    //Add the white pieces to the new board
    for (std::vector<Piece *>::iterator it = whitePieces.begin(); it != whitePieces.end(); ++it) {

        if ((*it) == piece) {
            Piece *new_piece = (*it)->newPiece();
            new_piece->setX(move->getX());
            new_piece->setY(move->getY());
            board->pushPiece(new_piece);
        }
        else {

            if (turn == BLACK) {
                if (!(move->getX() == (*it)->getX() && move->getY() == (*it)->getY())) {
                    board->pushPiece((*it)->newPiece());
                }
            }
            else {
                board->pushPiece((*it)->newPiece());
            }

        }

    }

    //Add the white pieces to the new board
    for (std::vector<Piece *>::iterator it = blackPieces.begin(); it != blackPieces.end(); ++it) {

        //The new piece
        if ((*it) == piece) {
            Piece *new_piece = (*it)->newPiece();
            new_piece->setX(move->getX());
            new_piece->setY(move->getY());
            board->pushPiece(new_piece);
        }
        else {
            if (turn == WHITE) {
                if (!(move->getX() == (*it)->getX() && move->getY() == (*it)->getY())) {
                    board->pushPiece((*it)->newPiece());
                }
            }
            else {
                board->pushPiece((*it)->newPiece());
            }
        }
    }

    board->matrix = board->getMatrix();
    board->blackKing = board->getBlackKing();
    board->whiteKing = board->getWhiteKing();

    //If the board was in check, the new state cant be check
    if (incheck) {
        if (board->isInCheck())
            board = nullptr;
    }

    else {
        //A movement cant put the side in check
        if (turn == WHITE) {
            if (board->isInCheckWithPieces(board->getWhiteKing(), board->getBlackPieces())) {
                board = nullptr;
            }
        }
        else {
            if (board->isInCheckWithPieces(board->getBlackKing(), board->getWhitePieces())) {
                board = nullptr;
            }
        }
    }

    return board;
}

/**
 * Function to check if a final stage has been reached
 */
bool Board::finalReached() {
    if (!isInCheck() && isInCheckmate()) {
        printf("King can not move, the game is finished with a tie\n");
        winner = 2;
        return true;
    }
    if (isInCheckmate()) {

        if (isInCheckmateWithPieces(getWhiteKing(),blackPieces))
            winner = BLACK;
        else
            winner = WHITE;
        printf("Check mate, %d is the winner\n",winner);
        std::cout << *(this);
        return true;
    }
    if (turnsLeft == 0) {
        printf("Move limit reached, the game is finished with a tie\n");
        winner = 2;
        return true;
    }
    return false;
}

/**
 * A function to execute all the posible movements for a piece, and creating all the new posible boards
 */
void Board::execute() {


    matrix = getMatrix();

    if (finalReached()){
        return;
    }

    bool incheck = isInCheck();

    std::vector<Piece *> pieces;
    if (turn == WHITE) {
        pieces = whitePieces;
    } else {
        pieces = blackPieces;
    }

    for (std::vector<Piece *>::iterator pieceIt = pieces.begin(); pieceIt != pieces.end(); ++pieceIt) {
        std::vector<Move *> *moves = (*pieceIt)->makeMove(getMatrix());
        removeInvalidMoves(*pieceIt, moves);
        for (std::vector<Move *>::iterator moveIt = moves->begin(); moveIt != moves->end(); ++moveIt) {

            Board *board = createBoard(*pieceIt, *moveIt, incheck, turnsLeft-1);
            if (board != nullptr) {
                board->execute();
            }
        }
    }
}

/**
 * Add a piece to the pieces array
 */
void Board::pushPiece(Piece *piece) {
    if (piece->getColor() == WHITE) {
        whitePieces.push_back(piece);
    } else {
        blackPieces.push_back(piece);
    }
}

void Board::clean() {

}

/**
 * Get the board matrix representation
 */
Piece **Board::getMatrix() {

    matrix = new Piece *[64];
    for (std::vector<Piece *>::iterator it = whitePieces.begin(); it != whitePieces.end(); ++it) {
        matrix[(*it)->getY() * 8 + (*it)->getX()] = *it;
    }

    for (std::vector<Piece *>::iterator it = blackPieces.begin(); it != blackPieces.end(); ++it) {
        matrix[(*it)->getY() * 8 + (*it)->getX()] = *it;
    }

    return matrix;
}

/**
 * Put a matrix to null
 */
void Board::invalidateMatrix() {
    if (matrix != nullptr) {
        delete matrix;
        matrix = nullptr;
    }
}

/**
 * Get the white king pointer
 */
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

/*
 * Get the black king pointer
 */
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

/**
 * Remove all the invalid moves
 */
void Board::removeInvalidMoves(Piece *piece, std::vector<Move *> *moves) {
    removeOverlappingPieces(piece, moves);
}

/**
 * Remove all the overlaps in the board
 */
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

/*
 * Check if the board is in check state
 */
bool Board::isInCheck() {
    bool inCheck = false;
    inCheck = inCheck || isInCheckWithPieces(getBlackKing(), whitePieces);
    inCheck = inCheck || isInCheckWithPieces(getWhiteKing(), blackPieces);
    return inCheck;
}

/**
 * Check a check state for a king and all the opposite pieces
 */
bool Board::isInCheckWithPieces(Piece *king, std::vector<Piece *> pieces) {

    for (std::vector<Piece *>::iterator it = pieces.begin(); it != pieces.end(); ++it) {

        std::vector<Move *> *moves = (*it)->makeMove(matrix);
        removeInvalidMoves(*it, moves);
        for (std::vector<Move *>::iterator move = moves->begin(); move != moves->end(); ++move) {
            if (king->getX() == (*move)->getX() && king->getY() == (*move)->getY()) {
                return true;
            }
        }
        delete moves;
    }

    return false;
}


/*
 * Check if the board is in checkmate
 */
bool Board::isInCheckmate() {
    bool inCheck;
    inCheck = isInCheckmateWithPieces(getBlackKing(), whitePieces);
    inCheck = inCheck || isInCheckmateWithPieces(getWhiteKing(), blackPieces);
    return inCheck;
}

/*
 * Check if and specific king is in checkmate with the opposite pieces
 */
bool Board::isInCheckmateWithPieces(Piece *king, std::vector<Piece *> pieces) {
    std::vector<Move *> *moves = king->makeMove(matrix);
    removeInvalidMoves(king, moves);
    for (std::vector<Move *>::iterator move = moves->begin(); move != moves->end(); ++move) {
        int x = king->getX();
        int y = king->getY();
        king->setX((*move)->getX());
        king->setY((*move)->getY());
        *(matrix + y * 8 + x) = nullptr;
        bool changed = false;
        Piece *temporal_piece;

        if (*(matrix + king->getY() * 8 + king->getX()) != nullptr) {
            temporal_piece = *(matrix + king->getY() * 8 + king->getX());
            *(matrix + king->getY() * 8 + king->getX()) = nullptr;
            changed = true;
        }

        bool inCheck = isInCheckWithPieces(king, pieces);

        if (changed) {
            *(matrix + king->getY() * 8 + king->getX()) = temporal_piece;
        }

        king->setX(x);
        king->setY(y);
        *(matrix + y * 8 + x) = king;

        if (!inCheck) {
            return false;
        }
    }
    return true;
}

/**
 * Override of the print function for the board class
 */
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

std::vector<Piece *> Board::getBlackPieces() {
    return blackPieces;
}

std::vector<Piece *>  Board::getWhitePieces() {
    return whitePieces;
}