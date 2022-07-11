/*
Owen Garrett Johnson
CS2060
HW04
Due 7/14
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>



#define arrayLength 80
#define CORRECT_PASSCODE "$3cr3t!"

void getString(char* inputStringPtr);
bool valString(char* inputStringPtr);



int main(void) {
	static const char* SIZE[4] = ("(s)mall" "(m)edium" "(l)arge" "(x)tra-large" );

	//getting passcode and validating it
	char inPasscode[arrayLength];
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


}


//Input argument of string pointer. Writes to string with max length, then changes new line character to \0
void getString(char* inputStringPtr) {

	//get input
	fgets(inputStringPtr, arrayLength, stdin);
	size_t length;

	//change new line character '\n' to null character '\0' if '\n' exists
	length = strlen(inputStringPtr);

	char check = inputStringPtr[length - 1];

	if (check == '\n') {
		inputStringPtr[length - 1] = '\0';
	}
}//getSTring


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
}




