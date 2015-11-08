cmake_minimum_required(VERSION 3.2)
project(chess_solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp game/Stats.cpp game/Stats.h)
add_executable(chess_solver ${SOURCE_FILES} board/Board.cpp board/Board.h piece/Piece.cpp piece/Piece.h game/Game.cpp game/Game.h piece/Color.h piece/bishop/Bishop.cpp piece/bishop/Bishop.h piece/king/King.cpp piece/king/King.h piece/knight/Knight.cpp piece/knight/Knight.h piece/pawn/Pawn.cpp piece/pawn/Pawn.h piece/queen/Queen.cpp piece/queen/Queen.h piece/rook/Rook.cpp piece/rook/Rook.h piece/Move.cpp piece/Move.h Helper.cpp Helper.h)