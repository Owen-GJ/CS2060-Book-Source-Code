
#include <stdio.h>
#include <float.h>
#include <math.h>
#define MAX_HOUR 24
#define MIN_HOUR 0
#define PRICE_PER_HOUR 0.50
#define MIN_PRICE 2.00
#define MAX_PRICE 10.00
#define PRICING_MIN_HOUR 3

// function prototypes
double validateInput(int min, int max);
void displayGarageFee(int car, double hours, double fee);
double calculateFee(double input);




// function main begins program execution
int main(void){

	//used for do while and input catching
	double input = 0;

	//other variables
	unsigned int cars = 0;
	double fee = 0;
	double totalHours = 0;
	double totalFee = 0;

	do {
		//greeting and retrieving input
		puts("Enter the number of hours the car was parked or enter -1 to quit.");
		input = validateInput(MIN_HOUR, MAX_HOUR);

		//if user doesn't want to end program
		if (input != -1) {
			
			//math for totals and current fee
			cars++;
			totalHours += input;
			fee = calculateFee(input);

			//checking if fee is greater than MAX_PRICE and setting to max price
			if (fee > MAX_PRICE) {
				fee = MAX_PRICE;
			}
			totalFee += fee;


			//header for display table
			printf("%s\t%s\t%s\n", "Car", "Hours", "Charge");
			displayGarageFee(cars, input, fee);
			puts("");


		}




	} while (input != -1);


	//if no cars came through
	if (cars == 0) {
		puts("There were no cars parked today.");
	}


	//cars came through
	else {
		//display totals
		//header
		printf("Totals for the day\n%s\t%s\t%s\n", "Cars", "Hours", "Charge");
		displayGarageFee(cars, totalHours, totalFee);
	}
}



//Validates input to be between values and returns input
double validateInput(int min, int max) {

	double input = 0;
	int scannedVar = 0;
	
	do {
		
		//security procedures
		scannedVar = scanf("%lf", &input);

		while (getchar() != '\n');


		//making sure the loop runs again if input is out of bounds
		if ((input != -1) && (input <= min || max < input)) {
			scannedVar = 0;

			printf("Input is not between %d and %d\n", min, max);

			puts("Enter the number of hours the car was parked or enter -1 to quit.");
		}



		else if (scannedVar != 1){
			puts("You did not enter a number");

			puts("Enter the number of hours the car was parked or enter -1 to quit.");
		}

		

	} while (scannedVar != 1);

	return input;


}


//prints (without header) a table of cars hours, and fees
void displayGarageFee(int car, double hours, double fee) {
	printf("%d\t%.2lf\t%.2lf\n", car, hours, fee);
}

//calculates fee 
double calculateFee(double input) {
	double fee = 0;

	//used for finding if input is an integer or not
	double floored = floor(input);
	
	//fee for hour < MIN_HOUR
	if (input < PRICING_MIN_HOUR) {
		fee = 2;
	}

	
	//fee for integer > MIN_HOUR
	else if (floored == input) {
		fee = ((input - PRICING_MIN_HOUR) * PRICE_PER_HOUR) + MIN_PRICE;
	}
	
	//fee for decimal
	else if (floored != input) {
		fee = (((floored + 1) - PRICING_MIN_HOUR) * PRICE_PER_HOUR) + MIN_PRICE;
	}


	return fee;
}