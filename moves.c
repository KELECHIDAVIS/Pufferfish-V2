#include "moves.h"

U64 KNIGHT_ATTACK_LOOKUP[] = {
    0x0000000000020400ULL,
    0x0000000000050800ULL,
    0x00000000000a1100ULL,
    0x0000000000142200ULL,
    0x0000000000284400ULL,
    0x0000000000508800ULL,
    0x0000000000a01000ULL,
    0x0000000000402000ULL,
    0x0000000002040004ULL,
    0x0000000005080008ULL,
    0x000000000a110011ULL,
    0x0000000014220022ULL,
    0x0000000028440044ULL,
    0x0000000050880088ULL,
    0x00000000a0100010ULL,
    0x0000000040200020ULL,
    0x0000000204000402ULL,
    0x0000000508000805ULL,
    0x0000000a1100110aULL,
    0x0000001422002214ULL,
    0x0000002844004428ULL,
    0x0000005088008850ULL,
    0x000000a0100010a0ULL,
    0x0000004020002040ULL,
    0x0000020400040200ULL,
    0x0000050800080500ULL,
    0x00000a1100110a00ULL,
    0x0000142200221400ULL,
    0x0000284400442800ULL,
    0x0000508800885000ULL,
    0x0000a0100010a000ULL,
    0x0000402000204000ULL,
    0x0002040004020000ULL,
    0x0005080008050000ULL,
    0x000a1100110a0000ULL,
    0x0014220022140000ULL,
    0x0028440044280000ULL,
    0x0050880088500000ULL,
    0x00a0100010a00000ULL,
    0x0040200020400000ULL,
    0x0204000402000000ULL,
    0x0508000805000000ULL,
    0x0a1100110a000000ULL,
    0x1422002214000000ULL,
    0x2844004428000000ULL,
    0x5088008850000000ULL,
    0xa0100010a0000000ULL,
    0x4020002040000000ULL,
    0x0400040200000000ULL,
    0x0800080500000000ULL,
    0x1100110a00000000ULL,
    0x2200221400000000ULL,
    0x4400442800000000ULL,
    0x8800885000000000ULL,
    0x100010a000000000ULL,
    0x2000204000000000ULL,
    0x0004020000000000ULL,
    0x0008050000000000ULL,
    0x00110a0000000000ULL,
    0x0022140000000000ULL,
    0x0044280000000000ULL,
    0x0088500000000000ULL,
    0x0010a00000000000ULL,
    0x0020400000000000ULL};

U64 noNoEa(U64 b) { return (b << 17) & ~FILE_A; }
U64 noEaEa(U64 b) { return (b << 10) & ~(FILE_A | FILE_B); }
U64 soEaEa(U64 b) { return (b >> 6) & ~(FILE_A | FILE_B); }
U64 soSoEa(U64 b) { return (b >> 15) & ~FILE_A; }
U64 noNoWe(U64 b) { return (b << 15) & ~FILE_H; }
U64 noWeWe(U64 b) { return (b << 6) & ~(FILE_G | FILE_H); }
U64 soWeWe(U64 b) { return (b >> 10) & ~(FILE_G | FILE_H); }
U64 soSoWe(U64 b) { return (b >> 17) & ~FILE_H; }

void precomputeKnightAttacks()
{
    for (int square = 0; square < 64; square++)
    {
        // add all possible knight moves from this square
        U64 attacks = 0ULL;
        U64 position = 1ULL << square;
        attacks |= noNoEa(position); // up-right
        attacks |= noEaEa(position); // up-left
        attacks |= soEaEa(position); // down-left
        attacks |= soSoEa(position); // down-right
        attacks |= noNoWe(position); // up-left
        attacks |= noWeWe(position); // up-right
        attacks |= soWeWe(position); // down-right
        attacks |= soSoWe(position); // down-left

        KNIGHT_ATTACK_LOOKUP[square] = attacks;
    }
}

void printKnightAttacks()
{
    for (int square = 0; square < 64; square++)
    {
        printf("Knight attacks from square %d:\n", square);
        printBB(KNIGHT_ATTACK_LOOKUP[square]);
    }
}

inline U64 getKnightAttackPattern(enumSquare square)
{
    return KNIGHT_ATTACK_LOOKUP[square];
}

static void extractMovesFromBB(Move* moveList, size_t *numMoves, U64 possibleMoves, const enumSquare fromSquare, const MoveFlag flag)
{
    while (possibleMoves)
    {
        U64 toBit = LSBIT(possibleMoves);
        possibleMoves = CLEARLSBIT(possibleMoves);
        enumSquare toSquare = __builtin_ctzll(toBit);

        Move move = encodeMove(fromSquare, toSquare, flag);
        moveList[(*numMoves)++] = move;
    }
}
void getKnightMoves(const Board *board, Move *moveList, size_t *numMoves)
{
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 knights = getSpecificColorPieces(board, side, nKnight);

    while (knights)
    {
        U64 pos = LSBIT(knights);
        knights = CLEARLSBIT(knights);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 attackPattern = getKnightAttackPattern(fromSquare);

        // and with empty to get quiet moves 
        U64 empty = ~getAllPieces(board);
        extractMovesFromBB(moveList, numMoves, attackPattern & empty, fromSquare, QUIET_MOVE_FLAG);


        // and with opponent pieces to get captures
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces, fromSquare, CAPTURE_FLAG);

    }
}
void translateFlagToAlgebraic(const MoveFlag flag, char *buffer)
{
    switch (flag)
    {
    case QUIET_MOVE_FLAG:
        buffer[0] = 'Q';
        break;
    case DOUBLE_PAWN_PUSH_FLAG:
        buffer[0] = 'D';
        break;
    case KING_CASTLE_FLAG:
        buffer[0] = 'K';
        break;
    case QUEEN_CASTLE_FLAG:
        buffer[0] = 'Q';
        break;
    case CAPTURE_FLAG:
        buffer[0] = 'C';
        break;
    case EN_PASSANT_CAPTURE_FLAG:
        buffer[0] = 'E';
        break;
    case KNIGHT_PROMOTION_FLAG:
        buffer[0] = 'N';
        break;
    case BISHOP_PROMOTION_FLAG:
        buffer[0] = 'B';
        break;
    case ROOK_PROMOTION_FLAG:
        buffer[0] = 'R';
        break;
    case QUEEN_PROMOTION_FLAG:
        buffer[0] = 'Q';
        break;
    case KNIGHT_PROMO_CAPTURE_FLAG:
        buffer[0] = 'N';
        break;
    case BISHOP_PROMO_CAPTURE_FLAG:
        buffer[0] = 'B';
        break;
    case ROOK_PROMO_CAPTURE_FLAG:
        buffer[0] = 'R';
        break;
    case QUEEN_PROMO_CAPTURE_FLAG:
        buffer[0] = 'Q';
        break;
    default:
        buffer[0] = '?';
        break;
    }
    buffer[1] = '\0';
}
void getLegalMoves(const Board *board, Move *moveList, size_t *numMoves)
{

    getPawnMoves(board, moveList, numMoves);
    getKnightMoves(board, moveList, numMoves);
    // getBishopMoves(board, moveList, numMoves);
    // getRookMoves(board, moveList, numMoves);
    // getQueenMoves(board, moveList, numMoves);
    // getKingMoves(board, moveList, numMoves);
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
    else{
        return (singlePushPattern >> 8) & emptySquares & RANK_5;
    }
}
void getPawnMoves(const Board *board, Move *moveList, size_t *numMoves)
{
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 pawns = getSpecificColorPieces(board, side, nPawn);

    while(pawns)
    {
        U64 pos = LSBIT(pawns);
        pawns = CLEARLSBIT(pawns);
        enumSquare fromSquare = __builtin_ctzll(pos);
        U64 emptySquares = ~getAllPieces(board);

        U64 singlePushPattern  = getSinglePushPattern(emptySquares, pos, side);
        extractMovesFromBB(moveList, numMoves, singlePushPattern, fromSquare, QUIET_MOVE_FLAG);

        // only if single push is possible
        if(singlePushPattern){
            U64 doublePushPattern = getDoublePushPattern(emptySquares, singlePushPattern, side);
            extractMovesFromBB(moveList, numMoves, doublePushPattern, fromSquare, DOUBLE_PAWN_PUSH_FLAG);
        }

        
    }

}
