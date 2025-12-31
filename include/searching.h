#ifndef SEARCH_H
#define SEARCH_H
#include "eval.h"
#include "moves.h"
#include "limits.h"

#include <stdbool.h>
#include <time.h>

#define DRAW_SCORE 0
#define MATE_SCORE 100000

typedef struct {
    time_t startTime;
    int allocatedTime; // in milliseconds
    bool timeUp;
} SearchInfo;

extern SearchInfo searchInfo; // Global search info

// https://www.chessprogramming.org/Transposition_Table
typedef enum {
    TT_EXACT, // PV-node: exact score
    TT_ALPHA, // All-node: upper bound (failed low)
    TT_BETA   // Cut-node: lower bound (failed high)
} TTType;

typedef struct {
    U64 zobristKey; // to verify if this is the same pos 
    int eval;        
    int depth;      // Depth searched
    TTType type;    
    Move bestMove;  // Best move found
} TTEntry;

#define TT_SIZE_MB 64
#define TT_SIZE ((TT_SIZE_MB * 1024 * 1024) / sizeof(TTEntry))

// transpoition table for searching
// since this table can be huge will dynamically allocate
extern TTEntry* SearchTransTable; // modulo zobrist by TT_SIZE to get index 

// Helper functions
void initSearch(int timeMs);
bool shouldStop();
int getElapsedTime();
extern int alphaBeta(Board* board, int depth , int alpha , int beta); 
extern Move getBestMove(Board* board, int depth );
extern void initTransTable(void);
extern void clearTransTable(void);
extern void freeTransTable(void);
extern bool probeTransTable(Board *board, int depth, int alpha, int beta,
                            int *score, Move *bestMove);
extern void storeTransTable(Board *board, int depth, int score,
                            TTType type, Move bestMove);

#endif //  SEARCH_H