
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_LENGTH 80


typedef struct pet {

	char name[NAME_LENGTH];

	int age;

	struct pet* nextPtr;
}Pet;


void addPet(Pet** headPtr, const char name[NAME_LENGTH], int age);
void displayPets(Pet** headPtr);
bool removePet(Pet** headPtr , const char name[NAME_LENGTH]);
void removeRemainingPets(Pet** headPointer);
bool yesNoVal();
void getString(char* inputStringPtr);


int main(void) {

	//create null headPtr
	Pet* headPtr = NULL;
	bool addContinue = true;
	do {
		


		//get name
		printf("%s", "Enter name: ");
		char name[NAME_LENGTH];
		getString(name);

		//next line
		puts("");

		//get age
		printf("%s", "Enter age: ");
		char ageStr[NAME_LENGTH];
		getString(ageStr);
		char* endPtr = NULL;
		int age = strtol(ageStr, &endPtr, 10);

		//next line and space
		puts("\n");

		//add to list
		addPet(&headPtr, name, age);

		printf("%s", "Do you want to add another pet? Please enter (y)es or (n)o: ");
		
		//if no break out of while
		if (yesNoVal()) {
			addContinue = false;
		}


	} while (addContinue);//do while to add pets


	displayPets(&headPtr);








}


//creates a pet struct and adds it to a linked list in alphabetical order
void addPet(Pet** headPtr, const char name[NAME_LENGTH], int age) {
	
	//create memory for pet and add pointer
	Pet* newPetPtr = malloc(sizeof(Pet));

	//check that the pointer didn't return null
	if (newPetPtr != NULL) {

		//setup new Pet
		//add name, make sure not to copy address but copy contents
		strcpy(newPetPtr->name, name);
		newPetPtr->age = age;
		newPetPtr->nextPtr = NULL;



		//create temp pointers to help change appropriate pointers and keep track of index
		Pet* previousPtr = NULL;
		Pet* currentPtr = *headPtr;


		//finds where in the list the Pet will fit alphabetically
		while (currentPtr != NULL && strcmp(name, currentPtr->name) >= 0) {

			//set privous pointer to current pointer. This is so that it can keep the previous pointer accurate as currentpointer
			//will be set to the next index
			previousPtr = currentPtr;

			//set current pointer to next index
			currentPtr = currentPtr->nextPtr;

		}//while(currentPtr comparisons)

		//this if statement occurs when there is no current headPtr
		if (previousPtr == NULL) {
			//set the Pet ptr to headPtr
			*headPtr = newPetPtr;
		}//if(previousPtr == NULL)

		
		//Insert the Pet into the list
		//First make the privous pointer point to this pet
		else {
			previousPtr->nextPtr = newPetPtr;
		}//else

		//Then make new Pet point to next Pet
		newPetPtr->nextPtr = currentPtr;

	}//if(Ptr !=NULL)

	//if memory couldn't be allocated for pet, the function will display error message
	else {
		printf("No memory to create Pet for %s", name);
	}//else

}//addPet



//removes 1 instance of a pet by name. Return true if successful, false if no pets to remove
bool removePet(Pet** headPtr, const char name[NAME_LENGTH]) {
	bool success = false;
	Pet *currentPtr = *headPtr;
	Pet *previousPtr = NULL;


	//There are pets still in the List
	if (*headPtr != NULL) {

		//check if headPtr is Pet to remove
		if (strcmp((*headPtr)->name, name) == 0) {
			//set new head as the next pet in list
			*headPtr = (*headPtr)->nextPtr;

			//free memory of Pet
			free(currentPtr);
			currentPtr = NULL;

		}//if head is pet to remove

		//if headPtr is not pet to remove
		else {
			//search for first pet with matching name
			while (currentPtr != NULL && strcmp(name, currentPtr->name) != 0) {
				//set previous pointer to this index
				previousPtr = currentPtr;

				//set current pointer to nextPet
				currentPtr = currentPtr->nextPtr;
			}//while search for pet name

			//if pet exists
			if (currentPtr != NULL) {

				//set privous ptr to pet after current pet
				previousPtr->nextPtr = currentPtr->nextPtr;

				//remove current pet
				free(currentPtr);
				currentPtr = NULL;

				success = true;
			}//if pet exists


			//no pet matching name found
			else {
				puts("Pet to remove not found");
			}

		}//head is not pet to remove


	}//if (pets still in list)


	//If no pets in List
	else {
		puts("No pets in List");
	}//else( no pets in List



	//return if successful
	return success;
}//removePet


//display all the pets
void displayPets(Pet** headPtr) {
	
	Pet *currentPtr = *headPtr;

	//check if List is empty
	//Not empty
	if (currentPtr != NULL) {

		//header for display
		puts("The names in alphabetical order:");
		//iterate through list and display name and age
		while (currentPtr != NULL) {

			printf("%s is %d years old\n", currentPtr->name, currentPtr->age);
			currentPtr = currentPtr->nextPtr;


		}//iterate through


	}//not empty

	
	//empty
	else {
		puts("No pets in list");
	}//empty


}//displayPets


//clears Pet list of any remaining pets if there are any
void removeRemainingPets(Pet** headPtr) {
	Pet* currentPtr = *headPtr;
	Pet* nextPtr = NULL;

	//iterate through list
	while (currentPtr != NULL) {
		//used to get to next pet
		nextPtr = currentPtr->nextPtr;

		//free current pet
		free(currentPtr);

		//move current to next
		currentPtr = nextPtr;
	}//iterate through list

	//make head null
	*headPtr = NULL;
}//removeRemainingPets


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


//Input argument of string pointer. Writes to string with max length, then changes new line character to \0
void getString(char* inputStringPtr) {

	//get input
	fgets(inputStringPtr, NAME_LENGTH, stdin);
	size_t length;

	//change new line character '\n' to null character '\0' if '\n' exists
	length = strlen(inputStringPtr);

	char check = inputStringPtr[length - 1];

	if (check == '\n') {
		inputStringPtr[length - 1] = '\0';
	}
}//getString