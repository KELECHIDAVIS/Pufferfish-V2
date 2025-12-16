#include "perft.h"

U64 perft(Board *board, int depth)
{
    if (depth == 0)
        return 1ULL;

    Move move_list[MAX_MOVES];
    size_t numMoves = 0;
    U64 nodes = 0;

    // getting pseudo legal moves and unmaking it is faster than just getting legal moves
    getPseudoLegalMoves(board, move_list, &numMoves);

    for (size_t i = 0; i < numMoves; i++)
    {
        enumPiece currSide = board->whiteToMove ? nWhite: nBlack;         
        makeMove(board, move_list[i]);
        // if you're still in check after the move, the move was invalid 
        if(!isSideInCheck(board, currSide))
            nodes += perft(board, depth - 1); // only go deeper if the prev move was valid 
        unmakeMove(board, move_list[i]);
    }
    return nodes;
}

