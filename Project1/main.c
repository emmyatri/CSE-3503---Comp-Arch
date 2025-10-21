// main.c - Main entry point for BitBoard Checkers with SDL2 GUI
#include <stdio.h>
#include <stdlib.h>
#include "checkers.h"
#include "bitops.h"

// Function prototype for GUI (implemented in checkers_gui.c)
int RunGUI(GameState* game);

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

int main(int argc, char* argv[]) {
    // Test bit operations first (demonstrates Phase 1)
    TestBitOperations();
    
    // Initialize game
    GameState game;
    InitGame(&game);
    
    // Start GUI
    printf("\nStarting BitBoard Checkers GUI...\n");
    printf("\nControls:\n");
    printf("  Left click - Select piece or move\n");
    printf("  B key - Toggle bitboard display\n");
    printf("  R key - Reset game\n");
    printf("  ESC - Exit\n\n");
    
    return RunGUI(&game);
}