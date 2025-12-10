#ifndef BOARD_H 
#define BOARD_H
#include <ctype.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <stdbool.h>
#include <assert.h> 
typedef unsigned long long U64;

typedef enum {
  a1, b1, c1, d1, e1, f1, g1, h1,
  a2, b2, c2, d2, e2, f2, g2, h2,
  a3, b3, c3, d3, e3, f3, g3, h3,
  a4, b4, c4, d4, e4, f4, g4, h4,
  a5, b5, c5, d5, e5, f5, g5, h5,
  a6, b6, c6, d6, e6, f6, g6, h6,
  a7, b7, c7, d7, e7, f7, g7, h7,
  a8, b8, c8, d8, e8, f8, g8, h8
} enumSquare;

typedef struct {
    // going w a dense representation the holds colors in first 2 then piece types in the following 6 
    U64 pieces[8]; // nWhite, nBlack, nPawn, nKnight, nBishop, nRook, nQueen, nKing
    bool whiteToMove;
    short castlingRights; // 4 bits KQkq
    enumSquare enPassantSquare; // square that can be captured via en passant
    int halfmoveClock; // for 50 move rule
    int fullmoveNumber; // starts at 1 and increments after

} Board;

typedef enum{
    nWhite, // any white piece
    nBlack, // any black piece
    nPawn,
    nKnight,
    nBishop,
    nRook,
    nQueen,
    nKing
} enumPiece;

extern U64 getAllPieces(const Board* board);
extern U64 getColorPieces(const Board* board, enumPiece color);
extern U64 getPieceTypePieces(const Board* board, enumPiece pieceType);
extern U64 getSpecificColorPieces(const Board* board, enumPiece color, enumPiece pieceType);
extern void initBoard(Board *board ,char* fen);
extern void addPiece(Board *board, enumPiece color, enumPiece pieceType, enumSquare square);
extern void printBB( U64 bb ); 

#endif // BOARD_H