#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(uint32_t n, char *out);
void to_ones_complement(uint32_t n, char *out);
void to_twos_complement(uint32_t n, char *out);


int main(){
	FILE *file = fopen("a2_test.txt", "r"); //open and read the test file provided
	if (file ==  NULL){
		printf("Error: Could not open test file a1_test_file.txt\n"); //throws error if file not found
		return 1;
	}

	char line[256]; //safe amount of storage for each line of test file (probably too much)
	char function[100]; //declare storage for function to compare against test file function(also probably too much)
	char input1[200]; //input1
	char input2[200]; //input2
	char expected[200]; //expected
	char result[200]; //result
	int test_count = 0; //counter for number of tests performed
	int passed = 0; //count how many tests passed




	printf("\n\nRunning tests from a2_test.txt...\n\n");

	while (fgets(line, sizeof(line), file)!= NULL){ //if the line isn't null, check lines
							//
		if(line[0] == '#' || line[0] == '\n'){ //if the line begins with "#" or is a new line, continue the loop
			continue;

		}

		int parsed = sscanf(line, "%s %s %s", function, input1, input2);
		if (parsed == 3){ //makes sure all test data is parsed correctly
			test_count ++;

			//direct mapping functions

			if (strcmp(function, "oct_to_bin")== 0){
				oct_to_bin(input1, input2);
				printf("Test %d: oct_to_bin(%s) -> Expected: [%s] || Got: [%s] ", test_count, input1, input2, result);
				if (strcmp(result, input2) == 0){
					printf("--> [[PASS]]\n\n");
					passed++;
				} else {
					printf("--> [[FAIL]]\n\n");
				}
		
			} else if (strcmp(function, "oct_to_hex")== 0){
				oct_to_hex(input1, input2);
				printf("Test %d: oct_to_hex(%s) -> Expected: [%s] || Got: [%s] ", test_count, input1, input2, result);
				if (strcmp(result, input2) == 0){
					printf("--> [[PASS]]\n\n");
					passed++;
				} else {
					printf("--> [[FAIL]]\n\n");
				}
			} else if (strcmp(function, "hex_to_bin")== 0){
				hex_to_bin(input1, input2);
				printf("Test %d: hex_to_bin(%s) -> Expected: [%s] || Got: [%s] ", test_count, input1, input2, result);
				if (strcmp(result, input2) == 0){
					printf("--> [[PASS]]\n\n");
					passed++;
				} else {
					printf("--> [[FAIL]]\n\n");
				}
			} 
			
			
			//signed representation functions
			
			else if (strcmp(function, "to_sign_magnitude") == 0){
				int32_t number = (int32_t)atoi(input1); //convert character to integer with atoi()
				to_sign_magnitude(number, result);
				printf("Test %d: to_sign_magnitude(%s) -> Expected: [%s] || Got: [%s] ", test_count, input1, input2, result);
				if (strcmp(result, input2) == 0){
					printf("--> [[PASS]]\n\n");
					passed++;
				} else {
					printf("--> [[FAIL]]\n\n");
				}
			} else if (strcmp(function, "to_ones_complement")== 0){
				int32_t number = (int32_t)atoi(input1); //character to integer
				to_ones_complement(number, result);
				printf("Test %d: to_ones_complement(%s) -> Expected: [%s] || Got: [%s] ", test_count, input1, input2, result);
				if (strcmp(result, input2) == 0){
					printf("--> [[PASS]]\n\n");
					passed++;
				} else {
					printf("--> [[FAIL]]\n\n");
				}
			} else if (strcmp(function, "to_twos_complement")== 0){
				int32_t number = (int32_t)atoi(input1); //character to integer
				to_twos_complement(number, result);
				printf("Test %d: to_twos_complement(%s) -> Expected: [%s] || Got: [%s] ", test_count, input1, input2, result);
				if (strcmp(result, input2) == 0){
					printf("--> [[PASS]]\n\n");
					passed++;
				} else {
					printf("--> [[FAIL]]\n\n");
				}
			}
		}
		
			fclose(file);

			printf("\nSummary: %d / %d tests passed.\n", passed, test_count);
			if (passed == test_count){
				printf("All tests passed sucessfully! \n\n");
			} else {
				printf("%d tests failed. Check implementation.", test_count - passed);
				return 1;
			}
		}
}








				
			

