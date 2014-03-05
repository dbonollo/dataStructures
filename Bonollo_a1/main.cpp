/*----------------------------------------
Destiny Bonollo -- Program 1
Date last modified: 02/06/2014

Summary: This program inputs three pairs of (x,y) values and calculates both the correlation 
		 coefficient and strength of association. The correlation coefficient (r) is a measure
		 of "relatedness," that is, a measure that indicates whether the x-data values are
		 related (either positively, negatively, or neither) to the y-data values.
-----------------------------------------
INPUT(from keyboard, stdin): three sets of REAL (x,y) pairs.

OUTPUT (console, stdout): the correlation coefficient, the strength of association and a
						  message indicating whether the association is strong or weak.
---------------------------------------*/

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "vitalSigns.h"

using namespace std;

int main()
{	
	// DECLARE CONSTANTS					// ----- CONSTANT declarations -----
	const short N = 3;						// number of(x, y) pairs
                                      
	
	const double STRENGTH = 0.50;			// value to measure strength of association
	
	
	// DECLARE VARIABLES	
	double									// ----- VARIABLE declarations -----
	x1, y1,									// first  (x,y) pair
	x2, y2,									// second (x,y) pair
	x3, y3;									// third  (x,y) pair

	double
	sumX, sumY,								//sum of the x and y values
	sumXX, sumYY,							//sum of the squares of the x and y values
	sumXY;									//sum of the products of x and y values

	double
	sqrtOne,								//before first square root denominator
	sqrtTwo;								//before second square root in denominator

	double
	correlationCoefficient,					//correlation coefficient (r)
	strengthAssoc;							//strength of association (r-squared)
	

	//------------print title-----------------------
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "      Regression analysis on THREE pairs of" << endl;
	cout << "       (BodyTemp, RespirationRate) values" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	//----------------------------------------------
    
    // hold first (temp, breathRate) pair
	x1 = getBodyTemperature_F();		//function returns value
	y1 = getRespirationRate_BPM();		//function returns value

	// hold second (temp, breathRate) pair
	x2 = getBodyTemperature_F();		//function returns value
	y2 = getRespirationRate_BPM();		//function returns value
	
	// hold third (temp, breathRate) pair
	x3 = getBodyTemperature_F();		//function returns value
	y3 = getRespirationRate_BPM();		//function returns value


	// ----------echo pairs to the console----------
	cout << endl << "Your three (BodyTempF, RespirationRate) pairs are: " << endl;
	printf("\tpair 1:  (%6.1f, %6.1f)\n", x1, y1);
	printf("\tpair 2:  (%6.1f, %6.1f)\n", x2, y2);
	printf("\tpair 3:  (%6.1f, %6.1f)\n", x3, y3);
	//----------------------------------------------

	//--------------Doing the math------------------
	sumX = (x1 + x2 + x3);		// sum of the x values
	sumY = (y1 + y2 + y3);		// sum of the y values

	sumXX = (x1*x1) + (x2*x2) + (x3*x3);	// sum of the squares of the x values
	sumYY = (y1*y1) + (y2*y2) + (y3*y3);	// sum of the squares of the x values
	
	sumXY = (x1*y1) + (x2*y2) + (x3*y3);	// sum of the products of corresponding (x,y) values
	//----------------------------------------------

    
	//----------Correlation coefficient-------------
	sqrtOne = (N*(sumXX) - (sumX * sumX));				//the first group of data for a square root
	sqrtTwo = (N*(sumYY) - (sumY * sumY));				//the second group of data for a square root

	// ----calculating correlationCoefficient-------
	if (sqrtOne && sqrtTwo <= 0)
	{
		cout << "ERROR: This leads to taking the square root of a negative!" << endl;
	}	// if
	else if (((sqrt(sqrtOne))*(sqrt(sqrtTwo))) == 0)
	{
		cout << "ERROR: This leads to division by zero!" << endl;
	}	// else if
	else
	{
		correlationCoefficient = (N*(sumXY)-(sumX * sumY)) / ((sqrt(N*(sumXX)-(sumX * sumX))) * (sqrt(N*(sumYY)-(sumY * sumY))));
		cout << endl << "--------------------------------------------------" << endl;
		printf("\tcorrelation coefficient = %6.2f\n", correlationCoefficient);
	}	// else
	//-----------------------------------------------

	//------Strength of Association------------------
	strengthAssoc = (correlationCoefficient * correlationCoefficient);
	printf("\tstrength of association = %6.2f", strengthAssoc);
	cout << endl << "--------------------------------------------------" << endl << endl;

	if (strengthAssoc >= STRENGTH)
	{
		cout << "This strength of association is strong enough!\nSTRONG r-squared (means r^2 is 0.50 or greater)." << endl;
	}	// if
	else
	{
		cout << "This strength of association is weak.\nWEAK r-squared (means r^2 is less than 0.50)." << endl;
	}	// else
	//-----------------------------------------------

    cout << endl << "Done." << endl << endl;

	system("PAUSE");
	return 0;
	
} // end main()
