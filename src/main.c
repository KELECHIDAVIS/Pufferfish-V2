
#include "moves.h"
#include "attack_patterns.h"
int main()
{
    // for each square, generate the magic number 
    precomputeBishopMasks(); 
    for (int square = 0; square< 64 ; square++){ // Bishops
        // shift amt is determined by the number of bits the relevant blocker has at this square then subtract that from 64
        int bitsSet = __builtin_popcountll(BishopMagicTable[square].mask); 
        int shiftAmt = 64 - bitsSet; 
        findMagicNum(false, square, shiftAmt );

        // now test all possible configurations for 
        U64 blockerBitboards[512]; 
        int numConfigs = 0; 
        createAllBlockerBitboards(BishopMagicTable[square].mask, blockerBitboards, &numConfigs); 
        
        // for each blocker config, print out accompanying attack pattern based on magic lookup 
        for (int j = 0 ; j< numConfigs; j++){
            puts("Relevant Movement Mask For Square");
            printBB(BishopMagicTable[square].mask); 
            puts("Blocker Config: "); 
            printBB(blockerBitboards[j]); 

            puts("Attack Pattern: "); 
            printBB(getBishopAttackPattern(square, blockerBitboards[j])); 
        }
        break; // TODO: remove 
    }

    return 0;
}