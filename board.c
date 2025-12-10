#include "board.h"

U64 getAllPieces(const Board *board)
{
    return board->pieces[nWhite] | board->pieces[nBlack];
}

U64 getColorPieces(const Board *board, enumPiece color)
{
    return board->pieces[color];
}

// returns bitboard of all pieces of given type regardless of color
U64 getPieceTypePieces(const Board *board, enumPiece pieceType)
{
    return board->pieces[pieceType ];
}

// returns bitboard of all pieces of given type and color
U64 getSpecificColorPieces(const Board *board, enumPiece color, enumPiece pieceType)
{
    return board->pieces[color] & board->pieces[pieceType];
}

Board *initBoard(const char *fen)
{
    Board board; 

    //starting from the top right, if the char is a number, skip that many squares
    // if its a /, move to next rank
    // if its a letter, place the corresponding piece on that square
    //uppercase white lowercase black 

    for (int rank= 7; rank >=0; rank--) {
        
    }
    return &board;
}
