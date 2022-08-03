
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <float.h>
#include <errno.h>



const char* FILE_PATH = {"C:/Users/TheBird/Desktop/T-Shirt Iteration 02 File Directory/"};
#define ARRAY_LENGTH 80
#define CORRECT_PASSCODE "b"
#define ADMIN_QUIT 'q'
#define SIZE_ARRAY_LENGTH 4
#define COLOR_ARRAY_LENGTH 5
const char* SHIRT_SIZE_ARRAY[SIZE_ARRAY_LENGTH] = { "(s)mall", "(m)edium", "(l)arge", "(x)tra-large" };
enum sizes { SMALL, MEDIUM, LARGE, EXTRA_LARGE };
const char* SHIRT_COLOR_ARRAY[COLOR_ARRAY_LENGTH] = { "(w)hite", "(b)lue", "(r)ed", "(p)ink", "(k)black" };
enum colors {WHITE, BLUE, RED, PINK, BLACK};
#define PRICE_MIN 40
#define PRICE_MAX 100
#define NUMBER_OF_ATTEMPTS 4
#define MIN_DONATE_PERCENT 10
#define MAX_DONATE_PERCENT 25

//stuct that holds information about a fundraiser organization
typedef struct orgNode {

	char orgName[ARRAY_LENGTH];
	double price;
	double percent;
	int orgTotalShirts[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH];
	struct orgNode* nextPtr;

}OrgNode;



void displayRecipt(const char* colorArray[], const char* sizeArray[], const int customerArray[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH],
	double price, const char* org, double percent, int charityArray[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH], bool yOrNo);
void displaySummary(char* org, double price, double percent, const char* colorArray[], const char* sizeArray[],
	const int array[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH]);
void getString(char* inputStringPtr);
bool getValidDouble(const char* buff, double* const value, int min, int max);
long getValidZip();
int valSize(char sizeSelect, const char* array[]);
int valColor(char colorSelect, const char* array[]);
bool valString(char* inputStringPtr);
bool yesNoVal();
void fundraiser();
int customerSize();
int customerColor();
void setup(OrgNode** headPtr);
double setPrice(int min, int max);
double setPercent(int min, int max, const char orgName[]);
void setName(char orgName[]);
bool customerPurchase(OrgNode** headPtr);
void checkout(double price, double percent, const char orgName[], int customerShirtArray[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH],
	int charityArray[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH]);
void addOrgNode(OrgNode** headPtr, const char* orgName, double price, double percent);
OrgNode* getOrgNode(OrgNode** headPtr, const char* orgName);
void writeSummariesToFiles(OrgNode** headPtr, const char* colorArray[], const char* sizeArray[]);
void displayOrganizations(OrgNode** headPtr);



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

//places a new orgNode alphabetically into the linked list with given headPtr
void addOrgNode(OrgNode** headPtr, const char* orgName, double price, double percent) {
	//create memory for node and add pointer
	OrgNode* newOrgPtr = malloc(sizeof(OrgNode));

	//check pointer didn't return null, then setup new node
	if (newOrgPtr != NULL) {
		strncpy(newOrgPtr->orgName, orgName, ARRAY_LENGTH);
		newOrgPtr->price = price;
		newOrgPtr->percent = percent;
		
		//fill orgTotalShirts
		for (int colors = 0; colors < COLOR_ARRAY_LENGTH; colors++) {
			for (int size = 0; size < SIZE_ARRAY_LENGTH; size++) {

				newOrgPtr->orgTotalShirts[colors][size] = 0;


			}//size
		}//color
		newOrgPtr->nextPtr = NULL;


		//pointers to keep track of were in list we are
		OrgNode* currentPtr = *headPtr;
		OrgNode* previousPtr = NULL;

		bool found = false;
		//nodes still exist
		while (currentPtr != NULL && !found ) {

			//to sort alphabetically, need to create lowercase string equivilants to compare
			char lowerOrgName[ARRAY_LENGTH] = { '\0' };
			char lowerCurrentPtrOrgName[ARRAY_LENGTH] = { '\0' };

			for (size_t i = 0; i < ARRAY_LENGTH; i++) {
				lowerOrgName[i] = tolower(orgName[i]);
				lowerCurrentPtrOrgName[i] = tolower(currentPtr->orgName[i]);
			}

			//current node is greater than the node to add
			if (strcmp(lowerOrgName, lowerCurrentPtrOrgName) <= 0) {

				found = true;
			}

			else {
				previousPtr = currentPtr;
				currentPtr = currentPtr->nextPtr;
			}

		}// current != null


		//if no head exists, make node the head
		if (previousPtr == NULL) {
			*headPtr = newOrgPtr;
		}//make head


		//found place in list, insert node
		else {
			previousPtr->nextPtr = newOrgPtr;
		}//add orgNode to end of List
		
		//make new orgNode point to next node
		newOrgPtr->nextPtr = currentPtr;


	}// != NULL

	else {
		printf("No memory to create OrgNode for %s\n", orgName);
	}
	
}//addOrgNode

//return pointer to node that has the same name as the one given
OrgNode* getOrgNode(OrgNode** headPtr, const char* orgName) {

	//used for finding and returning a node
	bool found = false;
	OrgNode* returnNode = NULL;
	OrgNode* currentNode = *headPtr;

	//catch if there isn't a head
	if (currentNode == NULL) {
		puts("There are no Organizations currently");
	}

	else {
		while (!found && currentNode != NULL) {
			
			if (strcmp(currentNode->orgName, orgName) == 0) {

				returnNode = currentNode;
				found = true;

			}//if

			else {
				currentNode = currentNode->nextPtr;
			}

		}//!found %% currentNode != NULL
	}//else


	return returnNode;
}//getOrgNode

//writes summaries of nodes past and including the node given, also frees the memory of each node.
void writeSummariesToFiles(OrgNode** headPtr, const char* colorArray[], const char* sizeArray[]) {
	//used to traverse the list
	OrgNode* currentNode = *headPtr;
	OrgNode* next = NULL;

	while (currentNode != NULL) {
		//create filePtr and open/create file for writing
		FILE* filePtr;

		//set up a filepath without editing orgName
		char filePath[ARRAY_LENGTH] = { '\0' };
		strcpy(filePath, FILE_PATH);
		char orgTxt[ARRAY_LENGTH] = { '\0' };
		strcpy(orgTxt, currentNode->orgName);
		strcat(orgTxt, ".txt");
		strcat(filePath, orgTxt);


		//couldn't open file
		if ((filePtr = fopen(filePath, "w")) == NULL) {
			printf("File for %s could not be opened\n", currentNode->orgName);
		}//coudn't open

		//opened file succesfully
		else {

			int totalShirts = 0;

			//calculate total shirts
			for (size_t color = 0; color < COLOR_ARRAY_LENGTH; color++) {
				for (size_t size = 0; size < SIZE_ARRAY_LENGTH; size++) {
					totalShirts += currentNode->orgTotalShirts[color][size];
				}
			}//calculate total shirts

			fprintf(filePtr, "Organization: %s\nT-Shirt purchases\n", currentNode->orgName);

			for (size_t color = 0; color < COLOR_ARRAY_LENGTH; color++) {


				for (size_t size = 0; size < SIZE_ARRAY_LENGTH; size++) {

					//prints header for size
					if (color == 0 && size == 0) {
						fprintf(filePtr, "%-9s\t", "");
						for (size_t i = 0; i < SIZE_ARRAY_LENGTH; i++) {
							fprintf(filePtr, "%-9s\t", sizeArray[i]);
						}
						fputs("\n", filePtr);
					}

					//prints body


					if (size == 0) {
						fprintf(filePtr, "%-9s\t", colorArray[color]);
					}
					fprintf(filePtr, "%-9d\t", currentNode->orgTotalShirts[color][size]);

				}//for size
				fputs("\n", filePtr);
			}//for color

			fprintf(filePtr, "Total shirts sold: %d\nTotal Sales: %.2lf\nFundraiser Percentage: %%%.2lf\nTotal Funds Raised: $%.2lf",
				totalShirts, (totalShirts * currentNode->price), currentNode->percent, (currentNode->percent / 100) * (totalShirts * currentNode->price));



		}//opened file succesfully


		next = currentNode->nextPtr;
		free(currentNode);
		currentNode = next;


	}//While currentNOde != NULL


	headPtr = NULL;

}//writeSummariestoFiles


void displayOrganizations(OrgNode** headPtr) {

	OrgNode* currentNode = *headPtr;

	//displays each node's name
	while (currentNode != NULL) {
		printf("%s\tPrice: %.2lf\t Percent to charity: %%%.2lf\n", currentNode->orgName, currentNode->price, currentNode->percent);
		currentNode = currentNode->nextPtr;
	}

}//displayOrganizations


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


//validates if a char was entered that matches a size, returns -1 for ADMIN_QUIT, -2 for no proper matches in size, and the index of a size if found.
int valSize(char sizeSelect, const char* array[]) {

	int returnIndex = -2;

	//Check entered char against the character in parenthesis.
	//go through for each size
	for (int i = SMALL; i <= EXTRA_LARGE; i++) {
		
		if (tolower(sizeSelect) == array[i][1]) {

			returnIndex = i;

		}//found valid

		else if (towlower(sizeSelect) == ADMIN_QUIT) {
			returnIndex = -1;
		}

	}//go through each size

	return returnIndex;

}//valSize



int valColor(char colorSelect, const char* array[]) {
	int returnIndex = -1;

	//Check entered char against the character in parenthesis.
	//go through for each color
	for (int i = WHITE; i <= BLACK; i++) {
		if (tolower(colorSelect) == array[i][1]) {
			returnIndex = i;
		}
	}


	return returnIndex;
}//ValColor



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


void displaySummary(char* org, double price, double percent, const char* colorArray[], const char* sizeArray[],
	const int array[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH]) {

	int totalShirts = 0;

	//calculate total shirts
	for (size_t color = 0; color < COLOR_ARRAY_LENGTH; color++) {
		for (size_t size = 0; size < SIZE_ARRAY_LENGTH; size++) {
			totalShirts += array[color][size];
		}
	}



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

	printf("Total shirts sold: %d\nTotal Sales: %.2lf\nFundraiser Percentage: %%%.2lf\nTotal Funds Raised: $%.2lf",
		totalShirts, (totalShirts * price), percent, (percent / 100) * (totalShirts * price));



}//displayRecipt


void displayRecipt(const char* colorArray[], const char* sizeArray[], const int customerArray[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH],
	double price, const char* org, double percent, int charityArray[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH], bool yOrNo) {
	int customerTotalShirts = 0;
	int charityTotalShirts = 0;


	
	//calculate customer total shirts and adding to charityArray
	for (size_t color = 0; color < COLOR_ARRAY_LENGTH; color++) {
		for (size_t size = 0; size < SIZE_ARRAY_LENGTH; size++) {
			customerTotalShirts += customerArray[color][size];
			charityArray[color][size] += customerArray[color][size];
			charityTotalShirts += charityArray[color][size];
		}
	}

	//print recipt
	if (yOrNo) {


		//prints out all the shirts
		for (size_t color = 0; color < COLOR_ARRAY_LENGTH; color++) {
			for (size_t size = 0; size < SIZE_ARRAY_LENGTH; size++) {

				for (int i = 0; i < customerArray[color][size]; i++) {
					printf("%s %s tshirt: $%.2lf\n", sizeArray[size], colorArray[color], price);
				}



			}//size
		}//color

		//print total, and ending message
		printf("Total Charge: $%.2lf\n", (customerTotalShirts * price));
		printf("Thank you for supporting %s.\n$%.2lf will be donated to charity.\n$%.2lf has been raised so far\n\n", org, ((percent / 100) * customerTotalShirts * price),
			((percent / 100) * ((charityTotalShirts)*price)));

	}//if(yOrNo)

	//print no recipt
	else {

		printf("Thank you for supporting %s. $%.2lf of your purchase will be donated.\n$%.2lf has been raised so far\n\n", 
			org, ((percent / 100) * customerTotalShirts * price), ((percent / 100) * ((charityTotalShirts)*price)));


	}


}//displayRecipt



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
	printf("Enter sales price of t-shirts between %d and %d\n", PRICE_MIN, PRICE_MAX);
	getString(userPrice);

	double valPrice = 0;
	double* const valPricePtr = &valPrice;

	//recieving input and validate
	bool correctRange = false;
	do {
		//validating
		while (!getValidDouble(userPrice, valPricePtr, PRICE_MIN, PRICE_MAX)) {
			printf("Enter a value between %d and %d\n", PRICE_MIN, PRICE_MAX);
			getString(userPrice);
		}

		//confirm
		printf("Is $%.2lf correct? Enter Y/y for yes; N/n for no.\n", valPrice);
		bool yOrNo = yesNoVal();
		if (yOrNo) {
			correctRange = true;
		}

		else if (!yOrNo) {
			printf("Enter a value between %d and %d\n", PRICE_MIN, PRICE_MAX);
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
void setup(OrgNode** headPtr) {
	
	bool addAnother = true;

	while (addAnother) {

		//name
		char orgName[ARRAY_LENGTH] = { '\0' };

		setName(orgName);

		//setup price
		double price = setPrice(PRICE_MIN, PRICE_MAX);


		double percent = setPercent(MIN_DONATE_PERCENT, MAX_DONATE_PERCENT, orgName);

		addOrgNode(headPtr, orgName, price, percent);


		puts("Would you like to add another organization? Enter Y/y for yes; N/n for no.");
		if (!yesNoVal()) {
			addAnother = false;
		}// y/n val

	}//while addAnother

	//display all organizations created
	puts("\nYou have added the following organizations:");
	displayOrganizations(headPtr);
	puts("\n");


}//setup


//gets the customers size and returns the index
int customerSize() {

	bool sizeIsValid = false;
	int returnIndex = 0;

	while (!sizeIsValid) {
		//ask for size
		puts("Select your shirt size by entering the character in parentheses: ");
		//display each option
		for (int i = SMALL; i <= EXTRA_LARGE; i++) {

			//used for formating
			if (i != EXTRA_LARGE) {
				printf("%s, ", SHIRT_SIZE_ARRAY[i]);
			}//if
			else if (i == EXTRA_LARGE) {
				printf("%s\n", SHIRT_SIZE_ARRAY[i]);
			}
		}//display each option

		//get selection
		char sizeSelect = getchar();
		while (getchar() != '\n');
		returnIndex = valSize(sizeSelect, SHIRT_SIZE_ARRAY);

		if (returnIndex == -2) {
			puts("Error: You did not enter a valid choice\n");

		}//==-2

		else {
			sizeIsValid = true;
		}


	}//while !valSize


	return returnIndex;
}


//gets the customers color and returns the index
int customerColor() {
	bool isValid = false;
	int returnIndex = 0;

	while (!isValid) {
		//ask for color
		puts("Select your shirt color by entering the character in parentheses: ");

		//display each option
		for (int i = WHITE; i <= BLACK; i++) {

			//used for formating
			if (i != BLACK) {
				printf("%s, ", SHIRT_COLOR_ARRAY[i]);
			}//if
			else if (i == BLACK) {
				printf("%s\n", SHIRT_COLOR_ARRAY[i]);
			}
		}//display each option

		char colorSelect = getchar();
		while (getchar() != '\n');
		returnIndex = valColor(colorSelect, SHIRT_COLOR_ARRAY);

		//not valid 
		if (returnIndex == -1) {

			puts("Error: you did not enter a valid choice\n");

		}//not valid

		//leave loop
		else {
			isValid = true;
		}

	}//while !isValid

	return returnIndex;
}


//recieves payment and prints recipt for customer
void checkout(double price, double percent, const char orgName[], int customerShirtArray[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH],
												int charityArray[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH]) {
	//get zipcode
	long zipCode = getValidZip();
	printf("Zip Code: %ld\n\n", zipCode);

	puts("Do you want a recipt? Enter Y/y for yes; N/n for no.");
	bool yOrNo = yesNoVal();
	puts("\n");
	displayRecipt(SHIRT_COLOR_ARRAY, SHIRT_SIZE_ARRAY, customerShirtArray, price, orgName, percent, charityArray, yOrNo);

	
}




//allows customer to purchase from the fundraiser
bool customerPurchase(OrgNode** headPtr) {


	//customer purchasing, need new variables for size and color indexes

	int sizeSelect = 0;
	int colorSelect = 0;


	//used for admin shutdown, when ADMIN_QUIT it will make the function return false, otherwise it will return true.
	bool anotherCustomer = true;
	while (anotherCustomer) {

		//local shirt array for recipt purposes and total shirt book keeping. It is recreated for every customer.
		int customerShirtArray[COLOR_ARRAY_LENGTH][SIZE_ARRAY_LENGTH] = { 0 };
			
		
		OrgNode* fundChoice = NULL;
		bool validChoice = false;
		while (!validChoice) {
			
			//ask customer which organizations they want to purchase from, then set it as a variable to use
			
			puts("Please enter the name of the organization you would like to purchase from from the list below:");
			displayOrganizations(headPtr);
			puts("");
			char userOrgChoice[ARRAY_LENGTH] = { '\0' };
			getString(userOrgChoice);
			puts("");

			fundChoice = getOrgNode(headPtr, userOrgChoice);

			//if the choice doens't match an organization, it will try again
			if(fundChoice == NULL) {
				puts("You did not enter a valid organization, please try again\n");
				false;
			}
			else {
				validChoice = true;
			}

		}//while validChoice


		bool continuePurchasing = true;
		while (continuePurchasing) {







			//get size and color indexes
			sizeSelect = customerSize();



			//don't continue purchasing if ADMIN_QUIT is entered.
			if (sizeSelect != -1) {


				printf("%s selected\n\n", SHIRT_SIZE_ARRAY[sizeSelect]);


				colorSelect = customerColor();
				printf("%s selected\n\n", SHIRT_COLOR_ARRAY[colorSelect]);


				//add shirt to localShirt array, don't add to totalShirtArray until purchase is finalized.
				customerShirtArray[colorSelect][sizeSelect]++;



				//See if customer want another shirt
				puts("Do you want to purchase another shirt? Enter Y/y for yes; N/n for no.");
				bool yOrNo = yesNoVal();
				if (!yOrNo) {
					continuePurchasing = false;
					puts("\n");

					checkout(fundChoice->price, fundChoice->percent, fundChoice->orgName, customerShirtArray, fundChoice->orgTotalShirts);

				}//if(!yOrNo)




			}// != ADMIN_QUIT

			//else make anotherCustomer false so that admin shutdown starts
			else {
				anotherCustomer = false;
				continuePurchasing = false;
			}

		}//continuePurchasing

	}//anotherCustomer
	return anotherCustomer;
}


void fundraiser() {

	//setup will only need a head ptr that we keep in fundraiser

	OrgNode* headPtr = NULL;

	setup(&headPtr);




	//sentinel for if admin shutdown
	bool shutdown = false;
	while (!shutdown) {
		while (customerPurchase(&headPtr));
		

		//attempt to go into admin shutdown
		//validting password
		int attempt = 0;

		while (attempt < NUMBER_OF_ATTEMPTS) {
			//getting passcode and validating it
			char inPasscode[ARRAY_LENGTH];
			puts("Enter passcode");
			getString(inPasscode);
			bool correctPasscode = valString(inPasscode);
			puts("\n");

			if (correctPasscode) {

				writeSummariesToFiles(&headPtr, SHIRT_COLOR_ARRAY, SHIRT_SIZE_ARRAY);
				shutdown = true;
				attempt = NUMBER_OF_ATTEMPTS;
			}//if true


			else if (!correctPasscode) {

				puts("Error: The password is incorrect");
				attempt++;
			}//if false

			if (!correctPasscode && attempt == NUMBER_OF_ATTEMPTS) {
				puts("Exiting admin shutdown");
			}

		}//while attempt < NUMBER_OF_ATTEMPTS

	}//While !shutdown


}//fundraiser