// ============ insert this code inside main() ==============

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <climits>

using namespace std;

int main()
{

	const char BEEP = char(7);

	short i, sum;
	short N = 0;

	i = 0;
	sum = 0;

	cout << "Please enter a value for N: ";
	cin >> N;


	while (i <= N)       // INV: sum == 0 + 1 + 2 + ... + (i-1)  &&  1 <= i <= N+1
	{
		sum = sum + i;
		i++;

	} // end while

	// you may NOT change this assertion
	assert(sum == N / 2.0*(N + 1) && i == N + 1);

	// if assert doesn't work  :(

	if (! (sum == N/2.0*(N+1)  && i == N+1)  )
	{
	cout << "ASSERT FAILED!" << endl;
	system("PAUSE");
	exit(-1);
	}

	cout << "\nSum is: " << sum << endl << endl;

	system("PAUSE");
}
