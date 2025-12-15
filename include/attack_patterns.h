#ifndef ATTACKS_H
#define ATTACKS_H

#include "board.h"

// Lookup tables
extern U64 KNIGHT_ATTACK_LOOKUP[64];
extern U64 PAWN_ATTACK_LOOKUP[2][64];
extern U64 KING_ATTACK_LOOKUP[64]; 

//Magic bb stuff for sliding pieces 
extern U64 ROOK_ATTACK_LOOKUP[64][4096]; // 2048K 
extern U64 BISHOP_ATTACK_LOOKUP[64][512]; // 256 K

typedef struct {
    U64 mask; // relevant blocking squares at pos 
    U64 magic ; // num to mult by to get hash 
    int shiftAmt; // amt to shift after multiplication (64-bitAmtAtSq)
}SMagic;

// where magic numbers and relevant masks for each square are stored 
extern SMagic BishopMagicTable[64];
extern SMagic RookMagicTable[64];

// Initialization functions
extern void precomputeAllAttacks(void); // Call this once at startup
extern void precomputeKnightAttacks(void);
extern void precomputePawnAttacks(void);
extern void precomputeKingAttacks(void);
extern void precomputeRookMasks(void);
extern void precomputeBishopMasks(void);
extern U64 findMagicNum(bool isBishop, enumSquare square); // continuoslly loop until we find a valid magic number  
// get index within hashtable 
static inline int magicIndex(SMagic* entry , U64 blockers){
    return (int)((blockers* entry->magic) >> (entry->shiftAmt));
}
static inline U64 randU64()
{
    U64 u1, u2, u3, u4;
    u1 = (U64)(rand()) & 0xFFFF;
    u2 = (U64)(rand()) & 0xFFFF;
    u3 = (U64)(rand()) & 0xFFFF;
    u4 = (U64)(rand()) & 0xFFFF;
    return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}
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

// Magic bb lookup tables
static inline U64 getRookAttackPattern(enumSquare square, U64 occupancy){
    int index = magicIndex(&RookMagicTable[square], occupancy);

    return ROOK_ATTACK_LOOKUP[square][index];
}
static inline U64 getBishopAttackPattern(enumSquare square, U64 occupancy){
    int index = magicIndex(&BishopMagicTable[square], occupancy);

    return BISHOP_ATTACK_LOOKUP[square][index];
}
static inline U64 getQueenAttackPattern(enumSquare square, U64 occupancy)
{
    return getBishopAttackPattern(square, occupancy) | getRookAttackPattern(square, occupancy);
}

// Debug/utility functions
extern void printKnightAttacks(void);
extern void printPawnAttacks(void);
extern void precomputeMagicNumbersAndSaveToFile(void); // for Smagic tables  
extern void precomputeSlidingPieceLookupTablesAndSaveToFile(void);// save all possible attack patterns to files  
extern void precomputeSlidingPieceLookupTables(void);  // just compute attack patterns on startup so we don't have to copy and paste file text (way too big )
#endif // ATTACKS_H