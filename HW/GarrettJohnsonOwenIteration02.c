
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
#define COLOR_ARRAY_LENGTH 4
const char* SHIRT_SIZE_ARRAY[SIZE_ARRAY_LENGTH] = { "(s)mall", "(m)edium", "(l)arge", "(x)tra-large" };
enum sizes { SMALL1, MEDIUM, LARGE, EXTRA_LARGE };
const char* SHIRT_COLOR_ARRAY[SIZE_ARRAY_LENGTH] = { "(w)hite", "(b)lue", "(p)ink", "(k)black" };
enum colors {WHITE, BLUE, PINK, BLACK};
#define MIN 10
#define MAX 100
#define NUMBER_OF_ATTEMPTS 3
#define MIN_DONATE_PERCENT 5
#define MAX_DONATE_PERCENT 30

void displayRecipt(const char* colorArray[], const char* sizeArray[], const int array[SIZE_ARRAY_LENGTH][COLOR_ARRAY_LENGTH],
	double price, int totalShirts, double charityTotalyShirts, char* org, double percent);
void displaySummary(char* org, double price, double percent, int totalShirts, const char* colorArray[], const char* sizeArray[],
	const int array[SIZE_ARRAY_LENGTH][COLOR_ARRAY_LENGTH]);
void fundraiser();
void getString(char* inputStringPtr);
bool getValidDouble(const char* buff, double* const value, int min, int max);
long getValidZip();
char valSizeOrColor(char sizeSelect, int* const indexPtr, const char* array[]);
bool valString(char* inputStringPtr);
bool yesNoVal();
void revisedFund();
void customerSize();
void customerColor();
void setupFundraiser();
void setup(double* price, double* percent, const char orgName[]);
double setPrice(int min, int max);
double setPercent(int min, int max, const char orgName[]);
void setName(char* orgName);



int main(void) {
	//validting password
	int attempt = 0;


	while (attempt < NUMBER_OF_ATTEMPTS) {
		//getting passcode and validating it
		char inPasscode[ARRAY_LENGTH];
		puts("Enter passcode");
		getString(inPasscode);
		bool correctPasscode = valString(inPasscode);

		if (correctPasscode) {
			revisedFund();

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
	size_t passSize = strlen(CORRECT_PASSCODE);
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
char valSizeOrColor(char sizeSelect, int* const indexPtr, const char* array[]) {

	char charReturn = '\0';


	//Check entered char against the character in parenthesis.
	int i = 0;
	while (charReturn == '\0') {
		if (tolower(sizeSelect) == array[i][1] || tolower(sizeSelect) == 'q') {

			charReturn = tolower(sizeSelect);
			*indexPtr = i;
		}
		else if (i == (int)strlen(*array) - 1)
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
long getValidZip() {

	puts("Enter your 5 digit zip code.");
	//get input and make sure it is only 5 digits and no characters
	char zipString[ARRAY_LENGTH];
	long returnValue = 0;
	char* endPtr;
	bool valid = false;
	errno = 0;
	//
	while (!valid) {
		getString(zipString);
		while (strlen(zipString) != 5) {
			//while (getchar() != '\n');
			puts("Zip code should be 5 digits long, try again");
			getString(zipString);
		}//while(strlen)

		long attemptValue = 0;
		attemptValue = strtol(zipString, &endPtr, 10);

		//no numeric input
		if (endPtr == zipString || endPtr[0] != '\0') {
			puts("Enter only numeric digits, try again");
		}//if

		else {
			valid = true;
			returnValue = attemptValue;
		}//else

	}//while(!valid)

	return returnValue;
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


void displaySummary(char* org, double price, double percent, int totalShirts, const char* colorArray[], const char* sizeArray[],
	const int array[SIZE_ARRAY_LENGTH][COLOR_ARRAY_LENGTH]) {

	printf("Organization: %s\nT-Shirt purchases\n", org);

	for (size_t color = 0; color < COLOR_ARRAY_LENGTH; color++) {


		for (size_t size = 0; size < SIZE_ARRAY_LENGTH; size++) {

			//prints header for size
			if (color == 0 && size == 0) {
				printf("%-9s\t", "");
				for (size_t i = 0; i < SIZE_ARRAY_LENGTH; i++) {
					printf("%-9s\t", sizeArray[i]);
				}
				puts("");
			}

			//prints body


			if (size == 0) {
				printf("%-9s\t", colorArray[color]);
			}
			printf("%-9d\t", array[color][size]);

		}//for size
		puts("");
	}//for color

	printf("Total shirt sold: %d\nTotal Sales: %.2lf\nFundraiser Percentage: %%%.2lf\nTotal Funds Raised: $%.2lf",
		totalShirts, (totalShirts * price), percent, (percent / 100) * (totalShirts * price));



}//displayRecipt


void displayRecipt(const char* colorArray[], const char* sizeArray[], const int array[SIZE_ARRAY_LENGTH][COLOR_ARRAY_LENGTH],
	double price, int totalShirts, double charityTotalyShirts, char* org, double percent) {

	//prints out all the shirts
	for (size_t color = 0; color < COLOR_ARRAY_LENGTH; color++) {
		for (size_t size = 0; size < SIZE_ARRAY_LENGTH; size++) {

			for (int i = 0; i < array[color][size]; i++) {
				printf("%s %s tshirt: $%.2lf\n", sizeArray[size], colorArray[color], price);
			}



		}//size
	}//color

	//print total, and ending message
	printf("Total Charge: $%.2lf\n", (totalShirts * price));
	printf("Thank you for supporting %s.\n%%%.2lf will be donated to charity.\n$%.2lf has been raised so far", org, percent,
		((percent / 100) * ((charityTotalyShirts + totalShirts) * price)));
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
	int totalShirtArray[SIZE_ARRAY_LENGTH][COLOR_ARRAY_LENGTH] = { 0 };


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

	//used for searching for admin shutdown if not shutdown, then continue selling


	//used for more customer status, if admin shutdown this turns false
	bool moreCustomers = true;

	//used to keep track of all shirt sales
	int totalCharityShirts = 0;


	while (moreCustomers) {

		//used for searching for admin shutdown if not shutdown, then continue selling
		bool shutdown = false;

		//used for each sale
		int salesShirtArray[SIZE_ARRAY_LENGTH][COLOR_ARRAY_LENGTH] = { 0 };

		//create space between last customer or admin setup
		puts("\n\n\n");



		int totalSalesShirts = 0;
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



			if (selectSize == 'q') {

				//this shows an attempt was made
				shutdown = true;
				customerContinue = false;

				int attempt = 0;
				while (attempt < NUMBER_OF_ATTEMPTS) {
					//getting passcode and validating it
					char inPasscode[ARRAY_LENGTH];
					puts("Enter passcode");
					getString(inPasscode);
					bool correctPasscode = valString(inPasscode);


					if (correctPasscode) {
						puts("\n");
						displaySummary(orgName, valPrice, valPercent, totalCharityShirts, SHIRT_COLOR_ARRAY, SHIRT_SIZE_ARRAY, totalShirtArray);

						attempt = NUMBER_OF_ATTEMPTS;
						moreCustomers = false;


					}//if true


					else if (!correctPasscode) {

						puts("Error: The password is incorrect");
						attempt++;
					}//if false

					if (!correctPasscode && attempt == NUMBER_OF_ATTEMPTS) {
						puts("Returning to sales mode, current sale has been restarted.");
					}//if

				}// while attempt < num


			}//if( size == q)



			if (!shutdown) {



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

				while (selectColor == EOF || selectColor == 'q') {

					puts("Error: You did not enter a valid choice");
					printf("Select your shirt color by entering the character in parentheses:\n%s, %s, %s, %s\n", SHIRT_COLOR_ARRAY[0], SHIRT_COLOR_ARRAY[1],
						SHIRT_COLOR_ARRAY[2], SHIRT_COLOR_ARRAY[3]);
					selectColor = getchar();
					while (getchar() != '\n');
					selectColor = valSizeOrColor(selectColor, colorIndexPtr, SHIRT_COLOR_ARRAY);
				}//while

				printf("%s was selected\n", SHIRT_COLOR_ARRAY[colorIndex]);





				//add shirt into sales array and totalArray
				salesShirtArray[sizeIndex][colorIndex]++;

				//See if customer want another shirt
				puts("Do you want to purchase another shirt? Enter Y/y for yes; N/n for no.");
				bool yOrNo = yesNoVal();
				if (!yOrNo) {
					customerContinue = false;
				}

				totalSalesShirts++;


			}//if(!shutdown)

		}//while(customsercontinue)


		//don't show recipt options if admin initiates shutdown
		if (!shutdown) {

			long zipCode = getValidZip();
			printf("Zip Code: %ld\n", zipCode);


			puts("Do you want a recipt? Enter Y/y for yes; N/n for no.");
			bool yOrNo = yesNoVal();
			if (yOrNo) {
				puts("\n");
				displayRecipt(SHIRT_COLOR_ARRAY, SHIRT_SIZE_ARRAY, salesShirtArray, valPrice, totalSalesShirts, totalCharityShirts, orgName, valPercent);
			}
			else {
				puts("\n");
				printf("Thank you for supporting %s. $%.2lf of your purchase will be donated.\n$%.2lf has been raised so far", orgName,
					((valPercent / 100) * (totalSalesShirts * valPrice)), (valPercent / 100) * ((totalCharityShirts + totalSalesShirts) * valPrice));
			}

			totalCharityShirts += totalSalesShirts;

			//adds all of the shirts that have been purchased to totalcharity shirts array
			for (int row = 0; row < SIZE_ARRAY_LENGTH; row++) {
				for (int column = 0; column < COLOR_ARRAY_LENGTH; column++) {

					totalShirtArray[row][column] += salesShirtArray[row][column];

				}
			}






		}//if(!shutdonw)
		//end of while for checking for Q

	}//while(morecustomers)

}//fundraiser


//sets the organization name
void setName(char orgName[]) {

	//getting name
	puts("Enter fundraiser orginization's name");

	getString(orgName);

}



//sets the price of a fundraiser
double setPrice(int min, int max) {

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



	return valPrice;
}



//sets the donation percent of the fundraiser
double setPercent(int min, int max, const char orgName[]) {


	//settup charity percent amount
	printf("Enter percentage of the t-shirt sales between %%%d and %%%d that will be donated to %s\n", MIN_DONATE_PERCENT, MAX_DONATE_PERCENT, orgName);
	char userPercent[ARRAY_LENGTH];
	getString(userPercent);



	double valPercent = 0;
	double* const valPercentPtr = &valPercent;


	bool correctRange = false;


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



	return valPercent;
}



//setups the price and percent of a fundraiser
void setup(double* price, double* percent, const char orgName[]) {
	
	//name
	setName(orgName);

	//setup price
	*price = setPrice(MIN, MAX);


	printf("price In setup: %lf\n", *price);

	*percent = setPercent(MIN_DONATE_PERCENT, MAX_DONATE_PERCENT, orgName);

	printf("percent in setup: %lf\n", *percent);

}//setup




void revisedFund() {

	//setup will need to change a few variables and keep in scope of fundraiser
	
	double price = 0;
	double percent = 0;
	double* pricePtr = &price;
	double* percentPtr = &percent;
	char* orgName[ARRAY_LENGTH] = {""};






	//price
	setup(pricePtr, percentPtr, *orgName);

	printf("In revised: %lf\n", price);
	printf("in revise: %lf\n", percent);
	




}//fundraiser