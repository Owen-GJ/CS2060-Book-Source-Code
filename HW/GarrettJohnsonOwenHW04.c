/*
Owen Garrett Johnson
CS2060
HW04
Due 7/14
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>



#define ARRAY_LENGTH 80
#define CORRECT_PASSCODE "$3cr3t!"
#define SIZE_ARRAY_LENGTH 4

void getString(char* inputStringPtr);
bool valString(char* inputStringPtr);
char valSize(char sizeSelect, const char *sizeArray);


int main(void) {


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

	//getting shirt size
	static const char* SHIRT_SIZE[SIZE_ARRAY_LENGTH] = { "(s)mall" "(m)edium" "(l)arge" "(x)tra-large" };

	printf("c", SHIRT_SIZE[0][1]);


	printf("Select your shirt size by entering the character in parentheses: %s %s %s %s", SHIRT_SIZE[0], SHIRT_SIZE[1], SHIRT_SIZE[2], SHIRT_SIZE[3]);
	char selectSize = getchar();
	selectSize = valSize(selectSize, SHIRT_SIZE);

	printf("%c", selectSize);
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
}//getSTring


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
char valSize(char sizeSelect, const char *stringArray) {
	


	for (size_t i = 0; i < SIZE_ARRAY_LENGTH; i++) {
		if (sizeSelect == *((stringArray + i))+1) {
			return sizeSelect;
		}

		else if (i == SIZE_ARRAY_LENGTH - 1)
		{
			return EOF;
		}
	}

}
