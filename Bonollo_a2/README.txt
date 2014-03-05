Destiny Bonollo -- Program 2
Date last modified: 02/28/2014

Summary: This program takes the existing medPing product and builds onto it; the 
	 purpose is to produce a quick mock-up of how one might save the history 
	 of a patient's vital signs in an array of structs.
 

Files:
- README.txt: preliminary information (the document you are reading now)
- History_medPing_Main.cpp: the source code, edited in Visual Studio
- main.cpp: the main function 
- medPing.cpp: Develops constructors and information from chip
- medPing.h: API (Application Programming Interface) for medPing
- mp_InputOutput.cpp: to get data FROM cellphone and send messages TO cellphone
- mp_InputOutput.h: header file for mp_InputOutput.cpp
- mp_normalVitalSigns.h: header file of values representing "normal" values for the entire population,
 not those of a specific individual.
- mpPatient.cpp: setting and returning patient's information and vitals
- mpPatient.h: header file holding the class mpPatient
- randomBell.cpp: sets seed of random number generator
- randomBell.h: implementation of independent randomization
 
- talk2chip.cpp: Retrieving information from the chip
- talk2chip.h: header file with constants for talk2chip.cpp

Status: The program is working but is not where it should be... Couldn't figure out a few bugs.
	Difficulties with output, specifically with the "records (so far)" the pulse persists on
	being incorrect.  