#include "attack_patterns.h"
U64 PAWN_ATTACK_LOOKUP[2][64] = {{0x0000000000000200ULL,
                                  0x0000000000000500ULL,
                                  0x0000000000000a00ULL,
                                  0x0000000000001400ULL,
                                  0x0000000000002800ULL,
                                  0x0000000000005000ULL,
                                  0x000000000000a000ULL,
                                  0x0000000000004000ULL,
                                  0x0000000000020000ULL,
                                  0x0000000000050000ULL,
                                  0x00000000000a0000ULL,
                                  0x0000000000140000ULL,
                                  0x0000000000280000ULL,
                                  0x0000000000500000ULL,
                                  0x0000000000a00000ULL,
                                  0x0000000000400000ULL,
                                  0x0000000002000000ULL,
                                  0x0000000005000000ULL,
                                  0x000000000a000000ULL,
                                  0x0000000014000000ULL,
                                  0x0000000028000000ULL,
                                  0x0000000050000000ULL,
                                  0x00000000a0000000ULL,
                                  0x0000000040000000ULL,
                                  0x0000000200000000ULL,
                                  0x0000000500000000ULL,
                                  0x0000000a00000000ULL,
                                  0x0000001400000000ULL,
                                  0x0000002800000000ULL,
                                  0x0000005000000000ULL,
                                  0x000000a000000000ULL,
                                  0x0000004000000000ULL,
                                  0x0000020000000000ULL,
                                  0x0000050000000000ULL,
                                  0x00000a0000000000ULL,
                                  0x0000140000000000ULL,
                                  0x0000280000000000ULL,
                                  0x0000500000000000ULL,
                                  0x0000a00000000000ULL,
                                  0x0000400000000000ULL,
                                  0x0002000000000000ULL,
                                  0x0005000000000000ULL,
                                  0x000a000000000000ULL,
                                  0x0014000000000000ULL,
                                  0x0028000000000000ULL,
                                  0x0050000000000000ULL,
                                  0x00a0000000000000ULL,
                                  0x0040000000000000ULL,
                                  0x0200000000000000ULL,
                                  0x0500000000000000ULL,
                                  0x0a00000000000000ULL,
                                  0x1400000000000000ULL,
                                  0x2800000000000000ULL,
                                  0x5000000000000000ULL,
                                  0xa000000000000000ULL,
                                  0x4000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL,
                                  0x0000000000000000ULL},
                                 {0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000002ULL, 0x0000000000000005ULL, 0x000000000000000aULL, 0x0000000000000014ULL, 0x0000000000000028ULL, 0x0000000000000050ULL, 0x00000000000000a0ULL, 0x0000000000000040ULL, 0x0000000000000200ULL, 0x0000000000000500ULL, 0x0000000000000a00ULL, 0x0000000000001400ULL, 0x0000000000002800ULL, 0x0000000000005000ULL, 0x000000000000a000ULL, 0x0000000000004000ULL, 0x0000000000020000ULL, 0x0000000000050000ULL, 0x00000000000a0000ULL, 0x0000000000140000ULL, 0x0000000000280000ULL, 0x0000000000500000ULL, 0x0000000000a00000ULL, 0x0000000000400000ULL, 0x0000000002000000ULL, 0x0000000005000000ULL, 0x000000000a000000ULL, 0x0000000014000000ULL, 0x0000000028000000ULL, 0x0000000050000000ULL, 0x00000000a0000000ULL, 0x0000000040000000ULL, 0x0000000200000000ULL, 0x0000000500000000ULL, 0x0000000a00000000ULL, 0x0000001400000000ULL, 0x0000002800000000ULL, 0x0000005000000000ULL, 0x000000a000000000ULL, 0x0000004000000000ULL, 0x0000020000000000ULL, 0x0000050000000000ULL, 0x00000a0000000000ULL, 0x0000140000000000ULL, 0x0000280000000000ULL, 0x0000500000000000ULL, 0x0000a00000000000ULL, 0x0000400000000000ULL, 0x0002000000000000ULL, 0x0005000000000000ULL, 0x000a000000000000ULL, 0x0014000000000000ULL, 0x0028000000000000ULL, 0x0050000000000000ULL, 0x00a0000000000000ULL, 0x0040000000000000ULL}};
U64 KNIGHT_ATTACK_LOOKUP[64] = {
    0x0000000000020400ULL,
    0x0000000000050800ULL,
    0x00000000000a1100ULL,
    0x0000000000142200ULL,
    0x0000000000284400ULL,
    0x0000000000508800ULL,
    0x0000000000a01000ULL,
    0x0000000000402000ULL,
    0x0000000002040004ULL,
    0x0000000005080008ULL,
    0x000000000a110011ULL,
    0x0000000014220022ULL,
    0x0000000028440044ULL,
    0x0000000050880088ULL,
    0x00000000a0100010ULL,
    0x0000000040200020ULL,
    0x0000000204000402ULL,
    0x0000000508000805ULL,
    0x0000000a1100110aULL,
    0x0000001422002214ULL,
    0x0000002844004428ULL,
    0x0000005088008850ULL,
    0x000000a0100010a0ULL,
    0x0000004020002040ULL,
    0x0000020400040200ULL,
    0x0000050800080500ULL,
    0x00000a1100110a00ULL,
    0x0000142200221400ULL,
    0x0000284400442800ULL,
    0x0000508800885000ULL,
    0x0000a0100010a000ULL,
    0x0000402000204000ULL,
    0x0002040004020000ULL,
    0x0005080008050000ULL,
    0x000a1100110a0000ULL,
    0x0014220022140000ULL,
    0x0028440044280000ULL,
    0x0050880088500000ULL,
    0x00a0100010a00000ULL,
    0x0040200020400000ULL,
    0x0204000402000000ULL,
    0x0508000805000000ULL,
    0x0a1100110a000000ULL,
    0x1422002214000000ULL,
    0x2844004428000000ULL,
    0x5088008850000000ULL,
    0xa0100010a0000000ULL,
    0x4020002040000000ULL,
    0x0400040200000000ULL,
    0x0800080500000000ULL,
    0x1100110a00000000ULL,
    0x2200221400000000ULL,
    0x4400442800000000ULL,
    0x8800885000000000ULL,
    0x100010a000000000ULL,
    0x2000204000000000ULL,
    0x0004020000000000ULL,
    0x0008050000000000ULL,
    0x00110a0000000000ULL,
    0x0022140000000000ULL,
    0x0044280000000000ULL,
    0x0088500000000000ULL,
    0x0010a00000000000ULL,
    0x0020400000000000ULL};

U64 KING_ATTACK_LOOKUP[64] = {

};

U64 ROOK_ATTACK_LOOKUP[64][4096] = {0ULL};
U64 BISHOP_ATTACK_LOOKUP[64][512] = {0ULL};

SMagic BishopMagicTable[64] = {
    {0x0040201008040200ULL, 0x0004501001002080ULL, 58},
    {0x0000402010080400ULL, 0x0854080841002c00ULL, 59},
    {0x0000004020100a00ULL, 0x0804410405000000ULL, 59},
    {0x0000000040221400ULL, 0x08111042002d00a0ULL, 59},
    {0x0000000002442800ULL, 0x0104042000000508ULL, 59},
    {0x0000000204085000ULL, 0x0142020220030810ULL, 59},
    {0x0000020408102000ULL, 0x0100480424222004ULL, 59},
    {0x0002040810204000ULL, 0x440520880c012000ULL, 58},
    {0x0020100804020000ULL, 0x0000442810640480ULL, 59},
    {0x0040201008040000ULL, 0x0010100210911200ULL, 59},
    {0x00004020100a0000ULL, 0x0010448404084002ULL, 59},
    {0x0000004022140000ULL, 0x0200040400884480ULL, 59},
    {0x0000000244280000ULL, 0x4901184841101400ULL, 59},
    {0x0000020408500000ULL, 0x0209708220220420ULL, 59},
    {0x0002040810200000ULL, 0x0082040201442118ULL, 59},
    {0x0004081020400000ULL, 0x0400008400883480ULL, 59},
    {0x0010080402000200ULL, 0x0005245838080840ULL, 59},
    {0x0020100804000400ULL, 0x0004401010820043ULL, 59},
    {0x004020100a000a00ULL, 0x400616e410220200ULL, 57},
    {0x0000402214001400ULL, 0x0020400401002000ULL, 57},
    {0x0000024428002800ULL, 0x0401000820080000ULL, 57},
    {0x0002040850005000ULL, 0x0000402200500418ULL, 57},
    {0x0004081020002000ULL, 0x2203000201292000ULL, 59},
    {0x0008102040004000ULL, 0x2842024900420231ULL, 59},
    {0x0008040200020400ULL, 0x0008040040044800ULL, 59},
    {0x0010080400040800ULL, 0x0902621008480825ULL, 59},
    {0x0020100a000a1000ULL, 0x1404010810090024ULL, 57},
    {0x0040221400142200ULL, 0x004004004a010810ULL, 55},
    {0x0002442800284400ULL, 0x4041001013004000ULL, 55},
    {0x0004085000500800ULL, 0x1400490002010101ULL, 57},
    {0x0008102000201000ULL, 0x0808090002010120ULL, 59},
    {0x0010204000402000ULL, 0x00110042020220a0ULL, 59},
    {0x0004020002040800ULL, 0x00043040001414c0ULL, 59},
    {0x0008040004081000ULL, 0x0108110400300401ULL, 59},
    {0x00100a000a102000ULL, 0x080200b000220384ULL, 57},
    {0x0022140014224000ULL, 0x2010280800220a00ULL, 55},
    {0x0044280028440200ULL, 0x0001080200002200ULL, 55},
    {0x0008500050080400ULL, 0x004c082200022280ULL, 57},
    {0x0010200020100800ULL, 0x0110010050a90400ULL, 59},
    {0x0020400040201000ULL, 0x1072008820210408ULL, 59},
    {0x0002000204081000ULL, 0x0309080904404000ULL, 59},
    {0x0004000408102000ULL, 0x4004024a10040280ULL, 59},
    {0x000a000a10204000ULL, 0x0000201402011020ULL, 57},
    {0x0014001422400000ULL, 0x0060082011001800ULL, 57},
    {0x0028002844020000ULL, 0x49a8120204120200ULL, 57},
    {0x0050005008040200ULL, 0x0060089020810041ULL, 57},
    {0x0020002010080400ULL, 0x0210024801201040ULL, 59},
    {0x0040004020100800ULL, 0x0022008106014108ULL, 59},
    {0x0000020408102000ULL, 0x0002026120080048ULL, 59},
    {0x0000040810204000ULL, 0x600101012120008cULL, 59},
    {0x00000a1020400000ULL, 0x0240042108080102ULL, 59},
    {0x0000142240000000ULL, 0x000000a120884002ULL, 59},
    {0x0000284402000000ULL, 0x100100c010410202ULL, 59},
    {0x0000500804020000ULL, 0x2000218202220020ULL, 59},
    {0x0000201008040200ULL, 0x0008200842004808ULL, 59},
    {0x0000402010080400ULL, 0x0251020200420229ULL, 59},
    {0x0002040810204000ULL, 0x000224004410288aULL, 58},
    {0x0004081020400000ULL, 0x4000204100882040ULL, 59},
    {0x000a102040000000ULL, 0x0010300022015001ULL, 59},
    {0x0014224000000000ULL, 0x2020048002420208ULL, 59},
    {0x0028440200000000ULL, 0x0c00004021204100ULL, 59},
    {0x0050080402000000ULL, 0x0044005022280840ULL, 59},
    {0x0020100804020000ULL, 0x0008280214184208ULL, 59},
    {0x0040201008040200ULL, 0x20c0210214004180ULL, 58}};

SMagic RookMagicTable[64] = {
    {0x000101010101017eULL, 0x0080004000976080ULL, 52},
    {0x000202020202027cULL, 0x1040400010002000ULL, 53},
    {0x000404040404047aULL, 0x4880200210000980ULL, 53},
    {0x0008080808080876ULL, 0x5280080010000482ULL, 53},
    {0x001010101010106eULL, 0x0200040200081020ULL, 53},
    {0x002020202020205eULL, 0x2100080100020400ULL, 53},
    {0x004040404040403eULL, 0x4280008001000200ULL, 53},
    {0x008080808080807eULL, 0x01000a4425820300ULL, 52},
    {0x0001010101017e00ULL, 0x0029002100800040ULL, 53},
    {0x0002020202027c00ULL, 0x4503400040201004ULL, 54},
    {0x0004040404047a00ULL, 0x0209002001004018ULL, 54},
    {0x0008080808087600ULL, 0x1131000a10002100ULL, 54},
    {0x0010101010106e00ULL, 0x0009000800120500ULL, 54},
    {0x0020202020205e00ULL, 0x010e001804820010ULL, 54},
    {0x0040404040403e00ULL, 0x0029000402000100ULL, 54},
    {0x0080808080807e00ULL, 0x2002000d01c40292ULL, 53},
    {0x00010101017e0100ULL, 0x0080084000200c40ULL, 53},
    {0x00020202027c0200ULL, 0x0010004040002002ULL, 54},
    {0x00040404047a0400ULL, 0x0201030020004014ULL, 54},
    {0x0008080808760800ULL, 0x080012000a420020ULL, 54},
    {0x00101010106e1000ULL, 0x0129010008001204ULL, 54},
    {0x00202020205e2000ULL, 0x6109010008040002ULL, 54},
    {0x00404040403e4000ULL, 0x0950010100020004ULL, 54},
    {0x00808080807e8000ULL, 0x00803a0000c50284ULL, 53},
    {0x000101017e010100ULL, 0x0080004100210080ULL, 53},
    {0x000202027c020200ULL, 0x0000200240100140ULL, 54},
    {0x000404047a040400ULL, 0x0020004040100800ULL, 54},
    {0x0008080876080800ULL, 0x4018090300201000ULL, 54},
    {0x001010106e101000ULL, 0x4802010a00102004ULL, 54},
    {0x002020205e202000ULL, 0x2001000900040002ULL, 54},
    {0x004040403e404000ULL, 0x04a02104001002a8ULL, 54},
    {0x008080807e808000ULL, 0x2188108200204401ULL, 53},
    {0x0001017e01010100ULL, 0x0040400020800080ULL, 53},
    {0x0002027c02020200ULL, 0x0880402000401004ULL, 54},
    {0x0004047a04040400ULL, 0x0010040800202000ULL, 54},
    {0x0008087608080800ULL, 0x0604410a02001020ULL, 54},
    {0x0010106e10101000ULL, 0x200200206a001410ULL, 54},
    {0x0020205e20202000ULL, 0x0086000400810080ULL, 54},
    {0x0040403e40404000ULL, 0x428200040600080bULL, 54},
    {0x0080807e80808000ULL, 0x2001000041000082ULL, 53},
    {0x00017e0101010100ULL, 0x0080002000484000ULL, 53},
    {0x00027c0202020200ULL, 0x0210002002c24000ULL, 54},
    {0x00047a0404040400ULL, 0x401a200100410014ULL, 54},
    {0x0008760808080800ULL, 0x0005021000a30009ULL, 54},
    {0x00106e1010101000ULL, 0x0218000509010010ULL, 54},
    {0x00205e2020202000ULL, 0x4000400410080120ULL, 54},
    {0x00403e4040404000ULL, 0x0000020801040010ULL, 54},
    {0x00807e8080808000ULL, 0x0029040040820011ULL, 53},
    {0x007e010101010100ULL, 0x4080400024800280ULL, 53},
    {0x007c020202020200ULL, 0x0500200040100440ULL, 54},
    {0x007a040404040400ULL, 0x2880142001004100ULL, 54},
    {0x0076080808080800ULL, 0x412020400a001200ULL, 54},
    {0x006e101010101000ULL, 0x018c028004080080ULL, 54},
    {0x005e202020202000ULL, 0x0884001020080401ULL, 54},
    {0x003e404040404000ULL, 0x0000210810420400ULL, 54},
    {0x007e808080808000ULL, 0x0801048745040200ULL, 53},
    {0x7e01010101010100ULL, 0x4401002040120082ULL, 52},
    {0x7c02020202020200ULL, 0x0000408200210012ULL, 53},
    {0x7a04040404040400ULL, 0x0000110008200441ULL, 53},
    {0x7608080808080800ULL, 0x2010002004100901ULL, 53},
    {0x6e10101010101000ULL, 0x0801000800040211ULL, 53},
    {0x5e20202020202000ULL, 0x480d000400820801ULL, 53},
    {0x3e40404040404000ULL, 0x0820104201280084ULL, 53},
    {0x7e80808080808000ULL, 0x1001040311802142ULL, 52}};

int RBits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12};

int BBits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6};

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

// precompute all attacks and save them to 
void precomputeAllAttacks(void)
{
}

//TODO: make pawn, king, and knight precompute functions write to file for copying 
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
