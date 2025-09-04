#include <string.h>
#include <stdint.h> // uint32_t

void div_convert(uint32_t n, int base, char *out){

	char temp[65]; //temporary buffer
	int position = 0; //declare integer as placeholder for position initialized at zero


	if (n==0){ //handle zero case
		strcpy(out, "0");
		return;
	}


	while (n > 0){

		int remainder = n % base; //remainder value denoted by modulus of 'n'
		n = n / base; //reassign n as the quotient of 'n' and the base


		//convert digit to character
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
	
void sub_convert(uint32_t n, int base, char *out){
	

}
