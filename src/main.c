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

    puts("Divide results: "); 
    U64 totalNodes = divide(&board, 1);
    printf("\nTotal Number of Nodes: %llu\n", totalNodes ) ; 
    return 0;
}