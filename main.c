#include "board.h"

int main()
{
    Board board;
    initBoard(&board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    // puts("\nAll Pieces:");
    // printBB(getAllPieces(&board));

    puts("\nWhite Pieces:");
    U64 whitePieces = getColorPieces(&board, nWhite);
    //assert ((board.pieces[nWhite] & 0x000000000000FFFF) != 0);
    printBB(whitePieces);

    // puts("\nBlack Pieces:");
    // printBB(getColorPieces(&board,nBlack));

    // puts("\nPawns:");
    // printBB( getPieceTypePieces(&board, nPawn) );

    // puts("\nKnights:");
    // printBB( getPieceTypePieces(&board, nKnight) );

    // puts("\nBishops:");
    // printBB( getPieceTypePieces(&board, nBishop) );
    // puts("\nRooks:");
    // printBB( getPieceTypePieces(&board, nRook) );
    // puts("\nQueens:");
    // printBB( getPieceTypePieces(&board, nQueen) );
    // puts("\nKings:");
    // printBB( getPieceTypePieces(&board, nKing) );

    return 0;
}
