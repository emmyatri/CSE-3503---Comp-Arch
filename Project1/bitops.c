#include <stdio.h>
#include "bitops.h"


// 32-Bit Operations


unsigned int ModifyBits(unsigned int value, int position, int operation) {
	if (position < 0 || position >= 32)
		return value; // Invalid position, return original value

	switch (operation) {
	case 0:return value & ~(1U << position); // Clear bit
	case 1:return value | (1U << position); // Set bit
	case 2:return value ^ (1U << position); // Toggle bit
	default:return value; // Invalid operation, return original value
	}
}

unsigned int SetBit(unsigned int value, int position) {
	return ModifyBits(value, position, 1);
}

unsigned int ClearBit(unsigned int value, int position) {
	return ModifyBits(value, position, 0);
}

unsigned int ToggleBit(unsigned int value, int position) {
	return ModifyBits(value, position, 2);
}

int GetBit(unsigned int value, int position){
	if (position < 0 || position >= 32) return 0;
	return (value >> position) & 1;
}

int CountBits(unsigned int value) {
	int count = 0;
	while (value) {
		count += value & 1;
		value >>= 1;
	}
	return count;
}

unsigned int ShiftLeft(unsigned int value, int positions) {
	if (positions < 0 || positions >= 32) return 0;
	return value << positions;
}

unsigned int ShiftRight(unsigned int value, int positions) {
	if (positions < 0 || positions >= 32) return 0;
	return value >> positions;
}

void PrintBinary(unsigned int value) {
	for (int i = 31; i >= 0; i--) {
		printf("%d", (int)(value >> i) & 1);
		if (i % 8 == 0 && i != 0) printf(" ");
	}
	printf("\n");
}

void PrintHex(unsigned int value) {
	printf("0x%08X\n", value);
}

unsigned long long ModifyBits64(unsigned long long value, int position, int operation) {
	if (position < 0 || position >= 64)
		return value; // Invalid position, return original value

	switch (operation) {
	case 0:return value & ~(1ULL << position); // Clear bit
	case 1:return value | (1ULL << position); // Set bit
	case 2:return value ^ (1ULL << position); // Toggle bit
	default:return value; // Invalid operation, return original value
	}
}

unsigned long long SetBit64(unsigned long long value, int position) {
	return ModifyBits64(value, position, 1);
}

unsigned long long ClearBit64(unsigned long long value, int position) {
	return ModifyBits64(value, position, 0);
}

unsigned long long ToggleBit64(unsigned long long value, int position) {
	return ModifyBits64(value, position, 2);
}

int GetBit64(unsigned long long value, int position) {
	if (position < 0 || position >= 64) return 0;
	return (value >> position) & 1;
}

int CountBits64(unsigned long long value) {
	int count = 0;
	while (value) {
		count += value & 1;
		value >>= 1;
	}
	return count;
}


void PrintBinary64(unsigned long long value) {
	for (int i = 63; i >= 0; i--) {
		printf("%d", (int)(value >> i) & 1);
		if (i % 8 == 0 && i != 0) printf(" ");
	}
	printf("\n");
}
