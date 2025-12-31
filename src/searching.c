#include "searching.h"

// --- Configuration ---
// 64MB is safe for Heroku's 512MB limit
#define TT_SIZE_MB 64
#define MATE_BOUND (MATE_SCORE - MAX_SEARCH_DEPTH)

SearchInfo searchInfo;
TTEntry *transTable = NULL;
size_t ttEntryCount = 0;

// --- Helper: Normalize Mate Scores ---
// Converts "Mate at absolute ply X" to "Mate in N moves (infinite reference)"
static int scoreToTT(int score, int ply) {
    if (score > MATE_BOUND)
        return score + ply;
    if (score < -MATE_BOUND)
        return score - ply;
    return score;
}

// Converts "Mate in N moves" back to "Mate at absolute ply X" for the current search
static int scoreFromTT(int score, int ply) {
    if (score > MATE_BOUND)
        return score - ply;
    if (score < -MATE_BOUND)
        return score + ply;
    return score;
}

// --- Memory Management ---
void initTransTable(void) {
    if (transTable != NULL)
        free(transTable);

    // Calculate entries based on MB size
    ttEntryCount = (TT_SIZE_MB * 1024 * 1024) / sizeof(TTEntry);

    // Use calloc to zero the memory (prevents garbage bugs)
    transTable = (TTEntry *)calloc(ttEntryCount, sizeof(TTEntry));

    if (transTable == NULL) {
        fprintf(stderr, "CRITICAL: Failed to allocate Transposition Table!\n");
        exit(1);
    }

    fprintf(stderr, "TT Initialized: %d MB (%zu entries)\n", TT_SIZE_MB, ttEntryCount);
}

void clearTransTable(void) {
    if (transTable != NULL) {
        memset(transTable, 0, ttEntryCount * sizeof(TTEntry));
    }
}

void freeTransTable(void) {
    if (transTable != NULL) {
        free(transTable);
        transTable = NULL;
    }
}

// --- TT Access ---
bool probeTransTable(Board *board, int depth, int alpha, int beta,
                     int *score, Move *bestMove) {
    if (transTable == NULL)
        return false;

    size_t index = board->zobristKey % ttEntryCount;
    TTEntry *entry = &transTable[index];

    // Check for hash collision
    if (entry->zobristKey != board->zobristKey) {
        return false;
    }

    // Always provide the best move for move ordering!
    if (bestMove != NULL) {
        *bestMove = entry->bestMove;
    }

    // We can only cut off if the stored depth is >= current required depth
    if (entry->depth < depth) {
        return false;
    }

    // Convert stored score to be relative to current ply
    int ttScore = scoreFromTT(entry->eval, board->historyPly);

    switch (entry->type) {
    case TT_EXACT:
        *score = ttScore;
        return true;
    case TT_BETA:
        if (ttScore >= beta) {
            *score = beta;
            return true;
        }
        break;
    case TT_ALPHA:
        if (ttScore <= alpha) {
            *score = alpha;
            return true;
        }
        break;
    }

    return false;
}

void storeTransTable(Board *board, int depth, int score,
                     TTType type, Move bestMove) {
    if (transTable == NULL)
        return;

    size_t index = board->zobristKey % ttEntryCount;
    TTEntry *entry = &transTable[index];

    // Depth-Preferred Replacement Strategy
    if (entry->zobristKey == 0 ||
        entry->zobristKey == board->zobristKey ||
        depth >= entry->depth) {

        entry->zobristKey = board->zobristKey;
        // Normalize score before storing
        entry->eval = scoreToTT(score, board->historyPly);
        entry->depth = depth;
        entry->type = type;
        entry->bestMove = bestMove;
    }
}

bool isRepetition(const Board *board) {
    // start 2 plies back (previous time we moved)
    // we stop if we go past the history or past the last irreversible move (halfmoveClock)
    for (int i = 2; i <= board->halfmoveClock && i < board->historyPly; i += 2) {

        // Compare current key with history
        if (board->historyArr[board->historyPly - i].zobristKey == board->zobristKey) {
            return true;
        }
    }
    return false;
}

// --- Search Implementation ---

void initSearch(int timeMs) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    searchInfo.startTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    searchInfo.allocatedTime = timeMs;
    searchInfo.timeUp = false;
}

int getElapsedTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long current = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (int)(current - searchInfo.startTime);
}

bool shouldStop() {
    if (searchInfo.timeUp)
        return true;

    // Check time every 2048 nodes to reduce overhead
    static int checkCounter = 0;
    if ((++checkCounter & 2047) == 0) {
        if (getElapsedTime() >= searchInfo.allocatedTime) {
            searchInfo.timeUp = true;
            return true;
        }
    }
    return false;
}

static uint64_t nodeCount = 0;

// https://www.chessprogramming.org/Quiescence_Search
int quiessence (Board *board, int alpha, int beta) {
    int static_eval = evaluate(board);

    // Stand Pat
    int best_value = static_eval;
    if (best_value >= beta)
        return best_value;

    // delta pruning: test if alpha can be improved by the greatest possible material swing (capturing a queen or promoting a pawn)
    // if we are so below alpha that even capturing a queen/promotion won't help then just return alpha 
    int BIG_DELTA = 900; // Value of a Queen
    enumPiece currSide = board->whiteToMove ? nWhite : nBlack;

    if (canSidePromote(board, currSide)){
        BIG_DELTA+=775 ; // replace pawn with queen 
    }

    if (static_eval < alpha - BIG_DELTA) {
        return alpha;
    }

    if (best_value > alpha)
        alpha = best_value;

    // search every capture to make sure last move didn't put the side in peril
    Move move_list[MAX_MOVES];
    size_t numMoves = 0;
    getPseudoLegalMoves(board, move_list, &numMoves);
    sortMoveList(board, move_list, numMoves); // sort so captures are usually near top


    for (size_t i = 0; i < numMoves; i++) {
        unsigned int flags = getFlags(move_list[i]);

        if (!(isCapture(move_list[i])))
            continue;

        makeMove(board, move_list[i]);

        if (!isSideInCheck(board, currSide)) {
            int score = -quiessence(board, -beta, -alpha);
            unmakeMove(board, move_list[i]);

            if (score >= beta)
                return score;
            if (score > best_value)
                best_value = score;
            if (score > alpha)
                alpha = score;
        } else {

            unmakeMove(board, move_list[i]); // unmake illegal move
        }
    }

    return best_value;
}

int alphaBeta(Board *board, int depth, int alpha, int beta) {
    int alphaOrig = alpha;
    nodeCount++;

    // Periodically check for timeout
    if (shouldStop())
        return 0;

    // Max depth safety check (matches your board.h define)
    if (board->historyPly >= MAX_SEARCH_DEPTH - 1) {
        return quiessence(board, alpha, beta);
    }

    // 50-move rule
    if (board->halfmoveClock >= 100) {
        return DRAW_SCORE;
    }

    // if the state was repeated before, through perfect play the opp can draw out a 3-fold-repetition
    if (isRepetition(board)) {
        return DRAW_SCORE;
    }

    // 1. Probe Transposition Table
    int ttScore;
    Move ttMove = 0;
    if (probeTransTable(board, depth, alpha, beta, &ttScore, &ttMove)) {
        return ttScore;
    }

    if (depth <= 0) {
        return quiessence(board, alpha, beta);
    }

    // 2. Generate Moves
    Move move_list[MAX_MOVES];
    size_t numMoves = 0;
    getPseudoLegalMoves(board, move_list, &numMoves);

    // 3. Score Moves (Your existing logic)
    // We prioritize the move from the TT if it exists
    sortMoveList(board, move_list, numMoves);

    // Explicitly move TT best-move to front if sortMoveList didn't handle it
    if (ttMove != 0) {
        for (size_t i = 0; i < numMoves; i++) {
            if (move_list[i] == ttMove) {
                // Simple swap to index 0
                Move temp = move_list[0];
                move_list[0] = ttMove;
                move_list[i] = temp;
                break;
            }
        }
    }

    enumPiece currSide = board->whiteToMove ? nWhite : nBlack;
    size_t legalMoveCount = 0;
    Move bestMove = 0;

    // 4. Iterate Moves
    for (size_t i = 0; i < numMoves; i++) {
        makeMove(board, move_list[i]);

        if (!isSideInCheck(board, currSide)) {
            legalMoveCount++;

            int score = -alphaBeta(board, depth - 1, -beta, -alpha);

            unmakeMove(board, move_list[i]);

            if (searchInfo.timeUp)
                return 0;

            if (score >= beta) {
                // Fail-High (Beta Cutoff)
                storeTransTable(board, depth, beta, TT_BETA, move_list[i]);
                return beta;
            }

            if (score > alpha) {
                // PV-Node (Improved Alpha)
                alpha = score;
                bestMove = move_list[i];
            }
        } else {
            unmakeMove(board, move_list[i]);
        }
    }

    // 5. Checkmate / Stalemate
    if (legalMoveCount == 0) {
        if (isSideInCheck(board, currSide)) {
            // Your format: -MATE + Ply (Absolute score)
            // TT Helper will convert this to stored format automatically
            return -MATE_SCORE + board->historyPly;
        } else {
            return DRAW_SCORE;
        }
    }

    // 6. Store Result
    if (alpha > alphaOrig) {
        storeTransTable(board, depth, alpha, TT_EXACT, bestMove);
    } else {
        storeTransTable(board, depth, alpha, TT_ALPHA, bestMove);
    }

    return alpha;
}

Move getBestMove(Board *board, int maxTimeMs) {
    Move bestMove = 0;
    int bestScore = -MATE_SCORE;

    nodeCount = 0;
    initSearch(maxTimeMs);

    // clearTransTable(); // Optional: Clear if you want fresh search every move

    fprintf(stderr, "Search Start: %dms limit\n", maxTimeMs);

    // Iterative Deepening
    for (int depth = 1; depth <= MAX_SEARCH_DEPTH; depth++) {

        int score = alphaBeta(board, depth, -MATE_SCORE, MATE_SCORE);

        if (searchInfo.timeUp) {
            fprintf(stderr, "Time Up at Depth %d\n", depth);
            break;
        }

        // Try to get the Best Move from TT for this depth
        // This is safer than relying on variables inside the loop
        TTEntry *entry = &transTable[board->zobristKey % ttEntryCount];
        if (entry->zobristKey == board->zobristKey && entry->bestMove != 0) {

            // validating that the move retrieved was a legal one
            Move moveList[MAX_MOVES];
            size_t numMoves = 0;
            getPseudoLegalMoves(board, moveList, &numMoves);
            enumPiece currSide = board->whiteToMove ? nWhite : nBlack;
            bool isLegal = false;
            for (size_t i = 0; i < numMoves; i++) {
                if (moveList[i] == entry->bestMove) {
                    // Check if move is actually legal (not leaving king in check)
                    makeMove(board, moveList[i]);
                    if (!isSideInCheck(board, currSide)) {
                        isLegal = true;
                    }
                    unmakeMove(board, moveList[i]);
                    break;
                }
            }

            if (isLegal) {
                bestMove = entry->bestMove;
                bestScore = score;
            }
        }

        int elapsed = getElapsedTime();
        fprintf(stderr, "Depth %d: Score %d, Nodes %llu, Time %dms\n",
                depth, score, (unsigned long long)nodeCount, elapsed);

        // Stop early if forced mate found
        if (score > MATE_BOUND || score < -MATE_BOUND)
            break;
    }

    return bestMove;
}