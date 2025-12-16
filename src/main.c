#include "moves.h"
#include "attack_patterns.h"
#include "perft.h"  
int main()
{
    Board board ; 
    initStandardChess(&board); 

    // precompute attack patterns 
    precomputeAllAttacks(); 

    divide(&board, 1); 
    return 0;
}