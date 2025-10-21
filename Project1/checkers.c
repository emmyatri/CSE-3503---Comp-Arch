#include <stdio.h>
#include <stdlib.h>
#include "checkers.h"
#include "bitops.h"

//Initialize game

void InitGame(GameState* game) {
    // Red pieces: bits 20-31 represents rows 5-7 (bottom 3 rows)
    game->red_pieces = 0xFFF00000;
    game->red_kings = 0;
    
    // Black pieces: bits 0-11 represent rows 0-2 (top 3 rows)
    game->black_pieces = 0xFFF;
    game->black_kings = 0;
    
    game->current_player = 0;  // Red starts
}

void PrintBoard(GameState* game) { //construct visualization of game board
    printf("\n  ");
    for (int i = 0; i < 8; i++) {
        printf(" %d", i);
    }
    printf("\n");
    
    for (int row = 0; row < 8; row++) {
        printf("%d ", row);
        for (int col = 0; col < 8; col++) {
            if ((row + col) % 2 == 0) {
                printf("  ");  // Light square
            } else {
                int pos = PosToIndex(row, col);
                if (GetBit64(game->red_pieces, pos)) {
                    printf(" r"); //red piece
                } else if (GetBit64(game->red_kings, pos)) {
                    printf(" R"); //red king
                } else if (GetBit64(game->black_pieces, pos)) {
                    printf(" b"); //black piece
                } else if (GetBit64(game->black_kings, pos)) {
                    printf(" B"); //black king
                } else {
                    printf(" ."); //dark squares
                }
            }
        }
        printf("\n");
    }
    printf("\nCurrent player: %s\n\n", game->current_player == 0 ? "Red" : "Black"); //display the current player
}

// Position validation
int IsValidPos(int row, int col) { //validate the position
    return row >= 0 && row < 8 && col >= 0 && col < 8 && (row + col) % 2 == 1;
}

// Convert position to bit index
int PosToIndex(int row, int col) {
    if (!IsValidPos(row, col)) return -1;
    return (row * 8 + col) / 2;
}

// Convert bit index to position
void IndexToPos(int index, int* row, int* col) {
    *row = index / 4;
    *col = (index % 4) * 2 + ((*row + 1) % 2);
}

// Check if occupied
int IsOccupied(GameState* game, int position) {
    unsigned long long all = GetAllPieces(game);
    return GetBit64(all, position);
}

// Get piece owner
int GetPieceOwner(GameState* game, int position) {
    if (GetBit64(game->red_pieces | game->red_kings, position)) return 0;
    if (GetBit64(game->black_pieces | game->black_kings, position)) return 1;
    return -1;
}

// Check if king
int IsKing(GameState* game, int position) {
    return GetBit64(game->red_kings | game->black_kings, position);
}

// Get all pieces
unsigned long long GetAllPieces(GameState* game) {
    return game->red_pieces | game->red_kings | game->black_pieces | game->black_kings;
}

// Get player pieces
unsigned long long GetPlayerPieces(GameState* game, int player) {
    if (player == 0) {
        return game->red_pieces | game->red_kings;
    }
    return game->black_pieces | game->black_kings;
}

// Switch player
void SwitchPlayer(GameState* game) {
    game->current_player = 1 - game->current_player;
}

// Check for king promotion
void PromoteKing(GameState* game) {
    // Red pieces reaching row 0
    for (int col = 0; col < 8; col++) {
        int pos = PosToIndex(0, col);
        if (pos != -1 && GetBit64(game->red_pieces, pos)) {
            game->red_pieces = ClearBit64(game->red_pieces, pos);
            game->red_kings = SetBit64(game->red_kings, pos);
        }
    }
    
    // Black pieces reaching row 7
    for (int col = 0; col < 8; col++) {
        int pos = PosToIndex(7, col);
        if (pos != -1 && GetBit64(game->black_pieces, pos)) {
            game->black_pieces = ClearBit64(game->black_pieces, pos);
            game->black_kings = SetBit64(game->black_kings, pos);
        }
    }
}

// Make move
int MakeMove(GameState* game, int from, int to) {
    if (from < 0 || from >= 32 || to < 0 || to >= 32) return 0;
    if (!IsOccupied(game, from) || IsOccupied(game, to)) return 0;
    
    int owner = GetPieceOwner(game, from);
    if (owner != game->current_player) return 0;
    
    int fromRow, fromCol, toRow, toCol;
    IndexToPos(from, &fromRow, &fromCol);
    IndexToPos(to, &toRow, &toCol);
    
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    
    // Check valid move
    if (rowDiff != 1 || colDiff != 1) return 0;
    
    // Check direction for non-kings
    if (!IsKing(game, from)) {
        if (owner == 0 && toRow > fromRow) return 0;  // Red must move up
        if (owner == 1 && toRow < fromRow) return 0;  // Black must move down
    }
    
    // Move piece
    if (owner == 0) {
        if (IsKing(game, from)) {
            game->red_kings = ClearBit64(game->red_kings, from);
            game->red_kings = SetBit64(game->red_kings, to);
        } else {
            game->red_pieces = ClearBit64(game->red_pieces, from);
            game->red_pieces = SetBit64(game->red_pieces, to);
        }
    } else {
        if (IsKing(game, from)) {
            game->black_kings = ClearBit64(game->black_kings, from);
            game->black_kings = SetBit64(game->black_kings, to);
        } else {
            game->black_pieces = ClearBit64(game->black_pieces, from);
            game->black_pieces = SetBit64(game->black_pieces, to);
        }
    }
    
    PromoteKing(game);
    SwitchPlayer(game);
    return 1;
}

// Make capture
int MakeCapture(GameState* game, int from, int to) {
    if (from < 0 || from >= 32 || to < 0 || to >= 32) return 0;
    if (!IsOccupied(game, from) || IsOccupied(game, to)) return 0;
    
    int owner = GetPieceOwner(game, from);
    if (owner != game->current_player) return 0;
    
    int fromRow, fromCol, toRow, toCol;
    IndexToPos(from, &fromRow, &fromCol);
    IndexToPos(to, &toRow, &toCol);
    
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    
    // Check valid jump
    if (rowDiff != 2 || colDiff != 2) return 0;
    
    // Check direction for non-kings
    if (!IsKing(game, from)) {
        if (owner == 0 && toRow > fromRow) return 0;  // Red must move up
        if (owner == 1 && toRow < fromRow) return 0;  // Black must move down
    }
    
    // Check captured piece
    int midRow = (fromRow + toRow) / 2;
    int midCol = (fromCol + toCol) / 2;
    int midPos = PosToIndex(midRow, midCol);
    
    if (!IsOccupied(game, midPos)) return 0;
    if (GetPieceOwner(game, midPos) == owner) return 0;
    
    // Remove captured piece
    if (GetPieceOwner(game, midPos) == 0) {
        if (IsKing(game, midPos)) {
            game->red_kings = ClearBit64(game->red_kings, midPos);
        } else {
            game->red_pieces = ClearBit64(game->red_pieces, midPos);
        }
    } else {
        if (IsKing(game, midPos)) {
            game->black_kings = ClearBit64(game->black_kings, midPos);
        } else {
            game->black_pieces = ClearBit64(game->black_pieces, midPos);
        }
    }
    
    // Move piece
    if (owner == 0) {
        if (IsKing(game, from)) {
            game->red_kings = ClearBit64(game->red_kings, from);
            game->red_kings = SetBit64(game->red_kings, to);
        } else {
            game->red_pieces = ClearBit64(game->red_pieces, from);
            game->red_pieces = SetBit64(game->red_pieces, to);
        }
    } else {
        if (IsKing(game, from)) {
            game->black_kings = ClearBit64(game->black_kings, from);
            game->black_kings = SetBit64(game->black_kings, to);
        } else {
            game->black_pieces = ClearBit64(game->black_pieces, from);
            game->black_pieces = SetBit64(game->black_pieces, to);
        }
    }
    
    PromoteKing(game);
    SwitchPlayer(game);
    return 1;
}

// Check if player has won
int HasWon(GameState* game, int player) {
    // Check if opponent has no pieces
    if (player == 0) {
        return (game->black_pieces | game->black_kings) == 0;
    } else {
        return (game->red_pieces | game->red_kings) == 0;
    }
}

// Check if player can move
int CanMove(GameState* game, int player) {
    unsigned long long pieces = GetPlayerPieces(game, player);
    
    // Check each piece
    for (int i = 0; i < 32; i++) {
        if (!GetBit64(pieces, i)) continue;
        
        int row, col;
        IndexToPos(i, &row, &col);
        
        // Check all possible moves
        int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        
        for (int d = 0; d < 4; d++) {
            int newRow = row + directions[d][0];
            int newCol = col + directions[d][1];
            
            // Check move
            if (IsValidPos(newRow, newCol)) {
                int newPos = PosToIndex(newRow, newCol);
                if (!IsOccupied(game, newPos)) {
                    // Check direction for non-kings
                    if (!IsKing(game, i)) {
                        if (player == 0 && directions[d][0] > 0) continue;
                        if (player == 1 && directions[d][0] < 0) continue;
                    }
                    return 1;  // Found valid move
                }
            }
            
            // Check jump
            int jumpRow = row + 2 * directions[d][0];
            int jumpCol = col + 2 * directions[d][1];
            
            if (IsValidPos(jumpRow, jumpCol)) {
                int jumpPos = PosToIndex(jumpRow, jumpCol);
                int midPos = PosToIndex(newRow, newCol);
                
                if (!IsOccupied(game, jumpPos) && IsOccupied(game, midPos) && 
                    GetPieceOwner(game, midPos) != player) {
                    // Check direction for non-kings
                    if (!IsKing(game, i)) {
                        if (player == 0 && directions[d][0] > 0) continue;
                        if (player == 1 && directions[d][0] < 0) continue;
                    }
                    return 1;  // Found valid jump
                }
            }
        }
    }

    
    return 0;  // No valid moves
}

// Validate ability to capture
int CanPieceCapture(GameState* game, int piecePos, int player) {
    if (!GetBit64(GetPlayerPieces(game, player), piecePos)) return 0;

    int row, col;
    IndexToPos(piecePos, &row, &col);
    int isKing = IsKing(game, piecePos);

    // Check all 4 diagonal directions
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (int d = 0; d < 4; d++) {

        // Skip backward directions for non-kings
        if (!isKing) {
            if (player == 0 && directions[d][0] > 0) continue;  // Red can't go down
            if (player == 1 && directions[d][0] < 0) continue;  // Black can't go up
        }

        int midRow = row + directions[d][0];
        int midCol = col + directions[d][1];
        int jumpRow = row + 2 * directions[d][0];
        int jumpCol = col + 2 * directions[d][1];

        if (IsValidPos(midRow, midCol) && IsValidPos(jumpRow, jumpCol)) {
            int midPos = PosToIndex(midRow, midCol);
            int jumpPos = PosToIndex(jumpRow, jumpCol);

            // Check if there's an opponent piece to jump and landing is empty
            if (IsOccupied(game, midPos) &&
                GetPieceOwner(game, midPos) != player &&
                !IsOccupied(game, jumpPos)) {
                return 1;  // Can capture
                }
        }
    }

    return 0;  // No captures available
}

int HasCaptures(GameState* game, int player) { //check if capture is available
    unsigned long long pieces = GetPlayerPieces(game, player);

    for (int i = 0; i < 32; i++) {
        if (GetBit64(pieces, i) && CanPieceCapture(game, i, player)) {
            return 1;
        }
    }

    return 0;
}

// Get all possible captures for display
void GetPossibleCaptures(GameState* game, int player, int* captures, int* count) {
    *count = 0;
    unsigned long long pieces = GetPlayerPieces(game, player);

    for (int i = 0; i < 32; i++) {
        if (GetBit64(pieces, i) && CanPieceCapture(game, i, player)) {
            captures[(*count)++] = i;
        }
    }
}

// Check for multiple jumps after a capture
int CanContinueCapture(GameState* game, int position) {
    // Get the owner of the piece at this position
    int player = GetPieceOwner(game, position);
    if (player == -1) return 0;  // No piece at position

    return CanPieceCapture(game, position, player);
}