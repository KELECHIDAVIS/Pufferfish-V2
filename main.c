#include "board.h"

int main(){
    
    puts("Starting debug"); 
    Board board;
    initBoard(&board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR ");

    puts("\nAll Pieces:");
    printBB(getAllPieces(&board));

    // coming out of the initialization , the white board is set to zero 
    puts("\nWhite Pieces:");
    U64 whitePieces = getColorPieces(&board, nWhite);
    printBB(whitePieces);

    puts("\nBlack Pieces:");
    printBB(getColorPieces(&board,nBlack));

    puts("\nPawns:");
    printBB( getPieceTypePieces(&board, nPawn) );

    puts("\nKnights:");
    printBB( getPieceTypePieces(&board, nKnight) );

    puts("\nBishops:");
    printBB( getPieceTypePieces(&board, nBishop) );
    puts("\nRooks:");
    printBB( getPieceTypePieces(&board, nRook) );
    puts("\nQueens:");
    printBB( getPieceTypePieces(&board, nQueen) );
    puts("\nKings:");
    printBB( getPieceTypePieces(&board, nKing) );

    return 0;
}
