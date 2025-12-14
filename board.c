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
        printf("%d| ", rank + 1);
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
void printChessBoard(Board *board)
{
    char possible[] = {'p', 'n', 'b', 'r', 'q', 'k'};
    U64 empty = ~getAllPieces(board);
    for (int rank = 7; rank >= 0; rank--)
    {
        printf("%d| ", rank + 1);
        for (int file = 0; file < 8; file++)
        {
            enumSquare square = rank * 8 + file;
            U64 bit = 1ULL << square;

            if (bit & empty)
            {
                printf(". ");
                continue;
            }

            U64 isWhite = board->pieces[nWhite] & bit;

            char c = 'x';
            for (int i = 2; i < 8; i++)
            {
                if (bit & board->pieces[i])
                {
                    c = possible[i - 2];
                    break;
                }
            }

            assert(c != 'x' && "Each character printed should have a relevant value");

            // white is upper
            c = isWhite != 0 ? (char)toupper(c) : c;

            printf("%c ", c);
        }
        printf("\n");
    }
    printf("   _ _ _ _ _ _ _ _ \n");
    printf("   a b c d e f g h \n");
}
void printBoardDetails(Board *board)
{
    puts("All Pieces");
    printChessBoard(board);

    printf("White to move: %d\n", board->whiteToMove);
    printf("Castling Rights: %d\n", board->castlingRights);
    printf("En Passant Square: %d\n", board->enPassantSquare);
    printf("Half Move Clock: %d\n", board->halfmoveClock);
    printf("Full Move Counter: %d\n", board->fullmoveNumber);
}
void translateSquareToAlgebraic(enumSquare square, char *buffer)
{
    int file = square % 8;
    int rank = (int)square / 8;

    buffer[0] = (char)('a' + file);
    buffer[1] = (char)('1' + rank);
    buffer[2] = '\0';
}
char *readPiecesFromFen(Board *board, char *fen)
{
    // initialize all bbs to 0
    for (int i = 0; i < 8; ++i)
    {
        board->pieces[i] = 0;
    }

    int rank = 7;
    int file = 0;

    while (*fen != ' ')
    {
        char c = *fen;

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

        fen++;
    }
    fen++; // going onto next word
    return fen;
}

char *readSideToMoveFromFen(Board *board, char *fen)
{
    board->whiteToMove = tolower(*fen) == 'w';
    fen += 2;
    return fen;
}
char *readFromCastlingRights(Board *board, char *fen)
{
    board->castlingRights = 0; // make sure it's initialized

    if (*fen == '-')
    {
        fen += 2;
        return fen;
    }

    while (*fen != ' ')
    {
        char c = *fen;
        switch (c)
        {
        case 'K':
            board->castlingRights |= W_K_CASTLE;
            break;
        case 'Q':
            board->castlingRights |= W_Q_CASTLE;
            break;
        case 'k':
            board->castlingRights |= B_K_CASTLE;
            break;
        case 'q':
            board->castlingRights |= B_Q_CASTLE;
            break;
        default:
            printf("Error parsing castling rights: %c\n", c);
            abort();
        }
        fen++;
    }

    fen++;

    return fen;
}
char *readEnPassantFromFen(Board *board, char *fen)
{
    if (*fen == '-')
    {
        fen += 2;
        return fen;
    }

    // first char should be a letter
    char file = *fen;
    if (!isalpha(file))
    {
        puts("Have to put enpassant in this format: a3 , E8, - (if no en passant)");
        abort();
    }

    int fileVal = tolower(file) - 'a';

    fen++;
    char rank = *fen;
    if (!isdigit(rank))
    {
        puts("Have to put enpassant in this format: a3 , E8, - (if no en passant)");
        abort();
    }

    int rankVal = rank - '0' - 1; // bring the range to 0-7

    board->enPassantSquare = (enumSquare)(rankVal * 8 + fileVal);

    fen += 2;
    return fen;
}
char *readHalfMoveClockFromFen(Board *board, char *fen)
{
    char c = *fen;

    if (!isdigit(c))
    {
        puts("Error. Have to enter a digit for halfmove clock");
        abort();
    }

    board->halfmoveClock = (unsigned short)atoi(fen); // get the first number string

    // could be a variable amount of digits
    while (*fen != ' ')
    {
        fen++;
    }
    fen++;

    return fen;
}
void readFullMoveClockFromFen(Board *board, char *fen)
{
    char c = *fen;

    if (!isdigit(c))
    {
        puts("Error. Have to enter a digit for fullmove number");
        abort();
    }

    board->fullmoveNumber = (unsigned short)atoi(fen); // get first number string

    // dnt increment to avoid undefined behavior
}
static void initMailbox ( Board * board){
    for (int sq = 0; sq < 64; sq++)
    {
        board->mailbox[sq] = nWhite; // if it doesn't hold a valid piece type it's empty
    }
    for (enumPiece piece = nPawn; piece <= nKing; piece++)
    {
        U64 bb = board->pieces[piece];
        while (bb)
        {
            int sq = __builtin_ctzll(bb);
            board->mailbox[sq] = piece;
            bb &= bb - 1;
        }
    }
}
void initBoard(Board *board, char *fen)
{

    char *curr = fen; // copy fen

    // now at side to move
    curr = readPiecesFromFen(board, curr);

    // if empty the format is weird
    assert(curr != NULL && "fen is empty after reading pieces");

    curr = readSideToMoveFromFen(board, curr);

    assert(curr != NULL && "fen is empty after reading side");

    curr = readFromCastlingRights(board, curr);

    assert(curr != NULL && "fen is empty after reading castling");

    curr = readEnPassantFromFen(board, curr);

    assert(curr != NULL && "fen is empty after reading en passant");

    curr = readHalfMoveClockFromFen(board, curr);

    assert(curr != NULL && "fen is empty after reading half move clock");

    readFullMoveClockFromFen(board, curr);

    initMailbox(board) ; 
}

void initStandardChess(Board* board){
    char *fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    initBoard(board, fen); 
} 