#ifndef CHECKERS_H
#define CHECKERS_H

//Game structure
typedef struct{
	unsigned long long red_pieces; //reg red pieces
	unsigned long long red_kings; //red king pieces
	unsigned long long blacn_pieces; //reg black pieces
	unsigned long long black_kings; //black kings
	int current_player; // 0 = red, 1 = black
} GameState;

//Initialize game

void InitGame(GameState* game);

//display functions

void PrintBoard(GameState* game);

//Move validation and execution

int IsValidPos (int row, int column);
int PosToIndex(int row, int column);
void IndexToPos(int index, int* row, int* column);
int IsOccupied(GameState* game, int position);
int GetPieceOwner(GameState* game, int position);
int IsKing(Gamestate* game, int position);

//Game logic

int MakeMove(GameState* game, int from, int to);
int MakeCapture(GameState* game, int from, int to);
void PromoteKing(GameState* game);
int HasWon(GameState* game, int player);
int CanMove(GameState* game, int player);

//helper functions for game logic

void SwitchPlayer(GameState* game);
unsigned long long GetAllPieces(GameState* game);
unsigned long long GetPlayerPieces(GameState* game, int player);

#endif
