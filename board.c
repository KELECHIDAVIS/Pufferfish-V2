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
    return board->pieces[pieceType];
}

// returns bitboard of all pieces of given type and color
U64 getSpecificColorPieces(const Board *board, enumPiece color, enumPiece pieceType)
{
    return board->pieces[color] & board->pieces[pieceType];
}

void addPiece(Board *board, enumPiece color, enumPiece pieceType, enumSquare square)
{
    U64 bit = 1ULL << square;
    board->pieces[color] |= bit;
    board->pieces[pieceType] |= bit;
}
void printBB(U64 bb)
{
    for (int rank = 7; rank >= 0; rank--)
    {
        printf("%d| ", rank+1);
        for (int file = 0; file < 8; file++)
        {
            enumSquare square = rank * 8 + file;
            U64 bit = 1ULL << square;
            if (bb & bit)
            {
                printf("1 ");
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("   _ _ _ _ _ _ _ _ \n");
    printf("   a b c d e f g h \n");
}
// prints corresponding characters at each spot 
void printChessBoard(Board *board ){
    char possible[] = {'p', 'n', 'b', 'r', 'q', 'k'};
    for (int rank = 7; rank >= 0; rank--)
    {
        printf("%d| ", rank+1);
        for (int file = 0; file < 8; file++)
        {
            enumSquare square = rank * 8 + file;
            U64 bit = 1ULL << square;

            if (bit & ~getAllPieces(board) ) {
                printf(". "); 
                continue; 
            }

            U64 isWhite= board->pieces[nWhite] & bit ; 

            char c = 'x';  
            for (int i=2; i < 8; i++){
                if (bit & board->pieces[i]){
                    c= possible[i] ;
                    break; 
                }
            }
            
            assert (c != 'x' && "Each character printed should have a relevant value"); 
            
            // white is upper 
            c  = isWhite ? toupper(c) : c ; 

            printf("%c ", c ); 
        }
        printf("\n");
    }
    printf("   _ _ _ _ _ _ _ _ \n");
    printf("   a b c d e f g h \n");
}
void initBoard(Board *board, char *fen)
{
    // initialize all bbs to 0 
    for (int i = 0; i < 8; ++i){
        board -> pieces[i] =0;
    }

    // starting from the top right, if the char is a number, skip that many squares
    //  if its a /, move to next rank
    //  if its a letter, place the corresponding piece on that square
    // uppercase white lowercase black
    char *curr = fen;
    int rank = 7;
    int file = 0;
    while (*curr != ' ')
    {
        char c = *curr;


        if (c == '/')
        {
            rank--;
            file = 0;
        }
        else if (isalpha(c))
        {
            if (!(file < 8 && file >= 0 && rank >= 0 && rank < 8))
            {
                printf("Error with out of bounds in FEN parsing should be between [0-7]: file %d rank %d\n", file, rank);
                abort();
            }
            enumPiece pieceType;
            enumPiece color;
            switch (tolower(c))
            {
            case 'p':
                pieceType = nPawn;
                break;
            case 'n':
                pieceType = nKnight;
                break;
            case 'b':
                pieceType = nBishop;
                break;
            case 'r':
                pieceType = nRook;
                break;
            case 'q':
                pieceType = nQueen;
                break;
            case 'k':
                pieceType = nKing;
                break;
            default:
                printf("Error parsing FEN: invalid piece char %c\n", c);
                abort();
            }
            if (isupper(c))
            {
                color = nWhite;
            }
            else
            {
                color = nBlack;
            }
            enumSquare square = (rank * 8 + file);

            addPiece(board, color, pieceType, square);

            file++;
        }
        else if (isdigit(c))
        {
            int emptySquares = c - '0';
            file += emptySquares;
        }

        curr++;
    }
    
}
