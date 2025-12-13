#include "board.h"
#include "moves.h"

int main()
{

    // Move moveList[MAX_MOVES];
    // size_t numMoves = 0;
    // Board board;
    // char *fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    // initBoard(&board, fen);
    // printChessBoard(&board);

    // getLegalMoves(&board, moveList, &numMoves);

    // printf("Number of legal moves: %zu\n", numMoves);
    // for (size_t i = 0; i < numMoves; i++)
    // {
    //     Move move = moveList[i];
    //     char fromAlgebraic[3];
    //     char toAlgebraic[3];
    //     char flagAlgebraic[3];
    //     translateSquareToAlgebraic(getFrom(move), fromAlgebraic);
    //     translateSquareToAlgebraic(getTo(move), toAlgebraic);
    //     translateFlagToAlgebraic((MoveFlag)getFlags(move), flagAlgebraic);
    //     printf("Move %zu: %s to %s, Flag: %s\n", i + 1, fromAlgebraic, toAlgebraic, flagAlgebraic);
    // }

    precomputePawnAttacks(); 
    
    FILE *fp = fopen("pawn_attacks_lookup.txt", "w");

    for(int color=0; color<=1; color++)
    {
        fprintf(fp, "{\n"); 
        for(int square=0; square<64; square++)
        {
            U64 attacks = PAWN_ATTACK_LOOKUP[color][square];
            fprintf(fp, "0x%016llxULL", attacks);
            if(square!=63) fprintf(fp, ",\n");   
        }
        fprintf(fp, "}");
        if (color==0) fprintf(fp, ",\n");
    }
    return 0;
}