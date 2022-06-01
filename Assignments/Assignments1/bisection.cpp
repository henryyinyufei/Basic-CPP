#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
	// Declare and initialized all constants.
	const int MAXTRYCOUNTS = 3;
	const double MINCOEF = -50.0;
	const double MAXCOEF = 50.0;
	const double MININTERVAL = -60.0;
	const double MAXINTERVAL = 60;
	const int MINNUMROWS = 1;
	const int MAXNUMROWS = 25;
	const double MINSHIFT = 0.0;
	const double MAXSHIFT = 20.0;
	const double EPS = 0.000001;
	const int MAXITERATION = 50;



	// Declare and initialized all variables.
	double coef0 = 0.0;
	double coef1 = 0.0;
	double coef2 = 0.0;
	double coef3 = 0.0;
	double coef4 = 0.0;
	int tryCount = 0;
	double intervalEndMin = 0.0;
	double intervalEndMax = 0.0;
	int numRows = 0;
	double intervalShift = 0.0;
	double intervalLen = 0.0;
	double midpoint = 0.0;
	double SolEndMin = 0.0;
	double SolEndMax = 0.0;
	double SolMid = 0.0;
	double intervalEnd1 = 0.0;
	double intervalEnd2 = 0.0;
	int Iteration = 1;
	double SolEnd1 = 0.0;
	double SolEnd2 = 0.0;
	
	string FileName;
	fstream MyStream;

	// prompt coef4.
	cout << "Please enter the value of the coefficient for the order 4 term\n";
	cout << "(-50.0 <= coefficient <= 50.0): ";


	// Validate input coef4.
	while (!(cin >> coef4))
	{
		cout << "ERROR: Unappropriated input." << endl;
		cout << "Program terminated" << endl;
		return 1;
	}

	while (tryCount < MAXTRYCOUNTS)
	{
		if (coef4 < MINCOEF || coef4 > MAXCOEF)
		{
			cout << "ERROR: The value of the order 4 term is out of range" << endl;
			cout << "Please re-enter the value of the coefficient for the order 4 term\n";
			cout << "(-50.0 <= coefficient <= 50.0): ";
			cin >> coef4;
			tryCount++;
		}
		else
		{
			break;
		}
	}

	// Validate the final input
	if ((coef4 < MINCOEF || coef4 > MAXCOEF) && tryCount >= MAXTRYCOUNTS)
	{
		cout << "ERROR: The value of the order 4 coefficient is out of range" << endl;
		cout << "Maximum number of tries entering data exceeded. Program terminating.";
		return 2;
	}

	// prompt coef3.
	cout << "Please enter the value of the coefficient for the order 3 term\n";
	cout << "(-50.0 <= coefficient <= 50.0): ";

	// Validate input coef3.
	while (!(cin >> coef3))
	{
		cout << "ERROR: Unappropriated input." << endl;
		cout << "Program terminated" << endl;
		return 3;
	}

	tryCount = 0;
	while (tryCount < MAXTRYCOUNTS)
	{
		if (coef3 < MINCOEF || coef3 > MAXCOEF)
		{
			cout << "ERROR: The value of the order 3 term is out of range" << endl;
			cout << "Please re-enter the value of the coefficient for the order 3 term\n";
			cout << "(-50.0 <= coefficient <= 50.0): ";
			cin >> coef3;
			tryCount++;
		}
		else
		{
			break;
		}
	}

	// Validate the final input
	if ((coef3 < MINCOEF || coef3 > MAXCOEF) && tryCount >= MAXTRYCOUNTS)
	{
		cout << "ERROR: The value of the order 3 coefficient is out of range" << endl;
		cout << "Maximum number of tries entering data exceeded. Program terminating.";
		return 4;
	}

	// prompt coef2.
	cout << "Please enter the value of the coefficient for the order 2 term\n";
	cout << "(-50.0 <= coefficient <= 50.0): ";


	// Validate input coef2.
	while (!(cin >> coef2))
	{
		cout << "ERROR: Unappropriated input." << endl;
		cout << "Program terminated" << endl;
		return 5;
	}

	tryCount = 0;
	while (tryCount < MAXTRYCOUNTS)
	{
		if (coef2 < MINCOEF || coef2 > MAXCOEF)
		{
			cout << "ERROR: The value of the order 2 term is out of range" << endl;
			cout << "Please re-enter the value of the coefficient for the order 2 term\n";
			cout << "(-50.0 <= coefficient <= 50.0): ";
			cin >> coef2;
			tryCount++;
		}
		else
		{
			break;
		}
	}

	// Validate the final input
	if ((coef2 < MINCOEF || coef2 > MAXCOEF) && tryCount >= MAXTRYCOUNTS)
	{
		cout << "ERROR: The value of the order 2 coefficient is out of range" << endl;
		cout << "Maximum number of tries entering data exceeded. Program terminating.";
		return 6;
	}

	// prompt coef1.
	cout << "Please enter the value of the coefficient for the order 1 term\n";
	cout << "(-50.0 <= coefficient <= 50.0): ";

	// Validate input coef1.
	while (!(cin >> coef1))
	{
		cout << "ERROR: Unappropriated input." << endl;
		cout << "Program terminated" << endl;
		return 7;
	}

	tryCount = 0;
	while (tryCount < MAXTRYCOUNTS)
	{
		if (coef1 < MINCOEF || coef1 > MAXCOEF)
		{
			cout << "ERROR: The value of the order 1 term is out of range" << endl;
			cout << "Please re-enter the value of the coefficient for the order 1 term\n";
			cout << "(-50.0 <= coefficient <= 50.0): ";
			cin >> coef1;
			tryCount++;
		}
		else
		{
			break;
		}
	}

	// Validate the final input
	if ((coef1 < MINCOEF || coef1 > MAXCOEF) && tryCount >= MAXTRYCOUNTS)
	{
		cout << "ERROR: The value of the order 1 coefficient is out of range" << endl;
		cout << "Maximum number of tries entering data exceeded. Program terminating.";
		return 8;
	}
	
	// prompt coef0.
	cout << "Please enter the value of the coefficient for the order 0 term\n";
	cout << "(-50.0 <= coefficient <= 50.0): ";


	// Validate input coef0.
	while (!(cin >> coef0))
	{
		cout << "ERROR: Unappropriated input." << endl;
		cout << "Program terminated" << endl;
		return 9;
	}

	tryCount = 0;
	while (tryCount < MAXTRYCOUNTS)
	{
		if (coef0 < MINCOEF || coef0 > MAXCOEF)
		{
			cout << "ERROR: The value of the order 0 term is out of range" << endl;
			cout << "Please re-enter the value of the coefficient for the order 0 term\n";
			cout << "(-50.0 <= coefficient <= 50.0): ";
			cin >> coef0;
			tryCount++;
		}
		else
		{
			break;
		}
	}

	// Validate the final input
	if ((coef0 < MINCOEF || coef0 > MAXCOEF) && tryCount >= MAXTRYCOUNTS)
	{
		cout << "ERROR: The value of the order 0 coefficient is out of range" << endl;
		cout << "Maximum number of tries entering data exceeded. Program terminating.";
		return 10;
	}

	// Prompt intervalEndMin.
	cout << "Please enter the minimum X value in the initial range" << endl;
	cout << "(-60.0 <= minimum X value in the initial range <= 60.0): ";


	// Validate input intervalEndMin.
	while (!(cin >> intervalEndMin))
	{
		cout << "ERROR: Unappropriated input." << endl;
		cout << "Program terminated" << endl;
		return 11;
	}

	tryCount = 0;
	while (tryCount < MAXTRYCOUNTS)
	{
		if (intervalEndMin < MININTERVAL || intervalEndMin > MAXINTERVAL)
		{
			cout << "ERROR: The minimum X value in the initial range is out of range" << endl;
			cout << "Please re-enter the minimum X value in the initial range" << endl;
			cout << "(-60.0 <= minimum X value in the initial range <= 60.0): ";
			cin >> intervalEndMin;
			tryCount++;
		}
		else
		{
			break;
		}
	}

	// Validate the final input
	if ((intervalEndMin < MININTERVAL || intervalEndMin > MAXINTERVAL) && tryCount >= MAXTRYCOUNTS)
	{
		cout << "ERROR: The minimum X value in the initial range is out of range" << endl;
		cout << "Maximum number of tries entering data exceeded. Program terminating.";
		return 12;
	}

	// Prompt intervalEndMax.
	cout << "Please enter the maximum X value in the initial range" << endl;
	cout << "(-60.0 <= maximum X value in the initial range <= 60.0): ";

	// Validate input intervalEndMax.
	while (!(cin >> intervalEndMax))
	{
		cout << "ERROR: Unappropriated input." << endl;
		cout << "Program terminated" << endl;
		return 13;
	}

	tryCount = 0;
	while (tryCount < MAXTRYCOUNTS)
	{
		if (intervalEndMax < intervalEndMin)
		{
			cout << "ERROR: The maximum X value should larger than the minimum X value " << intervalEndMin << endl;
			cout << "Please re-enter the maximum X value in the initial range" << endl;
			cout << "(" << intervalEndMin << " <= maximum X value in the initial range <= 60.0): ";
			cin >> intervalEndMax;
			tryCount++;
		}

		else if (intervalEndMax < MININTERVAL || intervalEndMax > MAXINTERVAL)
		{
			cout << "ERROR: The maximum X value in the initial range is out of range" << endl;
			cout << "Please re-enter the maximum X value in the initial range" << endl;
			cout << "(-60.0 <= maximum X value in the initial range <= 60.0): ";
			cin >> intervalEndMax;
			tryCount++;
		}
		else
		{
			break;
		}
	}

	// Validate the final input
	if ((intervalEndMax < intervalEndMin) && tryCount >= MAXTRYCOUNTS)
	{
		cout << "ERROR: The maximum X value should larger than the minimum X value " << intervalEndMin << endl;
		cout << "Maximum number of tries entering data exceeded. Program terminating.";
		return 14;
	}
	if ((intervalEndMax < MININTERVAL || intervalEndMax > MAXINTERVAL) && tryCount >= MAXTRYCOUNTS)
	{
		cout << "ERROR: The maximum X value in the initial range is out of range" << endl;
		cout << "Maximum number of tries entering data exceeded. Program terminating.";
		return 15;
	}

	// Prompt numRows.
	cout << "Please enter the number of rows in the table" << endl;
	cout << "(1 <= number of rows in the table <= 25): ";


	// Validate input numRows. 
	while (!(cin >> numRows))
	{
		cout << "ERROR: Unappropriated input." << endl;
		cout << "Program terminated" << endl;
		return 16;
	}

	tryCount = 0;
	while (tryCount < MAXTRYCOUNTS)
	{
		if (numRows < MINNUMROWS || numRows > MAXNUMROWS)
		{
			cout << "ERROR: The number of rows in the table is out of range" << endl;
			cout << "Please re-enter the number of rows in the table" << endl;
			cout << "(1 <= number of rows in the table <= 25): ";
			cin >> numRows;
			tryCount++;
		}
		else
		{
			break;
		}
	}

	// Validate the final input
	if ((numRows < MINNUMROWS || numRows > MAXNUMROWS) && tryCount >= MAXTRYCOUNTS)
	{
		cout << "ERROR: The number of rows in the table is out of range" << endl;
		cout << "Maximum number of tries entering data exceeded. Program terminating.";
		return 17;
	}

	// Prompt intervalShift
	cout << "Please enter the shift in the starting interval between rows" << endl;
	cout << "(0.0 <= shift in the starting interval between rows <= 20.0): ";


	// Validate intervalShift
	while (!(cin >> intervalShift))
	{
		cout << "ERROR: Unappropriated input." << endl;
		cout << "Program terminated" << endl;
		return 18;
	}

	tryCount = 0;
	while (tryCount < MAXTRYCOUNTS)
	{
		if (intervalShift < MINSHIFT || intervalShift > MAXSHIFT)
		{
			cout << "ERROR: The shift in the starting interval between rows is out of range" << endl;
			cout << "Please re-enter the shift in the starting interval between rows" << endl;
			cout << "(0.0 <= shift in the starting interval between rows <= 20.0): ";
			cin >> intervalShift;
			tryCount++;
		}
		else
		{
			break;
		}
	}

	// Validate the final input
	if ((intervalShift < MINSHIFT || intervalShift > MAXSHIFT) && tryCount >= MAXTRYCOUNTS)
	{
		cout << "ERROR: The shift in the starting interval between rows is out of range" << endl;
		cout << "Maximum number of tries entering data exceeded. Program terminating.";
		return 19;
	}

	// Prompt FileName
	cout << "Enter the name of the output file ";
	cin >> FileName;

	// Open Stream and check if its fail.
	MyStream.open(FileName, ios::out);
	if (MyStream.fail())
	{
		cout << "unable to open output file" << endl;
		return 20;
	}



	// Table
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(6);

	cout << setw(13) << "intEndMin" << setw(13) << "intEndMax" << setw(13) << "midpoint";
	cout << setw(13) << "root" << setw(5) << "N" << endl;


	for (int rowIndex = 0; rowIndex < numRows; rowIndex++)
	{
		MyStream << setw(16) << "Interval Start";
		MyStream << setw(16) << "P(x) Start";
		MyStream << setw(16) << "Interval End";
		MyStream << setw(16) << "P(x) End";
		MyStream << setw(16) << "Midpoint";
		MyStream << setw(16) << "P(Midpoint)";
		MyStream << "Iteration#" << endl;
		
		Iteration = 1;
		// Check to see if either of the endpoints are roots
		SolEndMin = ((((coef4*intervalEndMin + coef3)*intervalEndMin + coef2)*intervalEndMin + coef1)*intervalEndMin + coef0);
		SolEndMax = ((((coef4*intervalEndMax + coef3)*intervalEndMax + coef2)*intervalEndMax + coef1)*intervalEndMax + coef0);
	

		// Find the length of the interval
		intervalLen = intervalEndMax - intervalEndMin;

		// Find the midpoint of the interval
		midpoint = intervalEndMin + intervalLen / 2.0;
		SolMid = ((((coef4*midpoint + coef3)*midpoint + coef2)*midpoint + coef1)*midpoint + coef0);

		// Print the interval end values and the midpoint to the first row of the table on the screen
		cout << setw(13) << intervalEndMin;
		cout << setw(13) << intervalEndMax;
		cout << setw(13) << midpoint;

		// endpoints are roots
		if (SolEndMin == 0)
		{
			cout << setw(13) << intervalEndMin;
			cout << setw(5) << noshowpoint << setprecision(0) << Iteration << endl;
			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
			cout.precision(6);
			MyStream << setw(16) << fixed << setprecision(6) << intervalEndMin;
			MyStream << setw(16) << scientific << SolEndMin;
			MyStream << setw(16) << fixed << intervalEndMax;
			MyStream << setw(16) << scientific << SolEndMax;
			MyStream << setw(16) << fixed << midpoint;
			MyStream << setw(16) << scientific << SolMid;
			MyStream << setw(10) << fixed << noshowpoint << Iteration << endl;
		}
		else if (SolEndMax == 0)
		{
			cout << setw(13) << intervalEndMax;
			cout << setw(5) << noshowpoint << setprecision(0) << Iteration << endl;
			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
			cout.precision(6);
			MyStream << setw(16) << fixed << setprecision(6) << intervalEndMin;
			MyStream << setw(16) << scientific << SolEndMin;
			MyStream << setw(16) << fixed << intervalEndMax;
			MyStream << setw(16) << scientific << SolEndMax;
			MyStream << setw(16) << fixed << midpoint;
			MyStream << setw(16) << scientific << SolMid;
			MyStream << setw(10) << fixed << noshowpoint << Iteration << endl;
		}

		// Bisection method
		else
		{
			intervalEnd1 = intervalEndMin;
			intervalEnd2 = intervalEndMax;
			while (Iteration <= MAXITERATION)
			{
				intervalLen = intervalEnd2 - intervalEnd1;
				midpoint = intervalEnd1 + intervalLen / 2.0;
				SolEnd1 = ((((coef4*intervalEnd1 + coef3)*intervalEnd1 + coef2)*intervalEnd1 + coef1)*intervalEnd1 + coef0);
				SolEnd2 = ((((coef4*intervalEnd2 + coef3)*intervalEnd2 + coef2)*intervalEnd2 + coef1)*intervalEnd2 + coef0);
				SolMid = ((((coef4*midpoint + coef3)*midpoint + coef2)*midpoint + coef1)*midpoint + coef0);
				
				MyStream << setw(16) << fixed << setprecision(6) << intervalEnd1;
				MyStream << setw(16) << scientific << SolEnd1;
				MyStream << setw(16) << fixed << intervalEnd2;
				MyStream << setw(16) << scientific << SolEnd2;
				MyStream << setw(16) << fixed << midpoint;
				MyStream << setw(16) << scientific << SolMid;
				MyStream << setw(10) << fixed << noshowpoint << Iteration << endl;


				// find the root
				if (abs(SolMid) < EPS)
				{
					break;
				}
				else if ((intervalEnd2 - intervalEnd1) < EPS)
				{
					break;
				}
				// the same sign at the two ends of the interval then there is no root in the interval
				else if (SolEnd1 * SolEnd2 > 0)
				{
					cout << "-------------ERROR:  no roots in the interval" << endl;
					MyStream << "ERROR: no roots in the interval";
					break;
				}
				// One half of the interval
				else if (SolEnd1 * SolMid < 0)
				{
					intervalEnd2 = midpoint;
				}
				else
				{
					intervalEnd1 = midpoint;
				}	
				Iteration++;
			}


			// Print Roots and Number of Interations.
			if (SolEnd1 * SolEnd2 < 0)
			{
				if (Iteration > MAXITERATION)
				{
					cout << "-------------ERROR: did not converge" << endl;
					MyStream << "ERROR: did not converge" << endl;
				}
				else
				{
					cout << setw(13) << midpoint;
					cout << setw(5) << noshowpoint << setprecision(0) << Iteration << endl;
					cout.setf(ios::fixed);
					cout.setf(ios::showpoint);
					cout.precision(6);
				}
			}

		}
		
		// Shift interval
		intervalEndMin += intervalShift;
		intervalEndMax += intervalShift;
		MyStream << endl << endl << endl << endl;
	}
	
	MyStream.close();
	return 0;
}
