

#ifndef BITOPS_H
#define BITOPS_H

//basic bit operations

unsigned int SetBit(unsigned int value, int position); //Set bit to 1
unsigned int ClearBit(unsigned int value, int position); //Set bit to 0
unsigned int ToggleBit(unsigned int value, int position); //Flip Bit
unsigned int ModifyBits(unsigned int value, int position, int operation); //Combined: 0=clear, 1=set, 2=toggle
int GetBit (unsigned int value, int position); //Get bit value

//counting and finding

int CountBits(unsigned int value); //count 1s

//shift operations

unsigned int ShiftLeft(unsigned int value, int positions); //shift left
unsigned int ShiftRight(unsigned int value, int positions); //shift right

//display functions

void PrintBinary(unsigned int value); //show in binary
void PrintHex(unsigned int value); //show in hexadecimal

//64-bit versions for the game board

unsigned long long SetBit64(unsigned long long value, int position);
unsigned long long ClearBit64(unsigned long long value, int position);
unsigned long long ToggleBit64(unsigned long long value, int position);
unsigned long long ModifyBits64(unsigned long long value, int position, int operation);
int GetBit64(unsigned long long value, int position);
int CountBits64(unsigned long long value);
void PrintBinary64(unsigned long long value);

#endif

