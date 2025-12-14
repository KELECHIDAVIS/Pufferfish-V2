#include "moves.h"
U64 PAWN_ATTACK_LOOKUP[2][64] = {{0x0000000000000200ULL,
                                  0x0000000000000500ULL,
                                  0x0000000000000a00ULL,
                                  0x0000000000001400ULL,
                                  0x0000000000002800ULL,
                                  0x0000000000005000ULL,
                                  0x000000000000a000ULL,
                                  0x0000000000004000ULL,
                                  0x0000000000020000ULL,
                                  0x0000000000050000ULL,
                                  0x00000000000a0000ULL,
                                  0x0000000000140000ULL,
                                  0x0000000000280000ULL,
                                  0x0000000000500000ULL,
                                  0x0000000000a00000ULL,
                                  0x0000000000400000ULL,
                                  0x0000000002000000ULL,
                                  0x0000000005000000ULL,
                                  0x000000000a000000ULL,
                                  0x0000000014000000ULL,
                                  0x0000000028000000ULL,
                                  0x0000000050000000ULL,
                                  0x00000000a0000000ULL,
                                  0x0000000040000000ULL,
                                  0x0000000200000000ULL,
                                  0x0000000500000000ULL,
                                  0x0000000a00000000ULL,
                                  0x0000001400000000ULL,
                                  0x0000002800000000ULL,
                                  0x0000005000000000ULL,
                                  0x000000a000000000ULL,
                                  0x0000004000000000ULL,
                                  0x0000020000000000ULL,
                                  0x0000050000000000ULL,
                                  0x00000a0000000000ULL,
                                  0x0000140000000000ULL,
                                  0x0000280000000000ULL,
                                  0x0000500000000000ULL,
                                  0x0000a00000000000ULL,
                                  0x0000400000000000ULL,
                                  0x0002000000000000ULL,
                                  0x0005000000000000ULL,
                                  0x000a000000000000ULL,
                                  0x0014000000000000ULL,
                                  0x0028000000000000ULL,
                                  0x0050000000000000ULL,
                                  0x00a0000000000000ULL,
                                  0x0040000000000000ULL,
                                  0x0200000000000000ULL,
                                  0x0500000000000000ULL,
                                  0x0a00000000000000ULL,
                                  0x1400000000000000ULL,
                                  0x2800000000000000ULL,
                                  0x5000000000000000ULL,
                                  0xa000000000000000ULL,
                                  0x4000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL},
                                 {0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000002ULL, 0x0000000000000005ULL, 0x000000000000000aULL, 0x0000000000000014ULL, 0x0000000000000028ULL, 0x0000000000000050ULL, 0x00000000000000a0ULL, 0x0000000000000040ULL, 0x0000000000000200ULL, 0x0000000000000500ULL, 0x0000000000000a00ULL, 0x0000000000001400ULL, 0x0000000000002800ULL, 0x0000000000005000ULL, 0x000000000000a000ULL, 0x0000000000004000ULL, 0x0000000000020000ULL, 0x0000000000050000ULL, 0x00000000000a0000ULL, 0x0000000000140000ULL, 0x0000000000280000ULL, 0x0000000000500000ULL, 0x0000000000a00000ULL, 0x0000000000400000ULL, 0x0000000002000000ULL, 0x0000000005000000ULL, 0x000000000a000000ULL, 0x0000000014000000ULL, 0x0000000028000000ULL, 0x0000000050000000ULL, 0x00000000a0000000ULL, 0x0000000040000000ULL, 0x0000000200000000ULL, 0x0000000500000000ULL, 0x0000000a00000000ULL, 0x0000001400000000ULL, 0x0000002800000000ULL, 0x0000005000000000ULL, 0x000000a000000000ULL, 0x0000004000000000ULL, 0x0000020000000000ULL, 0x0000050000000000ULL, 0x00000a0000000000ULL, 0x0000140000000000ULL, 0x0000280000000000ULL, 0x0000500000000000ULL, 0x0000a00000000000ULL, 0x0000400000000000ULL, 0x0002000000000000ULL, 0x0005000000000000ULL, 0x000a000000000000ULL, 0x0014000000000000ULL, 0x0028000000000000ULL, 0x0050000000000000ULL, 0x00a0000000000000ULL, 0x0040000000000000ULL}};
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

void precomputePawnAttacks()
{
    for (int i = nWhite; i <= nBlack; i++) // for both colors
    {
        for (int square = 0; square < 64; square++)
        {
            U64 attacks = 0ULL;
            U64 position = 1ULL << square;

            if (i == nWhite)
            {
                // white pawns attack diagonally up
                if ((position << 7) & ~FILE_H)
                    attacks |= (position << 7); // up-right
                if ((position << 9) & ~FILE_A)
                    attacks |= (position << 9); // up-left
            }
            else
            {
                // black pawns attack diagonally down
                if ((position >> 7) & ~FILE_A)
                    attacks |= (position >> 7); // down-left
                if ((position >> 9) & ~FILE_H)
                    attacks |= (position >> 9); // down-right
            }
            PAWN_ATTACK_LOOKUP[i][square] = attacks;
        }
    }
}

void printPawnAttacks()
{
    for (int i = nWhite; i <= nBlack; i++) // for both colors
    {
        for (int square = 0; square < 64; square++)
        {
            printf("Pawn attacks for %s from square %d:\n", i == nWhite ? "White" : "Black", square);
            printBB(PAWN_ATTACK_LOOKUP[i][square]);
        }
    }
}

static void extractMovesFromBB(Move *moveList, size_t *numMoves, U64 possibleMoves, const enumSquare fromSquare, const MoveFlag flag)
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
// Moves Piece and updates it's bb, side bb and mailbox. If a piece was captured then update their side's bb and piece bb
static inline void movePiece(Board *board, unsigned int from, unsigned int to)
{
    enumPiece side = nWhite;
    enumPiece oppSide = nBlack;
    if (!board->whiteToMove)
    {
        side = nBlack;
        oppSide = nWhite;
    }
    U64 fromBit = 1ULL << from;
    U64 toBit = 1ULL << to;

    // use mailbox to see which piece was at that spot
    enumPiece piece = board->mailbox[from];
    enumPiece capturedPiece = board->mailbox[to];
    // has to be valid piece
    assert(piece >= nPawn && piece <= nKing && "The piece could not be found in any bb");
    // move from piece bb
    board->pieces[piece] ^= fromBit; // guarenteed to be set so just xor it
    board->pieces[piece] |= toBit;   // might be set or not if it's a capture of the same pc

    // move from side bb
    board->pieces[side] ^= (fromBit | toBit); // both guarenteed to be set and unset
    // update moving piece in mailbox
    board->mailbox[from] = nWhite; // no piece
    board->mailbox[to] = piece;

    if (capturedPiece >= nPawn && capturedPiece <= nKing)
    {
        // update captured piece's sidebb , piece bb
        board->pieces[capturedPiece] ^= toBit;
        board->pieces[oppSide] ^= toBit;
    }
}

// save state and move made at that board state
static inline saveBoardState(Board *board, Move move, unsigned int to)
{
    assert(board->historySize >= 0 && board->historySize < MAX_SEARCH_DEPTH && "Tried to save state with invalid history stack size");

    board->historyStack[board->historySize].move = move;
    board->historyStack[board->historySize].castlingRights = board->castlingRights;
    board->historyStack[board->historySize].enPassantSquare = board->enPassantSquare;
    board->historyStack[board->historySize].halfmoveClock = board->halfmoveClock;
    board->historyStack[board->historySize].fullMoveNumber = board->fullmoveNumber;
    board->historyStack[board->historySize].capturedPiece = board->mailbox[getTo(move)];
    board->historyStack[board->historySize].whiteToMove = board->whiteToMove; 
    board->historySize++;
}
void makeMove(Board *board, Move move)
{
    
    unsigned int from = getFrom(move);
    unsigned int to = getTo(move);
    unsigned int flags = getFlags(move);
    
    // save the state for this move
    saveBoardState(board, move, to); 
    // if capture remove captured piece (from side bb and piece bb)
    // if en passant have to remove piece above or below destination (depend on side)
    // move source piece from fromsquare to tosquare (from side bb and piece bb )
    // if promo put promo piece at to (side bb and piece bb ) //else just put original piece at to (side bb and piece bb )
    // if castle move corrensponding rook and king (from side and piece bb's respectively)

    // reset en passant square
    board->enPassantSquare = 0; // not valid ep square
    // update half move clock
    // update full move counter

    // opponent's turn
    board->whiteToMove = !board->whiteToMove;
}
void unmakeMove(Board *board, Move move)
{
}
void printMove(Move move)
{
    char fromAlgebraic[3];
    char toAlgebraic[3];
    char flagAlgebraic[3];
    translateSquareToAlgebraic(getFrom(move), fromAlgebraic);
    translateSquareToAlgebraic(getTo(move), toAlgebraic);
    translateFlagToAlgebraic((MoveFlag)getFlags(move), flagAlgebraic);
    printf("%s to %s, Flag: %s", fromAlgebraic, toAlgebraic, flagAlgebraic);
}
void getPseudoLegalMoves(const Board *board, Move *moveList, size_t *numMoves)
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
    else
    {
        return (singlePushPattern >> 8) & emptySquares & RANK_5;
    }
}

inline U64 getPawnAttackPattern(const enumSquare fromSquare, const enumPiece side)
{
    return PAWN_ATTACK_LOOKUP[side][fromSquare];
}
void getPawnMoves(const Board *board, Move *moveList, size_t *numMoves)
{
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 pawns = getSpecificColorPieces(board, side, nPawn);

    while (pawns)
    {
        U64 pos = LSBIT(pawns);
        pawns = CLEARLSBIT(pawns);
        enumSquare fromSquare = __builtin_ctzll(pos);
        U64 emptySquares = ~getAllPieces(board);
        U64 removeLastRank = side == nWhite ? ~RANK_8 : ~RANK_1; // promotions handled separately

        U64 singlePushPattern = getSinglePushPattern(emptySquares, pos, side);
        extractMovesFromBB(moveList, numMoves, singlePushPattern & removeLastRank, fromSquare, QUIET_MOVE_FLAG);

        // only if single push is possible
        if (singlePushPattern)
        {
            U64 doublePushPattern = getDoublePushPattern(emptySquares, singlePushPattern, side);
            extractMovesFromBB(moveList, numMoves, doublePushPattern, fromSquare, DOUBLE_PAWN_PUSH_FLAG);
        }

        // get pawn attacks
        U64 attackPattern = getPawnAttackPattern(fromSquare, side);

        // and with opponent pieces to get captures, also remove last rank for promotions
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces & removeLastRank, fromSquare, CAPTURE_FLAG);

        // for promotions can just get every single push or capture that lands on last rank
        U64 promotionPushes = singlePushPattern & ~removeLastRank;
        for (int i = KNIGHT_PROMOTION_FLAG; i <= QUEEN_PROMOTION_FLAG; i++)
        {
            U64 copy = promotionPushes;
            extractMovesFromBB(moveList, numMoves, copy, fromSquare, (MoveFlag)i);
        }

        U64 promotionCaptures = attackPattern & opponentPieces & ~removeLastRank;
        for (int i = KNIGHT_PROMO_CAPTURE_FLAG; i <= QUEEN_PROMO_CAPTURE_FLAG; i++)
        {
            U64 copy = promotionCaptures;
            extractMovesFromBB(moveList, numMoves, copy, fromSquare, (MoveFlag)i);
        }

        // check enpassant if nonzero
        if (board->enPassantSquare)
        {
            U64 enPassantBit = 1ULL << board->enPassantSquare;
            // if they can get to the enpassant square by capturing it's valid
            U64 enPassantCaptures = attackPattern & enPassantBit;
            extractMovesFromBB(moveList, numMoves, enPassantCaptures, fromSquare, EN_PASSANT_CAPTURE_FLAG);
        }
    }
}
