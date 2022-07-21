
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <float.h>
#include <errno.h>

#define ARRAY_LENGTH 80
#define CORRECT_PASSCODE "b"
#define SIZE_ARRAY_LENGTH 4
const char* SHIRT_ARRAY[4] = { "(s)mall", "(m)edium", "(l)arge", "(x)tra-large" };
#define MIN 10
#define MAX 100
#define NUMBER_OF_ATTEMPTS 3

void getString(char* inputStringPtr);
bool valString(char* inputStringPtr);
char valSize(char sizeSelect);
bool getValidDouble(const char* buff, double* const value, int min, int max);
void fundraiser();
bool yesNoVal();


int main(void) {

	int attempt = 0;

	while (attempt < 3) {
		//getting passcode and validating it
		char inPasscode[ARRAY_LENGTH];
		puts("Enter passcode");
		getString(inPasscode);
		bool correctPasscode = valString(inPasscode);

		if (correctPasscode) {
			fundraiser();

			attempt = NUMBER_OF_ATTEMPTS;
		}//if true

		else if (!correctPasscode) {

			puts("Error: The password is incorrect");
			attempt++;
		}//if false

	}//while

	if (attempt >= NUMBER_OF_ATTEMPTS) {

		puts("Exiting admin set-up");


	}


}




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
	int passSize = strlen(CORRECT_PASSCODE);
	check = strncmp(inputStringPtr, CORRECT_PASSCODE, strlen(CORRECT_PASSCODE));

	//makes sure that the inputStrPtr passcode ends at the correct place
	bool passwordEnd = false;
	if (inputStringPtr[strlen(CORRECT_PASSCODE)] == '\0') {
		passwordEnd = true;
	}



	//checking if input is equal to passcode
	bool match = false;
	if (check == 0 && passwordEnd) {
		match = true;
	}

	return match;
}//valString


//validates if a char was entered that matches a size
char valSize(char sizeSelect) {

	//Check entered char against the character in parenthesis.
	for (int i = 0; i < SIZE_ARRAY_LENGTH; i++) {
		if (tolower(sizeSelect) == SHIRT_ARRAY[i][1]) {
			return tolower(sizeSelect);
		}
		else if (i == SIZE_ARRAY_LENGTH - 1)
		{
			return EOF;
		}

	}

}//valSize



//returns false when n/N entered and true when y/Y entered
bool yesNoVal() {

	//used for when a valid return is enetered
	bool valInput = false;
	bool returnVal = false;
	while (!valInput) {
		char input = getchar();
		while (getchar() != '\n');

		if (input == 'y' || input == 'Y') {
			returnVal = true;
			valInput = true;
		}// y/Y

		else if (input == 'n' || input == 'N') {
			returnVal = false;
			valInput = true;
		}// n/N

		//no correct input
		else {
			puts("Please enter 'y' or 'Y' for yes; 'n' or 'N' for no");
		}//no correct input
	}//while

	return returnVal;
}//yesNoVal


//validates a double 
bool getValidDouble(const char* buff, double* const value, int min, int max) {
	char* ptr;
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
		printf("Error: value not between %d to %d\n", min, max);
	}
	//has extra characters after number
	else if (ptr[0] != '\0') {
		printf("Error: characters \"%s\" after number\n", ptr);
	}
	//makes it past checks
	else {
		valid = true;
	}


	return valid;



}


void fundraiser() {

	//*************************************
	//Setting up fundraiser
	//*************************************

	//getting name
	puts("Enter fundraiser orginization's name");

	char orgName[ARRAY_LENGTH];
	getString(orgName);

	//getting price and validating it
	//setup
	char userPrice[ARRAY_LENGTH];
	printf("Enter sales price of t-shirts between %d and %d\n", MIN, MAX);
	getString(userPrice);

	double valPrice = 0;
	double* const valPricePtr = &valPrice;
	
	//recieving input and validate
	bool correctPrice = false;
	do {
		while (!getValidDouble(userPrice, valPricePtr, MIN, MAX)) {
			printf("Enter a value between %d and %d\n", MIN, MAX);
			getString(userPrice);
		}

		printf("Is $%.2lf correct?\n", valPrice);
		bool yOrNo = yesNoVal();
		if (yOrNo) {
			correctPrice = true;
		}

		else if (!yOrNo) {
			printf("Enter a value between %d and %d\n", MIN, MAX);
			getString(userPrice);
		}


	} while (!correctPrice); // a valid price has been recieved and the user has said that it works




}