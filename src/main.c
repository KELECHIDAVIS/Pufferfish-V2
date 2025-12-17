#include "moves.h"
#include "attack_patterns.h"
#include "perft.h"  
int main()
{
    Board board ; 
    initStandardChess(&board); 

    printChessBoard(&board); 
    // precompute attack patterns 
    precomputeAllAttacks(); 

    puts(""); 
    for (int depth = 0 ; depth <=5; depth ++){
        printf("Divide depth %d\n", depth ); 
        U64 captures = 0, ep = 0, castles = 0, promotions = 0, checks = 0, checkmates = 0;
        U64 totalNodes = divide(&board, depth, &captures, &ep, &castles, &promotions, &checks, &checkmates);
        printf("Nodes: %llu , Captures: %llu , Ep: %llu , Castles: %llu , Promotions: %llu, Checks: %llu Checkmates: %llu\n", totalNodes, captures, ep , castles, promotions , checks , checkmates);
    }
    
    return 0;
}