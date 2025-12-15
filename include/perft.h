#ifndef PERFT_H
#define PERFT_H

#include "board.h"
#include "moves.h"  

// return total number of unique positions reachable from given board position at given depth
extern U64 perft(Board *board, int depth); 

// debug version that prints move counts at each depth
extern U64 divide(Board *board, int depth);

#endif // PERFT_H