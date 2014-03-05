// ============ insert this code inside main() ==============#include "stdafx.h"
#include <iostream>
#include <cassert>

using namespace std; int main(){	short j, oddSum;	j = 1;	oddSum = 0;	while ()   // INV: oddSum == 1 + 3 + ... + (j-2)  &&  1 <= j <= 101		//									 &&  j%2 == 1	{		// do NOT change or move this assertion		assert((1 <= j && j <= 101) && (j % 2 == 1));		// if assert doesn't work  :(		// then uncomment the following:		/*		   if (! ((1<=j && j<=101) && (j%2 == 1))  )		   {		   cout << "ASSERT FAILED!" << endl;		   system("PAUSE");		   exit(-1);		   }		   */	}	// ASSERT:  (you write this one HERE as a COMMENT, *not* a runtime assert() )	cout << "\n\n oddSum is: " << oddSum << endl;}