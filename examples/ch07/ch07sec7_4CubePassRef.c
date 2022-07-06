// Passing Primitive Data Types and pointers
//Add comments to explain the code

#include <stdio.h>	
#include <stdlib.h>


//function prototypes
int cubePass1(int number);
int cubePass2(int * numberPtr);

int main(void) {

	//declare variables
	int numberMain = 5;
	int result = 0;
	
	
	printf ("In main before cubePass1  numberMain = %d\n", numberMain);//prints out value of numberMain
	printf("&numberMain = %p\n", &numberMain);//prints out memory address of numberMain
	result = cubePass1(numberMain);


	printf ("In main after cubePass1  numberMain = %d\n", numberMain);// no change to numberMain
	printf ("Result = %d\n", result);//no change


	printf("\nIn main before cubePass2  numberMain = %d\n", numberMain);//still no change
	
	result = cubePass2(&numberMain);//result is the cube of original numbermain, the function will also cube numberMain
	printf("\nIn main after cubePass2  numberMain = %d\n", numberMain);//number main is now cube of its original number
	printf("result = %d\n", result);//cube of original numberMain

} // main


int cubePass1 (int number) 
{
	int cube = 0;
	puts("\nIn cubePass1");


	printf("number = %d\n", number);//value of passed value
	printf("&number = %p\n", &number);//memory location of the new variable created by pass by value

	cube = number * number * number;//cubing passed by value
	printf("cube  = %d\n", cube);

	number = cube;//setting variable created by pass by value to cube

	printf("number = %d\n", number);//print the cubed of passed by value
	return cube;
} 

int cubePass2 (int * numberPtr) 
{
	int cube = 0;
	puts ("\nIn cubePass2");

	printf("numberPtr = %p\n", numberPtr);//memory location of the variable that was passed into the function
	printf ("*numberPtr = %d\n", *numberPtr);//value of the variable passed into the function

	printf("&numberPtr = %p\n", &numberPtr);//memory location of the pointer pointing to the variable passed into the function
	cube = (* numberPtr )* (* numberPtr )* (* numberPtr);//cubing the value passed into the function

	*numberPtr = cube;//setting the variable passed into function to cube ie numberMain
	printf ("*numberPtr = %d\n", *numberPtr);//print cubed value of original numberMain

	return cube;
} 


