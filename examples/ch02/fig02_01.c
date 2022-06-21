// Fig. 2.1: fig02_01.c
// A first program in C 
#include <stdio.h>

// function main begins program execution 
int main( void )
{
   printf( "Welcome to C!\n" );

   //declaring variables
   unsigned int length = 0;
   unsigned int width = 0;
   unsigned int area = 0;
   unsigned int enteredNumber = 0;
   unsigned int inputVal = 0;
   unsigned int scannedVar = 0;
   unsigned int divisionResult = 0;

   //obtaining length
   puts("Enter the length");

   while (inputVal == 0) {
	   scannedVar = scanf("%u", &enteredNumber);//collecting input

	   while (getchar() != '\n');//clearing buffer

	   if (scannedVar == 1) {//assigning to variable if scanf scanned something
		   length = enteredNumber;
		   inputVal = 1;
	   }
	   else {
		   puts("Input is either negative or invalid, try again");
	   }
   }


   //obtaining width
   puts("Enter the width");

   scannedVar = scanf("%u", &enteredNumber);//collecting input

   while (getchar() != '\n');//clearing buffer

   if (scannedVar == 1) {//assigning to variable if scanf scanned something
	   width = enteredNumber;

   }


   //calculate area
   area = length * width;

   printf("Length: %u\nWidth: %u\nArea: %u\n", length, width, area);

   divisionResult = length / width;

   printf("Division Result: %u", divisionResult);

   return 0;
} // end function main 


/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
