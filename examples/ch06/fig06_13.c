// Fig. 6.13: fig06_13.c
// Passing arrays and individual array elements to functions.
#include <stdio.h>
#define SIZE 5
#define ROWS 3
#define COLUMNS 4


// function prototypes
void modifyArray(int b[], size_t size);
void modifyElement(int e);               
void printArray(const int c[], size_t size);
void writeTo2DArray(int[ROWS][COLUMNS]);
void print2DArray(int[ROWS][COLUMNS]);





// function main begins program execution
int main(void)
{
   int a[SIZE] = { 0, 1, 2, 3, 4 }; // initialize array a

   puts("Effects of passing entire array by reference:\n\nThe "
      "values of the original array are:");

   // output original array
   for (size_t i = 0; i < SIZE; ++i) { 
      printf("%3d", a[i]);
   } 

   puts(""); // outputs a newline

   modifyArray(a, SIZE); // pass array a to modifyArray by reference                         
   puts("The values of the modified array are:");

   // output modified array
   for (size_t i = 0; i < SIZE; ++i) {
      printf("%3d", a[i]);
   } 

   // output value of a[3]
   printf("\n\n\nEffects of passing array element "
      "by value:\n\nThe value of a[3] is %d\n", a[3]);
   
   modifyElement(a[3]); // pass array element a[3] by value

   // output value of a[3]
   printf("The value of a[3] is %d\n", a[3]);

   //adding line space
   puts("");



   //print values of array a
   printArray(a, SIZE);


   //creating a multidimensional array with rows and columns
   int multi[3][4];

   for (size_t row = 0; row < ROWS; row++)
   {
       for (size_t column = 0; column < COLUMNS; column++)
       {
           multi[row][column] = 0;
       }
   }

   //spacer
   puts("\n");


   writeTo2DArray(multi);

   //spacer
   puts("\n");


   print2DArray(multi);
}

// in function modifyArray, "b" points to the original array "a" 
// in memory                                                     
void modifyArray(int b[], size_t size)                               
{                                                                   
   // multiply each array element by 2                         
   for (size_t j = 0; j < size; ++j) {                                 
      b[j] *= 2; // actually modifies original array               
   }                                                 
} 

// in function modifyElement, "e" is a local copy of array element
// a[3] passed from main                                     
void modifyElement(int e)                                       
{                                                                 
   // multiply parameter by 2                                  
   printf("Value in modifyElement is %d\n", e *= 2);            
}


//prints all the elements in a 1 dimensional array
void printArray(const int c[], size_t size)
{
    printf("%s" , "Elements in array are: ");

    for (size_t i = 0; i < size; ++i) {

        printf("%d ", c[i]);

    }
}



//allows user to input values into the elements of a 2D array
void writeTo2DArray(int array[ROWS][COLUMNS])
{
    for (size_t row = 0; row < ROWS; row++) 
    {
        for (size_t column = 0; column < COLUMNS; column++) 
        {
            
            printf("Enter the value for array[%lli][%lli]: ", row, column);

            //scannedVar for input validation and do while
            int scannedVar = 0;
            do 
            {
                //input
                scannedVar = scanf("%d", &array[row][column]);

                while (getchar() != '\n');


                //check
                if (scannedVar != 1)
                {
                    puts("Input not an integer, try again.");
                }


            } while (scannedVar == 0);




        }
    }
}



void print2DArray(int array[ROWS][COLUMNS])
{
    for (size_t row = 0; row < ROWS; row++)
    {
        for (size_t column = 0; column < COLUMNS; column++)
        {

            printf("The value for index[%lli][%lli] is: %d\n", row, column, array[row][column]);


        }
    }
}
                          




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

