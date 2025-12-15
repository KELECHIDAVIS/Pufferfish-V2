#ifndef ATTACKS_H
#define ATTACKS_H

#include "board.h"

// Lookup tables
extern U64 KNIGHT_ATTACK_LOOKUP[64];
extern U64 PAWN_ATTACK_LOOKUP[2][64];
extern U64 KING_ATTACK_LOOKUP[64]; 

// Future: Magic bitboards for sliding pieces
// extern U64 ROOK_ATTACK_TABLE[64][4096];
// extern U64 BISHOP_ATTACK_TABLE[64][512];

// Initialization functions
extern void precomputeAllAttacks(void); // Call this once at startup
extern void precomputeKnightAttacks(void);
extern void precomputePawnAttacks(void);
extern void precomputeKingAttacks(void);

// Attack pattern getters (inline for performance)
static inline U64 getKnightAttackPattern(enumSquare square)
{
    return KNIGHT_ATTACK_LOOKUP[square];
}

static inline U64 getPawnAttackPattern(enumSquare square, enumPiece side)
{
    return PAWN_ATTACK_LOOKUP[side][square];
}

static inline U64 getKingAttackAttackPattern(enumSquare square)
{
    return KING_ATTACK_LOOKUP[square];
}
static inline U64 getSinglePushPattern(const U64 emptySquares, const U64 pawnPosition, const enumPiece side)
{
    if (side == nWhite)
    {
        return (pawnPosition << 8) & emptySquares;
    }
    else
    {
        return (pawnPosition >> 8) & emptySquares;
    }
}

static inline U64 getDoublePushPattern(const U64 emptySquares, const U64 singlePushPattern, const enumPiece side)
{
    // shift single push again to get double
    if (side == nWhite)
    {
        return (singlePushPattern << 8) & emptySquares & RANK_4;
    }
    else
    {
        return (singlePushPattern >> 8) & emptySquares & RANK_5;
    }
}

// Future sliding piece attacks
// extern U64 getRookAttacks(enumSquare square, U64 occupancy);
// extern U64 getBishopAttacks(enumSquare square, U64 occupancy);
// extern U64 getQueenAttacks(enumSquare square, U64 occupancy);

// Debug/utility functions
extern void printKnightAttacks(void);
extern void printPawnAttacks(void);

#endif // ATTACKS_H