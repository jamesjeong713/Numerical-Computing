/**********************************************************************
Filename:				ass2.cpp
Version:				1.0
Author:					Seong-yeop Jeong
Student No:				040885882
Course Name/Number:		Numerical computing - CST8233
Lab Sect:				304
Assignment #:			2
Assignment name:		Linear Regression Fit to Data
Due Date:				November 11 2018
Submission Date:		November 11 2018
Professor:				Andrew Tyler
Purpose:				this application is to fit data of linear and power law, 
						by using linear regression least suqres method. 
*********************************************************************/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

void openFile(vector <vector<double>>&data, bool isPowerFit);
void fit(vector<vector<double>>&data, bool isFit);
void square(double& slope, double& intercept, vector <vector<double>> xy);
void interpolate(vector <vector<double>> xy, bool isFit);
void linear(double& slope, double& intercept, vector <vector<double>> xy);
/*********************************************************************
Function Name: main
Purpose: main function to execute and select the methods
Function In parameters: void
Function Out parameters: 0 for successful execution
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
int main()
{
	char choice;
	while (1)
	{
		// vector is used for fitting the data whatever you use the text file.
		vector<vector<double>> data;
		cout << setw(40) << "LEAST_SQUARES LINEAR REGRESSION" << endl;
		cout << "MENU" << endl;
		cout << " 1. Linear Fit" << endl;
		cout << " 2. Power Law Fit" << endl;
		cout << " 3. Quit" << endl << endl;
		cin >> choice;

		switch (choice)
		{
		case '1':
			openFile(data, true);
			fit(data, true);
			break;
		case '2':
			openFile(data, false);
			fit(data, false);
			break;
		case '3':
			return 0;
		default:
			break;
		}
	}
	return 0;
}
/*********************************************************************
Function Name: openFile
Purpose: open file, and to put the values into element with two dimentinal vector
Function In parameters: vector<vector<double>>&data, bool isPowerFit
Function Out parameters: void
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
void openFile(vector<vector<double>>&data, bool isPowerFit)
{
	ifstream read;
	string fileName;
	double tempVal;

	//read.open("co2.txt");
	do
	{
		cout << "Please enter the name of the file to open: ";
		cin >> fileName;
		read.open(fileName);

		if (!read.is_open())
		{
			cout << "Please check your file name" << endl;
			cout << endl;
		}
		else 
			break;
	} while (1);

	int counter = 0;
	vector<double> row;
	while (!read.eof())
	{
		read >> tempVal;
		
		counter++;
		if (isPowerFit)
			row.push_back(tempVal);
		else
			row.push_back(log(tempVal));			
		
		if (counter == 2)
		{
			data.push_back(row);
			counter = 0;
			row.clear();
		}
	}
	cout << "There are " << data.size() << " records." << endl;
}
/*********************************************************************
Function Name: fit
Purpose: it is menu to fit a linear square and power law
Function In parameters: vector<vector<double>>&data, bool isPowerFit
Function Out parameters: void
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
void fit(vector<vector<double>>&data, bool isFit)
{
	double slope;
	double intercept;
	square(slope, intercept, data);
	// linear fit(true) or poqwer(false)
	if (!isFit) // power fit
	{
		intercept = exp(intercept); // assign base-e exponential funtion of x to intercept
		cout << "y= " << fixed << setprecision(2) << intercept << "x^" << slope << endl;
	}
	if (isFit) // linear fit
	{
		cout << "y= " << fixed << setprecision(2) << slope << "*x +" << intercept << endl;
	}
	
	char choice;

	while (1)
	{
		cout << "MENU" << endl;
		cout << " 1. Interpolate / Extrapolate" << endl;
		cout << " 2. Main Menu" << endl;
		cin >> choice;

		switch (choice)
		{
		case '1':
			// if it is false, interpolate for power fit
			// if it is true, interpolate for linear
			interpolate(data, isFit); 
			break;
		case '2':
			return;
		}
	}
}
/*********************************************************************
Function Name: interpolate
Purpose: to prompt user input based on the methods (linear / power fit)
Function In parameters: vector <vector<double>> xy, bool isFit
Function Out parameters: void
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
void interpolate(vector <vector<double>> xy, bool isFit)
{ 
	double slope;
	double intercept;
	// inputItp is int variable to get userinput for interpolate/extrapolate 
	int inputItp;
	if (!isFit)
	{
		square(slope, intercept, xy);
		cout << "Please enter the year to interpolate/extrapolate to: ";
		cin >> inputItp;
		cout << "The power law interpolated/extrapolated CO2 level in the year "
			<< inputItp << " is "; 
		cout << (exp(intercept) * pow(inputItp - 1960, slope) + 316.5) << endl;
	}
	if (isFit)
	{
		linear(slope, intercept, xy);
		cout << "Please enter the year to interpolate/extrapolate to: ";
		cin >> inputItp;
		cout << "The linear interpolated/extrapolated CO2 level in the year "
			<< inputItp << " is "; 
		cout << slope * inputItp + intercept << endl;
	}
}
/*********************************************************************
Function Name: square
Purpose: it is calculation for power law fit
Function In parameters: double& slope, double& intercept, vector <vector<double>> xy
Function Out parameters: void
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
void square(double& slope, double& intercept, vector <vector<double>> xy)
{
	double x = 0.0;
	double x2 = 0.0;
	double y = 0.0;
	double t_xy = 0.0;
	slope = 0.0;
	intercept = 0.0;

	for (int i = 0; i < xy.size(); i++)
	{
		x += xy[i][0];
		y += xy[i][1];
		x2 += (xy[i][0])*(xy[i][0]);
		t_xy += (xy[i][0])*(xy[i][1]);
	}
	int n = (int)xy.size();
	slope = ((n * t_xy) - (x * y)) / ((n*x2) - (x*x));
	intercept = ((x2 * y) - (x * t_xy)) / ((n*x2) - (x*x));
}
/*********************************************************************
Function Name: linear
Purpose: it is calculation for linear fit
Function In parameters: double& slope, double& intercept, vector <vector<double>> xy
Function Out parameters: void
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
void linear(double& slope, double& intercept, vector <vector<double>> xy)
{
	double x = 0.0;
	double x2 = 0.0;
	double y = 0.0;
	double t_xy = 0.0;
	slope = 0.0;
	intercept = 0.0;

	for (int i = 0; i < xy.size(); i++)
	{
		x += xy[i][0] + 1960;
		y += xy[i][1] + 316.5;
		x2 += (xy[i][0] + 1960)*(xy[i][0] + 1960);
		t_xy += (xy[i][0] + 1960)*(xy[i][1] + 316.5);
	}
	int n = (int)xy.size();
	slope = ((n * t_xy) - (x * y)) / ((n*x2) - (x*x));
	intercept = ((x2 * y) - (x * t_xy)) / ((n*x2) - (x*x));
}