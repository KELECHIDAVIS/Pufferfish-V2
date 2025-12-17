#include "perft.h"
U64 perft(Board *board, int depth, U64 *captures, U64 *ep, U64 *castles, U64 *promotions, U64 *checks, U64 *checkmates)
{
    if (depth == 0)
        return 1ULL;

    Move move_list[MAX_MOVES];
    size_t numMoves = 0;
    U64 nodes = 0;

    getPseudoLegalMoves(board, move_list, &numMoves);
    enumPiece currSide = board->whiteToMove ? nWhite : nBlack;
    enumPiece oppSide = board->whiteToMove ? nBlack : nWhite;

    for (size_t i = 0; i < numMoves; i++)
    {
        makeMove(board, move_list[i]);

        if (!isSideInCheck(board, currSide))
        {
            // Count checks delivered by THIS move
            if (depth == 1 && isSideInCheck(board, oppSide))
                (*checks)++;

            unsigned int flags = getFlags(move_list[i]);

            // Only count flags at depth 1 (when the move is actually played)
            if (depth == 1)
            {
                switch (flags)
                {
                case KING_CASTLE_FLAG:
                case QUEEN_CASTLE_FLAG:
                    (*castles)++;
                    break;
                case CAPTURE_FLAG:
                    (*captures)++;
                    break;
                case EN_PASSANT_CAPTURE_FLAG:
                    (*captures)++;
                    (*ep)++;
                    break;
                case KNIGHT_PROMOTION_FLAG:
                case BISHOP_PROMOTION_FLAG:
                case ROOK_PROMOTION_FLAG:
                case QUEEN_PROMOTION_FLAG:
                    (*promotions)++;
                    break;
                case KNIGHT_PROMO_CAPTURE_FLAG:
                case BISHOP_PROMO_CAPTURE_FLAG:
                case ROOK_PROMO_CAPTURE_FLAG:
                case QUEEN_PROMO_CAPTURE_FLAG:
                    (*promotions)++;
                    (*captures)++;
                    break;
                default:
                    break;
                }
            }

            nodes += perft(board, depth - 1, captures, ep, castles, promotions, checks, checkmates);
        }
        unmakeMove(board, move_list[i]);
    }

    if (nodes == 0 && isSideInCheck(board, currSide))
        (*checkmates)++;

    return nodes;
}

U64 divide(Board *board, int depth, U64 *captures, U64 *ep, U64 *castles, U64 *promotions, U64 *checks, U64 *checkmates)
{
    if (depth == 0)
        return 1ULL;

    Move move_list[MAX_MOVES];
    size_t numMoves = 0;
    U64 nodes = 0;

    getPseudoLegalMoves(board, move_list, &numMoves);

    enumPiece currSide = board->whiteToMove ? nWhite : nBlack;
    enumPiece oppSide = board->whiteToMove ? nBlack : nWhite;

    for (size_t i = 0; i < numMoves; i++)
    {
        U64 localNodes = 0;
        makeMove(board, move_list[i]);

        if (!isSideInCheck(board, currSide))
        {
            // Count checks delivered by THIS move (only at depth 1)
            if (depth == 1 && isSideInCheck(board, oppSide))
                (*checks)++;

            unsigned int flags = getFlags(move_list[i]);

            // Only count flags at depth 1
            if (depth == 1)
            {
                switch (flags)
                {
                case KING_CASTLE_FLAG:
                case QUEEN_CASTLE_FLAG:
                    (*castles)++;
                    break;
                case CAPTURE_FLAG:
                    (*captures)++;
                    break;
                case EN_PASSANT_CAPTURE_FLAG:
                    (*captures)++;
                    (*ep)++;
                    break;
                case KNIGHT_PROMOTION_FLAG:
                case BISHOP_PROMOTION_FLAG:
                case ROOK_PROMOTION_FLAG:
                case QUEEN_PROMOTION_FLAG:
                    (*promotions)++;
                    break;
                case KNIGHT_PROMO_CAPTURE_FLAG:
                case BISHOP_PROMO_CAPTURE_FLAG:
                case ROOK_PROMO_CAPTURE_FLAG:
                case QUEEN_PROMO_CAPTURE_FLAG:
                    (*promotions)++;
                    (*captures)++;
                    break;
                default:
                    break;
                }
            }

            localNodes = perft(board, depth - 1, captures, ep, castles, promotions, checks, checkmates);
        }
        unmakeMove(board, move_list[i]);

        printMove(move_list[i]);
        printf(" : %llu\n", localNodes);
        nodes += localNodes;
    }

    // Check for checkmate
    if (nodes == 0 && isSideInCheck(board, currSide))
        (*checkmates)++;

    return nodes;
}
