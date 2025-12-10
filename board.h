#ifndef BOARD_H 
#define BOARD_H

typedef unsigned long long U64;

typedef struct {
    // going w a dense representation the holds colors in first 2 then piece types in the following 6 
    U64 pieces[8]={0}; // nWhite, nBlack, nPawn, nKnight, nBishop, nRook, nQueen, nKing
} Board;

typedef enum{
    nWhite, // any white piece
    nBlack, // any black piece
    nPawn,
    nKnight,
    nBishop,
    nRook,
    nQueen,
    nKing
} enumPiece;

extern U64 getAllPieces(const Board* board);
extern U64 getColorPieces(const Board* board, enumPiece color);
extern U64 getPieceTypePieces(const Board* board, enumPiece pieceType);
extern U64 getSpecificColorPieces(const Board* board, enumPiece color, enumPiece pieceType);
extern Board* initBoard(char* fen); 

#endif // BOARD_H