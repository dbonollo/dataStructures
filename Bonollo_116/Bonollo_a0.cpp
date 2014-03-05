/*--------------------------------------------------------------
 Destiny Bonollo -- Program 0

 Summary: This program focuses on finding Real roots and printing 
          those values by handling quadratic or linear equations.

 Date last modified: January 31, 2014
 ----------------------------------------------------------------*/
/*--------------------------------------------------------------
 INPUT: (keyboard, stdin): User is prompted to enter real coefficients for A, B, and C.
 
 OUTPUT: (console, stdout): Roots; first root, second root, imaginary, infinite, NO roots.
							Warning messages for invalid input or operation.
 ---------------------------------------------------------------*/

//#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;

int main(void)
{
	double  A = 0,     // three coefficients for quadratic equation
			B = 0,
			C = 0;
	
	double rootONE,      // first root
		   rootTWO;      // second root

	// prompt user for input from the keyboard
	cout << "Please enter a (Real) coefficient for A: ";
	cin >> A;
	cout << "Please enter a (Real) coefficient for B: ";
	cin >> B;
	cout << "Please enter a (Real) coefficient for C: ";
	cin >> C;

	if (B*B - (4 * A*C) < 0)  // if discriminant is negative
	{
		cout << "Those roots would be imaginary! For Real roots, please try again." << endl;
	}
	else // discriminant is positive
	{
		if (A == 0)
		{
			cout << "Illegal Quadratic Operation: Division by 0. Conducting Linear Test..." << endl;

			//  Conducting linear test: y = BX + C
			if (B == 0)
			{
				if (C == 0)
				{
					cout << "This creates a line that hits all points on the x-axis and there are infinite ROOTS" << endl;
				}
				else
				{
					cout << "This is the equation of a line, thus there NO ROOTS " << endl;
				}
			}
			else
			{
				cout << "This is the equation of a line, thus there is only one Real ROOT and it is: " << B << endl;
			}
		else
		{
			// compute the first root
			rootONE = (-B + sqrt(B*B - 4 * A*C)) / (2 * A);

			// compute the second root
			rootTWO = (-B - sqrt(B*B - 4 * A*C)) / (2 * A);

			cout << "First root is:  " << rootONE << endl;
			cout << "Second root is: " << rootTWO << endl;
		} // end if A
		
	}   // end if discriminant

	//system("PAUSE");
	return 0;
	
} // main
