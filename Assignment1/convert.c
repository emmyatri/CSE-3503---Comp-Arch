#include <string.h>
#include <stdint.h> //for unsigned integer
#include <stdio.h>

void div_convert(uint32_t n, int base, char *out){

	char temp[65]; //temporary buffer
	int pos =  0; //declare integer as placeholder for position initialized at zero
		 


	if (n==0){ //handle zero case
		strcpy(out, "0");
		return;
	}


	while (n > 0){

		int remainder = n % base; //remainder value assigned to value of modulus of 'n'
		n = n / base; //reassign n as the quotient of 'n' and the base


		//convert digit to character
		if (remainder < 10)
			temp[pos++] = '0' + remainder;
		else
			temp[pos++] = 'A' + (remainder - 10);
		}


	temp[pos] = '\0'; //reverse the results
	int i = 0;
	for (int j = pos -1; j >= 0; j--){
		out[i++] = temp[j]; 
	}

	out [i] = '\0';
}

	
void sub_convert(uint32_t n, int base, char *out){
	char temp[65]; //same character buffer as above
	int pos =0;//initialize position at '0'

	if (n==0){ //handling edge case of zero value for number
		strcpy(out,"0");
		return;
	}

	uint32_t power = 1; //initialize power at base0 (1)

	while (power <= n / base){ //if the power is less than or equal to the number/base, multiply the power by the base
		power *= base; 
	}

	while (power > 0){ //while the power is positive, subtract the power from the number and add to the digits counter
		int digit = 0;

		while (n >= power){
			n -= power;
			digit ++;
		}

	if (digit < 10) //convert digit to character with rubric provided example
		temp[pos++] = '0' + digit;
	else
		temp[pos++] = 'A' + (digit - 10);

	power /= base;
	}

	temp[pos] = '\0';
	strcpy(out, temp); //no need to reverse output
	return;
}


void print_tables(uint32_t n){
	char bin[33], oct[12], hex[9];

	div_convert(n, 2, bin); //div_convert to base2 (binary)
	div_convert(n, 8, oct); //run this method for the rest of the bases.
	div_convert(n, 16, hex);
	printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);

	uint32_t shifted = n << 3;//account for left shift by 3
	div_convert(shifted, 2, bin);
	div_convert(shifted, 8, oct);
	div_convert(shifted, 16, hex);
	printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shifted, hex);

	uint32_t masked = n & 0xFF; //account for 0xFF
	div_convert(masked, 2, bin);
	div_convert(masked, 8, oct);
	div_convert(masked, 16, hex);
	printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s", bin, oct, masked, hex);

}

