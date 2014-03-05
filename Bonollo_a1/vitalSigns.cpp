#include "stdafx.h"
#include "vitalSigns.h"

// -------------------\
//  getBodyTemperature \
// ------------------------------------------------------------
// IN: (no arguments)
// RETURNS: simulated body temperature in degrees F
// ------------------------------------------------------------
double getBodyTemperature_F(void)
{
	double temp;

	// ----------prompt the user -----------------
	cout << "Please enter bodyTemp (F): ";
	cin >> temp;
	
	return temp;
}

// -------------------\
//  getRespirationRate \
// --------------------------------------------------------------
// IN: (no arguments)
// RETURNS: simulated respiration rate in beats per minute (BPM)
// --------------------------------------------------------------
double getRespirationRate_BPM(void)
{
	double rate;

	cout << "Please enter respirationRate: ";
	cin >> rate;

	return rate;
    
}
