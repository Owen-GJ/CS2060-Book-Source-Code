/*******************
 Understanding pointers

 Add comments to explain the code
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
	int *houseNumPtr = &houseNum;
	
	printf("houseNum %d\n", houseNum);//value of houseNum

	printf("&houseNum %p\n\n", &houseNum);//memory location of houseNum

	printf ("*houseNumPtr  %d\n", *houseNumPtr);//value of variable houseNumPtr is pointer at (value of houseNum)

	printf ("houseNumPtr %p\n\n", houseNumPtr);//memory location that houseNumPtr is pointer (memory of houseNum)

	printf ("&houseNumPtr %p\n\n", &houseNumPtr);//memory location of the ptr variable itself

	calcHouseNum1 =  *houseNumPtr + *houseNumPtr;//calcHouseNum1 = value ptr is pointing at + value ptr is pointing at

	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1);// 26

	calcHouseNum2 = 2 * (*houseNumPtr);//value pointer is pointing at x2

	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2);

	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", &*houseNumPtr, *&houseNumPtr);//both * and & can be used in either order to get the same result,
	//the memory location that the houseNumPtr is pointing at.
	return 0;
}
