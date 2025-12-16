#include "moves.h"
#include "attack_patterns.h"

int main()
{
    puts("Precomputing all attack patterns..."); 
    precomputeAllAttacks(); 
    puts("Precomputations complete!"); 

    for(int square = 0 ; square <32 ; square++){
        printf("If piece was on square %d: \n", square);
        U64 wpawnAttacks = getPawnAttackPattern(square, nWhite);
        U64 bpawnAttacks = getPawnAttackPattern(square, nBlack);

        puts("White Pawns"); 
        printBB(wpawnAttacks);
        puts("Black Pawns");
        printBB(bpawnAttacks);

        U64 knightAttacks = getKnightAttackPattern(square); 
        puts("Knight:"); 
        printBB(knightAttacks);

        U64 bishop = getBishopAttackPattern(square, 0); // no blockers
        puts("Bishop:");
        printBB(bishop);

        U64 rook = getRookAttackPattern(square, 0); // no blockers
        puts("Rook:");
        printBB(rook);

        puts("Queen"); 
        printBB(rook | bishop); 

        U64 king = getKingAttackAttackPattern(square); 
        puts("King");
        printBB(king); 
        
    }
    return 0;
}