
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NAME_LENGTH 80


typedef struct pet {

	char name[NAME_LENGTH];

	int age;

	struct pet* nextPtr;
}Pet;

void push();
void addPet(char name[NAME_LENGTH], int age);
void displayPets(Pet* headPointer);
void pop(char name[NAME_LENGTH]);
void removeRemainingPets(Pet* headPointer);



int main(void) {













}


//creates a pet struct and adds it to a linked list in alphabetical order
void addPet(char name[NAME_LENGTH], int age) {
	
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
		Pet* currentPtr = NULL;




	}//if(Ptr !=NULL)



}