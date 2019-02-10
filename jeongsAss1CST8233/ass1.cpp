/**********************************************************************
Filename: acc1.c
Version: 1.0
Author: Seong-yeop Jeong
Student No: 040885882
Course Name/Number: C++ Programming CST8219
Lab Sect: 302
Assignment #: 1
Assignment name: Catenary Function
Due Date: October 14 2018
Submission Date: October 12 2018
Professor: Andrew Tyler
Purpose: It is to investigate the series approximation to
the Catenary function to code a real-time simulation.
*********************************************************************/

#include <iostream>
#include <iomanip>

/* instead of using namespace std, you should use the using part of them. 
it is because of avoiding conflict of the name in the future which might be big problem. */
using std::cout;
using std::cin;
using std::endl;
using std::fixed;
using std::scientific;
using std::setprecision;
using std::setw;

void evaluate();

/*********************************************************************
Function Name: main
Purpose: main function to execute and display the Catenary series by using maclaurin series 
Function In parameters: void
Function Out parameters: 0 for successful execution
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
int main(void)
{
	char choice;
	bool isMenu = true;

	while (isMenu)
	{
		cout << "**********************************" << endl;
		cout << "\tCatenary Series" << endl;
		cout << "1. Evaluate the function" << endl;
		cout << "2. Quit" << endl;
		cout << "**********************************" << endl;
		
		cin >> choice;
		
		switch (choice) {
		case '1':
			evaluate();
			break;
		case '2':
			isMenu = false;
			cout << "End of the program" << endl << endl << "Have a good day!" << endl;
			break;
		default:
			cout << "Please enter valid input" << endl;
		}
		cout << endl;
	}
	return 0;
}

/********************************************************************
Function name: evaluate
Purpose: evaluate the series based on power, terms and low / high range.
In parameters: none
Out parameters: none
Version: 1.0
Author: Seongyeop Jeong
**********************************************************************/
void evaluate()
{
	int x;
	float lowRange, highRange;
	float scale;
	// First user input for power
	cout << "\tEVALUATING THE CATENARY SERIES APPROXIMATION" << endl << endl;
	while (1)
	{
		cin.clear();
		cin.ignore();

		cout << "Please enter the highest power of x in the catenary series (0, 2, 4, 6, 8, or 10): ";
		cin >> x;
		if (x % 2 == 0)
			break;
	}
	// Second user input for low range
	cout << endl << "\tCHOOSE THE RANGE OF EVALUATION - low x to high x" << endl;
	while (1)
	{
		cin.clear();
		cin.ignore();

		cout << "Please enter low x - in the range -10.0 to 0.0: ";
		cin >> lowRange;
		if (lowRange >= -10.0f && lowRange <= 0.0f)
			break;
	}
	// Third user input for high range
	while (1)
	{
		cin.clear();
		cin.ignore();

		cout << "Please enter high x - in the range 0.0 to +10.0: ";
		cin >> highRange;
		if (highRange >= 0.0f && highRange <= 10.0f)
			break;
	}
	// Fourth user input for scale factor
	while (1)
	{
		cin.clear();
		cin.ignore();
		cout << endl << "Please enter the scale factor the range 0.0 to +10.0: ";
		cin >> scale;
		if (scale >= 0.0f && highRange <= 10.0f)
			break;
	}
	/* Table title */
	cout << fixed << "CATENARY SERIES TO x^" << x << "from x = " << lowRange << " to x = ";
	cout << fixed << highRange << endl << endl;
	/* Categories */
	cout << setw(5) << " x " << setw(15) << "Series" << setw(15) << "Exact" << setw(20) << "Exact % Error" << setw(17) << "Trunc.% Error" << endl;
	// declaration for each terms, range, calculations
	double term = (highRange - lowRange) / 10;
	double range = lowRange;
	double termTwlv, termTen, termEight, termSix, termFour, termTwo;
	double trunc;
	double series;
	double exactValue;
	double exactError;
	double truncError;
	// loop for terms
	for (int i = 0; i <= 10; i++)
	{
		double test = ((range * range) / ((scale) * 2));
		// make one more method to use the trunc error
		trunc = 0;
		termTwlv = 0;
		termTen = 0;
		termEight = 0;
		termSix = 0;
		termFour = 0;
		termTwo = 0;
		// values
		series = 0;
		exactValue = 0;
		exactError = 0;
		truncError = 0;
		// Calculate them for each terms
		switch (x+2)
		{
		case 12:
			termTwlv = ((range * range * range * range * range * range * range * range * range * range * range * range) / ((scale * scale * scale * scale * scale * scale * scale * scale * scale * scale * scale) * 479001600));
		case 10:
			termTen = ((range * range * range * range * range * range * range * range * range * range) / ((scale * scale * scale * scale * scale * scale * scale * scale * scale) * 3628800));
		case 8:
			termEight = ((range * range * range * range * range * range * range * range) / ((scale * scale * scale * scale * scale * scale * scale) * 40320));
		case 6:
			termSix = ((range * range * range * range * range * range) / ((scale * scale * scale * scale * scale) * 720));
		case 4:
			termFour = ((range * range * range * range) / ((scale * scale * scale) * 24));
		case 2:
			termTwo = ((range * range) / ((scale) * 2));
		case 0:
			series += scale;
			break;
		default:
			break;
		}
		// depending on the terms, it has to be calculated. 
		if (x == 10)
		{
			trunc = termTwlv;
			series += termTen + termEight + termSix + termFour + termTwo;
		}
		if (x == 8)
		{
			trunc = termTen;
			series += termEight + termSix + termFour + termTwo;
		}
		if (x == 6)
		{
			trunc = termEight;
			series += termSix + termFour + termTwo;
		}
		if (x == 4)
		{
			trunc = termSix;
			series += termFour + termTwo;
		}
		if (x == 2)
		{
			trunc = termFour;
		}
		if (x == 0)
		{
			trunc = termTwo;
		}
		exactValue = scale * cosh(range / scale);
		exactError = 100 * (exactValue - series) / exactValue;
		truncError = 100 * trunc / series;
		// Result
		if (range >= 0)
			cout << '+';
		cout << setprecision(3) << scientific << range; // range section
		cout << setw(15) << setprecision(5) << series; // series values
		cout << setw(15) << exactValue; // exact values
		cout << setw(15) << exactError << setw(17) << truncError << endl;
		range += term;
	}
}