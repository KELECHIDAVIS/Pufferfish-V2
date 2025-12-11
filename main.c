#include "board.h"

int main(){

    
    Board board;
    initBoard(&board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR ");

    printChessBoard(&board);
    return 0;
}
