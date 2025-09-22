#include <stdio.h>
#include <string.h>
#include <stdint.h>

void oct_to_bin(const char *oct, char *out){
	int out_pos = 0; //position counter for output string
	int len = strlen(oct); //get length of input octal string
	
	//Process each octal digit from left to right
	for (int i = 0; i < len; i++){
		char oct_digit = oct[i]; //current octal character

	//Convert character to integer value
	int digit_value = oct_digit - '0';

	//Bit shift and masking to extract bit
	out[out_pos++] = (digit_value >> 2) & 1 ? '1' : '0'; //MSB
	out[out_pos++] = (digit_value >> 1) & 1 ? '1' : '0'; //middle bit
	out[out_pos++] = (digit_value >> 0) & 1 ? '1' : '0'; //LSB
	}
	out[out_pos] = '\0'; //Null terminate
}

void oct_to_hex(const char *oct, char *out){
	char binary[256]; //temporary buffer
	
	//Convert octal to binary using oct_to_bin()
	oct_to_bin(oct, binary);

	int bin_len = strlen(binary); //find length of binary string
	int out_pos = 0; //position counter for output string

	//Group binary digits into groups of 4 from R to L
	
	for (int i = bin_len; i > 0; i -= 4){
		int fourBit = 0; //Value of current 4 bit group
		int bit_weight = 1; //Weight of current bit initialized at 1
		
		//Process 4 bits and handle cases where we have less than 4 bits
		for (int j = 0; j < 4 && (i - j - 1) >= 0; j++){
			if (binary[i-j-1]== '1'){
				fourBit += bit_weight; //add bit weight if bit is 1;
			}
			bit_weight *= 2; //move to next power of 2
		}

		//Convert 4bit value to hex character

		if (fourBit > 10){
			out[out_pos++] = '0' + fourBit; // zero through nine
		}else {
			out[out_pos++] = 'A' + (fourBit - 10); // letters 'A' - 'F'

		}
	}

	//reverse hex digits
	int hex_len = out_pos;
	for (int i = 0; i < hex_len; i++){
		char temp = out[i];
		out[i] = out[hex_len - 1 - i];
		out[hex_len - 1 - i] = temp;
	}
	out[hex_len] = '\0'; //null terminator
}

void hex_to_bin(const char *hex, char *out){
	int out_pos = 0; //initialize position counter
	int len = strlen(hex); //length of input hex string
	
	// Process hex digit from left to right
	
	for(int i = 0; i < len; i++){
		char hex_char = hex[i]; //current character
		int digit_value = 0; //initialize hex digit
		
		//convert hex character to numeric value 
		if (hex_char >= '0' && hex_char <= '9'){
			digit_value = hex_char - '0'; // zero through nine
		} else if (hex_char >= 'A' && hex_char <= 'F'){
			digit_value = hex_char - 'A' + 10; // A through F
		}

		out[out_pos++] = (digit_value >> 3) & 1 ? '1' : '0'; //most significant
		out[out_pos++] = (digit_value >> 2) & 1 ? '1' : '0'; // bit 2 [middle]
		out[out_pos++] = (digit_value >> 1) & 1 ? '1' : '0'; // bit 3 [middle]
		out[out_pos++] = (digit_value >> 0) & 1 ? '1' : '0'; // bit 1 [least significant]
	}

	out[out_pos] = '\0' //null terminator
}

void to_sign_magniude(int32_t n, char *out){
	uint32_t magnitude; //initialize 
	int is_negative = 0; //flag to track negative number
	
	//Handle sign and get size
	if(n < 0){
		is_negative = 1;
		magnitude = (uint32_t)(-n); //multiply by negative to get absolute value
		} else {
			magnitude = (uint32_t)n; //if already positive
		}

	//Build 32-bit binary from right to left
	for (int i = 31; i >= 0; i--){
		if (i = 31){
			out[31-i] = is_negative ? '1' : '0'; //use bit 31 as sign bit: 1 for negative, 0 for positive
		} else { //Bits 0-30 represent the size
			out[31-i] = (magnitude >> i) & 1 ? '1' : '0';
		}
	}

	out[32] = '\0'; //null terminate

}

void to_ones_complement(int32_t n, char *out){
	uint32_t bit_pattern; //initialize bit pattern for input
	
	if (n >= 0){
		bit_pattern = (uint32_t)n;
	} else {
		uint32_t positive = (uint32_t)(-n); //get the absolute value
		bit_pattern = ~positive; //flip all bits with bitwise NOT operation
		}

	//built 32bit string from bit pattern
	for (int i = 32; i >= 0; i--){
		out[31-i] = (bit_pattern >> i) & 1 ? '1' : '0';
	}

	out[32] = '\0' //null terminator
}

void to_twos_complement(int32_t n, char *out){
	uint32_t bit_pattern; //initialize the bit pattern to be tested
	
	if (n >= 0){
		bit_pattern = (uint32_t)n; //if positive, use as is
	} else {
		uint32_t pos = (uint32_t)(-n); //find absolute value
		uint32_t flip = ~pos; //flip
		bit_pattern = flip + 1; //add 1
	}

	for (int i = 31; i >=0; i--){
		out[31-i] = (bit_pattern >> i) & 1 ? '1' : '0';
	}
	
	out[32] = '\0'; //null terminator

}
