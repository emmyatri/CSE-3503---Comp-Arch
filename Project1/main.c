// main.c - Main entry point for BitBoard Checkers with SDL2 GUI
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checkers.h"
#include "bitops.h"

// Test bit operations to demonstrate Phase 1 functionality
void TestBitOperations() {
    printf("=== TESTING BIT OPERATIONS (Phase 1) ===\n\n");
    
    unsigned int test = 0;
    printf("Initial value: ");
    PrintBinary(test);
    PrintHex(test);
    
    test = SetBit(test, 3);
    printf("\nAfter SetBit(3): ");
    PrintBinary(test);
    
    test = SetBit(test, 7);
    printf("After SetBit(7): ");
    PrintBinary(test);
    
    printf("GetBit(3): %d\n", GetBit(test, 3));
    printf("GetBit(4): %d\n", GetBit(test, 4));
    
    test = ToggleBit(test, 3);
    printf("\nAfter ToggleBit(3): ");
    PrintBinary(test);
    
    test = ClearBit(test, 7);
    printf("After ClearBit(7): ");
    PrintBinary(test);
    
    printf("\nCountBits: %d\n", CountBits(test));
    
    test = ShiftLeft(test, 2);
    printf("\nAfter ShiftLeft(2): ");
    PrintBinary(test);
    
    // Test 64-bit operations
    printf("\n\n=== Testing 64-bit Operations ===\n");
    unsigned long long test64 = 0xFFF;  // 12 bits set
    printf("Initial 64-bit value: ");
    PrintBinary64(test64);
    
    test64 = SetBit64(test64, 20);
    printf("After SetBit64(20): ");
    PrintBinary64(test64);
    
    printf("CountBits64: %d\n", CountBits64(test64));
    
    printf("\n=== BIT OPERATIONS TEST COMPLETE ===\n");
    printf("Press Enter to start the game...");
    getchar();
}

void ClearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void PrintInstructions() {
    printf("\n=== BITBOARD CHECKERS ===\n");
    printf("Instructions:\n");
    printf("- Enter moves as: row,col to row,col (e.g., 2,1 to 3,2)\n");
    printf("- Red pieces: r (regular), R (king)\n");
    printf("- Black pieces: b (regular), B (king)\n");
    printf("- Type 'quit' to exit\n");
    printf("- Type 'help' for instructions\n\n");
}

int ParseMove(const char* input, int* fromRow, int* fromCol, int* toRow, int* toCol) {
    if (sscanf(input, "%d,%d to %d,%d", fromRow, fromCol, toRow, toCol) == 4) {
        return 1;
    }
    return 0;
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
            printf("Thanks for playing!\n");
            break;
        } else if (strcmp(input, "help") == 0) {
            PrintInstructions();
            continue;
        }

        // Parse move
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
            // Regular move - but check for mandatory captures first
            if (HasCaptures(&game, game.current_player)) {
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
                        if (!isKing) {
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

                            if (IsOccupied(&game, midPos) &&
                                GetPieceOwner(&game, midPos) != capturePlayer &&
                                !IsOccupied(&game, jumpPos)) {
                                printf("  Can jump to (%d,%d)\n", jumpRow, jumpCol);
                            }
                        }
                    }
                    // Don't switch players yet - they need to continue
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