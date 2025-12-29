#include "searching.h"

//searches and sets board's best move for that position 
double alphaBeta(Board *board, int depth, double alpha, double beta) {
    if (board->historyPly >= MAX_SEARCH_DEPTH - 10) { // Leave some margin
        return evaluate(board);                       // Emergency exit
    }
    
    if (depth <= 0) 
        return evaluate(board); 

    // for all legal moves
    Move move_list[MAX_MOVES];
    size_t numMoves = 0;
    //TODO: research move ordering to make this search more efficient
    getPseudoLegalMoves(board, move_list, &numMoves);
    enumPiece currSide = board->whiteToMove ? nWhite : nBlack;

    for (size_t i = 0; i < numMoves; i++) {
       
        makeMove(board, move_list[i]);

        if (!isSideInCheck(board, currSide)) { // legal move
            
            double score = -alphaBeta(board, depth - 1, -beta , -alpha);
            
            unmakeMove(board, move_list[i]); // unmake move before returning 
            
            if(score>= beta)
                return beta; // opponent wouldn't allow move so return 

            if(score > alpha)
                alpha = score;

        }else{ // unmake illegal move 
            unmakeMove(board, move_list[i]);
        }
        
    }
    return alpha; 
}

Move getBestMove(Board *board, int depth) {
    Move move_list[MAX_MOVES];
    size_t numMoves = 0;
    getPseudoLegalMoves(board, move_list, &numMoves);
    enumPiece currSide = board->whiteToMove ? nWhite : nBlack;
    
    Move bestMove = 0;  // or some invalid move constant
    double bestScore = -INFINITY;  // or some very negative value
    
    for (size_t i = 0; i < numMoves; i++) {
        makeMove(board, move_list[i]);
        
        if (!isSideInCheck(board, currSide)) {
            double score = -alphaBeta(board, depth - 1, -INFINITY, INFINITY);
            unmakeMove(board, move_list[i]);
            
            if (score > bestScore) {
                bestScore = score;
                bestMove = move_list[i];
            }
        } else {
            unmakeMove(board, move_list[i]);
        }
    }
    
    return bestMove;
}