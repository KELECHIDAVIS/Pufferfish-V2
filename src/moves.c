#include "moves.h"

// extract pseudo legal moves
static void extractMovesFromBB(Move *moveList, size_t *numMoves, U64 possibleMoves, const enumSquare fromSquare, const MoveFlag flag) {
    while (possibleMoves) {
        U64 toBit = LSBIT(possibleMoves);
        possibleMoves = CLEARLSBIT(possibleMoves);
        enumSquare toSquare = __builtin_ctzll(toBit);

        Move move = encodeMove(fromSquare, toSquare, flag);
        moveList[(*numMoves)++] = move;
    }
}
// TODO: order moves to improve alpha beta performance,
void getPseudoLegalMoves(const Board *board, Move *moveList, size_t *numMoves) {
    getPawnMoves(board, moveList, numMoves);
    getKnightMoves(board, moveList, numMoves);
    getBishopMoves(board, moveList, numMoves);
    getRookMoves(board, moveList, numMoves);
    getQueenMoves(board, moveList, numMoves);
    getKingMoves(board, moveList, numMoves);
}

// TODO: sort moves based on viability to improve alpha beta

void sortMoveList(Move *moveList, size_t numMoves) {
}
void getPawnMoves(const Board *board, Move *moveList, size_t *numMoves) {
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 pawns = getSpecificColorPieces(board, side, nPawn);

    while (pawns) {
        U64 pos = LSBIT(pawns);
        pawns = CLEARLSBIT(pawns);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 emptySquares = ~getAllPieces(board);
        U64 removeLastRank = side == nWhite ? ~RANK_8 : ~RANK_1; // promotions handled separately

        U64 singlePushPattern = getSinglePushPattern(emptySquares, pos, side);
        extractMovesFromBB(moveList, numMoves, singlePushPattern & removeLastRank, fromSquare, QUIET_MOVE_FLAG);

        // only if single push is possible
        if (singlePushPattern) {
            U64 doublePushPattern = getDoublePushPattern(emptySquares, singlePushPattern, side);

            extractMovesFromBB(moveList, numMoves, doublePushPattern, fromSquare, DOUBLE_PAWN_PUSH_FLAG);
        }

        // get pawn attacks
        U64 attackPattern = getPawnAttackPattern(fromSquare, side);

        // and with opponent pieces to get captures, also remove last rank for
        // promotions
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces & removeLastRank, fromSquare, CAPTURE_FLAG);

        // for promotions can just get every single push or capture that lands
        // on last rank
        U64 promotionPushes = singlePushPattern & ~removeLastRank;

        for (int i = KNIGHT_PROMOTION_FLAG; i <= QUEEN_PROMOTION_FLAG; i++) {
            U64 copy = promotionPushes;
            extractMovesFromBB(moveList, numMoves, copy, fromSquare, (MoveFlag)i);
        }

        U64 promotionCaptures = attackPattern & opponentPieces & ~removeLastRank;
        for (int i = KNIGHT_PROMO_CAPTURE_FLAG; i <= QUEEN_PROMO_CAPTURE_FLAG; i++) {
            U64 copy = promotionCaptures;
            extractMovesFromBB(moveList, numMoves, copy, fromSquare, (MoveFlag)i);
        }

        // check enpassant if nonzero
        if (board->enPassantSquare != NO_SQUARE && board->enPassantSquare < 64) {
            U64 enPassantBit = 1ULL << board->enPassantSquare;
            // en passant is only valid if on the 3rd rank or 6th rank
            if ((enPassantBit & RANK_3) || (enPassantBit & RANK_6)) {
                // if they can get to the enpassant square by capturing it's valid
                U64 enPassantCaptures = attackPattern & enPassantBit;
                extractMovesFromBB(moveList, numMoves, enPassantCaptures, fromSquare, EN_PASSANT_CAPTURE_FLAG);
            }
        }
    }
}
void getKnightMoves(const Board *board, Move *moveList, size_t *numMoves) {
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 knights = getSpecificColorPieces(board, side, nKnight);

    while (knights) {
        U64 pos = LSBIT(knights);
        knights = CLEARLSBIT(knights);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 attackPattern = getKnightAttackPattern(fromSquare);

        // and with empty to get quiet moves
        U64 empty = ~getAllPieces(board);
        extractMovesFromBB(moveList, numMoves, attackPattern & empty,
                           fromSquare, QUIET_MOVE_FLAG);

        // and with opponent pieces to get captures
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces,
                           fromSquare, CAPTURE_FLAG);
    }
}
void getBishopMoves(const Board *board, Move *moveList, size_t *numMoves) {
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 bishops = getSpecificColorPieces(board, side, nBishop);

    while (bishops) {
        U64 pos = LSBIT(bishops);
        bishops = CLEARLSBIT(bishops);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 blockers = getAllPieces(board) & BishopMagicTable[fromSquare].mask;
        U64 attackPattern = getBishopAttackPattern(fromSquare, blockers);

        // and with empty to get quiet moves
        U64 empty = ~getAllPieces(board);
        extractMovesFromBB(moveList, numMoves, attackPattern & empty,
                           fromSquare, QUIET_MOVE_FLAG);

        // and with opponent pieces to get captures
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces,
                           fromSquare, CAPTURE_FLAG);
    }
}
void getRookMoves(const Board *board, Move *moveList, size_t *numMoves) {
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 rooks = getSpecificColorPieces(board, side, nRook);

    while (rooks) {
        U64 pos = LSBIT(rooks);
        rooks = CLEARLSBIT(rooks);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 blockers = getAllPieces(board) & RookMagicTable[fromSquare].mask;
        U64 attackPattern = getRookAttackPattern(fromSquare, blockers);

        // and with empty to get quiet moves
        U64 empty = ~getAllPieces(board);
        extractMovesFromBB(moveList, numMoves, attackPattern & empty,
                           fromSquare, QUIET_MOVE_FLAG);

        // and with opponent pieces to get captures
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces,
                           fromSquare, CAPTURE_FLAG);
    }
}
void getQueenMoves(const Board *board, Move *moveList, size_t *numMoves) {
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 queen = getSpecificColorPieces(board, side, nQueen);

    while (queen) {
        U64 pos = LSBIT(queen);
        queen = CLEARLSBIT(queen);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 bishopBlockers =
            getAllPieces(board) & BishopMagicTable[fromSquare].mask;
        U64 rookBlockers =
            getAllPieces(board) & RookMagicTable[fromSquare].mask;

        U64 attackPattern = getBishopAttackPattern(fromSquare, bishopBlockers);
        attackPattern |= getRookAttackPattern(fromSquare, rookBlockers);

        // and with empty to get quiet moves
        U64 empty = ~getAllPieces(board);
        extractMovesFromBB(moveList, numMoves, attackPattern & empty,
                           fromSquare, QUIET_MOVE_FLAG);

        // and with opponent pieces to get captures
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces,
                           fromSquare, CAPTURE_FLAG);
    }
}

void getKingMoves(const Board *board, Move *moveList, size_t *numMoves) {
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 kings = getSpecificColorPieces(board, side, nKing);

    while (kings) {
        U64 pos = LSBIT(kings);
        kings = CLEARLSBIT(kings);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 attackPattern = getKingAttackPattern(fromSquare);

        // and with empty to get quiet moves
        U64 empty = ~getAllPieces(board);
        extractMovesFromBB(moveList, numMoves, attackPattern & empty,
                           fromSquare, QUIET_MOVE_FLAG);

        // and with opponent pieces to get captures
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces,
                           fromSquare, CAPTURE_FLAG);

        // castling
        // king and relevant rook must not have been moved (the rights still
        // have to be active, they get turned off during make move ) king cannot
        // be in check (in the opponent attack pattern) the squares between
        // cannot be in the attack pattern either
        U64 oppAttackPattern = getSideAttackPattern(board, opponentSide);
        if (!(pos & oppAttackPattern)) // if king not in check
        {
            U64 destination = 0; // where king ends up
            U64 inBetween =
                0; // all inbetween squares that cannot be in attack pattern
            if (side == nWhite) {
                // check kingside
                if (board->castlingRights & W_K_CASTLE) {
                    // f1 and g1 have to be empty and not in attack pattern
                    destination = (1ULL << g1);
                    inBetween = (1ULL << f1) | destination;
                    // inbetween cannot be in attack pattern and has to be empty
                    if ((!(inBetween & oppAttackPattern)) &&
                        ((inBetween & empty) == inBetween))
                        extractMovesFromBB(moveList, numMoves, destination,
                                           fromSquare, KING_CASTLE_FLAG);
                }
                if (board->castlingRights & W_Q_CASTLE) {
                    destination = (1ULL << c1);
                    inBetween = (1ULL << d1) | destination;
                    U64 pathIsEmpty = inBetween | (1ULL << b1);
                    if ((!(inBetween & oppAttackPattern)) &&
                        ((pathIsEmpty & empty) == pathIsEmpty))
                        extractMovesFromBB(moveList, numMoves, destination,
                                           fromSquare, QUEEN_CASTLE_FLAG);
                }
            } else // black
            {
                if (board->castlingRights & B_K_CASTLE) {
                    // f8 and g8 have to be empty and not in attack pattern
                    destination = (1ULL << g8);
                    inBetween = (1ULL << f8) | destination;
                    // inbetween cannot be in attack pattern and has to be empty
                    if ((!(inBetween & oppAttackPattern)) &&
                        ((inBetween & empty) == inBetween))
                        extractMovesFromBB(moveList, numMoves, destination,
                                           fromSquare, KING_CASTLE_FLAG);
                }
                if (board->castlingRights & B_Q_CASTLE) {
                    destination = (1ULL << c8);
                    inBetween = (1ULL << d8) | destination;
                    U64 pathIsEmpty = inBetween | (1ULL << b8);
                    if ((!(inBetween & oppAttackPattern)) &&
                        ((pathIsEmpty & empty) == pathIsEmpty))
                        extractMovesFromBB(moveList, numMoves, destination,
                                           fromSquare, QUEEN_CASTLE_FLAG);
                }
            }
        }
    }
}

void translateFlagToAlgebraic(MoveFlag flag, char *buffer) {
    switch (flag) {
    case QUIET_MOVE_FLAG:
        strcpy(buffer, "quiet");
        break;
    case DOUBLE_PAWN_PUSH_FLAG:
        strcpy(buffer, "double pawn");
        break;
    case KING_CASTLE_FLAG:
        strcpy(buffer, "O-O");
        break;
    case QUEEN_CASTLE_FLAG:
        strcpy(buffer, "O-O-O");
        break;
    case CAPTURE_FLAG:
        strcpy(buffer, "capture");
        break;
    case EN_PASSANT_CAPTURE_FLAG:
        strcpy(buffer, "e.p.");
        break;
    case KNIGHT_PROMOTION_FLAG:
        strcpy(buffer, "=N");
        break;
    case BISHOP_PROMOTION_FLAG:
        strcpy(buffer, "=B");
        break;
    case ROOK_PROMOTION_FLAG:
        strcpy(buffer, "=R");
        break;
    case QUEEN_PROMOTION_FLAG:
        strcpy(buffer, "=Q");
        break;
    case KNIGHT_PROMO_CAPTURE_FLAG:
        strcpy(buffer, "x=N");
        break;
    case BISHOP_PROMO_CAPTURE_FLAG:
        strcpy(buffer, "x=B");
        break;
    case ROOK_PROMO_CAPTURE_FLAG:
        strcpy(buffer, "x=R");
        break;
    case QUEEN_PROMO_CAPTURE_FLAG:
        strcpy(buffer, "x=Q");
        break;
    default:
        strcpy(buffer, "unknown");
        break;
    }
}

// if move is a rook move/capture update corresponding rook ; if king move
// disable castling for side
static void updateCastlingRights(Board *board, enumPiece piece,
                                 unsigned int pos) {
    // if king moved turn off castling rights for whole side
    if (piece == nKing) {
        board->castlingRights &=
            board->whiteToMove ? (unsigned char)(~(W_K_CASTLE | W_Q_CASTLE))
                               : (unsigned char)(~(B_K_CASTLE | B_Q_CASTLE));
    } else if (piece == nRook) { // rook
        switch (pos) {           // based on which corner move originates from
        case a1:
            board->castlingRights &= (unsigned char)~W_Q_CASTLE;
            break;
        case h1:
            board->castlingRights &= (unsigned char)~W_K_CASTLE;
            break;
        case a8:
            board->castlingRights &= (unsigned char)~B_Q_CASTLE;
            break;
        case h8:
            board->castlingRights &= (unsigned char)~B_K_CASTLE;
            break;
        default:
            break;
        }
    }
}

// save current board state (whiteToMove, castlingRights, enPassantSquare,
// halfMoveClock, fullMoveNumber, moveToBeMade, capturedPiece ) into history to
// be recalled later in unmake move
void saveBoardState(Board *board, Move move, enumPiece capturedPiece) {

    if (board->historyPly >= MAX_SEARCH_DEPTH) {
        fprintf(stderr, "ERROR: History stack overflow at depth %d\n", board->historyPly);
        printChessBoard(board);
        abort();
    }

    MoveHistory *currHistory = &board->historyArr[board->historyPly];

    currHistory->castlingRights = board->castlingRights;
    currHistory->enPassantSquare = board->enPassantSquare;
    currHistory->halfmoveClock = board->halfmoveClock;
    currHistory->fullMoveNumber = board->fullmoveNumber;
    currHistory->move = move;
    currHistory->capturedPiece = capturedPiece; // will be valid piece if piece was captured

    board->historyPly++; // increase size of stack
}
bool isSideInCheck(const Board *board, const enumPiece side) {
    // see if this side's king lays within the enemy's attack pattern.
    enumPiece opp = side == nWhite ? nBlack : nWhite;
    U64 attackPattern = getSideAttackPattern(board, opp);
    U64 kingPos = getSpecificColorPieces(board, side, nKing);
    return kingPos & attackPattern;
}

void makeMove(Board *board, Move move) {
    unsigned int from = getFrom(move);
    unsigned int to = getTo(move);
    unsigned int flags = getFlags(move);

    enumPiece side, opp;
    int epPawnOffset;                                                                    // offset for the captured ep pawn
    enumSquare kingSideRookStart, queenSideRookStart, kingSideRookEnd, queenSideRookEnd; // castling rook positions
    if (board->whiteToMove) {
        side = nWhite;
        opp = nBlack;
        epPawnOffset = -8;
        kingSideRookStart = h1;
        queenSideRookStart = a1;
        kingSideRookEnd = f1;
        queenSideRookEnd = d1;
    } else {
        side = nBlack;
        opp = nWhite;
        epPawnOffset = 8;
        kingSideRookStart = h8;
        queenSideRookStart = a8;
        kingSideRookEnd = f8;
        queenSideRookEnd = d8;
    }

    int capturedDest = (int)to;
    if (flags == EN_PASSANT_CAPTURE_FLAG)
        capturedDest += epPawnOffset; // the captured piece will be above or below

    enumPiece capturedPiece = board->mailbox[capturedDest]; // can be empty if nothing was captured
    enumPiece movingPiece = board->mailbox[from];           // has to be valid

    assert(isValidPiece(movingPiece) && "Moving Piece Has To Be Valid in makeMove");

    // save current board state (whiteToMove, castlingRights, enPassantSquare,
    // halfMoveClock, fullMoveNumber, moveToBeMade, capturedPiece ) into history
    saveBoardState(board, move, capturedPiece);

    // remove captured Piece from dest and moving Piece from start
    if (isValidPiece(capturedPiece))
        removePiece(board, capturedPiece, opp, capturedDest);
    removePiece(board, movingPiece, side, from);

    // if capturedPiece isValidPiece or if pawn moved : halfmove clock = 0
    if (movingPiece == nPawn || isValidPiece(capturedPiece))
        board->halfmoveClock = 0;
    else
        board->halfmoveClock++;

    // put_piece the moving piece at destination
    putPiece(board, movingPiece, side, to);

    // if double pawn push, set enPassantSquare to square behind
    if (flags == DOUBLE_PAWN_PUSH_FLAG)
        board->enPassantSquare = to + epPawnOffset;
    else
        board->enPassantSquare = NO_SQUARE; // nonValid ep square

    // if king or rook moved OR rook was capturedPiece, update castling righ`ts
    if (movingPiece == nKing || movingPiece == nRook)
        updateCastlingRights(board, movingPiece, from);
    else if (capturedPiece == nRook)
        updateCastlingRights(board, capturedPiece, capturedDest);

    // if promo, remove_piece the pawn at dest then place promo piece
    if (flags >= KNIGHT_PROMOTION_FLAG && flags <= QUEEN_PROMO_CAPTURE_FLAG) {
        assert(movingPiece == nPawn &&
               "When promoting, Moving Piece has to be a pawn");
        removePiece(board, movingPiece, side, to); // remove pawn at destination
        enumPiece promoPiece = nQueen;
        switch (flags) {
        case KNIGHT_PROMOTION_FLAG:
        case KNIGHT_PROMO_CAPTURE_FLAG:
            promoPiece = nKnight;
            break;
        case BISHOP_PROMOTION_FLAG:
        case BISHOP_PROMO_CAPTURE_FLAG:
            promoPiece = nBishop;
            break;
        case ROOK_PROMOTION_FLAG:
        case ROOK_PROMO_CAPTURE_FLAG:
            promoPiece = nRook;
            break;
        case QUEEN_PROMOTION_FLAG:
        case QUEEN_PROMO_CAPTURE_FLAG:
            promoPiece = nQueen;
            break;
        default:
            break;
        }
        movingPiece = promoPiece;
        putPiece(board, movingPiece, side, to);
    }

    // if castle, remove_piece corresponding rook then put_piece corresponding
    // rook
    if (flags == KING_CASTLE_FLAG) {
        removePiece(board, nRook, side, kingSideRookStart);
        putPiece(board, nRook, side, kingSideRookEnd);
    } else if (flags == QUEEN_CASTLE_FLAG) {
        removePiece(board, nRook, side, queenSideRookStart);
        putPiece(board, nRook, side, queenSideRookEnd);
    }

    // increment fullmove clock if black moved
    if (side == nBlack)
        board->fullmoveNumber++;

    // change board' white to move
    board->whiteToMove = !board->whiteToMove;
}

void loadLastBoardState(Board *board) {
    board->historyPly--; // decrease size of stack

    MoveHistory *lastState = &board->historyArr[board->historyPly];

    board->castlingRights = lastState->castlingRights;
    board->enPassantSquare = lastState->enPassantSquare;
    board->halfmoveClock = lastState->halfmoveClock;
    board->fullmoveNumber = lastState->fullMoveNumber;
}

void unmakeMove(Board *board, Move move) {
    board->whiteToMove = !board->whiteToMove; // change to the side that performed this move
    unsigned int from = getFrom(move);
    unsigned int to = getTo(move);
    unsigned int flags = getFlags(move);

    enumPiece side, opp;
    int epPawnOffset;                                                                    // offset for the captured ep pawn
    enumSquare kingSideRookStart, queenSideRookStart, kingSideRookEnd, queenSideRookEnd; // castling rook positions
    if (board->whiteToMove) {
        side = nWhite;
        opp = nBlack;
        epPawnOffset = -8;
        kingSideRookStart = h1;
        queenSideRookStart = a1;
        kingSideRookEnd = f1;
        queenSideRookEnd = d1;
    } else {
        side = nBlack;
        opp = nWhite;
        epPawnOffset = 8;
        kingSideRookStart = h8;
        queenSideRookStart = a8;
        kingSideRookEnd = f8;
        queenSideRookEnd = d8;
    }

    int capturedDest = (int)to;
    if (flags == EN_PASSANT_CAPTURE_FLAG)
        capturedDest += epPawnOffset; // the captured piece was above or below

    enumPiece capturedPiece = board->historyArr[(board->historyPly - 1)].capturedPiece; // if piece was captured in the history
    enumPiece movingPiece = board->mailbox[to];                                         // has to be valid

    if (!isValidPiece(movingPiece)) {
        // print chess board
        printf("ERROR: an invalid piece with pieceType %d was trying to be moved in unmakeMove\n", movingPiece);
        printChessBoard(board);
        // print moves that go to this position
        printf("Moves: ");
        for (int i = 0; i < board->historyPly; i++) {
            printMove(board->historyArr[i].move);
            printf(" ");
        }
        printf("\n");
        abort();
    }

    // if castle, remove_piece corresponding rook at end then put_piece
    // corresponding rook at start
    if (flags == KING_CASTLE_FLAG) {
        removePiece(board, nRook, side, kingSideRookEnd);
        putPiece(board, nRook, side, kingSideRookStart);
    } else if (flags == QUEEN_CASTLE_FLAG) {
        removePiece(board, nRook, side, queenSideRookEnd);
        putPiece(board, nRook, side, queenSideRookStart);
    }

    // if promo, remove_piece promo piece at dest then place pawn at dest
    if (flags >= KNIGHT_PROMOTION_FLAG && flags <= QUEEN_PROMO_CAPTURE_FLAG) {
        assert(movingPiece >= nKnight && movingPiece <= nQueen &&
               "When undoing promotion, piece has to be between knight and queen ");
        removePiece(board, movingPiece, side, to); // remove promo piece
        movingPiece = nPawn;
    }

    removePiece(board, movingPiece, side, to); // remove moving piece from destination
    putPiece(board, movingPiece, side, from);  // place movingPiece at start; captured at dest
    if (isValidPiece(capturedPiece))
        putPiece(board, capturedPiece, opp, capturedDest); // if empty nothing will be placed

    // load last board state , decrement size then load state (whiteToMove (changed at start
    // of function), castlingRights, enPassantSquare, halfMoveClock,
    // fullMoveNumber) into current board,
    loadLastBoardState(board);
}

void getSquareName(unsigned int sq, char *buf) {
    buf[0] = 'a' + (char)(sq % 8);
    buf[1] = '1' + (char)(sq / 8);
    buf[2] = '\0';
}
// doesn't end with "\n"
// moves.c

void printMove(Move move) {
    unsigned int from = getFrom(move);
    unsigned int to = getTo(move);
    unsigned int flags = getFlags(move);

    char fromStr[3];
    char toStr[3];
    getSquareName(from, fromStr);
    getSquareName(to, toStr);

    printf("%s%s", fromStr, toStr);

    // Append promotion piece character if necessary
    // Based on your MoveFlag enum in moves.h
    switch (flags) {
    case KNIGHT_PROMOTION_FLAG:
    case KNIGHT_PROMO_CAPTURE_FLAG:
        printf("n");
        break;
    case BISHOP_PROMOTION_FLAG:
    case BISHOP_PROMO_CAPTURE_FLAG:
        printf("b");
        break;
    case ROOK_PROMOTION_FLAG:
    case ROOK_PROMO_CAPTURE_FLAG:
        printf("r");
        break;
    case QUEEN_PROMOTION_FLAG:
    case QUEEN_PROMO_CAPTURE_FLAG:
        printf("q");
        break;
    default:
        // Not a promotion move
        break;
    }
}
