#ifndef MOVES_H
#define MOVES_H

#include "board.h"
#include "attack_patterns.h"

#define MAX_MOVES 256 // maximum number of legal moves possible in a position (max is 218 for chess)



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

// defined in board.h 
//typedef uint16_t Move; // 16 bit move representation

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
extern void getBishopMoves(const Board *board, Move *moveList, size_t *numMoves);
extern void getRookMoves(const Board *board, Move *moveList, size_t *numMoves);
extern void getQueenMoves(const Board *board, Move *moveList, size_t *numMoves);
extern void getKingMoves(const Board *board, Move *moveList, size_t *numMoves);
extern void translateFlagToAlgebraic(MoveFlag flag, char *buffer);

extern bool isSideInCheck(const Board* board , const enumPiece side );    
extern void makeMove(Board *board, Move move);
extern void unmakeMove(Board *board, Move move);

extern void printMove(Move move);
#endif // MOVES_H