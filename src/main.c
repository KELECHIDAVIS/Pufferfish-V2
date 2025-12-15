
#include "moves.h"
#include "attack_patterns.h"
int main()
{
    // for each square, generate the magic number
    precomputeBishopMasks();
    FILE* fp = fopen("bishop_magic_structs.txt", "w"); 
    fprintf(fp , "{\n"); 
    for (int square = 0; square < 64; square++)
    { 
        printf("Square %d\n", square); 
        // Bishops
        // shift amt is determined by the number of bits the relevant blocker has at this square then subtract that from 64
        int bitsSet = __builtin_popcountll(BishopMagicTable[square].mask);
        int shiftAmt = 64 - bitsSet;
        findMagicNum(true, square, shiftAmt);

        // save SMagic struct for this square to file {mask , magic , shiftAmt}
        fprintf(fp, "{ %llx, %llx, %d }", BishopMagicTable[square].mask, BishopMagicTable[square].magic, BishopMagicTable[square].shiftAmt) ; 
        if (square <63) fprintf(fp, ",\n"); 
    }
    fprintf(fp, "\n}"); 

    return 0;
}