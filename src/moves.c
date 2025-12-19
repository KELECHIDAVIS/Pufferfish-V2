#include "moves.h"

// extract pseudo legal moves
static void extractMovesFromBB(Move *moveList, size_t *numMoves, U64 possibleMoves, const enumSquare fromSquare, const MoveFlag flag)
{
    while (possibleMoves)
    {
        U64 toBit = LSBIT(possibleMoves);
        possibleMoves = CLEARLSBIT(possibleMoves);
        enumSquare toSquare = __builtin_ctzll(toBit);

        Move move = encodeMove(fromSquare, toSquare, flag);
        moveList[(*numMoves)++] = move;
    }
}
void getKnightMoves(const Board *board, Move *moveList, size_t *numMoves)
{
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 knights = getSpecificColorPieces(board, side, nKnight);

    while (knights)
    {
        U64 pos = LSBIT(knights);
        knights = CLEARLSBIT(knights);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 attackPattern = getKnightAttackPattern(fromSquare);

        // and with empty to get quiet moves
        U64 empty = ~getAllPieces(board);
        extractMovesFromBB(moveList, numMoves, attackPattern & empty, fromSquare, QUIET_MOVE_FLAG);

        // and with opponent pieces to get captures
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces, fromSquare, CAPTURE_FLAG);
    }
}
void getBishopMoves(const Board *board, Move *moveList, size_t *numMoves)
{
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 bishops = getSpecificColorPieces(board, side, nBishop);

    while (bishops)
    {
        U64 pos = LSBIT(bishops);
        bishops = CLEARLSBIT(bishops);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 blockers = getAllPieces(board) & BishopMagicTable[fromSquare].mask;
        U64 attackPattern = getBishopAttackPattern(fromSquare, blockers);

        // and with empty to get quiet moves
        U64 empty = ~getAllPieces(board);
        extractMovesFromBB(moveList, numMoves, attackPattern & empty, fromSquare, QUIET_MOVE_FLAG);

        // and with opponent pieces to get captures
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces, fromSquare, CAPTURE_FLAG);
    }
}
void getRookMoves(const Board *board, Move *moveList, size_t *numMoves)
{
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 rooks = getSpecificColorPieces(board, side, nRook);

    while (rooks)
    {
        U64 pos = LSBIT(rooks);
        rooks = CLEARLSBIT(rooks);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 blockers = getAllPieces(board) & RookMagicTable[fromSquare].mask;
        U64 attackPattern = getRookAttackPattern(fromSquare, blockers);

        // and with empty to get quiet moves
        U64 empty = ~getAllPieces(board);
        extractMovesFromBB(moveList, numMoves, attackPattern & empty, fromSquare, QUIET_MOVE_FLAG);

        // and with opponent pieces to get captures
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces, fromSquare, CAPTURE_FLAG);
    }
}
void getQueenMoves(const Board *board, Move *moveList, size_t *numMoves)
{
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 queen = getSpecificColorPieces(board, side, nQueen);

    while (queen)
    {
        U64 pos = LSBIT(queen);
        queen = CLEARLSBIT(queen);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 bishopBlockers = getAllPieces(board) & BishopMagicTable[fromSquare].mask;
        U64 rookBlockers = getAllPieces(board) & RookMagicTable[fromSquare].mask;

        U64 attackPattern = getBishopAttackPattern(fromSquare, bishopBlockers);
        attackPattern |= getRookAttackPattern(fromSquare, rookBlockers);

        // and with empty to get quiet moves
        U64 empty = ~getAllPieces(board);
        extractMovesFromBB(moveList, numMoves, attackPattern & empty, fromSquare, QUIET_MOVE_FLAG);

        // and with opponent pieces to get captures
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces, fromSquare, CAPTURE_FLAG);
    }
}

void getKingMoves(const Board *board, Move *moveList, size_t *numMoves)
{
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 kings = getSpecificColorPieces(board, side, nKing);

    while (kings)
    {
        U64 pos = LSBIT(kings);
        kings = CLEARLSBIT(kings);
        enumSquare fromSquare = __builtin_ctzll(pos);

        U64 attackPattern = getKingAttackPattern(fromSquare);

        // and with empty to get quiet moves
        U64 empty = ~getAllPieces(board);
        extractMovesFromBB(moveList, numMoves, attackPattern & empty, fromSquare, QUIET_MOVE_FLAG);

        // and with opponent pieces to get captures
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces, fromSquare, CAPTURE_FLAG);

        // castling
        // king and relevant rook must not have been moved (the rights still have to be active, they get turned off during make move )
        // king cannot be in check (in the opponent attack pattern)
        // the squares between cannot be in the attack pattern either
        U64 oppAttackPattern = getSideAttackPattern(board, opponentSide);
        if (!(pos & oppAttackPattern)) // if king not in check
        {
            U64 destination = 0; // where king ends up
            U64 inBetween = 0; // all inbetween squares that cannot be in attack pattern 
            if (side == nWhite)
            {
                // check kingside
                if (board->castlingRights & W_K_CASTLE)
                {
                    // f1 and g1 have to be empty and not in attack pattern
                    destination = (1ULL << g1);  
                    inBetween = (1ULL << f1) | destination;
                    // inbetween cannot be in attack pattern and has to be empty 
                    if((!(inBetween & oppAttackPattern) ) && ((inBetween & empty) == inBetween)) 
                        extractMovesFromBB(moveList, numMoves, destination , fromSquare, KING_CASTLE_FLAG); 
                }
                if (board->castlingRights & W_Q_CASTLE){
                    destination = (1ULL << c1);
                    inBetween =  (1ULL << d1 )| destination;
                    U64 pathIsEmpty = inBetween | (1ULL << b1); 
                    if ((!(inBetween & oppAttackPattern)) && ((pathIsEmpty & empty) == pathIsEmpty)) 
                        extractMovesFromBB(moveList, numMoves, destination, fromSquare, QUEEN_CASTLE_FLAG); 
                }
            }
            else // black 
            {
                if (board->castlingRights & B_K_CASTLE)
                {
                    // f8 and g8 have to be empty and not in attack pattern
                    destination = (1ULL << g8);
                    inBetween = (1ULL << f8) | destination;
                    // inbetween cannot be in attack pattern and has to be empty
                    if ((!(inBetween & oppAttackPattern)) && ((inBetween & empty) == inBetween))
                        extractMovesFromBB(moveList, numMoves, destination, fromSquare, KING_CASTLE_FLAG);
                }
                if (board->castlingRights & B_Q_CASTLE)
                {
                    destination = (1ULL << c8);
                    inBetween = (1ULL << d8) | destination;
                    U64 pathIsEmpty = inBetween | (1ULL << b8);
                    if ((!(inBetween & oppAttackPattern)) && ((pathIsEmpty & empty) == pathIsEmpty))
                        extractMovesFromBB(moveList, numMoves, destination, fromSquare, QUEEN_CASTLE_FLAG);
                }
            }
        }
    }
}

// if move is a rook move update if king move disable castling for side
static void updateCastlingRights(Board *board, enumPiece piece, unsigned int from)
{
    // if king moved turn off castling rights for whole side
    if (piece == nKing)
    {
        board->castlingRights &= board->whiteToMove ? (unsigned char)(~(W_K_CASTLE | W_Q_CASTLE)) : (unsigned char)(~(B_K_CASTLE | B_Q_CASTLE));
    }
    else
    { // rook
        switch (from)
        { // based on which corner move originates from
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
// Moves Piece and updates it's bb, side bb and mailbox. If a piece was captured then update their side's bb and piece bb
void movePiece(Board *board, unsigned int from, unsigned int to, MoveFlag flags)
{
    enumPiece side = nWhite;
    enumPiece oppSide = nBlack;
    if (!board->whiteToMove)
    {
        side = nBlack;
        oppSide = nWhite;
    }
    U64 fromBit = 1ULL << from;
    U64 toBit = 1ULL << to;

    // use mailbox to see which piece was at that spot
    enumPiece piece = board->mailbox[from];
    enumPiece capturedPiece = board->mailbox[to];
    // has to be valid piece
    assert(piece >= nPawn && piece <= nKing && "The piece could not be found in any bb");
    // move from piece bb
    
    board->pieces[piece] ^= fromBit; // guarenteed to be set so just xor it
    
    board->pieces[piece] |= toBit;   // might be set or not if it's a capture of the same pc
    
    // move from side bb
    board->pieces[side] ^= (fromBit | toBit); // both guarenteed to be set and unset
    

    // update moving piece in mailbox
    board->mailbox[from] = nWhite; // no piece
    board->mailbox[to] = piece;

    if (capturedPiece >= nPawn && capturedPiece <= nKing)
    {
        //if a piece type has been captured by the same type of a piece, this turns off the capturing piece's position 
         
        // update captured piece's sidebb , piece bb
        // only turn off if they're not the same piece type bc that would turn off the capturing piece 
        if (capturedPiece != piece)
            board->pieces[capturedPiece] ^= toBit;

        board->pieces[oppSide] ^= toBit; // this fine 

        // if a capture was a rook have to update castling rights
        if (capturedPiece == nRook)
            updateCastlingRights(board, nRook, to); // where the rook is
    }

    // SPECIAL FLAG CASES
    // if en passant have to remove pawn above or below destination (depend on side)
    if (flags == EN_PASSANT_CAPTURE_FLAG)
    {
        U64 capturePawnPos = 0;
        int pos = NO_SQUARE;
        if (side == nWhite)
        {
            capturePawnPos = toBit >> 8;
            pos = (int)to - 8;
        }
        else
        {
            capturePawnPos = toBit << 8;
            pos = (int)to + 8;
        }
        board->mailbox[pos] = nWhite;             // place empty square where piece used to be
        board->pieces[nPawn] ^= capturePawnPos;   // toggle the captured pawn bit off
        board->pieces[oppSide] ^= capturePawnPos; // in the side aswell
    }

    // if promo, put promo piece at to (side bb and piece bb )
    if (flags >= KNIGHT_PROMOTION_FLAG && flags <= QUEEN_PROMO_CAPTURE_FLAG)
    {
        // capture should already be taken care of
        board->pieces[nPawn] ^= toBit; // remove pawn
        enumPiece promoPiece = nQueen; // assume queen
        switch (flags)
        {
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
            printf("Nonvalid promo piece type within promoflag check. Flag value should be between %d and %d. Was: %d: ", KNIGHT_PROMOTION_FLAG, QUEEN_PROMO_CAPTURE_FLAG, flags);
            abort();
        }
        board->pieces[promoPiece] ^= toBit; // place promo piece
        board->mailbox[to] = promoPiece;    // update mailbox
    }

    // if castle move corrensponding rook (from side and piece bb's respectively) (the king will already have moved )
    if (flags == KING_CASTLE_FLAG || flags == QUEEN_CASTLE_FLAG)
    {
        unsigned int rookFrom = side == nWhite ? h1 : h8;
        unsigned int rookTo = side == nWhite ? f1 : f8;
        if (flags == QUEEN_CASTLE_FLAG)
        {
            rookFrom = side == nWhite ? a1 : a8;
            rookTo = side == nWhite ? d1 : d8;
        }
        U64 rookFromBit = 1ULL << rookFrom;
        U64 rookToBit = 1ULL << rookTo;

        board->pieces[nRook] ^= rookFromBit;
        board->pieces[nRook] |= rookToBit;
        board->pieces[side] ^= rookFromBit;
        board->pieces[side] |= rookToBit;

        // Update mailbox
        board->mailbox[rookFrom] = nWhite;
        board->mailbox[rookTo] = nRook;
    }
}

// save state and move made at that board state
void saveBoardState(Board *board, Move move)
{
    assert(board->historyPly >= 0 && board->historyPly < MAX_SEARCH_DEPTH && "Tried to save state with invalid history stack size");

    board->historyArr[board->historyPly].move = move;
    board->historyArr[board->historyPly].castlingRights = board->castlingRights;
    board->historyArr[board->historyPly].enPassantSquare = board->enPassantSquare;
    board->historyArr[board->historyPly].halfmoveClock = board->halfmoveClock;
    board->historyArr[board->historyPly].fullMoveNumber = board->fullmoveNumber;
    unsigned int to = getTo(move);
    if (getFlags(move) == EN_PASSANT_CAPTURE_FLAG)
    {
        // depending on the side, the captured pawn is above or below
        int capturedPawnPos = (int)to;
        capturedPawnPos += board->whiteToMove ? -8 : 8;
        board->historyArr[board->historyPly].capturedPiece = board->mailbox[capturedPawnPos];
        assert(board->historyArr[board->historyPly].capturedPiece == nPawn && "The Piece That Was Captured During enPassant was not a pawn"); 
    }
    else
    {
        board->historyArr[board->historyPly].capturedPiece = board->mailbox[to]; // could be empty 
    }
    board->historyPly++;
}
bool isSideInCheck(const Board *board, const enumPiece side)
{
    // see if this side's king lays within the enemy's attack pattern.
    enumPiece opp = side == nWhite ? nBlack : nWhite;
    U64 attackPattern = getSideAttackPattern(board, opp);
    U64 kingPos = getSpecificColorPieces(board, side, nKing);
    return kingPos & attackPattern;
}
void makeMove(Board *board, Move move)
{

    unsigned int from = getFrom(move);
    unsigned int to = getTo(move);
    unsigned int flags = getFlags(move);

    enumPiece piece = board->mailbox[from];

    // save the state for this move
    saveBoardState(board, move);
    if (piece == nRook || piece == nKing)
        updateCastlingRights(board, piece, from);

    // reset en passant square
    board->enPassantSquare = NO_SQUARE; // not valid ep square
    
    if (flags == DOUBLE_PAWN_PUSH_FLAG)
    { // set ep square to behind/above the pawn
        int newEpPos = (int)to;
        newEpPos += board->whiteToMove ? -8 : 8;
        board->enPassantSquare = newEpPos;
    }
    // update half move clock
    if (piece == nPawn || isCapture(move))
    {
        board->halfmoveClock = 0;
    }
    else
    {
        board->halfmoveClock++;
    }
    // move piece
    movePiece(board, from, to, flags);
    // update full move counter
    if (!board->whiteToMove) // after every black move
        board->fullmoveNumber++;
    // opponent's turn
    board->whiteToMove = !board->whiteToMove;
}

// unmove moved piece(s), including rooks if a castled occurred, promo pieces if promo occurred, and enpassant if that occured
void unmovePiece(Board *board, Move move, enumPiece capturedPiece)
{
    unsigned int from = getFrom(move);
    unsigned int to = getTo(move);
    unsigned int flags = getFlags(move);

    // 1. Determine side (Assuming you flipped board->whiteToMove in unmakeMove first)
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    enumPiece oppSide = board->whiteToMove ? nBlack : nWhite;

    U64 fromBit = 1ULL << from;
    U64 toBit = 1ULL << to;

    // 2. Identify the piece that moved
    enumPiece piece = board->mailbox[to];

    // VALIDATION
    if (piece == nWhite)
    {
        printf("Error: No piece at 'to' square %d during unmove!\n", to);
        printChessBoard(board);
        assert(false);
    }

    // 3. Move the piece back geometrically
    board->pieces[piece] &= ~toBit;
    board->pieces[piece] |= fromBit;
    board->pieces[side] ^= (fromBit | toBit);

    board->mailbox[from] = piece;
    board->mailbox[to] = nWhite; // Start by assuming the 'to' square is now empty

    // 4. Restore Captured Pieces (Crucial Fix)
    if (flags == EN_PASSANT_CAPTURE_FLAG)
    {
        int pos = (side == nWhite) ? (int)to - 8 : (int)to + 8;
        U64 capturePawnPos = 1ULL << pos;

        board->mailbox[pos] = nPawn;
        board->pieces[nPawn] |= capturePawnPos;
        board->pieces[oppSide] |= capturePawnPos;
    }
    else if (capturedPiece != nWhite) // Only restore if something was actually captured
    {
        board->mailbox[to] = capturedPiece;
        board->pieces[capturedPiece] |= toBit;
        board->pieces[oppSide] |= toBit;
    }

    // 5. Handle Promotions (Move back as a pawn)
    if (flags >= KNIGHT_PROMOTION_FLAG && flags <= QUEEN_PROMO_CAPTURE_FLAG)
    {
        board->pieces[piece] &= ~fromBit;
        board->pieces[nPawn] |= fromBit;
        board->mailbox[from] = nPawn;
    }

    // if castling place rook back where it came (king alr moved back)
    if (flags == KING_CASTLE_FLAG || flags == QUEEN_CASTLE_FLAG)
    {
        unsigned int rookFrom = side == nWhite ? f1 : f8;
        unsigned int rookTo = side == nWhite ? h1 : h8;
        if (flags == QUEEN_CASTLE_FLAG)
        {
            rookFrom = side == nWhite ? d1 : d8;
            rookTo = side == nWhite ? a1 : a8;
        }
        U64 rookFromBit = 1ULL << rookFrom;
        U64 rookToBit = 1ULL << rookTo;
        
        // Move Rook bits
        board->pieces[nRook] ^= (rookFromBit | rookToBit); // Toggle both to swap
        board->pieces[side] ^= (rookFromBit | rookToBit);
        
        // Update mailbox
        board->mailbox[rookFrom] = nWhite;
        board->mailbox[rookTo] = nRook;
    }
}
void unmakeMove(Board *board, Move move)
{
    // 1. Flip the turn BACK first.
    // If it was Black's turn to move next, flipping it back makes it White's turn (the mover).
    board->whiteToMove = !board->whiteToMove;

    // 2. Retrieve history
    board->historyPly--;
    MoveHistory *lastState = &board->historyArr[board->historyPly];

    // 3. Now unmove the piece.
    // Inside unmovePiece, 'side' should now be board->whiteToMove.
    unmovePiece(board, move, lastState->capturedPiece);

    // 4. Reinstate state variables
    board->castlingRights = lastState->castlingRights;
    board->enPassantSquare = lastState->enPassantSquare;
    board->halfmoveClock = lastState->halfmoveClock;
    board->fullmoveNumber = lastState->fullMoveNumber;
}
void getSquareName(unsigned int sq, char *buf)
{
    buf[0] = 'a' + (char)(sq % 8);
    buf[1] = '1' + (char)(sq / 8);
    buf[2] = '\0';
}
// doesn't end with "\n"
// moves.c

void printMove(Move move)
{
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
    switch (flags)
    {
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
void getPseudoLegalMoves(const Board *board, Move *moveList, size_t *numMoves)
{

    getPawnMoves(board, moveList, numMoves);
    getKnightMoves(board, moveList, numMoves);
    getBishopMoves(board, moveList, numMoves);
    getRookMoves(board, moveList, numMoves);
    getQueenMoves(board, moveList, numMoves);
    getKingMoves(board, moveList, numMoves);
}

void getPawnMoves(const Board *board, Move *moveList, size_t *numMoves)
{
    enumPiece side = board->whiteToMove ? nWhite : nBlack;
    U64 pawns = getSpecificColorPieces(board, side, nPawn);

    while (pawns)
    {
        U64 pos = LSBIT(pawns);
        pawns = CLEARLSBIT(pawns);
        enumSquare fromSquare = __builtin_ctzll(pos);
        U64 emptySquares = ~getAllPieces(board);
        U64 removeLastRank = side == nWhite ? ~RANK_8 : ~RANK_1; // promotions handled separately

        U64 singlePushPattern = getSinglePushPattern(emptySquares, pos, side);
        extractMovesFromBB(moveList, numMoves, singlePushPattern & removeLastRank, fromSquare, QUIET_MOVE_FLAG);

        // only if single push is possible
        if (singlePushPattern)
        {
            U64 doublePushPattern = getDoublePushPattern(emptySquares, singlePushPattern, side);
            extractMovesFromBB(moveList, numMoves, doublePushPattern, fromSquare, DOUBLE_PAWN_PUSH_FLAG);
        }

        // get pawn attacks
        U64 attackPattern = getPawnAttackPattern(fromSquare, side);

        // and with opponent pieces to get captures, also remove last rank for promotions
        enumPiece opponentSide = side == nWhite ? nBlack : nWhite;
        U64 opponentPieces = getColorPieces(board, opponentSide);
        extractMovesFromBB(moveList, numMoves, attackPattern & opponentPieces & removeLastRank, fromSquare, CAPTURE_FLAG);

        // for promotions can just get every single push or capture that lands on last rank
        U64 promotionPushes = singlePushPattern & ~removeLastRank;
        for (int i = KNIGHT_PROMOTION_FLAG; i <= QUEEN_PROMOTION_FLAG; i++)
        {
            U64 copy = promotionPushes;
            extractMovesFromBB(moveList, numMoves, copy, fromSquare, (MoveFlag)i);
        }

        U64 promotionCaptures = attackPattern & opponentPieces & ~removeLastRank;
        for (int i = KNIGHT_PROMO_CAPTURE_FLAG; i <= QUEEN_PROMO_CAPTURE_FLAG; i++)
        {
            U64 copy = promotionCaptures;
            extractMovesFromBB(moveList, numMoves, copy, fromSquare, (MoveFlag)i);
        }

        // check enpassant if nonzero
        if (board->enPassantSquare)
        {
            U64 enPassantBit = 1ULL << board->enPassantSquare;
            // if they can get to the enpassant square by capturing it's valid
            U64 enPassantCaptures = attackPattern & enPassantBit;
            extractMovesFromBB(moveList, numMoves, enPassantCaptures, fromSquare, EN_PASSANT_CAPTURE_FLAG);
        }
    }
}
