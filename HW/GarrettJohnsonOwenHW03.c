
#include <stdio.h>
#include <float.h>
#include <math.h>
#define MAX 24
#define MIN 0
#define PRICE_PER_HOUR 0.50
#define MIN_PRICE 2.00
#define MAX_PRICE 10.00


// function prototypes
double validateInput(void);
void displayGarageFee(int car, double hours, double fee);
double calculateFee(double input);




// function main begins program execution
int main(void){

	printf("here is number %lf", validateInput());
	puts("");
	displayGarageFee(3, 2.4, 5);
}



//Validates input to be between values and returns input
double validateInput() {

	double input = 0;
	unsigned int scannedVar = 0;
	
	do {
		
		//security procedures
		scannedVar = scanf("%lf", &input);

		while (getchar() != '\n');


		//making sure the loop runs again if input is out of bounds

		if (input != -1 && input < MIN || MAX < input) {
			scannedVar = 0;
		}


		if (scannedVar != 1){
			puts("Invalid input, try again");
		}

		

	} while (scannedVar != 1);

	return input;


}


//prints (without header) a table of cars hours, and fees
void displayGarageFee(int car, double hours, double fee) {
	printf("%d\t%.2lf\t%.2lf", car, hours, fee);
}

//calculates fee 
double calculateFee(double input) {





}