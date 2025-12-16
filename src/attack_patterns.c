#include "attack_patterns.h"

U64 PAWN_ATTACK_LOOKUP[2][64] = {0ULL};
U64 KNIGHT_ATTACK_LOOKUP[64] = {0ULL};
U64 KING_ATTACK_LOOKUP[64] = {0ULL};
U64 ROOK_ATTACK_LOOKUP[64][4096] = {0ULL};
U64 BISHOP_ATTACK_LOOKUP[64][512] = {0ULL};

SMagic BishopMagicTable[64]; 
SMagic RookMagicTable[64] ; 

U64 noNoEa(U64 b) { return (b << 17) & ~FILE_A; }
U64 noEaEa(U64 b) { return (b << 10) & ~(FILE_A | FILE_B); }
U64 soEaEa(U64 b) { return (b >> 6) & ~(FILE_A | FILE_B); }
U64 soSoEa(U64 b) { return (b >> 15) & ~FILE_A; }
U64 noNoWe(U64 b) { return (b << 15) & ~FILE_H; }
U64 noWeWe(U64 b) { return (b << 6) & ~(FILE_G | FILE_H); }
U64 soWeWe(U64 b) { return (b >> 10) & ~(FILE_G | FILE_H); }
U64 soSoWe(U64 b) { return (b >> 17) & ~FILE_H; }
U64 north(U64 b) { return (b << 8) & ~RANK_1; }
U64 south(U64 b) { return (b >> 8) & ~RANK_8; }
U64 east(U64 b) { return (b << 1) & ~FILE_A; }
U64 west(U64 b) { return (b >> 1) & ~FILE_H; }
U64 northEast(U64 b) { return (b << 9) & ~RANK_1 & ~FILE_A; }
U64 southEast(U64 b) { return (b >> 7) & ~RANK_8 & ~FILE_A; }
U64 northWest(U64 b) { return (b << 7) & ~FILE_H & ~RANK_1; }
U64 southWest(U64 b) { return (b >> 9) & ~FILE_H & ~RANK_8; }

// call on start up 
void precomputeAllAttacks(void)
{
    precomputePawnAttacks(); 
    precomputeKnightAttacks(); 
    precomputeKingAttacks(); 

    // sliding moves 
    precomputeMagicNumbers(); 
    precomputeSlidingPieceLookupTables(); 
}


void precomputePawnAttacks()
{
    for (int i = nWhite; i <= nBlack; i++) // for both colors
    {
        for (int square = 0; square < 64; square++)
        {
            U64 attacks = 0ULL;
            U64 position = 1ULL << square;

            if (i == nWhite)
            {
                // white pawns attack diagonally up
                if ((position << 7) & ~FILE_H)
                    attacks |= (position << 7); // up-right
                if ((position << 9) & ~FILE_A)
                    attacks |= (position << 9); // up-left
            }
            else
            {
                // black pawns attack diagonally down
                if ((position >> 7) & ~FILE_A)
                    attacks |= (position >> 7); // down-left
                if ((position >> 9) & ~FILE_H)
                    attacks |= (position >> 9); // down-right
            }
            PAWN_ATTACK_LOOKUP[i][square] = attacks;
        }
    }
}

void precomputeKingAttacks(void)
{
    for (int square = 0; square < 64; square++)
    {
        // add all possible king  moves from this square
        U64 attacks = 0ULL;
        U64 position = 1ULL << square;
        attacks |= north(position);
        attacks |= south(position);
        attacks |= east(position);
        attacks |= west(position);
        attacks |= northEast(position);
        attacks |= southEast(position);
        attacks |= northWest(position);
        attacks |= southWest(position);

        KING_ATTACK_LOOKUP[square] = attacks;
    }
}

void precomputeKnightAttacks()
{
    for (int square = 0; square < 64; square++)
    {
        // add all possible knight moves from this square
        U64 attacks = 0ULL;
        U64 position = 1ULL << square;
        attacks |= noNoEa(position); // up-right
        attacks |= noEaEa(position); // up-left
        attacks |= soEaEa(position); // down-left
        attacks |= soSoEa(position); // down-right
        attacks |= noNoWe(position); // up-left
        attacks |= noWeWe(position); // up-right
        attacks |= soWeWe(position); // down-right
        attacks |= soSoWe(position); // down-left

        KNIGHT_ATTACK_LOOKUP[square] = attacks;
    }
}

// precomputes the relevant blocking squares for each square (code from:https://www.chessprogramming.org/Looking_for_Magics )
void precomputeRookMasks()
{
    for (int sq = 0; sq < 64; sq++)
    {
        U64 result = 0ULL;
        int rk = sq / 8, fl = sq % 8, r, f;
        for (r = rk + 1; r <= 6; r++)
            result |= (1ULL << (fl + r * 8));
        for (r = rk - 1; r >= 1; r--)
            result |= (1ULL << (fl + r * 8));
        for (f = fl + 1; f <= 6; f++)
            result |= (1ULL << (f + rk * 8));
        for (f = fl - 1; f >= 1; f--)
            result |= (1ULL << (f + rk * 8));

        RookMagicTable[sq].mask = result;
    }
}
void precomputeBishopMasks()
{
    for (int sq = 0; sq < 64; sq++)
    {
        U64 result = 0ULL;
        int rk = sq / 8, fl = sq % 8, r, f;
        for (r = rk + 1, f = fl + 1; r <= 6 && f <= 6; r++, f++)
            result |= (1ULL << (f + r * 8));
        for (r = rk + 1, f = fl - 1; r <= 6 && f >= 1; r++, f--)
            result |= (1ULL << (f + r * 8));
        for (r = rk - 1, f = fl + 1; r >= 1 && f <= 6; r--, f++)
            result |= (1ULL << (f + r * 8));
        for (r = rk - 1, f = fl - 1; r >= 1 && f >= 1; r--, f--)
            result |= (1ULL << (f + r * 8));

        BishopMagicTable[sq].mask = result;
    }
}


U64 iterative_getBishopAttackPattern(U64 block, enumSquare sq)
{
    U64 result = 0ULL;
    int rk = (int)sq / 8, fl = (int)sq % 8, r, f;
    for (r = rk + 1, f = fl + 1; r <= 7 && f <= 7; r++, f++)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    for (r = rk + 1, f = fl - 1; r <= 7 && f >= 0; r++, f--)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    for (r = rk - 1, f = fl + 1; r >= 0 && f <= 7; r--, f++)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    for (r = rk - 1, f = fl - 1; r >= 0 && f >= 0; r--, f--)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    return result;
}
U64 iterative_getRookAttackPattern(U64 block, enumSquare sq)
{
    U64 result = 0ULL;
    int rk = (int)sq / 8, fl = (int)sq % 8, r, f;
    for (r = rk + 1; r <= 7; r++)
    {
        result |= (1ULL << (fl + r * 8));
        if (block & (1ULL << (fl + r * 8)))
            break;
    }
    for (r = rk - 1; r >= 0; r--)
    {
        result |= (1ULL << (fl + r * 8));
        if (block & (1ULL << (fl + r * 8)))
            break;
    }
    for (f = fl + 1; f <= 7; f++)
    {
        result |= (1ULL << (f + rk * 8));
        if (block & (1ULL << (f + rk * 8)))
            break;
    }
    for (f = fl - 1; f >= 0; f--)
    {
        result |= (1ULL << (f + rk * 8));
        if (block & (1ULL << (f + rk * 8)))
            break;
    }
    return result;
}
// Extract the position of the least significant set bit and clear it from the bitboard
int popLeastSignificantBit(U64 *bitboard)
{
    if (*bitboard == 0)
        return -1; // Handle empty bitboard

    // Find the index of the least significant bit using built-in function
    int bitIndex = __builtin_ctzll(*bitboard); // Count trailing zeros

    // Clear that bit from the bitboard
    *bitboard &= (*bitboard - 1);

    return bitIndex;
}

U64 createBlockerConfig(int blockerIndex, int numBitsInMask, U64 mask){
    U64 result =0; 
    for(int i =0; i< numBitsInMask; i++){
        int index = popLeastSignificantBit(&mask);
        if (blockerIndex & (1 << i))
        {
            result |= (1ULL << index)   ;
        }
    }
    return result; 
}

// find magic numbers through trial and error
// based on this code: https://www.chessprogramming.org/Looking_for_Magics
U64 findMagicNum(bool isBishop, enumSquare square)
{
    U64 mask = isBishop ? BishopMagicTable[square].mask : RookMagicTable[square].mask;
    assert(mask != 0 && "Masks weren't initialized prior to calling the findMagicNum function.");

    U64 blockerConfigs[4096];
    U64 attackPatterns[4096];
    U64 hashTable[4096];
    U64 magicNumber;
    int numConfigs, numBitsInMask;

    numBitsInMask = __builtin_popcountll(mask);
    numConfigs = 1 << numBitsInMask;

    // Generate all blocker configurations and attack patterns
    for (int i = 0; i < numConfigs; i++)
    {
        blockerConfigs[i] = createBlockerConfig(i, numBitsInMask, mask);
        attackPatterns[i] = isBishop ? iterative_getBishopAttackPattern(blockerConfigs[i], square) : iterative_getRookAttackPattern(blockerConfigs[i], square);
    }

    int shiftAmt = 64 - numBitsInMask;

    // Try random magic numbers
    for (int z = 0; z < 100000000; z++)
    {
        magicNumber = randU64() & randU64() & randU64();

        // Skip if not enough bits in upper byte
        int numSetBits = __builtin_popcountll((mask * magicNumber) & 0xFF00000000000000ULL);
        if (numSetBits < 6)
            continue;

        // Clear hash table
        memset(hashTable, 0, sizeof(hashTable));

        // Test this magic number
        bool fail = false;
        for (int i = 0; i < numConfigs && !fail; i++)
        {
            int hashIndex = (int)((blockerConfigs[i] * magicNumber) >> shiftAmt);

            if (hashTable[hashIndex] == 0ULL)
            {
                hashTable[hashIndex] = attackPatterns[i];
            }
            else if (hashTable[hashIndex] != attackPatterns[i])
            {
                fail = true; // Non-constructive collision
            }
        }

        // If no collisions, we found a valid magic!
        if (!fail)
        {
            return magicNumber;
        }
    }

    // Failed to find magic after all attempts
    printf("Magic generation for square %d (%s) failed after 100000000 attempts.\n",
           square, isBishop ? "Bishop" : "Rook");
    return 0;
}
void printPawnAttacks()
{
    for (int i = nWhite; i <= nBlack; i++) // for both colors
    {
        for (int square = 0; square < 64; square++)
        {
            printf("Pawn attacks for %s from square %d:\n", i == nWhite ? "White" : "Black", square);
            printBB(PAWN_ATTACK_LOOKUP[i][square]);
        }
    }
}




void printKnightAttacks()
{
    for (int square = 0; square < 64; square++)
    {
        printf("Knight attacks from square %d:\n", square);
        printBB(KNIGHT_ATTACK_LOOKUP[square]);
    }
}

void precomputeMagicNumbersAndSaveToFile(){

    // Generate Bishop Magic Numbers
    printf("Generating Bishop Magic Numbers...\n");
    precomputeBishopMasks();

    FILE *fp = fopen("bishop_magic_structs.txt", "w");
    if (!fp)
    {
        fprintf(stderr, "Error: Could not open bishop_magic_structs.txt for writing\n");
        abort();
    }

    fprintf(fp, "{\n");
    for (int square = 0; square < 64; square++)
    {
        int bitsSet = __builtin_popcountll(BishopMagicTable[square].mask);
        int shiftAmt = 64 - bitsSet;
        U64 magic =  findMagicNum(true, square);

        
        printf("Square %2d: { 0x%016llx, 0x%016llx, %d }\n",
               square, BishopMagicTable[square].mask,
               magic ,
               shiftAmt);

        if (magic == 0)
        {
            printf("Magic Generation failed, Returned magic number was zero"); 
            abort(); 
        }

        fprintf(fp, "    { 0x%016llxULL, 0x%016llxULL, %d }%s\n",
                BishopMagicTable[square].mask,
                magic,
                shiftAmt,
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
        abort();
    }

    fprintf(fp2, "{\n");
    for (int square = 0; square < 64; square++)
    {
        int bitsSet = __builtin_popcountll(RookMagicTable[square].mask);
        int shiftAmt = 64 - bitsSet;
        U64 magic = findMagicNum(false, square);

        printf("Square %2d: { 0x%016llx, 0x%016llx, %d }\n",
               square, RookMagicTable[square].mask,
               magic,
               shiftAmt);

        if (magic == 0)
        {
            printf("Magic Generation failed, Returned magic number was zero");
            abort();
        }
        fprintf(fp2, "    { 0x%016llxULL, 0x%016llxULL, %d }%s\n",
                RookMagicTable[square].mask,
                magic,
                shiftAmt,
                square < 63 ? "," : "");
    }
    fprintf(fp2, "};\n");
    fclose(fp2);
    printf("Rook magic numbers saved to rook_magic_structs.txt\n");
}

// precompute relevant blocker masks, magic numbers, and shift amounts for all squares
void precomputeMagicNumbers()
{
    // Generate Bishop Magic Numbers
    precomputeBishopMasks();
    for (int square = 0; square < 64; square++)
    {
        int bitsSet = __builtin_popcountll(BishopMagicTable[square].mask);
        int shiftAmt = 64 - bitsSet;
        U64 magic = findMagicNum(true, square);

        if (magic == 0)
        {
            printf("Magic Generation failed, Returned magic number was zero");
            abort();
        }

        BishopMagicTable[square].magic = magic; 
        BishopMagicTable[square].shiftAmt = shiftAmt; 
    }

    // generate rook magics
    precomputeRookMasks();
    for (int square = 0; square < 64; square++)
    {
        int bitsSet = __builtin_popcountll(RookMagicTable[square].mask);
        int shiftAmt = 64 - bitsSet;
        U64 magic = findMagicNum(false, square);

        if (magic == 0)
        {
            printf("Magic Generation failed, Returned magic number was zero");
            abort();
        }
        
        RookMagicTable[square].magic = magic; 
        RookMagicTable[square].shiftAmt= shiftAmt; 
    }

}

// Call this function after magic numbers have been precomputed and copy-pasted into the SMagic tables
void precomputeSlidingPieceLookupTablesAndSaveToFile()
{
    printf("Precomputing sliding piece lookup tables...\n");

    // Process both bishops and rooks
    for (int isBishop = 0; isBishop <= 1; isBishop++)
    {
        const char *pieceName = isBishop ? "Bishop" : "Rook";
        printf("\nGenerating %s attack lookup tables...\n", pieceName);

        // Open file for this piece type
        char filename[50];
        snprintf(filename, sizeof(filename), "%s_attack_lookup.txt",
                 isBishop ? "bishop" : "rook");
        FILE *fp = fopen(filename, "w");
        if (!fp)
        {
            fprintf(stderr, "Error: Could not open %s for writing\n", filename);
            abort();
        }

        fprintf(fp, "// %s Attack Lookup Table [64 squares][max configs]\n", pieceName);
        fprintf(fp, "U64 %s_ATTACK_LOOKUP[64][%d] = {\n",
                isBishop ? "BISHOP" : "ROOK",
                isBishop ? 512 : 4096);

        for (int square = 0; square < 64; square++)
        {
            SMagic entry = isBishop ? BishopMagicTable[square] : RookMagicTable[square];
            U64 mask = entry.mask;

            // Verify magic number exists
            if (entry.magic == 0ULL)
            {
                fprintf(stderr, "Error: No magic number for %s at square %d\n",
                        pieceName, square);
                abort();
            }

            int numBitsInMask = __builtin_popcountll(mask);
            int numConfigs = 1 << numBitsInMask;
            int maxConfigs = isBishop ? 512 : 4096;

            // Get pointer to the lookup table for this square
            U64 *lookupTable = isBishop ? BISHOP_ATTACK_LOOKUP[square] : ROOK_ATTACK_LOOKUP[square];

            // Clear the table first (in case of reruns)
            memset(lookupTable, 0, (size_t)maxConfigs * sizeof(U64));

            printf("  Square %2d: Processing %d configurations...\n", square, numConfigs);

            // Populate lookup table for all blocker configurations
            for (int i = 0; i < numConfigs; i++)
            {
                U64 blockers = createBlockerConfig(i, numBitsInMask, mask);
                U64 attackPattern = isBishop ? iterative_getBishopAttackPattern(blockers, square) : iterative_getRookAttackPattern(blockers, square);

                int hashIndex = magicIndex(&entry, blockers);

                // Verify hash index is in bounds
                if (hashIndex < 0 || hashIndex >= maxConfigs)
                {
                    fprintf(stderr, "Error: Hash index %d out of bounds [0, %d) for square %d\n",
                            hashIndex, maxConfigs, square);
                    abort();
                }

                // Check for non-constructive collisions
                if (lookupTable[hashIndex] == 0ULL)
                {
                    lookupTable[hashIndex] = attackPattern;
                }
                else if (lookupTable[hashIndex] != attackPattern)
                {
                    // Non-constructive collision - magic number is invalid!
                    fprintf(stderr, "\nERROR: Non-constructive collision in %s at square %d\n",
                            pieceName, square);
                    fprintf(stderr, "Hash Index: %d\n", hashIndex);
                    fprintf(stderr, "Blocker Config %d:\n", i);
                    printBB(blockers);
                    fprintf(stderr, "Expected Attack Pattern:\n");
                    printBB(attackPattern);
                    fprintf(stderr, "Existing Attack Pattern:\n");
                    printBB(lookupTable[hashIndex]);
                    fprintf(stderr, "This means the magic number is invalid!\n");
                    fclose(fp);
                    abort();
                }
                // else: constructive collision (same attack pattern) - this is fine
            }

            // Write this square's lookup table to file
            fprintf(fp, "    { // Square %d\n", square);
            for (int i = 0; i < maxConfigs; i++)
            {
                if (i % 4 == 0)
                    fprintf(fp, "        ");
                fprintf(fp, "0x%016llxULL", lookupTable[i]);
                if (i < maxConfigs - 1)
                    fprintf(fp, ", ");
                if (i % 4 == 3)
                    fprintf(fp, "\n");
            }
            fprintf(fp, "    }%s\n", square < 63 ? "," : "");
        }

        fprintf(fp, "};\n");
        fclose(fp);
        printf("%s attack lookup table saved to %s\n", pieceName, filename);
    }

    printf("\nAll lookup tables generated successfully!\n");
}

void fprintBB(FILE *fp, U64 bitboard)
{
    for (int rank = 7; rank >= 0; rank--)
    {
        fprintf(fp, "%d| ", rank + 1);
        for (int file = 0; file < 8; file++)
        {
            int square = rank * 8 + file;
            if (bitboard & (1ULL << square))
            {
                fprintf(fp, "1 ");
            }
            else
            {
                fprintf(fp, ". ");
            }
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "   _ _ _ _ _ _ _ _ \n");
    fprintf(fp, "   a b c d e f g h\n");
}

void writeAllAttackPatternsToFile(void)
{
    puts("Precomputing all attack patterns...");
    precomputeAllAttacks();
    puts("Precomputations complete!");

    FILE *fp = fopen("attack_patterns_visualization.txt", "w");
    if (!fp)
    {
        fprintf(stderr, "Error: Could not open attack_patterns_visualization.txt for writing\n");
        abort(); 
    }

    fprintf(fp, "========================================\n");
    fprintf(fp, "ATTACK PATTERNS FOR ALL PIECES\n");
    fprintf(fp, "========================================\n\n");

    for (int square = 0; square < 64; square++)
    {
        fprintf(fp, "============ SQUARE %d ============\n", square);

        // White Pawn Attacks
        U64 wpawnAttacks = getPawnAttackPattern(square, nWhite);
        fprintf(fp, "\nWhite Pawn Attacks:\n");
        fprintBB(fp, wpawnAttacks);

        // Black Pawn Attacks
        U64 bpawnAttacks = getPawnAttackPattern(square, nBlack);
        fprintf(fp, "\nBlack Pawn Attacks:\n");
        fprintBB(fp, bpawnAttacks);

        // Knight Attacks
        U64 knightAttacks = getKnightAttackPattern(square);
        fprintf(fp, "\nKnight Attacks:\n");
        fprintBB(fp, knightAttacks);

        // Bishop Attacks (no blockers)
        U64 bishop = getBishopAttackPattern(square, 0);
        fprintf(fp, "\nBishop Attacks (no blockers):\n");
        fprintBB(fp, bishop);

        // Rook Attacks (no blockers)
        U64 rook = getRookAttackPattern(square, 0);
        fprintf(fp, "\nRook Attacks (no blockers):\n");
        fprintBB(fp, rook);

        // Queen Attacks
        fprintf(fp, "\nQueen Attacks (no blockers):\n");
        fprintBB(fp, rook | bishop);

        // King Attacks
        U64 king = getKingAttackAttackPattern(square);
        fprintf(fp, "\nKing Attacks:\n");
        fprintBB(fp, king);

        fprintf(fp, "\n\n");
    }

    fclose(fp);
    printf("Attack patterns saved to attack_patterns_visualization.txt\n");
}

void precomputeSlidingPieceLookupTables()
{
    printf("Initializing magic bitboard lookup tables...\n");

    // For both bishops and rooks
    for (int isBishop = 0; isBishop <= 1; isBishop++)
    {
        for (int square = 0; square < 64; square++)
        {
            SMagic entry = isBishop ? BishopMagicTable[square] : RookMagicTable[square];
            U64 mask = entry.mask;

            int numBitsInMask = __builtin_popcountll(mask);
            int numConfigs = 1 << numBitsInMask;

            // Get pointer to lookup table for this square
            U64 *lookupTable = isBishop ? BISHOP_ATTACK_LOOKUP[square] : ROOK_ATTACK_LOOKUP[square];

            // Populate ALL possible blocker configurations
            for (int i = 0; i < numConfigs; i++)
            {
                U64 blockers = createBlockerConfig(i, numBitsInMask, mask);
                U64 attackPattern = isBishop ? iterative_getBishopAttackPattern(blockers, square) : iterative_getRookAttackPattern(blockers, square);

                int hashIndex = magicIndex(&entry, blockers);
                lookupTable[hashIndex] = attackPattern;
            }
        }
    }

    printf("Magic bitboard initialization complete!\n");
}

//test lookup generation 
void testLookupGeneration(){
    precomputeSlidingPieceLookupTables();

    // test out 50 random attack patterns and see if they give the correct response
    puts("Starting random lookup tests");
    for (int i = 0; i < 50; i++)
    {
        U64 randOccupancy = randU64();
        int randSquare = rand() % 64;
        int isBishop = rand() % 2;
        printf("%s on square %d\n",
               isBishop ? "Bishop" : "Rook",
               randSquare);
        puts("Random Occupancy: ");
        printBB(randOccupancy);

        SMagic entry = isBishop ? BishopMagicTable[randSquare] : RookMagicTable[randSquare];
        U64 blockers = entry.mask & randOccupancy;

        printf("Relevant Blockers:\n");
        printBB(blockers);

        int hashIndex = magicIndex(&entry, blockers);
        printf("Hash Index %d: \n", hashIndex);

        puts("Attack Pattern: ");
        U64 attackPattern = isBishop ? BISHOP_ATTACK_LOOKUP[randSquare][hashIndex] : ROOK_ATTACK_LOOKUP[randSquare][hashIndex];
        printBB(attackPattern);
    }
}
