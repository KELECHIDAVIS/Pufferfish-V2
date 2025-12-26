#ifndef BOARD_H
#define BOARD_H

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#define RANK_3 0x0000000000FF0000ULL
#define RANK_6 0x0000FF0000000000ULL
#define RANK_7 0x00FF000000000000ULL
#define RANK_4 0x00000000FF000000ULL
#define RANK_5 0x000000FF00000000ULL
// for searching specifically
#define MAX_SEARCH_DEPTH 256
typedef unsigned long long U64;

// returns the lsb and cleared lsb
#define LSBIT(X) ((X) & (-(X)))
#define CLEARLSBIT(X) ((X) & ((X) - 1))

typedef enum {
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
    NO_SQUARE = 64
} enumSquare;
typedef enum {
    nWhite = 0, // any white piece
    nBlack,     // any black piece
    nPawn,
    nKnight,
    nBishop,
    nRook,
    nQueen,
    nKing,
    EMPTY, // amount of enums
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

static inline U64 getAllPieces(const Board *board) {
    return board->pieces[nWhite] | board->pieces[nBlack];
}
static inline U64 getColorPieces(const Board *board, enumPiece color) {
    return board->pieces[color];
}
// returns bitboard of all pieces of given type regardless of color
static inline U64 getPieceTypePieces(const Board *board, enumPiece pieceType) {
    return board->pieces[pieceType];
}
// returns bitboard of all pieces of given type and color
static inline U64 getSpecificColorPieces(const Board *board, enumPiece color, enumPiece pieceType) {
    return board->pieces[color] & board->pieces[pieceType];
}
static inline bool isValidPiece(enumPiece piece) {
    return (piece >= nPawn && piece <= nKing);
}
static inline void removePiece(Board *board, enumPiece piece, enumPiece side,
                               unsigned int pos) {
    U64 posBit = 1ULL << pos;
    board->pieces[piece] &= ~posBit;
    board->pieces[side] &= ~posBit;
    board->mailbox[pos] = EMPTY; // empty
}
static inline void putPiece(Board *board, enumPiece piece, enumPiece side,
                            unsigned int dest) {
    U64 destBit = 1ULL << dest;
    board->pieces[piece] |= destBit;
    board->pieces[side] |= destBit;
    board->mailbox[dest] = piece;
}
extern void initBoard(Board *board, char *fen);
extern void initStandardChess(Board *board);
extern void addPiece(Board *board, enumPiece color, enumPiece pieceType, enumSquare square);
extern void printBB(U64 bb);
extern void printChessBoard(const Board *board);
extern void printBoardDetails(Board *board);
extern void translateSquareToAlgebraic(enumSquare square, char *buffer);

#endif // BOARD_H