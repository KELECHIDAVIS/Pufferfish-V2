#include "moves.h"

U64 KNIGHT_ATTACK_LOOKUP[64];

U64 noNoEa(U64 b) { return (b << 17) & ~FILE_A; }
U64 noEaEa(U64 b) { return (b << 10) & ~(FILE_A |FILE_B) ; }
U64 soEaEa(U64 b) { return (b >> 6) & ~(FILE_A | FILE_B); }
U64 soSoEa(U64 b) { return (b >> 15) & ~FILE_A; }
U64 noNoWe(U64 b) { return (b << 15) &  ~FILE_H; }
U64 noWeWe(U64 b) { return (b << 6) & ~(FILE_G | FILE_H); }
U64 soWeWe(U64 b) { return (b >> 10) & ~(FILE_G | FILE_H); }
U64 soSoWe(U64 b) { return (b >> 17) & ~FILE_H; }

void precomputeKnightAttacks()
{
    for( int square = 0 ; square <64 ; square++){
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

void printKnightAttacks()
{
    for( int square = 0 ; square < 64 ; square++){
        printf("Knight attacks from square %d:\n", square);
        printBB(KNIGHT_ATTACK_LOOKUP[square]);
    }
}

U64 getKnightAttacks(enumSquare square)
{
    square++; 
    return 0ULL; 
}

void getKnightMoves(Board *board, Move *moveList, size_t *numMoves)
{
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 knights = getSpecificColorPieces(board, side , nKnight); 
   
    //TODO: remove this placeholder code
    moveList[0] = 0;
    *numMoves = 0;
    // TODO: remove this placeholder code


    while( knights ){
        //U64 pos = LSBIT(knights);
        knights = CLEARLSBIT(knights);
    }
}
void getLegalMoves(Board *board, Move *moveList, size_t *numMoves)
{

    //getPawnMoves(board, moveList, numMoves);
    getKnightMoves(board, moveList, numMoves);
    //getBishopMoves(board, moveList, numMoves);
    //getRookMoves(board, moveList, numMoves);
    //getQueenMoves(board, moveList, numMoves);
    //getKingMoves(board, moveList, numMoves);

}
