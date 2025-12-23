#include <gtest/gtest.h>
#include <string>
#include <vector>

extern "C" {
#include "board.h"
#include "perft.h"
}

class ChessEnvironment : public ::testing::Environment {
  public:
    // This runs once before all tests in the entire program
    void SetUp() override {
        precomputeAllAttacks();
    }

    // This runs once after all tests have finished
    void TearDown() override {
        // Optional: clean up memory if your engine allocates tables on the heap
    }
};

// Structure to hold our test data
struct PerftTestParams {
    std::string label;  // Name of the position (e.g., "Kiwipete")
    std::string fen;    // The FEN string to set up
    int depth;          // Depth to search
    U64 expected_nodes; // Correct leaf node count
};

class PerftTest : public ::testing::TestWithParam<PerftTestParams> {
  public:
    // This runs once before the first test in this suite starts
    static void SetUpTestSuite() {
        printf("\n[ ENGINE ] Precomputing attack tables...\n");
        precomputeAllAttacks();
    }

    // Optional: runs before EVERY individual test
    void SetUp() override {
        // Reset board or other engine state if needed
    }
};

TEST_P(PerftTest, VerifyMoveGeneration) {
    const auto &params = GetParam();
    Board board;
    std::string fen_copy = params.fen;
    initBoard(&board, &fen_copy[0]);

    precomputeAllAttacks();

    // 2. Execute perft
    U64 actual_nodes = perft(&board, params.depth);

    // 3. Assert with a custom message for better debugging
    EXPECT_EQ(actual_nodes, params.expected_nodes)
        << "Failed " << params.label
        << " at Depth " << params.depth
        << "\nFEN: " << params.fen;
}

INSTANTIATE_TEST_SUITE_P(
    OfficialSuite,
    PerftTest,
    ::testing::Values(
        // --- Standard Starting Position ---
        PerftTestParams{"StartPos_D0", "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 0, 1},
        PerftTestParams{"StartPos_D1", "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 1, 20},
        PerftTestParams{"StartPos_D2", "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 2, 400},
        PerftTestParams{"StartPos_D3", "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 3, 8902},
        PerftTestParams{"StartPos_D4", "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 4, 197281},
        PerftTestParams{"StartPos_D5", "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 5, 4865609},
        PerftTestParams{"StartPos_D6", "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 6, 119060324},

        // --- Position 2: Kiwipete (Tests complex movegen like en passant/castling) ---
        PerftTestParams{"Kiwipete_D1", "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1", 1, 48},
        PerftTestParams{"Kiwipete_D2", "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1", 2, 2039},
        PerftTestParams{"Kiwipete_D3", "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1", 3, 97862},
        PerftTestParams{"Kiwipete_D4", "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1", 4, 4085603},
        PerftTestParams{"Kiwipete_D5", "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1", 5, 193690690},
        /*TODO:  THIS ONE GIVES ERROR MAY COME BACK TO IT LATER  */
        PerftTestParams{"Kiwipete_D6", "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1", 6, 8031647685ULL},

        /* Next few positions are from : https://www.chessprogramming.org/Perft_Results */
        PerftTestParams{"Position3_D1", "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1", 1, 14},
        PerftTestParams{"Position3_D2", "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1", 2, 191},
        PerftTestParams{"Position3_D3", "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1", 3, 2812},
        PerftTestParams{"Position3_D4", "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1", 4, 43238},
        PerftTestParams{"Position3_D5", "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1", 5, 674624},
        PerftTestParams{"Position3_D6", "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1", 6, 11030083},
        PerftTestParams{"Position3_D7", "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1", 7, 178633661ULL},
        PerftTestParams{"Position3_D8", "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1", 8, 3009794393ULL},

        PerftTestParams{"Position4_D1", "r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 1, 6},
        PerftTestParams{"Position4_D2", "r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 2, 264},
        PerftTestParams{"Position4_D3", "r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 3, 9467},
        PerftTestParams{"Position4_D4", "r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 4, 422333},
        PerftTestParams{"Position4_D5", "r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 5, 15833292},
        PerftTestParams{"Position4_D6", "r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 6, 706045033ULL}

        ),

    [](const testing::TestParamInfo<PerftTestParams> &info) {
        return info.param.label; // Use the 'label' field as the test name
    }

);
