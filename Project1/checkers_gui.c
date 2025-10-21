// checkers_gui.c - SDL2 GUI implementation for checkers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "checkers.h"
#include "bitops.h"

// Window and board dimensions
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 720
#define BOARD_SIZE 480
#define SQUARE_SIZE (BOARD_SIZE / 8)
#define BOARD_OFFSET_X 80
#define BOARD_OFFSET_Y 80

// Colors
#define COLOR_LIGHT_SQUARE 0xF0D9B5FF
#define COLOR_DARK_SQUARE 0xB58863FF
#define COLOR_RED_PIECE 0xE74C3CFF
#define COLOR_BLACK_PIECE 0x2C3E50FF
#define COLOR_SELECTED 0x3498DBFF
#define COLOR_POSSIBLE_MOVE 0x3498DB80
#define COLOR_BACKGROUND 0x2C3E50FF

// GUI state
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    GameState* game;
    int selected_piece;
    int possible_moves[12];
    int num_possible_moves;
    int show_bits;
} GUI_State;

// Function prototypes
static int InitSDL(GUI_State* gui);
static void CleanupSDL(GUI_State* gui);
static void SetRenderColor(SDL_Renderer* renderer, Uint32 color);
static void DrawText(GUI_State* gui, const char* text, int x, int y, SDL_Color color);
static void DrawCircle(SDL_Renderer* renderer, int cx, int cy, int radius);
static void DrawPiece(GUI_State* gui, int row, int col, int isRed, int isKing, int isSelected);
static void CalculatePossibleMoves(GUI_State* gui);
static int IsPossibleMove(GUI_State* gui, int pos);
static void DrawBoard(GUI_State* gui);
static void HandleClick(GUI_State* gui, int x, int y);

// Initialize SDL
static int InitSDL(GUI_State* gui) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL init failed: %s\n", SDL_GetError());
        return 0;
    }
    
    if (TTF_Init() < 0) {
        printf("TTF init failed: %s\n", TTF_GetError());
        SDL_Quit();
        return 0;
    }
    
    gui->window = SDL_CreateWindow("BitBoard Checkers",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    
    if (!gui->window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 0;
    }
    
    gui->renderer = SDL_CreateRenderer(gui->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (!gui->renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(gui->window);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }
    
    // Try to load font - continue without it if not found
    gui->font = TTF_OpenFont("arial.ttf", 16);
    if (!gui->font) {
        gui->font = TTF_OpenFont("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 16);
    }
    if (!gui->font) {
        gui->font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 16);
    }
    if (!gui->font) {
        printf("Warning: Font not loaded, continuing without text\n");
    }
    
    return 1;
}

// Cleanup SDL
static void CleanupSDL(GUI_State* gui) {
    if (gui->font) TTF_CloseFont(gui->font);
    if (gui->renderer) SDL_DestroyRenderer(gui->renderer);
    if (gui->window) SDL_DestroyWindow(gui->window);
    TTF_Quit();
    SDL_Quit();
}

// Convert RGBA to SDL format
static void SetRenderColor(SDL_Renderer* renderer, Uint32 color) {
    SDL_SetRenderDrawColor(renderer,
        (color >> 24) & 0xFF,
        (color >> 16) & 0xFF,
        (color >> 8) & 0xFF,
        color & 0xFF);
}

// Draw text
static void DrawText(GUI_State* gui, const char* text, int x, int y, SDL_Color color) {
    if (!gui->font) return;
    
    SDL_Surface* surface = TTF_RenderText_Solid(gui->font, text, color);
    if (!surface) return;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gui->renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect dest = {x, y, surface->w, surface->h};
    SDL_RenderCopy(gui->renderer, texture, NULL, &dest);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// Draw a filled circle
static void DrawCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

// Draw a piece
static void DrawPiece(GUI_State* gui, int row, int col, int isRed, int isKing, int isSelected) {
    int x = BOARD_OFFSET_X + col * SQUARE_SIZE + SQUARE_SIZE / 2;
    int y = BOARD_OFFSET_Y + row * SQUARE_SIZE + SQUARE_SIZE / 2;
    int radius = SQUARE_SIZE / 2 - 10;
    
    // Draw piece shadow for depth
    SetRenderColor(gui->renderer, 0x00000080);
    DrawCircle(gui->renderer, x + 2, y + 2, radius);
    
    // Draw piece
    SetRenderColor(gui->renderer, isRed ? COLOR_RED_PIECE : COLOR_BLACK_PIECE);
    DrawCircle(gui->renderer, x, y, radius);
    
    // Draw piece border
    SetRenderColor(gui->renderer, 0x000000FF);
    for (int i = 0; i < 2; i++) {
        for (int angle = 0; angle < 360; angle++) {
            int px = x + (radius - i) * SDL_cos(angle * M_PI / 180);
            int py = y + (radius - i) * SDL_sin(angle * M_PI / 180);
            SDL_RenderDrawPoint(gui->renderer, px, py);
        }
    }
    
    // Draw selection highlight
    if (isSelected) {
        SetRenderColor(gui->renderer, COLOR_SELECTED);
        for (int i = 0; i < 3; i++) {
            for (int angle = 0; angle < 360; angle++) {
                int px = x + (radius + 3 + i) * SDL_cos(angle * M_PI / 180);
                int py = y + (radius + 3 + i) * SDL_sin(angle * M_PI / 180);
                SDL_RenderDrawPoint(gui->renderer, px, py);
            }
        }
    }
    
    // Draw king crown
    if (isKing) {
        SDL_Color gold = {255, 215, 0, 255};
        DrawText(gui, "K", x - 6, y - 10, gold);
    }
}

// Calculate possible moves for selected piece
static void CalculatePossibleMoves(GUI_State* gui) {
    gui->num_possible_moves = 0;
    
    if (gui->selected_piece < 0) return;
    
    int row, col;
    IndexToPos(gui->selected_piece, &row, &col);
    
    int owner = GetPieceOwner(gui->game, gui->selected_piece);
    int isKingPiece = IsKing(gui->game, gui->selected_piece);
    
    // Check all four directions
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    
    for (int d = 0; d < 4; d++) {
        int dr = directions[d][0];
        int dc = directions[d][1];
        
        // Check if direction is valid for non-kings
        if (!isKingPiece) {
            if (owner == 0 && dr > 0) continue;  // Red moves up
            if (owner == 1 && dr < 0) continue;  // Black moves down
        }
        
        // Check regular move
        int newRow = row + dr;
        int newCol = col + dc;
        
        if (IsValidPos(newRow, newCol)) {
            int newPos = PosToIndex(newRow, newCol);
            if (!IsOccupied(gui->game, newPos)) {
                gui->possible_moves[gui->num_possible_moves++] = newPos;
            } else if (GetPieceOwner(gui->game, newPos) != owner) {
                // Check jump
                int jumpRow = newRow + dr;
                int jumpCol = newCol + dc;
                
                if (IsValidPos(jumpRow, jumpCol)) {
                    int jumpPos = PosToIndex(jumpRow, jumpCol);
                    if (!IsOccupied(gui->game, jumpPos)) {
                        gui->possible_moves[gui->num_possible_moves++] = jumpPos;
                    }
                }
            }
        }
    }
}

// Check if position is a possible move
static int IsPossibleMove(GUI_State* gui, int pos) {
    for (int i = 0; i < gui->num_possible_moves; i++) {
        if (gui->possible_moves[i] == pos) return 1;
    }
    return 0;
}

// Draw the board
static void DrawBoard(GUI_State* gui) {
    // Clear screen
    SetRenderColor(gui->renderer, COLOR_BACKGROUND);
    SDL_RenderClear(gui->renderer);
    
    // Draw title
    SDL_Color white = {255, 255, 255, 255};
    DrawText(gui, "BitBoard Checkers", WINDOW_WIDTH / 2 - 80, 20, white);
    
    // Draw turn indicator
    char turnText[32];
    sprintf(turnText, "Current Player: %s", gui->game->current_player == 0 ? "Red" : "Black");
    DrawText(gui, turnText, WINDOW_WIDTH / 2 - 80, 50, white);
    
    // Draw board squares
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            SDL_Rect square = {
                BOARD_OFFSET_X + col * SQUARE_SIZE,
                BOARD_OFFSET_Y + row * SQUARE_SIZE,
                SQUARE_SIZE,
                SQUARE_SIZE
            };
            
            // Draw square
            SetRenderColor(gui->renderer, 
                (row + col) % 2 == 0 ? COLOR_LIGHT_SQUARE : COLOR_DARK_SQUARE);
            SDL_RenderFillRect(gui->renderer, &square);
            
            // Draw possible move highlight
            if ((row + col) % 2 == 1) {
                int pos = PosToIndex(row, col);
                if (IsPossibleMove(gui, pos)) {
                    SetRenderColor(gui->renderer, COLOR_POSSIBLE_MOVE);
                    SDL_RenderFillRect(gui->renderer, &square);
                }
            }
            
            // Draw square border
            SetRenderColor(gui->renderer, 0x00000040);
            SDL_RenderDrawRect(gui->renderer, &square);
        }
    }
    
    // Draw coordinate labels
    SDL_Color gray = {200, 200, 200, 255};
    for (int i = 0; i < 8; i++) {
        char coord[2] = {' ', '\0'};
        
        // Row numbers
        coord[0] = '0' + i;
        DrawText(gui, coord, BOARD_OFFSET_X - 20, BOARD_OFFSET_Y + i * SQUARE_SIZE + SQUARE_SIZE/2 - 8, gray);
        
        // Column numbers
        DrawText(gui, coord, BOARD_OFFSET_X + i * SQUARE_SIZE + SQUARE_SIZE/2 - 4, BOARD_OFFSET_Y - 20, gray);
    }
    
    // Draw pieces
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((row + col) % 2 == 0) continue;
            
            int pos = PosToIndex(row, col);
            if (IsOccupied(gui->game, pos)) {
                int owner = GetPieceOwner(gui->game, pos);
                int isKingPiece = IsKing(gui->game, pos);
                int isSelected = (pos == gui->selected_piece);
                
                DrawPiece(gui, row, col, owner == 0, isKingPiece, isSelected);
            }
        }
    }
    
    // Draw instructions
    DrawText(gui, "Click piece to select, click square to move", BOARD_OFFSET_X, BOARD_OFFSET_Y + BOARD_SIZE + 10, white);
    DrawText(gui, "R - Reset, B - Show bits, ESC - Exit", BOARD_OFFSET_X, BOARD_OFFSET_Y + BOARD_SIZE + 30, white);
    
    // Draw bit display if enabled
    if (gui->show_bits) {
        char bitText[128];
        int y = BOARD_OFFSET_Y + BOARD_SIZE + 60;
        
        sprintf(bitText, "Red: %016llX", gui->game->red_pieces);
        DrawText(gui, bitText, BOARD_OFFSET_X, y, white);
        
        sprintf(bitText, "Red Kings: %016llX", gui->game->red_kings);
        DrawText(gui, bitText, BOARD_OFFSET_X, y + 20, white);
        
        sprintf(bitText, "Black: %016llX", gui->game->black_pieces);
        DrawText(gui, bitText, BOARD_OFFSET_X + 250, y, white);
        
        sprintf(bitText, "Black Kings: %016llX", gui->game->black_kings);
        DrawText(gui, bitText, BOARD_OFFSET_X + 250, y + 20, white);
    }
    
    SDL_RenderPresent(gui->renderer);
}

// Handle mouse click
static void HandleClick(GUI_State* gui, int x, int y) {
    // Check if click is on board
    if (x < BOARD_OFFSET_X || x >= BOARD_OFFSET_X + BOARD_SIZE ||
        y < BOARD_OFFSET_Y || y >= BOARD_OFFSET_Y + BOARD_SIZE) {
        return;
    }
    
    // Get square coordinates
    int col = (x - BOARD_OFFSET_X) / SQUARE_SIZE;
    int row = (y - BOARD_OFFSET_Y) / SQUARE_SIZE;
    
    if ((row + col) % 2 == 0) return;  // Light square
    
    int pos = PosToIndex(row, col);
    
    // Check if clicking on possible move
    if (IsPossibleMove(gui, pos)) {
        // Determine if it's a jump
        int fromRow, fromCol;
        IndexToPos(gui->selected_piece, &fromRow, &fromCol);
        
        int rowDiff = abs(row - fromRow);
        
        if (rowDiff == 2) {
            // It's a jump
            MakeCapture(gui->game, gui->selected_piece, pos);
        } else {
            // It's a regular move
            MakeMove(gui->game, gui->selected_piece, pos);
        }
        
        gui->selected_piece = -1;
        gui->num_possible_moves = 0;
        
        // Check win condition
        if (HasWon(gui->game, 0)) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                "Game Over", "Red Wins!", gui->window);
            InitGame(gui->game);
        } else if (HasWon(gui->game, 1)) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                "Game Over", "Black Wins!", gui->window);
            InitGame(gui->game);
        } else if (!CanMove(gui->game, gui->game->current_player)) {
            char msg[64];
            sprintf(msg, "%s has no moves. %s Wins!", 
                    gui->game->current_player == 0 ? "Red" : "Black",
                    gui->game->current_player == 0 ? "Black" : "Red");
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                "Game Over", msg, gui->window);
            InitGame(gui->game);
        }
        
        DrawBoard(gui);
        return;
    }
    
    // Check if clicking on own piece
    if (IsOccupied(gui->game, pos) && 
        GetPieceOwner(gui->game, pos) == gui->game->current_player) {
        gui->selected_piece = pos;
        CalculatePossibleMoves(gui);
        DrawBoard(gui);
    } else {
        // Deselect
        gui->selected_piece = -1;
        gui->num_possible_moves = 0;
        DrawBoard(gui);
    }
}

// Main GUI function - called from main.c
int RunGUI(GameState* game) {
    GUI_State gui = {0};
    gui.game = game;
    gui.selected_piece = -1;
    gui.num_possible_moves = 0;
    gui.show_bits = 0;
    
    if (!InitSDL(&gui)) {
        return 1;
    }
    
    DrawBoard(&gui);
    
    SDL_Event event;
    int running = 1;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        HandleClick(&gui, event.button.x, event.button.y);
                    }
                    break;
                    
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_b:
                            gui.show_bits = !gui.show_bits;
                            DrawBoard(&gui);
                            break;
                            
                        case SDLK_r:
                            InitGame(game);
                            gui.selected_piece = -1;
                            gui.num_possible_moves = 0;
                            DrawBoard(&gui);
                            break;
                            
                        case SDLK_ESCAPE:
                            running = 0;
                            break;
                    }
                    break;
            }
        }
        
        SDL_Delay(16);  // ~60 FPS
    }
    
    CleanupSDL(&gui);
    return 0;
}