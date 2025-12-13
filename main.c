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

    // // precompute knight attacks and save to file to embed later 
    // precomputeKnightAttacks();
    // FILE *file = fopen("knight_attacks_lookup.txt", "w");
    // if (file == NULL) {
    //     perror("Failed to open file for writing");
    //     return 1;
    // }
    
    // for (int i = 0; i < 64; i++) {
    //     fprintf(file, "    0x%016llxULL", KNIGHT_ATTACK_LOOKUP[i]);
    //     if (i < 63) {
    //         fprintf(file, ",\n");
    //     } 
    // }
    
    // fclose(file);

    for ( int i = 0 ; i < 64 ; i++){
        printf("Knight attacks from square %d:\n", i);
        printBB(KNIGHT_ATTACK_LOOKUP[i]);
    }

    return 0;
}