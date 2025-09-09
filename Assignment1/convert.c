#include <string.h>
#include <stdint.h> // uint32_t
#include <stdio.h>

void div_convert(uint32_t n, int base, char *out){

	char temp[65]; //temporary buffer
	int pos =  0; //declare integer as placeholder for position initialized at zero
		 


	if (n==0){ //handle zero case
		strcpy(out, "0");
		return;
	}


	while (n > 0){

		int remainder = n % base; //remainder value denoted by modulus of 'n'
		n = n / base; //reassign n as the quotient of 'n' and the base


		//convert digit to character
		if (remainder < 10)
			temp[pos++] = '0' + remainder;
		else
			temp[pos++] = 'A' + (remainder - 10);
		}


	temp[pos] = '\0';
	int i = 0;
	for (int j = pos -1; j >= 0; j--){
	
		out[i++] = temp[j];
	}

	out [i] = '\0';
}

	
void sub_convert(uint32_t n, int base, char *out){
	char temp[65];
	int pos =0;

	if (n==0){
		strcpy(out,"0");
		return;
	}

	uint32_t power = 1;

	while (power <= n / base){
		power *= base;
	}

	while (power > 0){
		int digit = 0;

		while (n >= power){
			n -= power;
			digit ++;
		}

	if (digit < 10)
		temp[pos++] = '0' + digit;
	else
		temp[pos++] = 'A' + (digit - 10);

	power /= base;
	}

	temp[pos] = '\0';
	strcpy(out, temp);
	return;
}


void print_tables(uint32_t n){
	char bin[33], oct[12], hex[9];

	div_convert(n, 2, bin);
	div_convert(n, 8, oct);
	div_convert(n, 16, hex);
	printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);

	uint32_t shifted = n << 3;
	div_convert(shifted, 2, bin);
	div_convert(shifted, 8, oct);
	div_convert(shifted, 16, hex);
	printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shifted, hex);

	uint32_t masked = n & 0xFF;
	div_convert(masked, 2, bin);
	div_convert(masked, 8, oct);
	div_convert(masked, 16, hex);
	printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s", bin, oct, masked, hex);
}
