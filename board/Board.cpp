//
// Created by pablo on 4/11/15.
//

#include <iostream>
#include "Board.h"

/**
 * Function to create a board, with a new piece, the new move and a boolean to check if the previous state was check
 */
Board *Board::createBoard(Piece *piece, Move *move, bool incheck, int turns) {
    Color turnColor = turn == WHITE ? BLACK : WHITE;
    Board *board = new Board(turnColor, turns);

    //Add the white pieces to the new board
    for (std::vector<Piece *>::iterator it = whitePieces.begin(); it != whitePieces.end(); ++it) {

        //The new piece
        if ((*it) == piece) {
            if (piece->getType() == 5 && move->getX() == 7) {
                board->pushPiece(new Queen(7, move->getY(), WHITE));
            }
            else {
                Piece *new_piece = (*it)->newPiece();
                new_piece->setX(move->getX());
                new_piece->setY(move->getY());
                board->pushPiece(new_piece);
            }
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
            if (piece->getType() == 5 && move->getX() == 0) {
                board->pushPiece(new Queen(0, move->getY(), BLACK));
            }
            else {
                Piece *new_piece = (*it)->newPiece();
                new_piece->setX(move->getX());
                new_piece->setY(move->getY());
                board->pushPiece(new_piece);
            }
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
    board->father = this;



    //If the board was in check, the new state cant be check
    if (incheck) {
        if (board->isInCheck()) {
            board = nullptr;
        }
    }

    else {
        //A movement cant put the mover side in check
        if (turn == WHITE) {
            board->whiteKing = nullptr;
            board->whiteKing = board->getWhiteKing();
            if (board->isInCheckWithPieces(board->whiteKing, board->getBlackPieces())) {
                board = nullptr;
            }
        }
        else {
            board->blackKing = nullptr;
            board->blackKing = board->getBlackKing();
            if (board->isInCheckWithPieces(board->blackKing, board->getWhitePieces())) {
                board = nullptr;
            }
        }
    }

    return board;
}

int Board::calculateHeuristic(Color color) {

    /*std::vector<Piece *> pieces, otherPieces;

    if (color == WHITE) {
        pieces = whitePieces;
        otherPieces = blackPieces;
    }

    else {
        pieces = blackPieces;
        otherPieces = whitePieces;
    }*/

    std::vector<Piece *> pieces, otherPieces;
    pieces = blackPieces;
    otherPieces = whitePieces;


    int total = 0;

    for (std::vector<Piece *>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
        total += (*it)->getWeight();
    }

    for (std::vector<Piece *>::iterator it = otherPieces.begin(); it != otherPieces.end(); ++it) {
        total -= (*it)->getWeight();
    }

    //TODO pawns and king safety and movements

    return total;
}

/**
 * Function to check if a final stage has been reached
 */
bool Board::finalReached() {
    if (!isInCheck() && isInCheckmate()) {
        Stats *s = s->getInstance();
#pragma omp atomic
        s->draw++;
        winner = 2;
        decision = calculateHeuristic(turn);
        bestBoard = nullptr;

        json_t *json_board = board_to_json();
#pragma omp critical
        {
            json_t *array_json = json_object_get(s->boards_json,"boards");
            json_array_append(array_json,json_board);
        }

        return true;
    }


    whiteKing = nullptr;
    whiteKing = getWhiteKing();
    if (isInCheckmateWithPieces(whiteKing, blackPieces)) {
        winner = BLACK;
        decision = calculateHeuristic(BLACK) * 2;
        Stats *s = s->getInstance();
#pragma omp atomic
        s->blackWins++;
        bestBoard = nullptr;

        json_t *json_board = board_to_json();
#pragma omp critical
        {
            json_t *array_json = json_object_get(s->boards_json,"boards");
            json_array_append(array_json,json_board);
        }
        return true;
    }

    blackKing = nullptr;
    blackKing = getBlackKing();
    if (isInCheckmateWithPieces(blackKing, whitePieces)) {
        winner = WHITE;
        decision = calculateHeuristic(WHITE) * 2;
        Stats *s = s->getInstance();
#pragma omp atomic
        s->whiteWins++;
        bestBoard = nullptr;

        json_t *json_board = board_to_json();
#pragma omp critical
        {
            json_t *array_json = json_object_get(s->boards_json,"boards");
            json_array_append(array_json,json_board);
        }

        return true;
    }

    if (turnsLeft == 0) {
        winner = 2;
        decision = calculateHeuristic(turn);
        Stats *s = s->getInstance();
#pragma omp atomic
        s->draw++;
        bestBoard = nullptr;

        json_t *json_board = board_to_json();
#pragma omp critical
        {
            json_t *array_json = json_object_get(s->boards_json,"boards");
            json_array_append(array_json,json_board);
        }
        return true;
    }
    return false;
}

/**
 * A function to execute all the posible movements for a piece, and creating all the new posible boards
 */
void Board::execute() {

    if (finalReached()) {
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
        std::vector<Move *> *moves = (*pieceIt)->makeMove(matrix);
        removeInvalidMoves(*pieceIt, moves);
        for (std::vector<Move *>::iterator moveIt = moves->begin(); moveIt != moves->end(); ++moveIt) {
            Board *board = createBoard(*pieceIt, *moveIt, incheck, turnsLeft - 1);
            if (board != nullptr) {
#pragma omp task
                {
                    board->execute();
                    board->updateFather();
                }

            }

        }

        delete moves;
    }
#pragma omp taskwait
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

void Board::updateFather() {
    if (father->turn == WHITE) {
        if (decision < father->decision) {
            father->decision = decision;
            father->bestBoard = this;
        }
    }
    else {
        if (decision > father->decision) {
            father->decision = decision;
            father->bestBoard = this;
        }
    }
}

void Board::clean() {

}

void Board::getBestPath() {
    printf("Best path has decision %d\n", decision);
}

/**
 * Get the board matrix representation
 */
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

/**
 * Put a matrix to null
 */
void Board::invalidateMatrix() {
    if (matrix != nullptr) {
        delete matrix;
    }
    matrix = nullptr;
}

/**
 * Get the white king pointer
 */
Piece *Board::getWhiteKing() {
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

    for (std::vector<Move *>::iterator it = moves->begin(); it != moves->end(); ++it) {
        Move *move = *it;


        //matrix = nullptr;
        invalidateMatrix();
        matrix = getMatrix();

        std::vector<Piece *> pieces;
        if (piece->getColor() == WHITE) {
            pieces = whitePieces;
        } else {
            pieces = blackPieces;
        }

        for (std::vector<Piece *>::iterator piecesIt = pieces.begin(); piecesIt != pieces.end(); ++piecesIt) {
            if (!((*piecesIt) == piece)) {
                if ((*piecesIt)->getX() == move->getX() && (*piecesIt)->getY() == move->getY()) {
                    moves->erase(it);
                    --it;
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
    blackKing = nullptr;
    blackKing = getBlackKing();
    if (blackKing == nullptr)
        return true;
    inCheck = inCheck || isInCheckWithPieces(blackKing, whitePieces);
    whiteKing = nullptr;
    whiteKing = getWhiteKing();
    if (whiteKing == nullptr)
        return true;
    inCheck = inCheck || isInCheckWithPieces(whiteKing, blackPieces);
    return inCheck;
}

/**
 * Check a check state for a king and all the opposite pieces
 */
bool Board::isInCheckWithPieces(Piece *king, std::vector<Piece *> pieces) {

    for (std::vector<Piece *>::iterator it = pieces.begin(); it != pieces.end(); ++it) {

        matrix = nullptr;
        matrix = getMatrix();
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

    blackKing = nullptr;
    blackKing = getBlackKing();
    inCheck = isInCheckmateWithPieces(blackKing, whitePieces);

    whiteKing = nullptr;
    whiteKing = getWhiteKing();
    inCheck = inCheck || isInCheckmateWithPieces(whiteKing, blackPieces);
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

        if (!inCheck) {
            delete moves;
            matrix = nullptr;
            matrix = getMatrix();
            return false;
        }
    }
    delete moves;
    matrix = nullptr;
    matrix = getMatrix();
    return true;
}

/**
 * Override of the print function for the board class
 */
std::ostream &operator<<(std::ostream &out, Board &board) {
    board.matrix = nullptr;
    board.matrix = board.getMatrix();
    Piece **matrix = board.matrix;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int num = *(matrix + j * 8 + i) == nullptr ? 1 : 0;
            if (num == 1) {
                out << "00 ";
            }
            else {
                Piece *piece = *(matrix + j * 8 + i);
                switch (piece->getType()) {
                    case 0:
                        out << "KN ";
                        break;
                    case 1:
                        out << "KI ";
                        break;
                    case 3:
                        out << "RO ";
                        break;
                    case 2:
                        out << "QU ";
                        break;
                    case 4:
                        out << "BI ";
                        break;
                    case 5:
                        out << "PW ";
                        break;
                    default:
                        out << "11 ";
                        break;
                }
            }

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

Board::~Board() {
    if (matrix != nullptr)
        delete matrix;

    for (std::vector<Piece *>::iterator it = whitePieces.begin(); it != whitePieces.end(); ++it) {
        delete (*it);
    }
    for (std::vector<Piece *>::iterator it = blackPieces.begin(); it != blackPieces.end(); ++it) {
        delete (*it);
    }
}

Board *Board::getBestBoard() {
    return bestBoard;
}

//PASS A BOARD TO A JSON OBJECT
json_t *Board::board_to_json() {

    json_t *board_json = json_object();
    json_t *color;

    if (turn == WHITE)
        color = json_string("white");
    else
        color = json_string("black");

    json_object_set(board_json, "turn", color);

    json_t *array_json = json_array();

    json_t *piece;

    for (std::vector<Piece *>::iterator it = whitePieces.begin(); it != whitePieces.end(); ++it) {

        piece = json_object();

        json_t *x = json_integer((*it)->getX());
        json_object_set(piece, "x", x);

        json_t *y = json_integer((*it)->getY());
        json_object_set(piece, "y", x);

        json_t *piece_color = json_string("white");
        json_object_set(piece, "color", piece_color);

        json_t *piece_type;

        switch ((*it)->getType()) {
            case 0:
                piece_type = json_string("knight");
                json_object_set(piece, "kind", piece_type);
                break;
            case 1:
                piece_type = json_string("king");
                json_object_set(piece, "kind", piece_type);
                break;
            case 3:
                piece_type = json_string("rook");
                json_object_set(piece, "kind", piece_type);
                break;
            case 2:
                piece_type = json_string("queen");
                json_object_set(piece, "kind", piece_type);
                break;
            case 4:
                piece_type = json_string("bishop");
                json_object_set(piece, "kind", piece_type);
                break;
            case 5:
                piece_type = json_string("pawn");
                json_object_set(piece, "kind", piece_type);
                break;
            default:
                break;
        }

        json_array_append(array_json, piece);
    }

    for (std::vector<Piece *>::iterator it = blackPieces.begin(); it != blackPieces.end(); ++it) {

        piece = json_object();

        json_t *x = json_integer((*it)->getX());
        json_object_set(piece, "x", x);

        json_t *y = json_integer((*it)->getY());
        json_object_set(piece, "y", x);

        json_t *piece_color = json_string("black");
        json_object_set(piece, "color", piece_color);

        json_t *piece_type;

        switch ((*it)->getType()) {
            case 0:
                piece_type = json_string("knight");
                json_object_set(piece, "kind", piece_type);
                break;
            case 1:
                piece_type = json_string("king");
                json_object_set(piece, "kind", piece_type);
                break;
            case 3:
                piece_type = json_string("rook");
                json_object_set(piece, "kind", piece_type);
                break;
            case 2:
                piece_type = json_string("queen");
                json_object_set(piece, "kind", piece_type);
                break;
            case 4:
                piece_type = json_string("bishop");
                json_object_set(piece, "kind", piece_type);
                break;
            case 5:
                piece_type = json_string("pawn");
                json_object_set(piece, "kind", piece_type);
                break;
            default:
                break;
        }

        json_array_append(array_json, piece);
    }

    json_object_set(board_json, "pieces", array_json);

    return board_json;
}
