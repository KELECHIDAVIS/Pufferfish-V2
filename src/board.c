#include "board.h"

void addPiece(Board *board, enumPiece color, enumPiece pieceType, enumSquare square) {
    U64 bit = 1ULL << square;
    board->pieces[color] |= bit;
    board->pieces[pieceType] |= bit;
    board->mailbox[square] = pieceType;
}
void printBB(U64 bb) {
    for (int rank = 7; rank >= 0; rank--) {
        printf("%d| ", rank + 1);
        for (int file = 0; file < 8; file++) {
            enumSquare square = rank * 8 + file;
            U64 bit = 1ULL << square;
            if (bb & bit) {
                printf("1 ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("   _ _ _ _ _ _ _ _ \n");
    printf("   a b c d e f g h \n");
}
// prints corresponding characters at each spot
void printChessBoard(const Board *board) {
    char possible[] = {'p', 'n', 'b', 'r', 'q', 'k'};
    U64 empty = ~getAllPieces(board);
    for (int rank = 7; rank >= 0; rank--) {
        printf("%d| ", rank + 1);
        for (int file = 0; file < 8; file++) {
            enumSquare square = rank * 8 + file;
            U64 bit = 1ULL << square;

            if (bit & empty) {
                printf(". ");
                continue;
            }

            U64 isWhite = board->pieces[nWhite] & bit;

            char c = 'x';
            for (int i = 2; i < 8; i++) {
                if (bit & board->pieces[i]) {
                    c = possible[i - 2];
                    break;
                }
            }

            //TODO: uncomment out after debugging 
            //  assert(c != 'x' && "Each character printed should have a relevant value");

            // white is upper
            c = isWhite != 0 ? (char)toupper(c) : c;

            printf("%c ", c);
        }
        printf("\n");
    }
    printf("   _ _ _ _ _ _ _ _ \n");
    printf("   a b c d e f g h \n");

#ifdef DEBUG
    puts("White Pieces");
    printBB(board->pieces[nWhite]);
    puts("Black Pieces");
    printBB(board->pieces[nBlack]);
    puts("Pawns");
    printBB(board->pieces[nPawn]);
    puts("Knights");
    printBB(board->pieces[nKnight]);
    puts("Bishops");
    printBB(board->pieces[nBishop]);
    puts("Rooks");
    printBB(board->pieces[nRook]);
    puts("Queens");
    printBB(board->pieces[nQueen]);
    puts("Kings");
    printBB(board->pieces[nKing]);
#endif
}
void getFEN(Board *board, char *fen) {
    int pos = 0;

    // 1. Piece placement
    for (int rank = 7; rank >= 0; rank--) {
        int emptySquares = 0;
        for (int file = 0; file < 8; file++) {
            enumSquare square = rank * 8 + file;
            U64 bit = 1ULL << square;

            // Check if there's a piece here
            U64 allPieces = getAllPieces(board);

            if (bit & allPieces) {
                // If we found a piece, first write any accumulated empty squares
                if (emptySquares > 0) {
                    fen[pos++] = (char)emptySquares + '0';
                    emptySquares = 0;
                }

                // Determine piece type and color
                char c = 'x';
                char possible[] = {'p', 'n', 'b', 'r', 'q', 'k'};
                for (int i = nPawn; i <= nKing; i++) {
                    if (bit & board->pieces[i]) {
                        c = possible[i - 2];
                        break;
                    }
                }
                if (bit & board->pieces[nWhite])
                    c = (char)toupper(c);
                fen[pos++] = c;
            } else {
                emptySquares++;
            }
        }
        if (emptySquares > 0)
            fen[pos++] = (char)emptySquares + '0';
        if (rank > 0)
            fen[pos++] = '/';
    }

    // 2. Side to move
    fen[pos++] = ' ';
    fen[pos++] = board->whiteToMove ? 'w' : 'b';

    // 3. Castling rights
    fen[pos++] = ' ';
    int startPos = pos;
    if (board->castlingRights & W_K_CASTLE)
        fen[pos++] = 'K';
    if (board->castlingRights & W_Q_CASTLE)
        fen[pos++] = 'Q';
    if (board->castlingRights & B_K_CASTLE)
        fen[pos++] = 'k';
    if (board->castlingRights & B_Q_CASTLE)
        fen[pos++] = 'q';
    if (pos == startPos)
        fen[pos++] = '-';

    // 4. En Passant Square
    fen[pos++] = ' ';
    // Note: To match Stockfish exactly, you'd only print this
    // if a capture is possible, but here we print the stored square.
    if (board->enPassantSquare >= a1 && board->enPassantSquare <= h8) {
        // if a current side pawn can capture the ep square then we should print it
        if (board->whiteToMove) {
            U64 pawnPos = board->enPassantSquare >> 9 | board->enPassantSquare >> 7;
            if (pawnPos & getSpecificColorPieces(board, nWhite, nPawn)) {
                char sqBuf[3];
                translateSquareToAlgebraic(board->enPassantSquare, sqBuf);
                fen[pos++] = sqBuf[0];
                fen[pos++] = sqBuf[1];
            } else {
                fen[pos++] = '-';
            }
        } else {
            U64 pawnPos = board->enPassantSquare << 9 | board->enPassantSquare << 7;
            if (pawnPos & getSpecificColorPieces(board, nBlack, nPawn)) {
                char sqBuf[3];
                translateSquareToAlgebraic(board->enPassantSquare, sqBuf);
                fen[pos++] = sqBuf[0];
                fen[pos++] = sqBuf[1];
            } else {
                fen[pos++] = '-';
            }
        }

    } else {
        fen[pos++] = '-';
    }

    // 5. Halfmove clock
    pos += sprintf(&fen[pos], " %d", board->halfmoveClock);

    // 6. Fullmove number
    pos += sprintf(&fen[pos], " %d", board->fullmoveNumber);

    fen[pos] = '\0';
}
void printBoardDetails(Board *board) {
    printChessBoard(board);

    char fenBuffer[128];
    getFEN(board, fenBuffer);

    printf("Fen: %s\n", fenBuffer);
}
void translateSquareToAlgebraic(enumSquare square, char *buffer) {
    int file = square % 8;
    int rank = (int)square / 8;

    buffer[0] = (char)('a' + file);
    buffer[1] = (char)('1' + rank);
    buffer[2] = '\0';
}
char *readPiecesFromFen(Board *board, char *fen) {
    // initialize all bbs to 0
    for (int i = 0; i < 8; ++i) {
        board->pieces[i] = 0;
    }

    int rank = 7;
    int file = 0;

    while (*fen != ' ') {
        char c = *fen;

        if (c == '/') {
            rank--;
            file = 0;
        } else if (isalpha(c)) {
            if (!(file < 8 && file >= 0 && rank >= 0 && rank < 8)) {
                printf("Error with out of bounds in FEN parsing should be between [0-7]: file %d rank %d\n", file, rank);
                abort();
            }
            enumPiece pieceType;
            enumPiece color;
            switch (tolower(c)) {
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
            if (isupper(c)) {
                color = nWhite;
            } else {
                color = nBlack;
            }
            enumSquare square = (rank * 8 + file);

            addPiece(board, color, pieceType, square);

            file++;
        } else if (isdigit(c)) {
            int emptySquares = c - '0';
            file += emptySquares;
        }

        fen++;
    }
    fen++; // going onto next word
    return fen;
}

char *readSideToMoveFromFen(Board *board, char *fen) {
    board->whiteToMove = tolower(*fen) == 'w';
    fen += 2;
    return fen;
}
char *readFromCastlingRights(Board *board, char *fen) {
    board->castlingRights = 0; // make sure it's initialized

    if (*fen == '-') {
        fen += 2;
        return fen;
    }

    while (*fen != ' ') {
        char c = *fen;
        switch (c) {
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
char *readEnPassantFromFen(Board *board, char *fen) {
    board->enPassantSquare = NO_SQUARE; // make invalid square

    if (*fen == '-') {
        fen += 2;
        return fen;
    }

    // first char should be a letter
    char file = *fen;
    if (!isalpha(file)) {
        puts("Have to put enpassant in this format: a3 , E8, - (if no en passant)");
        abort();
    }

    int fileVal = tolower(file) - 'a';

    fen++;
    char rank = *fen;
    if (!isdigit(rank)) {
        puts("Have to put enpassant in this format: a3 , E8, - (if no en passant)");
        abort();
    }

    int rankVal = rank - '0' - 1; // bring the range to 0-7

    board->enPassantSquare = (enumSquare)(rankVal * 8 + fileVal);

    fen += 2;
    return fen;
}
char *readHalfMoveClockFromFen(Board *board, char *fen) {
    char c = *fen;

    board->halfmoveClock = 0;

    if (!isdigit(c)) {
        return "";
    }

    board->halfmoveClock = (unsigned short)atoi(fen); // get the first number string

    // could be a variable amount of digits
    while (*fen != ' ') {
        fen++;
    }
    fen++;

    return fen;
}
void readFullMoveClockFromFen(Board *board, char *fen) {
    char c = *fen;

    board->fullmoveNumber = 1;
    if (!isdigit(c)) {
        return;
    }

    board->fullmoveNumber = (unsigned short)atoi(fen); // get first number string

    // dnt increment to avoid undefined behavior
}
static void initMailbox(Board *board) {
    for (int sq = 0; sq < 64; sq++) {
        board->mailbox[sq] = EMPTY; // if it doesn't hold a valid piece type it's empty
    }
    for (enumPiece piece = nPawn; piece <= nKing; piece++) {
        U64 bb = board->pieces[piece];
        while (bb) {
            int sq = __builtin_ctzll(bb);
            board->mailbox[sq] = piece;
            bb &= bb - 1;
        }
    }
}

U64 PieceRandoms[2][6][64]; // sides , piece types , num squares
U64 CastlingRandoms[16];    // castling rights range from 0000 -> 1111
U64 SideRandom ; // white to move if on, 
U64 EpRandoms[65]; // can be any square or NO_SQUARE

void initZobristRandoms() {
    //piece randoms 
    for (int side = nWhite; side <= nBlack ; side++){
        for (enumPiece piece = nPawn; piece <= nKing; piece++){
            for(enumSquare square = a1 ; square <=h8; square++){
                PieceRandoms[side][piece-2][square] = randU64(); 
            }
        }
    }

    // castling 
    for (int i =0 ; i< 16; i++){
        CastlingRandoms[i] = randU64(); 
    }

    // side 
    SideRandom = randU64(); 

    // en passant 
    for(int square= 0; square <= NO_SQUARE; square++){
        EpRandoms[square] = randU64(); 
    }
}


void initZobristKey(Board* board) {
    board->zobristKey = 0; 

    // iterate through all piece types for white and black 
    // get the square that that piece is on 
    // xor that specifc side,piece,square rand value with zobrist key 
    for(int square = 0 ; square<64 ; square++ ){
        
        enumPiece piece = board->mailbox[square]; 
        
        if (!isValidPiece(piece)) continue ; 
        
        U64 pieceBit = 1ULL<< square ; 
        enumPiece side = getColorPieces(board, nWhite) & pieceBit ? nWhite : nBlack;
        
        board->zobristKey ^= PieceRandoms[side][piece-2][square];  // have to minus 2 from piece cus nPawn =2 
        
    }

    // castling
    board->zobristKey ^= CastlingRandoms[board->castlingRights]; 

    // toggle white to move on if it's white to move
    if (board->whiteToMove)
        board->zobristKey ^= SideRandom;  
    // enPassant
    board->zobristKey ^= EpRandoms[board->enPassantSquare]; 
}

void initBoard(Board *board, char *fen) {

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

    initMailbox(board);

    // init the history to 0
    board->historyPly = 0;

    //init zobrist key 
    initZobristKey(board);
}

void initStandardChess(Board *board) {
    char *fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    initBoard(board, fen);
}