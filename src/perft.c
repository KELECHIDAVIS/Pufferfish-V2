#include "perft.h"
U64 perft(Board *board, int depth)
{
    Move move_list[MAX_MOVES];
    size_t numMoves = 0;
    U64 nodes = 0;

    if (depth == 0)
        return 1ULL;

    getPseudoLegalMoves(board, move_list, &numMoves);
    enumPiece currSide = board->whiteToMove ? nWhite : nBlack;

    for (size_t i = 0; i < numMoves; i++)
    {
        makeMove(board, move_list[i]);
        if (!isSideInCheck(board, currSide))
        {
            nodes += perft(board, depth - 1);
        }
        unmakeMove(board, move_list[i]);
    }
    return nodes;
}

U64 divide(Board *board, int depth)
{
    Move move_list[MAX_MOVES];
    size_t numMoves = 0;
    U64 totalNodes = 0;

    if (depth == 0)
        return 1ULL;

    getPseudoLegalMoves(board, move_list, &numMoves);
    enumPiece currSide = board->whiteToMove ? nWhite : nBlack;

    for (size_t i = 0; i < numMoves; i++)
    {
        makeMove(board, move_list[i]);
        if (!isSideInCheck(board, currSide))
        {
            // For each top-level move, see how many nodes it produces at the target depth
            U64 nodes = perft(board, depth - 1);

            printMove(move_list[i]); // Prints e2e4, etc.
            printf(": %llu\n", nodes);

            totalNodes += nodes;
        }
        unmakeMove(board, move_list[i]);
    }

    printf("\nNodes searched: %llu\n", totalNodes);
    return totalNodes;
}