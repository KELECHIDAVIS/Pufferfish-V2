#ifndef BOARD_H
#define BOARD_H

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
// castling rights
#define W_K_CASTLE 0b1000
#define W_Q_CASTLE 0b0100
#define B_K_CASTLE 0b0010
#define B_Q_CASTLE 0b0001

// where a file/rank is filled with ones
#define FILE_A 0x0101010101010101ULL
#define FILE_H 0x8080808080808080ULL
#define FILE_B 0x0202020202020202ULL
#define FILE_G 0x4040404040404040ULL
#define RANK_1 0x00000000000000FFULL
#define RANK_8 0xFF00000000000000ULL
#define RANK_2 0x000000000000FF00ULL
#define RANK_7 0x00FF000000000000ULL
#define RANK_4 0x00000000FF000000ULL
#define RANK_5 0x000000FF00000000ULL
// for searching specifically
#define MAX_SEARCH_DEPTH 256
typedef unsigned long long U64;

typedef enum
{
  a1,
  b1,
  c1,
  d1,
  e1,
  f1,
  g1,
  h1,
  a2,
  b2,
  c2,
  d2,
  e2,
  f2,
  g2,
  h2,
  a3,
  b3,
  c3,
  d3,
  e3,
  f3,
  g3,
  h3,
  a4,
  b4,
  c4,
  d4,
  e4,
  f4,
  g4,
  h4,
  a5,
  b5,
  c5,
  d5,
  e5,
  f5,
  g5,
  h5,
  a6,
  b6,
  c6,
  d6,
  e6,
  f6,
  g6,
  h6,
  a7,
  b7,
  c7,
  d7,
  e7,
  f7,
  g7,
  h7,
  a8,
  b8,
  c8,
  d8,
  e8,
  f8,
  g8,
  h8,
  NO_SQUARE
} enumSquare;
typedef enum
{
  nWhite = 0, // any white piece
  nBlack,     // any black piece
  nPawn,
  nKnight,
  nBishop,
  nRook,
  nQueen,
  nKing,
  nSize, // amount of enums
} enumPiece;

// forward declaring Move,  which is defined in move.h
typedef uint16_t Move;

typedef struct
{
  Move move;
  unsigned char castlingRights;
  enumSquare enPassantSquare;
  unsigned short halfmoveClock;
  unsigned short fullMoveNumber;
  enumPiece capturedPiece;
} MoveHistory;

typedef struct
{
  // going w a dense representation the holds colors in first 2 then piece types in the following 6
  U64 pieces[8];         // nWhite, nBlack, nPawn, nKnight, nBishop, nRook, nQueen, nKing
  enumPiece mailbox[64]; // holds the piecetype at each square for quicker lookup
  bool whiteToMove;
  unsigned char castlingRights;  // 4 bits KQkq
  enumSquare enPassantSquare;    // square that can be captured via en passant
  unsigned short halfmoveClock;  // for 50 move rule
  unsigned short fullmoveNumber; // starts at 1 and increments after
  MoveHistory historyArr[MAX_SEARCH_DEPTH];
  int historyPly;
} Board;

extern U64 getAllPieces(const Board *board);
extern U64 getColorPieces(const Board *board, enumPiece color);
extern U64 getPieceTypePieces(const Board *board, enumPiece pieceType);
extern U64 getSpecificColorPieces(const Board *board, enumPiece color, enumPiece pieceType);
extern void initBoard(Board *board, char *fen);
extern void addPiece(Board *board, enumPiece color, enumPiece pieceType, enumSquare square);
extern void printBB(U64 bb);
extern void printChessBoard(Board *board);
extern void printBoardDetails(Board *board);
extern void translateSquareToAlgebraic(enumSquare square, char *buffer);
// static inline bool isOppInCheck(const Board *board);
// static bool isSideToMoveInCheck(const Board *board);
#endif // BOARD_H