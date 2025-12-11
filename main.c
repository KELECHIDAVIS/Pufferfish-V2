#include "board.h"

int main(){
    
    
    char fen1[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; 
    char fen2[] = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"; 
    char fen3[] = "4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0 1"; 

     
    Board board1;
    initBoard(&board1, fen1 );

    Board board2;
    initBoard(&board2, fen2 );

    Board board3;
    initBoard(&board3, fen3);

    puts("Board 1 details: "); 
    printBoardDetails(&board1); 
    puts("Board 2 details: "); 
    printBoardDetails(&board2); 
    puts("Board 3 details: "); 
    printBoardDetails(&board3); 
    return 0;
}