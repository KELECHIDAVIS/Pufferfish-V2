#ifndef MOVES_H
#define MOVES_H

#include "board.h"
#include <stdint.h>

#define MAX_MOVES 256 // maximum number of legal moves possible in a position (max is 218 for chess)
#define LSBIT(X) ((X) & (-(X)))
#define CLEARLSBIT(X) ((X) & ((X) - 1))

extern U64 KNIGHT_ATTACK_LOOKUP[64];  // precomputed knight attacks for each square
extern U64 PAWN_ATTACK_LOOKUP[2][64]; // precomputed pawn attacks for each color and square
extern void precomputeKnightAttacks();
extern void printKnightAttacks();
extern U64 getKnightAttackPattern(enumSquare square); // returns knight pattern from square

extern void precomputePawnAttacks();
extern void printPawnAttacks();
extern U64 getPawnAttackPattern(const enumSquare fromSquare, const enumPiece side); // returns pawn attack pattern from square and side
// Moves are encoded into 16 bit integers as follows:
// bits 0-5: destination square (0-63)
// bits 6-11: source square (0-63)
// bits 12-15: move flags : the kind of move in table : https://www.chessprogramming.org/Encoding_Moves
typedef enum
{
    QUIET_MOVE_FLAG = 0,
    DOUBLE_PAWN_PUSH_FLAG = 1,
    KING_CASTLE_FLAG = 2,
    QUEEN_CASTLE_FLAG = 3,
    CAPTURE_FLAG = 4,
    EN_PASSANT_CAPTURE_FLAG = 5,
    KNIGHT_PROMOTION_FLAG = 8,
    BISHOP_PROMOTION_FLAG = 9,
    ROOK_PROMOTION_FLAG = 10,
    QUEEN_PROMOTION_FLAG = 11,
    KNIGHT_PROMO_CAPTURE_FLAG = 12,
    BISHOP_PROMO_CAPTURE_FLAG = 13,
    ROOK_PROMO_CAPTURE_FLAG = 14,
    QUEEN_PROMO_CAPTURE_FLAG = 15
} MoveFlag;

typedef uint16_t Move; // 16 bit move representation

static inline Move encodeMove(enumSquare from, enumSquare to, MoveFlag flag)
{
    return ((flag & 0xF) << 12) | ((from & 0x3F) << 6) | (to & 0x3F);
}

static inline unsigned int getTo(Move move) { return move & 0x3f; }
static inline unsigned int getFrom(Move move) { return (move >> 6) & 0x3f; }
static inline unsigned int getFlags(Move move) { return (move >> 12) & 0x0f; }

static inline void setTo(Move *move, unsigned int to)
{
    *move &= (Move)(~0x3fU);
    *move |= to & 0x3fU;
}

static inline void setFrom(Move *move, unsigned int from)
{
    *move &= (Move)(~0xFC0U);
    *move |= (from & 0x3fU) << 6;
}
static inline bool isCapture(Move move) { return (move & CAPTURE_FLAG) != 0; }

// Pass in a move list array and it'll be filled with legal moves
extern void getPseudoLegalMoves(const Board *board, Move *moveList, size_t *numMoves);
extern void getPawnMoves(const Board *board, Move *moveList, size_t *numMoves);
extern void getKnightMoves(const Board *board, Move *moveList, size_t *numMoves);
extern void getBishopMoves(Board *board, Move *moveList, size_t *numMoves);
extern void getRookMoves(Board *board, Move *moveList, size_t *numMoves);
extern void getQueenMoves(Board *board, Move *moveList, size_t *numMoves);
extern void getKingMoves(Board *board, Move *moveList, size_t *numMoves);
extern void translateFlagToAlgebraic(MoveFlag flag, char *buffer);

extern void makeMove(Board *board, Move move);
extern void unmakeMove(Board *board, Move move);
//extern void printMove(Move move);
#endif // MOVES_H