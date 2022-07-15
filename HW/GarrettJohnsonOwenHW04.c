/*
Owen Garrett Johnson
CS2060
HW04
Due 7/14
This program will ask for a passcode and tell you if it matches, it will then ask and validate shirt size, then finally shirt price
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <float.h>
#include <errno.h>

#define ARRAY_LENGTH 80
#define CORRECT_PASSCODE "$3cr3t!"
#define SIZE_ARRAY_LENGTH 4
const char* SHIRT_ARRAY[4] = { "(s)mall", "(m)edium", "(l)arge", "(x)tra-large" };
#define MIN 20
#define MAX 50

void getString(char* inputStringPtr);
bool valString(char* inputStringPtr);
char valSize(char sizeSelect);
bool getValidDouble(const char* buff, double* const value, int min, int max);


int main(void) {

	//Task 2
	//getting passcode and validating it
	char inPasscode[ARRAY_LENGTH];
	puts("Enter passcode");
	getString(inPasscode);
	bool correctPasscode = valString(inPasscode);

	//printing if passcode was correct
	if (correctPasscode) {
		puts("Passcode correct");
	}
	else if (!correctPasscode) {
		puts("Passcode incorrect");
	}


	//Task 3
	//getting size and validating it
	printf("Select your shirt size by entering the character in parentheses:\n%s, %s, %s, %s\n", SHIRT_ARRAY[0], SHIRT_ARRAY[1], SHIRT_ARRAY[2], SHIRT_ARRAY[3]);
	char selectSize = getchar();
	while (getchar() != '\n');
	selectSize = valSize(selectSize);

	if (selectSize == EOF) {
		puts("Error: You did not enter a valid choice");
	}
	switch (selectSize) {
	case 's': puts("[Small] was selected"); 
	break;
	case 'm': puts("[Medium] was selected");
	break;
	case 'l': puts("[Large] was selected");
	break;
	case 'x': puts("[Xtra-Large] was selected");
	break;
	}



	//task 4
	char userPrice[ARRAY_LENGTH];
	puts("Enter sales price of t-shirts");
	getString(userPrice);

	double valPrice = 0;
	double *const valPricePtr = &valPrice;
	
	
	if (getValidDouble(userPrice, valPricePtr, MIN, MAX) ){
		printf("You entered $%.2lf for the t-shirt price." , valPrice);
	}


}//main

//Task 1
//Input argument of string pointer. Writes to string with max length, then changes new line character to \0
void getString(char* inputStringPtr) {

	//get input
	fgets(inputStringPtr, ARRAY_LENGTH, stdin);
	size_t length;

	//change new line character '\n' to null character '\0' if '\n' exists
	length = strlen(inputStringPtr);

	char check = inputStringPtr[length - 1];

	if (check == '\n') {
		inputStringPtr[length - 1] = '\0';
	}
}//getString


//validates if a string is equal to a password
bool valString(char* inputStringPtr) {

	//compare input to passcode
	int check;
	check = strncmp(inputStringPtr, CORRECT_PASSCODE, strlen(CORRECT_PASSCODE));

	//checking if input is equal to passcode
	bool match = false;
	if (check == 0) {
		match = true;
	}

	return match;
}//valString


//validates if a char was entered that matches a size
char valSize(char sizeSelect) {
	
	//Check entered char against the character in parenthesis.
	for (int i = 0; i < 4; i++) {
		if (tolower(sizeSelect) ==  SHIRT_ARRAY[i][1]) {
			return tolower(sizeSelect);
		}
		else if (i == SIZE_ARRAY_LENGTH - 1)
		{
			return EOF;
		}

	}

}//valSize



//validates a double 
bool getValidDouble(const char* buff, double* const value, int min, int max){
	char *ptr;
	bool valid = false;
	errno = 0;

	*value = strtod(buff, &ptr);


	//if the buff and the ptr are the same, that means there were no numeric values in the input
	if (ptr == buff) {
		puts("Error: you did not enter a valid numeric value");
	}
	//this checks if double is equal to min or max, and and error occured
	else if ((*value == DBL_MIN || *value == DBL_MAX) && ERANGE == errno) {
		puts("Error: you did not enter a valid numeric value");
	}
	//checking if in range of min and max we want
	else if (*value < min || *value > max) {
		printf("Error: Enter a value from %d to %d", min, max);
	}
	//makes it past checks
	else {
		valid = true;
	}


	return valid;



}