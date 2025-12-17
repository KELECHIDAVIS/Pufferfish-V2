#ifndef PERFT_H
#define PERFT_H

#include "board.h"
#include "moves.h"  

// return total number of unique positions reachable from given board position at given depth
extern U64 perft(Board *board, int depth, U64 *captures, U64 *ep, U64 *castles, U64 *promotions, U64 *checks, U64 *checkmates);

// debug version that prints move counts at each depth
extern U64 divide(Board *board, int depth, U64 *captures, U64 *ep, U64 *castles, U64 *promotions, U64 *checks, U64 *checkmates);

#endif // PERFT_H