#ifndef MOVES_H
#define MOVES_H

#include "board.h"

extern U64 KNIGHT_ATTACK_LOOKUP[64]; // precomputed knight attacks for each square

extern void precomputeKnightAttacks();
extern void printKnightAttacks();
extern U64 getKnightAttacks (enumSquare square); // returns knight pattern from square 


#endif //MOVES_H