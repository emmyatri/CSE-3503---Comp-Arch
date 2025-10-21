#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checkers.h"
#include "bitops.h"

// Test bit operations to demonstrate Phase 1 functionality
void TestBitOperations() {
    printf("=== COMPREHENSIVE BIT OPERATIONS TESTING (Phase 1) ===\n\n");

    int passed = 0;
    int failed = 0;

    // Test 1: SetBit Operation
    printf("TEST 1: SetBit Operation\n");
    printf("----------------------------------------\n");
    unsigned int test1 = 0;
    printf("Initial value: ");
    PrintBinary(test1);
    PrintHex(test1);

    test1 = SetBit(test1, 0);
    printf("After SetBit(0): ");
    PrintBinary(test1);
    if (test1 == 0x00000001) {
        printf("PASS: SetBit(0) correctly set bit 0\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x00000001, got 0x%08X\n", test1);
        failed++;
    }

    test1 = SetBit(test1, 15);
    printf("\nAfter SetBit(15): ");
    PrintBinary(test1);
    if (test1 == 0x00008001) {
        printf("PASS: SetBit(15) correctly set bit 15\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x00008001, got 0x%08X\n", test1);
        failed++;
    }

    test1 = SetBit(test1, 31);
    printf("\nAfter SetBit(31): ");
    PrintBinary(test1);
    if (test1 == 0x80008001) {
        printf("PASS: SetBit(31) correctly set bit 31\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x80008001, got 0x%08X\n", test1);
        failed++;
    }

    // Test 2: GetBit Operation
    printf("\n\nTEST 2: GetBit Operation\n");
    printf("----------------------------------------\n");
    unsigned int test2 = 0x0000000A; // Binary: 1010
    printf("Test value: \n");
    printf("Binary: ");
    PrintBinary(test2);
    printf("Hexadecimal: ");
    PrintHex(test2);

    int bit_val = GetBit(test2, 1);
    printf("GetBit(1): %d ", bit_val);
    if (bit_val == 1) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (Expected 1)\n");
        failed++;
    }

    bit_val = GetBit(test2, 2);
    printf("GetBit(2): %d ", bit_val);
    if (bit_val == 0) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (Expected 0)\n");
        failed++;
    }

    bit_val = GetBit(test2, 3);
    printf("GetBit(3): %d ", bit_val);
    if (bit_val == 1) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (Expected 1)\n");
        failed++;
    }

    // Test 3: ToggleBit Operation
    printf("\n\nTEST 3: ToggleBit Operation\n");
    printf("----------------------------------------\n");
    unsigned int test3 = 0x0000000F; // Binary: 1111
    printf("Initial value: ");
    PrintBinary(test3);
    PrintHex(test3);

    test3 = ToggleBit(test3, 0);
    printf("\nAfter ToggleBit(0): ");
    PrintBinary(test3);
    if (test3 == 0x0000000E) {
        printf("PASS: Toggled bit 0 from 1 to 0\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x0000000E, got 0x%08X\n", test3);
        failed++;
    }

    test3 = ToggleBit(test3, 4);
    printf("\nAfter ToggleBit(4): ");
    PrintBinary(test3);
    if (test3 == 0x0000001E) {
        printf("PASS: Toggled bit 4 from 0 to 1\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x0000001E, got 0x%08X\n", test3);
        failed++;
    }

    test3 = ToggleBit(test3, 4);
    printf("\nAfter ToggleBit(4) again: ");
    PrintBinary(test3);
    if (test3 == 0x0000000E) {
        printf("PASS: Toggled bit 4 back from 1 to 0\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x0000000E, got 0x%08X\n", test3);
        failed++;
    }

    // Test 4: ClearBit Operation
    printf("\n\nTEST 4: ClearBit Operation\n");
    printf("----------------------------------------\n");
    unsigned int test4 = 0xFFFFFFFF; // All bits set
    printf("Initial value: ");
    PrintBinary(test4);
    PrintHex(test4);

    test4 = ClearBit(test4, 0);
    printf("\nAfter ClearBit(0): ");
    PrintBinary(test4);
    if (test4 == 0xFFFFFFFE) {
        printf("PASS: Cleared bit 0\n");
        passed++;
    } else {
        printf("FAIL: Expected 0xFFFFFFFE, got 0x%08X\n", test4);
        failed++;
    }

    test4 = ClearBit(test4, 16);
    printf("\nAfter ClearBit(16): ");
    PrintBinary(test4);
    if (test4 == 0xFFFEFFFE) {
        printf("PASS: Cleared bit 16\n");
        passed++;
    } else {
        printf("FAIL: Expected 0xFFFEFFFE, got 0x%08X\n", test4);
        failed++;
    }

    test4 = ClearBit(test4, 31);
    printf("\nAfter ClearBit(31): ");
    PrintBinary(test4);
    if (test4 == 0x7FFEFFFE) {
        printf("PASS: Cleared bit 31\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x7FFEFFFE, got 0x%08X\n", test4);
        failed++;
    }

    // Test 5: ShiftLeft Operation
    printf("\n\nTEST 5: ShiftLeft Operation\n");
    printf("----------------------------------------\n");
    unsigned int test5 = 0x00000001;
    printf("Initial value: ");
    PrintBinary(test5);
    PrintHex(test5);

    test5 = ShiftLeft(test5, 1);
    printf("\nAfter ShiftLeft(1): ");
    PrintBinary(test5);
    if (test5 == 0x00000002) {
        printf("PASS: Shifted left by 1\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x00000002, got 0x%08X\n", test5);
        failed++;
    }

    test5 = ShiftLeft(test5, 3);
    printf("\nAfter ShiftLeft(3): ");
    PrintBinary(test5);
    if (test5 == 0x00000010) {
        printf("PASS: Shifted left by 3\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x00000010, got 0x%08X\n", test5);
        failed++;
    }

    unsigned int test5b = 0x0000000F;
    test5b = ShiftLeft(test5b, 4);
    printf("\nShiftLeft(0x0F, 4): ");
    PrintBinary(test5b);
    if (test5b == 0x000000F0) {
        printf("PASS: Shifted 0x0F left by 4\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x000000F0, got 0x%08X\n", test5b);
        failed++;
    }

    // Test 6: ShiftRight Operation
    printf("\n\nTEST 6: ShiftRight Operation\n");
    printf("----------------------------------------\n");
    unsigned int test6 = 0x80000000;
    printf("Initial value: ");
    PrintBinary(test6);
    PrintHex(test6);

    test6 = ShiftRight(test6, 1);
    printf("\nAfter ShiftRight(1): ");
    PrintBinary(test6);
    if (test6 == 0x40000000) {
        printf("PASS: Shifted right by 1\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x40000000, got 0x%08X\n", test6);
        failed++;
    }

    test6 = ShiftRight(test6, 4);
    printf("\nAfter ShiftRight(4): ");
    PrintBinary(test6);
    if (test6 == 0x04000000) {
        printf("PASS: Shifted right by 4\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x04000000, got 0x%08X\n", test6);
        failed++;
    }

    unsigned int test6b = 0x000000F0;
    test6b = ShiftRight(test6b, 4);
    printf("\nShiftRight(0xF0, 4): ");
    PrintBinary(test6b);
    if (test6b == 0x0000000F) {
        printf("PASS: Shifted 0xF0 right by 4\n");
        passed++;
    } else {
        printf("FAIL: Expected 0x0000000F, got 0x%08X\n", test6b);
        failed++;
    }

    // Test 7: CountBits Operation
    printf("\n\nTEST 7: CountBits Operation\n");
    printf("----------------------------------------\n");
    unsigned int test7 = 0x0000000F; // 4 bits set
    int count = CountBits(test7);
    printf("CountBits(0x0000000F): %d ", count);
    if (count == 4) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (Expected 4)\n");
        failed++;
    }

    test7 = 0x000000FF; // 8 bits set
    count = CountBits(test7);
    printf("CountBits(0x000000FF): %d ", count);
    if (count == 8) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (Expected 8)\n");
        failed++;
    }

    test7 = 0xFFFFFFFF; // All 32 bits set
    count = CountBits(test7);
    printf("CountBits(0xFFFFFFFF): %d ", count);
    if (count == 32) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (Expected 32)\n");
        failed++;
    }

    // Test 8: Edge Cases
    printf("\n\nTEST 8: Edge Cases & Boundary Conditions\n");
    printf("----------------------------------------\n");

    // Test invalid positions
    unsigned int test8 = 0x00000001;
    unsigned int result = SetBit(test8, -1);
    if (result == test8) {
        printf("PASS: SetBit with negative position returns unchanged\n");
        passed++;
    } else {
        printf("FAIL: SetBit with negative position modified value\n");
        failed++;
    }

    result = SetBit(test8, 32);
    if (result == test8) {
        printf("PASS: SetBit with position >= 32 returns unchanged\n");
        passed++;
    } else {
        printf("FAIL: SetBit with position >= 32 modified value\n");
        failed++;
    }

    // Test 9: 64-bit Operations
    printf("\n\nTEST 9: 64-bit Operations\n");
    printf("----------------------------------------\n");
    unsigned long long test64 = 0xFFF;  // 12 bits set
    printf("Initial 64-bit value: ");
    PrintBinary64(test64);

    int count64 = CountBits64(test64);
    printf("CountBits64(0xFFF): %d ", count64);
    if (count64 == 12) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (Expected 12)\n");
        failed++;
    }

    test64 = SetBit64(test64, 20);
    printf("\nAfter SetBit64(20): ");
    PrintBinary64(test64);
    if (GetBit64(test64, 20) == 1) {
        printf("PASS: SetBit64(20) correctly set\n");
        passed++;
    } else {
        printf("FAIL: SetBit64(20) did not set bit\n");
        failed++;
    }

    test64 = ClearBit64(test64, 0);
    if (GetBit64(test64, 0) == 0) {
        printf("PASS: ClearBit64(0) correctly cleared\n");
        passed++;
    } else {
        printf("FAIL: ClearBit64(0) did not clear bit\n");
        failed++;
    }

    // Final Summary
    printf("\n\n");
    printf("========================================\n");
    printf("       TEST SUMMARY\n");
    printf("========================================\n");
    printf("Tests Passed: %d\n", passed);
    printf("Tests Failed: %d\n", failed);
    printf("Total Tests:  %d\n", passed + failed);
    printf("========================================\n");

    if (failed == 0) {
        printf("\nALL TESTS PASSED! Phase 1 is working correctly.\n");
    } else {
        printf("\n⚠Some tests failed. Review the failures above.\n");
    }

    printf("\nPress Enter to start the game...");
    getchar(); //collect keystroke from user
}

void ClearScreen() { //clear the terminal to start checkers game (cross-platform)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void PrintInstructions() { //write game instructions
    printf("\n=== BITBOARD CHECKERS ===\n");
    printf("Instructions:\n");
    printf("- Enter moves as: row,col to row,col (e.g., 2,1 to 3,2)\n");
    printf("- Red pieces: r (regular), R (king)\n");
    printf("- Black pieces: b (regular), B (king)\n");
    printf("- Type 'quit' to exit\n");
    printf("- Type 'help' for instructions\n\n");
}

// Parse player input into move coordinates
int ParseMove(const char* input, int* fromRow, int* fromCol, int* toRow, int* toCol) {
    if (sscanf(input, "%d,%d to %d,%d", fromRow, fromCol, toRow, toCol) == 4) {
        return 1; //on success
    }
    return 0; //on failure
}

int main(int argc, char* argv[]) {

    // Test bit operations first (demonstrates Phase 1)
    TestBitOperations();

    // Initialize game
    GameState game;
    InitGame(&game);

    char input[100];
    int fromRow, fromCol, toRow, toCol;

    ClearScreen();
    PrintInstructions();

    // Main game loop
    while (1) {
        PrintBoard(&game);

        // Check for win condition
        if (HasWon(&game, 0)) {
            printf("Red wins!\n");
            break;
        } else if (HasWon(&game, 1)) {
            printf("Black wins!\n");
            break;
        }

        // Check if current player can move
        if (!CanMove(&game, game.current_player)) {
            printf("%s has no valid moves. %s wins!\n",
                   game.current_player == 0 ? "Red" : "Black",
                   game.current_player == 0 ? "Black" : "Red");
            break;
        }

        // Get player input
        printf("Enter move (row,col to row,col) or type 'quit' to exit: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove newline
        input[strcspn(input, "\n")] = 0;

        // Check for special commands
        if (strcmp(input, "quit") == 0) {
            printf("\n\nThanks for playing!\n"); //exit message when program terminates
            break;
        } else if (strcmp(input, "help") == 0) { //redisplay the menu if the user needs to see instructions again
            PrintInstructions();
            continue;
        }

        // Parse move and validate
        if (!ParseMove(input, &fromRow, &fromCol, &toRow, &toCol)) {
            printf("Invalid format. Use: row,col to row,col\n");
            continue;
        }

        // Validate positions
        if (!IsValidPos(fromRow, fromCol) || !IsValidPos(toRow, toCol)) {
            printf("Invalid position. Use dark squares only.\n");
            continue;
        }

        // Convert to bit positions
        int from = PosToIndex(fromRow, fromCol);
        int to = PosToIndex(toRow, toCol);

        // Try to make the move
        int moveDistance = abs(toRow - fromRow);
        if (moveDistance == 1) {
            if (HasCaptures(&game, game.current_player)) { // Regular move - but check for mandatory captures first
                printf("You must capture! Available captures:\n");

                // Show all pieces that can capture
                unsigned long long pieces = GetPlayerPieces(&game, game.current_player);
                for (int i = 0; i < 32; i++) {
                    if (GetBit64(pieces, i) && CanPieceCapture(&game, i, game.current_player)) {
                        int r, c;
                        IndexToPos(i, &r, &c);
                        printf("  Piece at (%d,%d) can capture\n", r, c);
                    }
                }
                continue;  // Skip to next iteration of game loop
            }

            // No captures available, make regular move
            if (MakeMove(&game, from, to)) {
                ClearScreen();
                printf("Move successful!\n");
            } else {
                printf("Invalid move. Try again.\n");
            }
        } else if (moveDistance == 2) {
            // Jump/capture
            // Store position for potential multiple jumps
            int jumpingPiecePos = to;
            int capturePlayer = game.current_player;

            if (MakeCapture(&game, from, to)) {
                ClearScreen();
                printf("Capture successful!\n");

                // Check for multiple jumps
                // Temporarily switch back to check if piece can continue
                game.current_player = capturePlayer;
                if (CanPieceCapture(&game, jumpingPiecePos, capturePlayer)) {
                    // Player must continue jumping
                    printf("\nYou must continue jumping with the piece at ");
                    int r, c;
                    IndexToPos(jumpingPiecePos, &r, &c);
                    printf("(%d,%d)\n", r, c);

                    // Show available jumps
                    printf("Available captures from this position:\n");
                    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
                    int isKing = IsKing(&game, jumpingPiecePos);

                    for (int d = 0; d < 4; d++) {
                        if (!isKing) { //non-kings cannot go backward
                            if (capturePlayer == 0 && directions[d][0] > 0) continue;
                            if (capturePlayer == 1 && directions[d][0] < 0) continue;
                        }

                        int midRow = r + directions[d][0];
                        int midCol = c + directions[d][1];
                        int jumpRow = r + 2 * directions[d][0];
                        int jumpCol = c + 2 * directions[d][1];

                        if (IsValidPos(midRow, midCol) && IsValidPos(jumpRow, jumpCol)) {
                            int midPos = PosToIndex(midRow, midCol);
                            int jumpPos = PosToIndex(jumpRow, jumpCol);

                            if (IsOccupied(&game, midPos) && //check valid capture: enemy in middle with empty square to jump to
                                GetPieceOwner(&game, midPos) != capturePlayer &&
                                !IsOccupied(&game, jumpPos)) {
                                printf("  Can jump to (%d,%d)\n", jumpRow, jumpCol);
                            }
                        }
                    }
                    // Don't switch players yet - they have more jumps
                } else {
                    // No more jumps, switch to other player
                    game.current_player = 1 - capturePlayer;
                }
            } else {
                printf("Invalid capture. Try again.\n");
            }
        } else {
            printf("Invalid move distance.\n");
        }
    }

    return 0;
}