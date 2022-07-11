/*
	if (inputStr[strlen(inputStr) - 1] == '\n')
	{
		inputStr[strlen(inputStr) - 1] = '\0';
	}
*/

#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define LENGTH 13

//added arguments to prototype so that it can accept a pointer to a passed in int. It works similar to scanf as that i can modify
//a reference passed in. This allows the function to return a bool and change a value in main.
bool exploreValidateInt(const char* buff, int *modifyInt);
bool validateInt(char* buff, int* const validInt);
void printLimits();

int main(void)
{
	char inputStr[LENGTH]; // create char arintray
	bool isValid = false;
	int integerValue = 0;
	size_t inputLength = 0;

	printLimits();

	puts("\nEnter an integer");
	fgets(inputStr, LENGTH, stdin);

	//commented out for loop because it wouldn't change stuff.
	//for (unsigned int counter = 1; counter < 6; counter++)
	//{
		isValid = exploreValidateInt(inputStr, &integerValue);
		printf("integerValue is now: %d", integerValue);

	//}

	
}



void printLimits()
{
	printf("The number of bits in a byte %d\n", CHAR_BIT);

	printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
	printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
	printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);

	printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
	printf("The maximum value of SHORT INT = %d\n", SHRT_MAX);

	printf("The minimum value of INT = %d\n", INT_MIN);
	printf("The maximum value of INT = %d\n", INT_MAX);

	printf("The minimum value of CHAR = %d\n", CHAR_MIN);
	printf("The maximum value of CHAR = %d\n", CHAR_MAX);

	printf("The minimum value of LONG = %ld\n", LONG_MIN);
	printf("The maximum value of LONG = %ld\n", LONG_MAX);
}


bool  exploreValidateInt(const char* buff, int *modifyInt)
{
	//boolean added to say if it is valid
	bool isValid = false;

	//used in first if else
	char* compareToNull = "\n";

	char* end;
	errno = 0;
	int validInt = 0;
	long intTest = strtol(buff, &end, 10);
	if (end == buff) {
		fprintf(stderr, "%s: not a decimal number\n", buff);
	}

	//comparing string to another string needs function comparison so I changed it
	else if (strcmp(compareToNull, end) != 0) {
		fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
	}
	else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
		fprintf(stderr, "%s out of range of type long\n", buff);
	}
	else if (intTest > INT_MAX) {
		fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
	}
	else if (intTest < INT_MIN) {
		fprintf(stderr, "%ld less than INT_MIN\n", intTest);
	}
	else {
		validInt = (int)intTest;
		printf("%ld is integer value ", intTest);
		//chang isValid to true
		isValid = true;

		//edit referenced memory to inputed integer.
		*modifyInt = (int) intTest;

	}

	return isValid;
}
