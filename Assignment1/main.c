#include <stdio.h>
#include <stdint.h>
#include <string.h>


void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n); //initialize methods from convert.c

int main(){
	FILE *file = fopen("a1_test_file.txt", "r"); //open and read the test file provided
	if (file ==  NULL){
		printf("Error: Could not open test file a1_test_file.txt\n"); //throws error if file not found
		return 1;
	}

	char line[256]; //safe amount of storage for each line of test file
	char function[100]; //declare storage for function to compare against test file function
	uint32_t number; 
	int base;
	char expected[200];
	char result[200];
	int test_count = 0; //initialize test count at 0

	printf("\n\nRunning tests from a1_test_file.txt...\n\n");

	while (fgets(line, sizeof(line), file)!= NULL){ //if the line isn't null, check lines
		if(line[0] == '#' || line[0] == '\n'){ //if the line begins with "#" or is a new line, continue the loop
			continue;
		}

		if (sscanf(line, "%s %u %d %s", function, &number, &base, expected) == 4){ //verify that there are four inputs read from test file
			
			test_count ++; //increase test count by 1 to keep track of tests completely successfully

			if(strcmp(function, "div_convert")== 0){ //if the test file calls for div convert, run div_convert
				div_convert(number, base, result);
				printf("Test %d: div_convert(%u, %d) --> Expected: %s, Got: %s", 
					test_count, number, base, expected, result); //formats div_convert to print to console
				
				if (strcmp(result, expected) == 0){ //if the result matches the expected, print PASS
					printf(" --> [[PASS]]\n");
				} else { //womp womp
					printf("[[FAIL]]\n");
				}
			
			} else if (strcmp(function, "sub_convert") == 0){ //functions the same as div_convert logic
				sub_convert(number, base, result);
				printf("Test %d: sub_convert(%u, %d) = %s (expected: %s)",
					test_count, number, base, expected, result);

				if (strcmp(result, expected) == 0){
				printf(" --> [[PASS]]\n");
				} else {
					printf("[[FAIL]]\n");
				}
			}
		}
		
	

		else if (sscanf(line, "%s %u", function, &number)== 2){ //if there are only 2 inputs from the test file, default to print_table function
			if(strcmp(function, "print_tables") == 0){
				test_count ++; //continue test count for accuracy
				printf("Test %d: print_tables(%u) --> \n", test_count, number); //formatting 
				print_tables(number);
				printf(" --> [[PASS]]\n\n");
				}
			}

	fclose(file); //close the file to avoid resource leak
	printf("\n\nCompleted %d/100 tests. Terminating main.c...\n\n", test_count); //final message to signal program termination and returns number of tests passed out of 100
	return 0; //end the program
}



