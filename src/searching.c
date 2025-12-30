#include "searching.h"
#include <sys/time.h>

SearchInfo searchInfo;

void initSearch(int timeMs) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    searchInfo.startTime = tv.tv_sec * 1000 + tv.tv_usec / 1000; // Convert to ms
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
    if (getElapsedTime() >= searchInfo.allocatedTime) {
        searchInfo.timeUp = true;
        return true;
    }
    return false;
}

static uint64_t nodeCount = 0;

// searches and sets board's best move for that position
double alphaBeta(Board *board, int depth, double alpha, double beta) {

    nodeCount++;

    // Check time:
    // 1. At higher depths (cheap since few nodes)
    // 2. Every 2048 nodes at lower depths (where most time is spent)
    if (depth >= 4 || (nodeCount & 2047) == 0) {
        if (shouldStop()) {
            return evaluate(board);
        }
    }

    if (board->historyPly >= MAX_SEARCH_DEPTH - 10) { // Leave some margin
        return evaluate(board);                       // Emergency exit
    }

    if (depth <= 0)
        return evaluate(board);

    // Check for draw by fifty-move rule
    if (board->halfmoveClock >= 100) {
        return DRAW_SCORE;
    }
    // for all legal moves
    Move move_list[MAX_MOVES];
    size_t numMoves = 0;

    // get psuedo legal moves and sort them
    getPseudoLegalMoves(board, move_list, &numMoves);
    sortMoveList(board, move_list, numMoves);

    enumPiece currSide = board->whiteToMove ? nWhite : nBlack;
    size_t legalMoveCount = 0;

    for (size_t i = 0; i < numMoves; i++) {

        makeMove(board, move_list[i]);

        if (!isSideInCheck(board, currSide)) { // legal move
            legalMoveCount++;
            double score = -alphaBeta(board, depth - 1, -beta, -alpha);

            unmakeMove(board, move_list[i]); // unmake move before returning

            if (score >= beta)
                return beta; // opponent wouldn't allow move so return

            if (score > alpha)
                alpha = score;

        } else { // unmake illegal move
            unmakeMove(board, move_list[i]);
        }
    }

    // No legal moves found - check for checkmate or stalemate
    if (legalMoveCount == 0) {
        if (isSideInCheck(board, currSide)) {
            // Checkmate: return a mate score adjusted by depth
            // This makes the engine prefer shorter mates
            return -MATE_SCORE + board->historyPly;
        } else {
            // Stalemate: it's a draw
            return DRAW_SCORE;
        }
    }

    return alpha; // alpha being returned is probably neg inifinity
}

Move getBestMove(Board *board, int maxTimeMs) {
    Move bestMove = 0;
    double bestScore = -INFINITY;

    nodeCount = 0;
    initSearch(maxTimeMs);

    fprintf(stderr, "Starting search with %dms allocated\n", maxTimeMs);
    fflush(stderr);

    int maxDepth = 10; // Reasonable hard limit

    // iterative deepening
    for (int depth = 1; depth < maxDepth && depth < MAX_SEARCH_DEPTH; depth++) {
        Move move_list[MAX_MOVES];
        size_t numMoves = 0;

        getPseudoLegalMoves(board, move_list, &numMoves);
        sortMoveList(board, move_list, numMoves);

        enumPiece currSide = board->whiteToMove ? nWhite : nBlack;

        Move iterationBestMove = 0;
        double iterationBestScore = -INFINITY;
        bool completedDepth = true;

        for (size_t i = 0; i < numMoves; i++) {
            makeMove(board, move_list[i]);

            if (!isSideInCheck(board, currSide)) {
                double score = -alphaBeta(board, depth - 1, -INFINITY, INFINITY);
                unmakeMove(board, move_list[i]);

                if (searchInfo.timeUp) {
                    completedDepth = false;
                    break;
                }

                if (score > iterationBestScore) {
                    iterationBestScore = score;
                    iterationBestMove = move_list[i];
                }
            } else {
                unmakeMove(board, move_list[i]); // unmake illegal move
            }
        }

        if (completedDepth && iterationBestMove) {
            bestMove = iterationBestMove;
            bestScore = iterationBestScore;

            int elapsed = getElapsedTime();
            fprintf(stderr, "Completed depth %d in %dms (score: %.0f)\n",
                    depth, elapsed, bestScore);
            fflush(stderr);
        }

        if (searchInfo.timeUp) {
            fprintf(stderr, "Time up at depth %d\n", depth);
            fflush(stderr);
            break;
        }

        if (bestScore > MATE_SCORE - 100) {
            fprintf(stderr, "Found mate, stopping search\n");
            fflush(stderr);
            break;
        }
    }

    fprintf(stderr, "Returning move after %dms, searched %llu nodes\n",
            getElapsedTime(), nodeCount);
    fflush(stderr);

    return bestMove;
}