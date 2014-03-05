/*--------------------------------------------------------------
Programmer: Destiny Bonollo		
 
Summary: This program takes the existing medPing product and builds onto it; 
		 the purpose is to produce a quick mock-up of how one might save the 
		 history of a patient's vital signs in an array of structs.
 
Date last modified: 02/28/2014
02/14/2014: (dbb) Downloaded Starter Kit
02/19/2014: (dbb) After lab -- Worked on drawing pictures of possible structs/arrays
02/23/2014: (dbb) Studying the code and following the comments
02/24/2014: (dbb) unable to make Devin's office hours.. working on the basics
02/26/2014: (dbb) After lab -- working on functions; pre- and post- conditions, etc.
02/27/2014: (dbb) Working with the array of structs.. lots of bugs!
02/28/2014: (dbb) Finishing touches/Commenting and Testing (a lot)
----------------------------------------------------------------*/

/*--------------------------------------------------------------
INPUT: stdin (KEYBOARD): In this simulation the assumed input would be "pinged" from a chip within a patient or through 
	   the patient's cellphone, for this assignment the input will be standard input through the keyboard. The initial
	   inquiry of data is in SECONDS, this should be a reasonable number. The last inquiry of input is when prompting
	   the user, upon viewing, if they want to delete a record and this is answered with a character ('Y' or 'N'). If the
	   user chooses to delete the record then they will need to input the time stamp from the record (integers). All input
	   of data and records is processed into an array of structs awaiting display or editing.

OUTPUT: stdout (CONSOLE/DEVICE): In this simulation the output is to the patient's cellphone or media device. The records will be 
		printed to the screen every second (adjustable) as the data is collected for the entirety of the simulation time. 
		Once the simulation has completed the 5 most recent records will print to the screen. The user is prompted with the
		and option to manipulate their records, if the user chooses to do so then any changes will also be printed to the screen.
---------------------------------------------------------------*/

#include "stdafx.h"
#include <iostream>
#include "medPing.h"
#include <cassert>
#include <time.h>
#include <windows.h>		// Windows users require this header file

using namespace std;

//=======================================
const long MAX_HISTORY  = 5;	// can store upto (last) 5 sets of vital signs

const long MAX_WAIT_SEC = 4;	// will random pause from 1 to MAX_WAIT_SEC 

//========================================
struct oneVitalHistoryRecord
{
	long nSecs;
	double beats, newTemp, bpm;
};
//========================================

// function prototypes for keeping track of HISTORY
void AddHistoryRecord(long nSecs, double beats, double newTemp, double bpm, oneVitalHistoryRecord vitalHistory[ ], long hmr);

const long NOT_FOUND = -1;  // used to indicate failure on linear search
long FindVitalRecord(long rawTime, oneVitalHistoryRecord vitalHistory[], short recordLocation);

void DeleteHistoryRecord(long recordIndex, long rawTime, oneVitalHistoryRecord vitalHistory[], short recordLocation, long hmr);

void printAllVitalRecords(medPing& mP, const oneVitalHistoryRecord vitalHistory[], long hmr);
// end function prototypes


//-----------------------------------------------------------------------
//create a medPing object (mP object has global file scope)
medPing mP;	

//--------------
// medPing_Main \
//----------------------------------------------------------------------
// called from iPhone runSim-tab
int medPing_Main()
{
	// print a message to the cell phone
	mP.CELL_PrintF("Hello medPing patient!\n\n");
	
	//======= DATA STRUCTURE ======================================
	// to hold patient's history of vital signs
	oneVitalHistoryRecord	vitalHistory[MAX_HISTORY];	
	
	// hmr (how many really) vital signs  0 <= hmr < MAX_HISTORY
	long hmr = 0;  
	//=============================================================
	
	RandGen		randGenerator;	// i need a random number generator
	time_t		start, now;		// keep track of time in simulation

	
	// ask user at CELL to input length of simulation
	mP.CELL_PrintF("How many SECONDS would you like to simulate?\n");
	double simulationTime = mP.CELL_fetchReal();
	time(&start);
	
	// simulation loop ....
	time(&now);
	while ( difftime(now,start) < simulationTime )		// while still time to simulate ...
	{
		long waitThisLongSEC = 1;
		mP.CELL_PrintF("\n--------------------------\n");
		mP.CELL_PrintF("\n[PAUSE ... (%d seconds) ]\n", waitThisLongSEC);
		Sleep(waitThisLongSEC*1000);	//ZZzzzz...
		
		// check our watch ...
		long nSecs = time(&now);
		
		// fetch vital signs from the medPing chip
		double newTemp, beats, bpm;

		newTemp = mP.getBodyTemperature_F();
		beats = mP.getPulseRate_BPM();
		bpm = mP.getRespirationRate_BPM();

		// efficient! print to screen as collected
		cout << "Temperature (F): \t" << newTemp << endl;
		cout << "Pulse Rate (bpm): \t" << beats << endl;
		
		// now ADD these new vital signs to our history DATA STRUCTURE
		AddHistoryRecord(nSecs, newTemp, bpm, beats, vitalHistory, hmr);
		hmr++;
	}
		
	mP.CELL_PrintF("\n\nSIMULATION OVER.\n\n");

	// PRINT ALL of the series of vital signs so far
	printAllVitalRecords(mP, vitalHistory, hmr);


	//VARIABLES
	long rawTime;				// the time stamp of a record
	bool found;					// true = found, false = not found
	short recordLocation;		// identifying record
	char eraseData;				// asking if user would like to remove data
	char DeleteRecord;			// prompting user for confirmation of deletion

	// prompt user if they would like to delete a record
	mP.CELL_PrintF("DELETE a record? Enter ('Y' or 'N'): \n");
	cin >> eraseData;

	if (eraseData == 'Y' | eraseData == 'y')
	{
		cout << "Please enter the rawTime of the record you would like to delete: ";
		cin >> rawTime;

		recordLocation = 0;
		// based on the user input find the corresponding record
		found = FindVitalRecord(rawTime, vitalHistory, recordLocation);

		long recordIndex = found;

		// Double-checking with the user
		cout << "Are you sure you want to delete this record? Enter ('Y' or 'N'): ";
		cin >> DeleteRecord;

		if (DeleteRecord == 'Y' | DeleteRecord == 'y')
		{
			// Proceed to delete!
			DeleteHistoryRecord(recordIndex, rawTime, vitalHistory, recordLocation, hmr);
		}

	} // if
	
	// prompt user that the program finished
	mP.CELL_PrintF("\n\nDONE.\n");
	
	system("PAUSE");
	return 0;
} // end medPing_Main()


// HISTORY functions below
//------------------\
// AddHistoryRecords \
//---------------------------------------------------------------------------------------------
// AddHistoryRecords communicates with main and adds data into structs one at a time.
// The purpose is to only retain the the most RECENT 5 records.
// PRE: Requires data from main.cpp
// POST: Over writing the oldest data when input exceeds 5 (MAX_HISTORY) records.
//---------------------------------------------------------------------------------------------
void AddHistoryRecord(long nSecs, double beats, double newTemp, double bpm,
					  oneVitalHistoryRecord vitalHistory[ ], long hmr )
{
	double arrayPosition;
	arrayPosition = hmr;

	//Filling the cells
	if (arrayPosition < MAX_HISTORY)
	{
		vitalHistory[hmr].nSecs = nSecs;
		vitalHistory[hmr].newTemp =  newTemp;
		vitalHistory[hmr].beats = beats;

		cout << "\nHistory added.\n" << endl;
	} // if

	else
	{
		//if entries exceed 5 then shift the most recent to the first of the cells
		for (long i=0; i < MAX_HISTORY-1; i++)
		{
			vitalHistory[i].nSecs = vitalHistory[i+1].nSecs;
			vitalHistory[i].newTemp =  vitalHistory[i+1].newTemp;
			vitalHistory[i].beats = vitalHistory[i+1].beats;
		} // for

		//the new data is then entered into the newly freed array cell
		vitalHistory[4].nSecs = nSecs;
		vitalHistory[4].newTemp =  newTemp;
		vitalHistory[4].beats =  beats;

		cout << "History added" << endl;
	} // else

}


//-----------------\
// FindVitalRecords \
//---------------------------------------------------------------------------------------------
// Searches the corresponding array based on input from the user (keyboard).
// PRE: Minimum stored in vitalHistory array; minimum of 1
// POST: if nSecs found within oneVitalHistoryRecord[] then RETURNS index of array cell where found
//		 otherwise RETURNS "NOT_FOUND" (constant indicating "not found")
//---------------------------------------------------------------------------------------------
long FindVitalRecord(long rawTime, oneVitalHistoryRecord vitalHistory[], short recordLocation)
{
	// searching within the last 5 set of vital signs
	for (long i = 0; i < MAX_HISTORY; i++)
	{
		if (vitalHistory[i].nSecs == rawTime)
		{
			cout << " Found it!" << endl;
			recordLocation = i;
		} // if
		else
		{
			return NOT_FOUND;
		}
	} // for

} // FindVitalRecord()


//---------------------\
// DeleteHistoryRecords \
//---------------------------------------------------------------------------------------------
// Based on the user input (keyboard), find the corresponding data in preparation for deletion
// PRE: Minimum stored in vitalHistory array; minimum of 1
// POST: Erases the information stored and replaces the cells with zeros
//---------------------------------------------------------------------------------------------
void DeleteHistoryRecord(long recordIndex, long rawTime, oneVitalHistoryRecord vitalHistory[], short recordLocation, long hmr)
{
	//"Wiping" data and leaving nothing (0's)
	vitalHistory[recordLocation].nSecs = 0;
	vitalHistory[recordLocation].newTemp = 0;
	vitalHistory[recordLocation].beats = 0;

	//Visually confirms the erasing of the data
	cout << "Deleted Record: " << recordLocation << endl;
	printAllVitalRecords(mP, vitalHistory, hmr);

} // DeleteHistoryRecord()


//---------------------\
// printAllVitalRecords \
//---------------------------------------------------------------------------------------------
// Prints history (last set of) hmr vital signs (to medPing output)
// PRE: Requires an array of structs containing at minimum one vital sign.
// POST: Prints the 5 most recent records in the array.
//---------------------------------------------------------------------------------------------
void printAllVitalRecords(medPing& mP, const oneVitalHistoryRecord vitalHistory[ ], long hmr)
{
	if (hmr > 0)
	{
		mP.CELL_PrintF("\n---- Records (so far) ----");
		for(long i=0; i < hmr; i++)
		{
			mP.CELL_PrintF("\nRECORD [%02d]\n", i);
			mP.CELL_PrintF(" Raw time: \t\t%d\n", vitalHistory[i].nSecs);
			mP.CELL_PrintF(" Temperature (F): \t%4.1f\n",   vitalHistory[i].beats);
			mP.CELL_PrintF(" Pulse Rate (bpm):  \t%4.1f\n", vitalHistory[i].newTemp);
		} // for

		mP.CELL_PrintF("\n---- END History ----\n\n");

	} // if
	else 
		mP.CELL_PrintF("\n------NO History-------\n\n");
	
} // printAllVitalRecords()


