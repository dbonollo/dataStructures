/*--------------------------------------------------------------
Programmer: Destiny Bonollo
Summary:
Date last modified:
----------------------------------------------------------------*/

/*--------------------------------------------------------------
INPUT:
OUTPUT:
---------------------------------------------------------------*/

#include "stdafx.h"
#include "medPing.h"
#include <Windows.h>


//--------------
// medPing_Main \
//----------------------------------------------------------------------
int medPing_Main()
{
	// create a medPing object
	medPing mP;

	double temp, bpm, pulse;

	short sys, diast, glucose, 
	hmr = 5;

	//print greeting
	mP.CELL_PrintF("\nHello medPing patient! Hope that all is well.\n");
	mP.CELL_PrintF("\nPlease proceed to enter your vital signs...\n\n");

	for (short i = 0; i < hmr; i++)
	{
		temp = mP.getBodyTemperature_F();
		bpm = mP.getRespirationRate_BPM();
		pulse = mP.getPulseRate_BPM();
		glucose = mP.getGlucoseLevel_mgdL();
		mP.getBloodPressure_mmHg(sys, diast);

		// print a message to the cell phone
		mP.CELL_PrintF("\nBody Temperature: %5.2f\n", temp);
		mP.CELL_PrintF("Pulse Rate: %5.2f\n", pulse);
		mP.CELL_PrintF("Respiration Rate: %5.2f\n", bpm);
		mP.CELL_PrintF("Glucose Level: %hd\n", glucose);
		mP.CELL_PrintF("Blood Pressure: %hd over %hd\n\n", sys, diast);

		// recording each set of vital signs
		struct myData
		{
			short hmr;
			short sys;
			short diast;

			double temp;
			double bpm;
			double pulse;
			double glucose;
		};

		myData oneRec;
		oneRec.sys;
		oneRec.diast;
		oneRec.glucose;
		oneRec.temp = mP.getBodyTemperature_F();
		oneRec.pulse = mP.getPulseRate_BPM();
		oneRec.bpm = mP.getRespirationRate_BPM();

		myData allRecs[100];
		allRecs[i].sys = oneRec.sys;
		allRecs[i].diast = oneRec.diast;
		allRecs[i].glucose = oneRec.glucose;
		allRecs[i].temp = oneRec.temp;
		allRecs[i].pulse = oneRec.pulse;
		allRecs[i].bpm = oneRec.bpm;

		//Brief pause before next set of information in loop
		Sleep(2000);
	} // for
	


	return 0;

} // end medPing_Main()
