
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <float.h>
#include <errno.h>

#define ARRAY_LENGTH 80
#define CORRECT_PASSCODE "b"
#define SIZE_COLOR_ARRAY_LENGTH 4
const char* SHIRT_SIZE_ARRAY[SIZE_COLOR_ARRAY_LENGTH] = { "(s)mall", "(m)edium", "(l)arge", "(x)tra-large" };
const char* SHIRT_COLOR_ARRAY[SIZE_COLOR_ARRAY_LENGTH] = { "(w)hite", "(b)lue", "(p)ink", "(k)black" };
#define MIN 10
#define MAX 100
#define NUMBER_OF_ATTEMPTS 3
#define MIN_DONATE_PERCENT 5
#define MAX_DONATE_PERCENT 30

void getString(char* inputStringPtr);
bool valString(char* inputStringPtr);
char valSizeOrColor(char sizeSelect, int* const indexPtr, const char* array[SIZE_COLOR_ARRAY_LENGTH]);
bool getValidDouble(const char* buff, double* const value, int min, int max);
void fundraiser();
bool yesNoVal();
int getValidZip();


int main(void) {
	getValidZip();
	//validting password
	int attempt = 0;
	while (attempt < NUMBER_OF_ATTEMPTS) {
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

		if (!correctPasscode && attempt == NUMBER_OF_ATTEMPTS) {
			puts("Exiting admin set-up");
		}

	}//while


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
	check = strncmp(inputStringPtr, CORRECT_PASSCODE, passSize);

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
char valSizeOrColor(char sizeSelect, int* const indexPtr, const char* array[SIZE_COLOR_ARRAY_LENGTH]) {

	char charReturn = '\0';


	//Check entered char against the character in parenthesis.
	int i = 0;
	while (charReturn == '\0') {
		if (tolower(sizeSelect) == array[i][1]) {

			charReturn = tolower(sizeSelect);
			*indexPtr = i;
		}
		else if (i == SIZE_COLOR_ARRAY_LENGTH - 1)
		{
			charReturn = EOF;
		}
		i++;
	}

	return charReturn;

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


//validates a 5 digit zip code
int getValidZip() {
	
	puts("Enter your 5 digit zip code.");
	//get input and make sure it is only 5 digits and no characters
	char zipString[ARRAY_LENGTH];
	double returnValue = 0;
	double* returnValuePtr = &returnValue;
	char* endPtr

	//
	while (strlen(zipString) != 5) {
		puts("Zip code should be 5 digits long, try again");
		getString(zipString);
	}//while

	int attemptValue = 0;
	att = strtol(zipString, endPtr, 10);



}//getValidZip



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
	bool correctRange = false;
	do {
		//validating
		while (!getValidDouble(userPrice, valPricePtr, MIN, MAX)) {
			printf("Enter a value between %d and %d\n", MIN, MAX);
			getString(userPrice);
		}

		//confirm
		printf("Is $%.2lf correct? Enter Y/y for yes; N/n for no.\n", valPrice);
		bool yOrNo = yesNoVal();
		if (yOrNo) {
			correctRange = true;
		}

		else if (!yOrNo) {
			printf("Enter a value between %d and %d\n", MIN, MAX);
			getString(userPrice);
		}


	} while (!correctRange); // a valid price has been recieved and the user has said that it works

	//settup charity percent amount
	printf("Enter percentage of the t-shirt sales between %%%d and %%%d that will be donated to %s\n", MIN_DONATE_PERCENT, MAX_DONATE_PERCENT, orgName);
	char userPercent[ARRAY_LENGTH];
	getString(userPercent);

	double valPercent = 0;
	double* const valPercentPtr = &valPercent;


	correctRange = false;
	

	//2D array to store how many of each shirt was bought.
	int totalShirtArray[SIZE_COLOR_ARRAY_LENGTH][SIZE_COLOR_ARRAY_LENGTH] = { 0 };
	

	do {

		//validate
		while (!getValidDouble(userPercent, valPercentPtr, MIN_DONATE_PERCENT, MAX_DONATE_PERCENT)) {
			printf("Enter percentage of the t-shirt sales between %%%d and %%%d that will be donated to %s\n", MIN_DONATE_PERCENT, MAX_DONATE_PERCENT, orgName);
			getString(userPercent);
		}

		//confirm
		printf("Is %%%.2lf correct? Enter Y/y for yes; N/n for no.\n", valPercent);
		bool yOrNo = yesNoVal();
		if (yOrNo) {
			correctRange = true;
		}

		else if (!yOrNo) {
			printf("Enter percentage of the t-shirt sales between %%%d and %%%d that will be donated to %s\n", MIN_DONATE_PERCENT, MAX_DONATE_PERCENT, orgName);
			getString(userPercent);
		}


	} while (!correctRange);

	//display information about fundraiser
	printf("Purchase a t-shirt for $%.2lf and %%%.2lf will be donated to %s.\n", valPrice, valPercent, orgName);


	//******************************************
	//Customer Purchasing
	//******************************************

	int totalShirts = 0;
	bool customerContinue = true;
	while (customerContinue) {
		//getting size and validating it
		printf("Select your shirt size by entering the character in parentheses:\n%s, %s, %s, %s\n", SHIRT_SIZE_ARRAY[0], SHIRT_SIZE_ARRAY[1],
			SHIRT_SIZE_ARRAY[2], SHIRT_SIZE_ARRAY[3]);
		char selectSize = getchar();
		while (getchar() != '\n');

		//used to return index
		int sizeIndex;
		int* sizeIndexPtr = &sizeIndex;

		selectSize = valSizeOrColor(selectSize, sizeIndexPtr, SHIRT_SIZE_ARRAY);

		while (selectSize == EOF) {

			puts("Error: You did not enter a valid choice");
			printf("Select your shirt size by entering the character in parentheses:\n%s, %s, %s, %s\n", SHIRT_SIZE_ARRAY[0], SHIRT_SIZE_ARRAY[1],
				SHIRT_SIZE_ARRAY[2], SHIRT_SIZE_ARRAY[3]);
			selectSize = getchar();
			while (getchar() != '\n');
			selectSize = valSizeOrColor(selectSize, sizeIndexPtr, SHIRT_SIZE_ARRAY);
		}//while

		printf("%s was selected\n", SHIRT_SIZE_ARRAY[sizeIndex]);







		//getting color and validating it
		printf("Select your shirt color by entering the character in parentheses:\n%s, %s, %s, %s\n", SHIRT_COLOR_ARRAY[0], SHIRT_COLOR_ARRAY[1],
			SHIRT_COLOR_ARRAY[2], SHIRT_COLOR_ARRAY[3]);
		char selectColor = getchar();
		while (getchar() != '\n');

		//used to return index
		int colorIndex;
		int* colorIndexPtr = &colorIndex;

		selectColor = valSizeOrColor(selectColor, colorIndexPtr, SHIRT_COLOR_ARRAY);

		while (selectColor == EOF) {

			puts("Error: You did not enter a valid choice");
			printf("Select your shirt color by entering the character in parentheses:\n%s, %s, %s, %s\n", SHIRT_COLOR_ARRAY[0], SHIRT_COLOR_ARRAY[1],
				SHIRT_COLOR_ARRAY[2], SHIRT_COLOR_ARRAY[3]);
			selectColor = getchar();
			while (getchar() != '\n');
			selectColor = valSizeOrColor(selectColor, colorIndexPtr, SHIRT_COLOR_ARRAY);
		}//while

		printf("%s was selected\n", SHIRT_COLOR_ARRAY[colorIndex]);


		//add shirt into array
		totalShirtArray[sizeIndex][colorIndex]++;


		//See if customer want another shirt
		puts("Do you want to purchase another shirt? Enter Y/y for yes; N/n for no.");
		bool yOrNo = yesNoVal();
		if (!yOrNo) {
			customerContinue = false;
		}

		totalShirts++;
	}//while(customsercontinue)


	//used for debugging, shows the array of shirts sizes are rows, colors are columns
	for (size_t row = 0; row < SIZE_COLOR_ARRAY_LENGTH; row++) {
		for (size_t column = 0; column < SIZE_COLOR_ARRAY_LENGTH; column++) {
			printf("%d\t", totalShirtArray[row][column]);
		}
		puts("");
	}

	puts("Enter your 5 digit zip code.");





}//fundraiser