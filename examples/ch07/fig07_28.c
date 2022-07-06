// Fig. 7.28: fig07_28.c
// Demonstrating an array of pointers to functions.
#include <stdio.h>

// prototypes
double addition(double a, double b);
double subtraction(double a, double b);
double multiplication(double a, double b);
double division(double a, double b);

int main(void)
{
   // initialize array of 3 pointers to functions that each take an
   // int argument and return void                              
   double (*f[4])(double,double) = {addition, subtraction, multiplication, division};    

   printf("%s", "Enter a number between 0 and 4: \n"
       "0: Addition\n1: Subtraction\n2: Multiplication\n3: Division\n4: End program\n");
   size_t choice; // variable to hold user's choice
   scanf("%llu", &choice);
   
   //i realize we aren't worried too much about security practices, but this is to make things easier
   while (getchar() != '\n');

   //variable to catch the return of function
   double catch = 0;

   // process user's choice
   while (choice >= 0 && choice < 4) {

       //variables to hold users calculation inputs
       double first;
       double second;

       switch (choice) {
       case 0: puts("Addition selected"); break;
       case 1: puts("Subtraction selected"); break;
       case 2: puts("Multiplication  selected"); break;
       case 3: puts("Division selected"); break;
       }


       puts("Enter the two inputs for the calculation");

       printf("%s", "First input: ");
       scanf("%lf", &first);
       while (getchar() != '\n');
       puts("");

       printf("%s", "Second input: ");
       scanf("%lf", &second);
       while (getchar() != '\n');
       puts("");

      catch = (*f[choice])(first, second);                                

      printf("The return value is %.2lf\n\n", catch);

      printf("%s", "Enter a number between 0 and 4: \n"
          "0: Addition\n1: Subtraction\n2: Multiplication\n3: Division\n4: End program\n");

      scanf("%llu", &choice);
   } 


   puts("Program execution completed.");
} 

//returns the sum of a + b
double addition(double a, double b)
{
    double sum = a + b;

    return sum;
}

//returns difference of a - b
double subtraction(double a, double b)
{
    double difference = a - b;

   return difference;
}


//returns product of a * b
double multiplication(double a, double b)
{
    double product = a * b;

    return product;
}


//returns quotient of a / b
double division(double a, double b) {

    double quotient = a / b;

    return quotient;

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

