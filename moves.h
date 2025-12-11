#ifndef MOVES_H
#define MOVES_H

#include "board.h"

U64 arrKnightAttacks[64];

extern void precomputeKnightAttacks();
extern 
U64 getKnightAttacks (enumSquare square); // returns knight pattern from square 


#endif //MOVES_H