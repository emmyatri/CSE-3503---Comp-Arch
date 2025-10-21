# CS 3503 Project 1 - BitBoard Checkers

## Author
Amelia Ellingson

## Description

A bitboard-based checkers game implementation demonstrating efficient bit manipulation techniques.  
This project implements a fully functional checkers game using bitwise operations for board representation  
and game logic, including mandatory capture rules.

## What's New

- Complete checkers game with bitboard representation
- Efficient bit manipulation operations for 32-bit and 64-bit integers
- Multiple jump and mandatory capture support
- King promotion and backwards movement

## Features

### Phase 1 - Bit Operations

- Set, clear, toggle, and get individual bits
- Count bits and shift operations
- Binary and hexadecimal display functions
- Support for both 32 and 64-bit operations

### Phase 2 - Game Implementation

- Full checks gameplay with proper move validation
- Capture mechanics with piece removal
- King promotion at board's edge
- Win detection (no pieces or valid moves)
- Multiple jump sequences and mandatory capture enforcement

## Build Instructions

### Make Build
```
bash

//compile the game
make clean
make

//run the game
make run

or

./checkers
```

### Quick Build

```
gcc checkers.c bitops.c main.c -o checkers
./checkers
```
