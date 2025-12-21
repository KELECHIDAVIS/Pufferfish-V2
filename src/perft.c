#include "perft.h"

#ifdef DEBUG
    void validateBoardIntegrity(const Board *board)
    {
        // Check mailbox matches all piece bitboards
        for (int sq = 0; sq < 64; sq++)
        {
            U64 sqBit = 1ULL << sq;
            enumPiece mailboxPiece = board->mailbox[sq];

            if (mailboxPiece >= nPawn && mailboxPiece <= nKing)
            {
                if (!(board->pieces[mailboxPiece] & sqBit))
                {
                    printf("ERROR: Mailbox has %d at %d but piece bitboard doesn't!\n",
                        mailboxPiece, sq);
                    printChessBoard(board);
                    abort();
                }
            }
        }

        // Verify each piece bitboard square exists in mailbox
        for (enumPiece p = nPawn; p <= nKing; p++)
        {
            U64 pieces = board->pieces[p];
            while (pieces)
            {
                U64 sqBit = LSBIT(pieces);
                pieces = CLEARLSBIT(pieces);
                int sq = __builtin_ctzll(sqBit);

                if (board->mailbox[sq] != p)
                {
                    printf("ERROR: Piece bitboard %d has bit at %d but mailbox has %d!\n",
                        p, sq, board->mailbox[sq]);
                    printChessBoard(board);
                    abort();
                }
            }
        }
    }
#endif
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
        
        #ifdef DEBUG 
            validateBoardIntegrity(board); 
        #endif
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