/**********************************************************************
Filename:				ass3.cpp
Version:				1.0
Author:					Seong-yeop Jeong
Student No:				040885882
Course Name/Number:		Numerical computing - CST8233
Lab Sect:				304
Assignment #:			2
Assignment name:		Martian Lander
Due Date:				December 2 2018
Submission Date:		December 2 2018
Professor:				Andrew Tyler
Purpose:				this application is to solve ODEs in real time through
						landing flight simulator
*********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <vector>
using namespace std;

const int vmax = 46;
const double g = 3.7; // gravity
const double c = 0.13; // atmospheric_drag
const double a = 8.3; // acceleration


void simulator(bool isPressed, char isKey, float pressedBt, DWORD &previousTime, int &totalTime,
	double &velocity, double &burnReserved, double &height, double &speedDescPrev,
	double &lastDelta, int &bounces, bool &running, bool &endGame);
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
	bool running = true;
	bool isPressed = false;
	bool endGame = false;
	char isKey = 'a';
	float pressedBt = 0.0f;
	int totalTime = 0;
	double velocity = 0;
	double burnReserved = 100;
	double height = 5;
	double speedDescPrev = 0;
	double lastDelta = 0;
	int bounces = 0;
	DWORD previousTime = GetTickCount(); // program starts

	cout << "************************** STARTING DESCENT" <<
		"**************************" << endl;
	cout << ": BURN = 0.000; BURN RESERVE = 100.000" << endl;
	while (running)
	{
		if (_kbhit())
		{
			char ch = _getch();
			switch (ch)
			{
				// reduce button
			case 'e':
				isPressed = true;
				isKey = 'e';
				if (pressedBt > 0)
					pressedBt--;
				break;
				// increase button
			case 'w': // isKey = true
				isPressed = true;
				isKey = 'w';
				pressedBt++;
				break;
			case 'q':
				cout << "End program";
				running = false;
				isKey = 'q';
				break;
			}
		}
		if (!endGame) {
			simulator(isPressed, isKey, pressedBt, previousTime,
				totalTime, velocity, burnReserved, height,
				speedDescPrev, lastDelta, bounces, running, endGame);
		}
		else {
			char playerName[128];
			cout << "What is your name? ";
			cin >> playerName;
			cout << "Saving your name... Please wait...";
			Sleep(2000);
			system("cls");
			cout << "*********** Results ***********" << endl;
			cout << "Player name: " << playerName << endl;
			cout << "Bounces: " << bounces << endl;
			cout << "Total time: " << totalTime / 1000 / 60 % 60 << " minutes "
				<< totalTime / 1000 % 60 << " seconds " << totalTime % 1000 << " milliseconds " << endl;
			cout << endl;
			cout << "Replay? (y/n)";
			char ch = _getch();
			switch (ch)
			{
				// reduce button
			case 'y':
				endGame = false;
				pressedBt = 0.0f;
				velocity = 0;
				burnReserved = 100;
				height = 1000;
				speedDescPrev = 0;
				lastDelta = 0;
				bounces = 0;
				previousTime = GetTickCount();
				totalTime = 0;
				break;
			case 'n':
				cout << endl;
				running = false;
				break;
			default:
				break;
			}
		}
	}

}
/*********************************************************************
Function Name: simulator
Purpose: it is for simulating and calculating
Function In parameters: bool isPressed, char isKey, float pressedBt,
DWORD &previousTime, int &totalTime, double &velocity,
double &burnReserved, double &height,
double &speedDescPrev, double &lastDelta,
int &bounces, bool &running, bool &endGame
Function Out parameters: void
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
void simulator(bool isPressed, char isKey, float pressedBt, DWORD &previousTime,
	int &totalTime, double &velocity, double &burnReserved, double &height,
	double &speedDescPrev, double &lastDelta, int &bounces, bool &running, bool &endGame)
{
	// initial values for time
	int solutionTime = 100; // 5 seconds
							// variables to calculate the data
	double fin_velocity = 0; //

							 // times
	DWORD currentTime = GetTickCount();
	double deltaTime = currentTime - previousTime;
	totalTime += deltaTime;
	double minutes = totalTime / 1000 / 60 % 60;
	double seconds = totalTime / 1000 % 60; // working well
	double milliseconds = totalTime % 1000; // working well
	DWORD interval = 50;	// 10th of a second
							// calc
	double delta = g - c * (velocity + a * pow((velocity / vmax), 3)) - pressedBt;
	speedDescPrev = velocity + (delta) * (deltaTime / 1000); // (deltaTime / 1000)
	lastDelta = g - c * (speedDescPrev + a * pow((speedDescPrev / vmax), 3)) - pressedBt;
	velocity = speedDescPrev + (delta + lastDelta) / 2 * (deltaTime / 1000);
	height -= velocity * deltaTime / 1000;
	if (height <= 0)
	{
		if (velocity > 1)
		{
			velocity = -velocity;
			bounces++;
		}
	}
	if (height <= 1 && height >= 0)
	{
		if (velocity <= 1 && velocity >= 0)
		{
			system("cls");
			cout << "Game over..." << endl;
			Sleep(2000);
			endGame = true;
		}
	}

	system("cls");
	if (!isPressed)
	{
		cout << "************************** STARTING DESCENT " <<
			"**************************" << endl;
		cout << ": BURN = 0.000; BURN RESERVE = 100.000" << endl;
	}
	if (isKey == 'w') // if it is true, key 'W'
	{
		cout << "W was pressed - increase burn: ";
		cout << "BURN = " << setprecision(3) << fixed;
		cout << pressedBt << "; ";
		cout << "BURN RESERVE = " << endl;
		cout << burnReserved << endl;
	}
	else if (isKey == 'e')// Key 'e' reduce
	{
		cout << "E was pressed - reduce burn: ";
		cout << "BURN = " << setprecision(3) << fixed;
		cout << pressedBt << "; ";
		cout << "BURN RESERVE = " << endl;
		cout << burnReserved << endl;
	}
	if (pressedBt > 0)
	{
		burnReserved = burnReserved - (pressedBt * deltaTime / 1000);
	}
	else {
		burnReserved = burnReserved;
	}
	cout << setprecision(0) << fixed;
	cout << "MINUTE = " << minutes << "; ";
	cout << "SECOND = " << seconds << "; ";// working well
	cout << "MILLISECOND = " << milliseconds << endl;
	cout << "SPEED OF DESCENT = " << setprecision(3) << fixed << velocity << "m/s" << endl;
	cout << "HEIGHT ABOVE MARTIAN SURFACE = " << setprecision(3) << fixed << height << "metres" << endl;
	cout << "NUMBER OF BOUNCES = " << bounces << endl;
	previousTime = currentTime;

}