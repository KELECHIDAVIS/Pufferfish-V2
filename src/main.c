// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "board.h"
#include "moves.h"
#include "attack_patterns.h"
#include "perft.h"
#include "searching.h"
#include <time.h>

#define INPUT_BUFFER 4096

// --- Helper: Convert UCI string (e.g., "e2e4", "a7a8q") to your internal Move ---
Move parseMove(Board *board, char *moveStr)
{
    // 1. Parse source and destination from string
    int fromFile = moveStr[0] - 'a';
    int fromRank = moveStr[1] - '1';
    int toFile = moveStr[2] - 'a';
    int toRank = moveStr[3] - '1';

    enumSquare from = fromRank * 8 + fromFile;
    enumSquare to = toRank * 8 + toFile;

    // 2. Generate all valid moves for the current position
    Move moveList[MAX_MOVES];
    size_t numMoves = 0;
    getPseudoLegalMoves(board, moveList, &numMoves);

    // 3. Find the matching move in the list
    for (size_t i = 0; i < numMoves; i++)
    {
        Move m = moveList[i];

        // Check if coordinates match
        if (getFrom(m) == from && getTo(m) == to)
        {
            // Check for promotion (if the string has a 5th char like 'q')
            unsigned int flags = getFlags(m);
            bool isPromo = (flags >= KNIGHT_PROMOTION_FLAG && flags <= QUEEN_PROMO_CAPTURE_FLAG);

            if (isPromo)
            {
                // If UCI string has no promo char but move is promo, skip (wrong move)
                // If UCI string has promo char, we must match the piece type
                if (strlen(moveStr) > 4)
                {
                    // char promoChar = moveStr[4];
                    //  Map flag to char to compare
                    //  (Simplified check: assuming 'q' is most common, or check your flag logic)
                    //  For robustness, you can verify exact type match here.
                    //  For now, if it's a promo flag and string has a char, we assume it's the right one
                    //  or simply return the first match if you don't support underpromotions yet.
                    return m;
                }
            }
            else
            {
                // Not a promotion move, and string has no promo char -> MATCH
                return m;
            }
        }
    }
    return 0; // Invalid move
}

// --- Helper: Handle "position" command from GUI ---
void parsePosition(Board *board, char *line)
{
    // line looks like: "position startpos moves e2e4 e7e5"
    // or: "position fen rnbqk... moves e2e4"

    char *ptr = line + 9; // Skip "position "

    if (strncmp(ptr, "startpos", 8) == 0)
    {
        initStandardChess(board);
        ptr += 8;
    }
    else if (strncmp(ptr, "fen", 3) == 0)
    {
        ptr += 4;              // Skip "fen "
        initBoard(board, ptr); // Your initBoard handles the FEN string
        // We need to advance ptr past the FEN string to get to "moves"
        // FENs end when " moves" starts.
        char *movesCmd = strstr(line, "moves");
        if (movesCmd)
        {
            ptr = movesCmd;
        }
        else
        {
            return; // No moves to apply
        }
    }

    // Apply moves if present
    ptr = strstr(line, "moves");
    if (ptr)
    {
        ptr += 6; // Skip "moves "
        while (*ptr)
        {
            // Extract the next move string (e.g., "e2e4")
            char moveStr[6];
            int i = 0;
            while (*ptr && *ptr != ' ' && *ptr != '\n' && i < 5)
            {
                moveStr[i++] = *ptr++;
            }
            moveStr[i] = '\0';

            // Skip spaces
            while (*ptr == ' ')
                ptr++;

            if (strlen(moveStr) > 0)
            {
                Move m = parseMove(board, moveStr);
                if (m != 0)
                {
                    makeMove(board, m);
                }
            }
        }
    }
    // Debug: print board to console so you can see it in Arena Log
    // printChessBoard(board);
}

// --- Helper: Parse "go perft <depth>" ---
void parseGo(Board *board, char *line)
{
    // "go perft 5" or just "go" (Arena might send just "go" for a game)
    // For debugging, we can implement a custom perft trigger.

    if (strstr(line, "perft"))
    {
        int depth = 3; // default
        char *ptr = strstr(line, "perft");
        if (ptr)
        {
            depth = atoi(ptr + 6);
        }

        clock_t t;
        t = clock();
        U64 nodes = divide(board, depth);
        t = clock() - t;
        double seconds = ((double)t) / CLOCKS_PER_SEC;
        U64 nodesPerSecond = (U64)((double)nodes / seconds);
        printf("Nodes Per Second: %llu\n", nodesPerSecond);
    }
    else // ex: go 4, return the best move searching a depth of 4
    {

        int depth = atoi (line+2); 
        
        if(!depth)
            depth = 5; //default; 

        
        Move bestMove = getBestMove(board, depth); 

        
        if (bestMove){
            printf("bestmove ");
            printMove(bestMove); 
            printf("\n"); 
        }else{ // If no moves or mated
            printf("bestmove (none)\n");
        }
    }
}

int main()
{
    char line[INPUT_BUFFER];
    Board board;

    // 1. Important: Disable buffering
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    initStandardChess(&board);
    precomputeAllAttacks();

    // 2. UCI Loop
    while (fgets(line, INPUT_BUFFER, stdin))
    {
        // Strip newline
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "uci") == 0)
        {
            printf("id name Pufferfish\n");
            printf("id author Kelechi Duru \n");
            printf("uciok\n");
        }
        else if (strcmp(line, "isready") == 0)
        {
            printf("readyok\n");
        }
        else if (strncmp(line, "position", 8) == 0)
        {
            parsePosition(&board, line);
        }
        else if (strncmp(line, "go", 2) == 0)
        {
            parseGo(&board, line);
        }
        else if (strcmp(line, "quit") == 0)
        {
            break;
        }
        else if (strcmp(line, "d") == 0)
        {
            printBoardDetails(&board);
        }
    }

 

    return 0;
}