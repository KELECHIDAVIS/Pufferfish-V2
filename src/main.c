#include "moves.h"
#include "attack_patterns.h"

int main()
{
    // Generate Bishop Magic Numbers
    printf("Generating Bishop Magic Numbers...\n");
    precomputeBishopMasks();

    FILE *fp = fopen("bishop_magic_structs.txt", "w");
    if (!fp)
    {
        fprintf(stderr, "Error: Could not open bishop_magic_structs.txt for writing\n");
        return 1;
    }

    fprintf(fp, "{\n");
    for (int square = 0; square < 64; square++)
    {
        int bitsSet = __builtin_popcountll(BishopMagicTable[square].mask);
        int shiftAmt = 64 - bitsSet;
        findMagicNum(true, square, shiftAmt);

        printf("Square %2d: { 0x%016llx, 0x%016llx, %d }\n",
               square, BishopMagicTable[square].mask,
               BishopMagicTable[square].magic,
               BishopMagicTable[square].shiftAmt);

        fprintf(fp, "    { 0x%016llxULL, 0x%016llxULL, %d }%s\n",
                BishopMagicTable[square].mask,
                BishopMagicTable[square].magic,
                BishopMagicTable[square].shiftAmt,
                square < 63 ? "," : "");
    }
    fprintf(fp, "};\n");
    fclose(fp);
    printf("Bishop magic numbers saved to bishop_magic_structs.txt\n\n");

    // Generate Rook Magic Numbers
    printf("Generating Rook Magic Numbers...\n");
    precomputeRookMasks();

    FILE *fp2 = fopen("rook_magic_structs.txt", "w");
    if (!fp2)
    {
        fprintf(stderr, "Error: Could not open rook_magic_structs.txt for writing\n");
        return 1;
    }

    fprintf(fp2, "{\n");
    for (int square = 0; square < 64; square++)
    {
        int bitsSet = __builtin_popcountll(RookMagicTable[square].mask);
        int shiftAmt = 64 - bitsSet;
        findMagicNum(false, square, shiftAmt);

        printf("Square %2d: { 0x%016llx, 0x%016llx, %d }\n",
               square, RookMagicTable[square].mask,
               RookMagicTable[square].magic,
               RookMagicTable[square].shiftAmt);

        fprintf(fp2, "    { 0x%016llxULL, 0x%016llxULL, %d }%s\n",
                RookMagicTable[square].mask,
                RookMagicTable[square].magic,
                RookMagicTable[square].shiftAmt,
                square < 63 ? "," : "");
    }
    fprintf(fp2, "};\n");
    fclose(fp2);
    printf("Rook magic numbers saved to rook_magic_structs.txt\n");

    return 0;
}