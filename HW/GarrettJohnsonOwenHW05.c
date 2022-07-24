
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NAME_LENGTH 80


typedef struct pet {

	char name[NAME_LENGTH];

	int age;

	struct pet* nextPtr;
}Pet;


void addPet(Pet** headPtr, char name[NAME_LENGTH], int age);
void displayPets(Pet* headPointer);
void pop(char name[NAME_LENGTH]);
void removeRemainingPets(Pet* headPointer);



int main(void) {













}


//creates a pet struct and adds it to a linked list in alphabetical order
void addPet(Pet** headPtr,char name[NAME_LENGTH], int age) {
	
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
		while (currentPtr != NULL && currentPtr->name[0] <= name[0]) {

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