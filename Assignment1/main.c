
#include <stdio.h>
#include <stdint.h>

void div_convert(uint32_t n, int base, char *out);

int main(){

	char result[65];

	div_convert(156, 8, result);
	printf("156 in base 8: %s (expected: 234\n", result);

	return 0;

}
