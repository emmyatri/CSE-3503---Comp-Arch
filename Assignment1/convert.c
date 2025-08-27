#include <string.h>
#include <stdint.h> // uint32_t

void div_convert(uint32_t n, int base, char *out){
	char temp[65]; //temporary buffer
	int position = 0;

	if (n==0){
		strcpy(out, "0");
		return;
	}

	while (n > 0){
		int remainder = n % base;
		n = n / base;

		if (remainder < 10)
			temp[position++] = '0' + remainder;
		else
			temp[position++] = 'A' + (remainder - 10);
		}

	for (int i = 0; i < position; i++){
		*out = temp[position-1-i];
		out++;}
		*out = '\0';
		return;
	}
