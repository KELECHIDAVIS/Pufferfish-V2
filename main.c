#include "board.h"
#include "moves.h"

int main()
{
   
    // Move moveList[MAX_MOVES];
    // size_t numMoves = 0;
    // Board board;
    // char *fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    // initBoard(&board, fen ); 
    // getLegalMoves(&board, moveList, &numMoves);
    
    // printf("Number of legal moves: %zu\n", numMoves);
    // for (size_t i = 0; i < numMoves; i++) {
    //     Move move = moveList[i];
    //     printf("Move %zu: from %u to %u with flags %u\n", i, getFrom(move), getTo(move), getFlags(move));
    // }

    U64 bitTest = 0x0000000000000045ULL;
    printBB(bitTest);

    while( bitTest ){
        U64 lsb = LSBIT(bitTest);
        bitTest = CLEARLSBIT(bitTest);
        printf("LSB: \n");
        printBB(lsb);
    }
    
    return 0;
}