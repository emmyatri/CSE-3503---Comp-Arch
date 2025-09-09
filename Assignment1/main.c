#include <stdio.h>
#include <stdint.h>
#include <string.h>


void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

int main(){
	FILE *file = fopen("A1_tests.txt", "r");
	if (file = NULL){
		printf("Error: Could not open test file A1_tests.txt\n");
		return 1;
	}

	char line[256];
	char function[100];
	uint32_t number;
	int base;
	char expected[200];
	char result[200];
	int test_count = 1;

	printf("\n\nRunning tests from A1_tests.txt...\n\n");

	while (fgets(line, sizeof(line), file)!= NULL){
		if(line[0] == '#' || line[0] == '\n'){
			continue;
		}

		if (sscanf(line, "%s %u %d %s", function, &number, &base, expected) == 4){
			
			test_count ++;

			if(strcmp(function, "div_convert")== 0){
				div_convert(number, base, result);
				printf("Test %d: div_convert(%u, %d) = %s (expected: %s)", 
					test_count, number, base, result, expected);
				
				if (strcmp(result, expected) == 0){
					printf("[PASS]\n");
				} else {
					printf("[FAIL]\n");
				}
			}
		} else if (strcmp(function, "sub_convert") == 0){
			sub_convert(number, base, result);
			printf("Test %d: sub_convert(%u, %d) = %s (expected: %s)",
					test_count, number, base, result, expected);

			if (strcmp(result, expected) == 0){
				printf("[PASS]\n");
			} else {
				printf("[FAIL]\n");
			}
		}
	

	else if (sscanf(line, "%s %u", function, &number)== 2){
		if(strcmp(function, "print_tables") == 0){
			test_count ++;
			printf("Test %d: print_tables(%u): \n", test_count, number);
			print_tables(number);
			printf("[PASS}\n\n");
			}
		}
	}

	fclose(file);
	printf("\n\nCompleted %d/100 tests. Terminating main.c...", test_count);
	return 0;
}



