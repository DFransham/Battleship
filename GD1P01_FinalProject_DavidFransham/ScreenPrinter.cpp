/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : ScreenPrinter.cpp
Description : Implementation file for collected functions relating to printing to screen
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/
#include "ScreenPrinter.h"

//Prints interim screens between players in two player mode.  _user is to get required dimensions of screen
void PrintPlayerPauseScreen(CParticipant& _user, int _playerNum)
{
	ClearScreen();

	int iWidth = GetConsoleDimensions();
	int iHeight = GetConsoleDimensions(false);
	int iXstart = _user.s_iMiddleX - 23;
	int iYstart = _user.s_iMenuY;
	
	//print border around text
	PrintBorder(iXstart - 2, iYstart - 2, 47, 26);

	//print the word "PLAYER"
	SetRgb(EColour::COLOUR_YELLOW_ON_BLACK);
	PrintBetweenArray(playerPrint, iXstart, iYstart);
	
	iXstart += 10;
	iYstart = _user.s_iOutputY + 3;

	//print the word "ONE" or "TWO"
	if (_playerNum==0)
	{
		SetRgb(EColour::COLOUR_BLUE_ON_BLACK);
		PrintBetweenArray(onePrint, iXstart, iYstart);
	}
	else
	{
		SetRgb(EColour::COLOUR_MAGENTA_ON_BLACK);
		PrintBetweenArray(twoPrint, iXstart, iYstart);
	}

	//print border on screen edge
	PrintBorder(0, 0, iWidth, iHeight);
}

//prints border of + and | and - in black on grey font for aesthetic purposes
void PrintBorder(int _iXStart, int _iYStart, int _iWidth, int _iHeight)
{
	SetRgb(EColour::COLOUR_BLACK_ON_GRAY);

	//print corners first
	GoToXY(_iXStart, _iYStart);
	std::cout << "+";
	GoToXY(_iXStart + _iWidth - 1, _iYStart);
	std::cout << "+";
	GoToXY(_iXStart, _iYStart + _iHeight - 1);
	std::cout << "+";
	GoToXY(_iXStart + _iWidth - 1, _iYStart + _iHeight - 1);
	std::cout << "+";

	//print horizontals
	for (int i = _iXStart + 1; i < _iXStart + _iWidth - 1; ++i)
	{
		GoToXY(i, _iYStart);
		std::cout << "-";
		GoToXY(i, _iYStart + _iHeight - 1);
		std::cout << "-";
	}
	//print verticals
	for (int j = _iYStart + 1; j < _iYStart + _iHeight - 1; ++j)
	{
		GoToXY(_iXStart, j);
		std::cout << "|";
		GoToXY(_iXStart + _iWidth - 1, j);
		std::cout << "|";
	}
}

//References array to print the funky words on player turn screen
void PrintBetweenArray(const int (&_arrToPrint)[10][20], int _iXstart, int _iYstart)
{
	GoToXY(_iXstart, _iYstart++);

	bool bPrint = false;
	int iLen = 0;
	
	for (int i = 0; i < 10; i++)
	{
		for (int z = 0; z < 20; z++)
		{
			//array is 20 long, but only non-zero values relevant so length is calculated from non-zeros
			if (_arrToPrint[i][z] > 0)
			{
				iLen++;
			}
		}

		bPrint = false;

		//loop through each row of the array
		for (int j = 0; j < iLen; j++)
		{
			//print relevant character as many times as that value in the array
			for (int k = 0; k < _arrToPrint[i][j]; k++)
			{
				if (bPrint)
				{
					std::cout << "X";
				}
				else
				{
					std::cout << " ";
				}
			}
			//toggle bool to change from printing to non-printing and vice versa
			bPrint = !bPrint;
		}
		//go to next row, reset length to begin loop on fresh row
		GoToXY(_iXstart, _iYstart++);
		iLen = 0;
	}
}

//resize and move the console window on windows machines
void ResizeConsoleWindow(int _iWidth, int _iHeight)
{
	// Get console window handle
	HWND wh = GetConsoleWindow();

	// Move window to required position
	MoveWindow(wh, 50, 50, _iWidth, _iHeight, TRUE);
}

//sets font size on windows console application.  Default is 16.
void SetFontSize(int _iSize)
{
	static CONSOLE_FONT_INFOEX  fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, 0, &fontex);
	fontex.FontWeight = 400;
	fontex.dwFontSize.X = _iSize;
	fontex.dwFontSize.Y = _iSize;
	SetCurrentConsoleFontEx(hOut, NULL, &fontex);
}

//put cursor at a particular location on screen before printing
void GoToXY(int _iX, int _iY)
{
	COORD point;
	point.X = _iX;
	point.Y = _iY;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
	
	return;
}

//return current position of cursor - thanks to StackOverflow
COORD GetCursorPos()
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi = { };
	BOOL ok = GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);
	return csbi.dwCursorPosition;
}

//to set the console text to a particular colour
void SetRgb(EColour colour)
{
	switch (colour)
	{
	case EColour::COLOUR_WHITE_ON_BLACK: // White on Black.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case EColour::COLOUR_RED_ON_BLACK: // Red on Black.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		break;
	case EColour::COLOUR_GREEN_ON_BLACK: // Green on Black.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	case EColour::COLOUR_YELLOW_ON_BLACK: // Yellow on Black.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case EColour::COLOUR_BLUE_ON_BLACK: // Blue on Black.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		break;
	case EColour::COLOUR_MAGENTA_ON_BLACK: // Magenta on Black.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	case EColour::COLOUR_CYAN_ON_BLACK: // Cyan on Black.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case EColour::COLOUR_BLACK_ON_GRAY: // Black on Gray.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_INTENSITY);
		break;
	case EColour::COLOUR_BLACK_ON_WHITE: // Black on White.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		break;
	case EColour::COLOUR_RED_ON_WHITE: // Red on White.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
		break;
	case EColour::COLOUR_GREEN_ON_WHITE: // Green on White.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN);
		break;
	case EColour::COLOUR_YELLOW_ON_WHITE: // Yellow on White.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case EColour::COLOUR_BLUE_ON_WHITE: // Blue on White.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);
		break;
	case EColour::COLOUR_MAGENTA_ON_WHITE: // Magenta on White.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	case EColour::COLOUR_CYAN_ON_WHITE: // Cyan on White.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case EColour::COLOUR_WHITE_ON_WHITE: // White on White.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	default: // White on Black.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	}
	return;
}

//Clears console screen. Copied from Lecture Slides in GD1P01_22071.
void ClearScreen()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}

//function to get screen width info from console buffer.  Default input returns width, false input returns height
int GetConsoleDimensions(bool _bWidth)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	
	if (_bWidth)
	{
		return columns;
	}
	else
	{
		return rows - 1;
	}
}

//clears the screen, prints the borders and titles.
void PrintBattleshipUI(CParticipant& _user, CParticipant& _opponent)
{
	ClearScreen();
	int width = GetConsoleDimensions();
	int height = GetConsoleDimensions(false);

	//print game border
	PrintBorder(0, 0, width, height);
	SetRgb(EColour::COLOUR_RED_ON_BLACK);
	string title = "BATTLESHIP GAME";
	GoToXY((width / 2) - (static_cast<int>(title.length()) / 2), 2);
	std::cout << title;

	//print player info maps
	title = "YOUR SHIPS";
	PrintBorder(_user.s_iLeftMapX, _user.s_iTopMapY, 27, 14);
	PrintCoordinateTitles(_user.s_iLeftMapX, _user.s_iTopMapY, title);
	
	title = "OPPONENT'S SHIPS";
	PrintBorder(_user.s_iRightMapX, _user.s_iTopMapY, 27, 14);
	PrintCoordinateTitles(_user.s_iRightMapX, _user.s_iTopMapY, title);

	//print debug maps if debug mode active
	PrintDebugInfo(_user, _opponent);
	return;
}

//prints A-J and 1-10 for map coordinate titles, and title of map
void PrintCoordinateTitles(int _iXStart, int _iYStart, string _sTitle)
{
	int width = 27;
	int height = 14;
	GoToXY(_iXStart + (width / 2) - ((static_cast<int>(_sTitle.length())) / 2), _iYStart - 1);

	//print map title
	SetRgb(EColour::COLOUR_MAGENTA_ON_BLACK);
	std::cout << _sTitle;
	
	//print A-J
	SetRgb(EColour::COLOUR_GREEN_ON_BLACK);
	char toPrint = 'A';
	int toAdd = 0;
	do
	{
		toPrint = 'A';
		GoToXY(_iXStart + 3, _iYStart + 1 + toAdd);
		for (int k = 0; k < 10; k++)
		{
			std::cout << " " << toPrint;
			toPrint++;
		}
		toAdd += (height - 3);
	} while (toAdd < 20);

	//print 1-10
	toPrint = '1';
	for (int i = 0; i < 10; i++)
	{
		if (toPrint == ':')
		{
			GoToXY(_iXStart + 1, _iYStart + 2 + i);
			std::cout << "10";
		}
		else
		{
			GoToXY(_iXStart + 2, _iYStart + 2 + i);
			std::cout << toPrint;
		}
		GoToXY(_iXStart + width - 3, _iYStart + 2 + i);
		if (toPrint == ':')
		{
			std::cout << "10";
		}
		else
		{
			std::cout << toPrint;
		}
		toPrint++;
	}
}

//Prints list of which ships are still operational and which have been sunk
void PrintShipStatus(int _iXStart, int _iYStart, const CParticipant& _user)
{
	int OperationalCount = 0;
	int SunkCount = 0;

	ESHIPTYPE OperationalArray[5];
	ESHIPTYPE SunkArray[5];
	
	for (int i = 0; i < 5; i++)
	{
		ESHIPTYPE tempShip = _user.GetShipClass(i);
		
		if (_user.IsShipAlive(i))
		{
			OperationalArray[OperationalCount] = tempShip;
			OperationalCount++;
		}
		else
		{
			SunkArray[SunkCount] = tempShip;
			SunkCount++;
		}
	}

	string toPrint = "";

	if (OperationalCount > 0)
	{
		GoToXY(_iXStart, _iYStart);
		SetRgb(EColour::COLOUR_WHITE_ON_BLACK);
		std::cout << "~~OPERATIONAL~~";

		for (int j = 0; j < OperationalCount; j++)
		{
			GoToXY(_iXStart, _iYStart + 2 + j);
			switch (OperationalArray[j])
			{
			case ESHIPTYPE::AIRCRAFTCARRIER:
				toPrint = "A: Aircraft Carrier";
				SetRgb(EColour::COLOUR_RED_ON_BLACK);
				break;
			case ESHIPTYPE::BATTLESHIP:
				toPrint = "B: Battleship";
				SetRgb(EColour::COLOUR_BLUE_ON_BLACK);
				break;
			case ESHIPTYPE::DESTROYER:
				toPrint = "D: Destroyer";
				SetRgb(EColour::COLOUR_MAGENTA_ON_BLACK);
				break;
			case ESHIPTYPE::PATROLBOAT:
				toPrint = "P: Patrol Boat";
				SetRgb(EColour::COLOUR_CYAN_ON_BLACK);
				break;
			case ESHIPTYPE::SUBMARINE:
				toPrint = "S: Submarine";
				SetRgb(EColour::COLOUR_YELLOW_ON_BLACK);
			default:
				break;
			}
			std::cout << toPrint;
		}
		_iYStart += OperationalCount + 3;
	}

	if (SunkCount > 0)
	{
		GoToXY(_iXStart, _iYStart);
		SetRgb(EColour::COLOUR_WHITE_ON_BLACK);
		std::cout << "~~SUNK~~";

		for (int k = 0; k < SunkCount; k++)
		{
			GoToXY(_iXStart, _iYStart + 2 + k);
			switch (SunkArray[k])
			{
			case ESHIPTYPE::AIRCRAFTCARRIER:
				toPrint = "A: Aircraft Carrier";
				SetRgb(EColour::COLOUR_RED_ON_BLACK);
				break;
			case ESHIPTYPE::BATTLESHIP:
				toPrint = "B: Battleship";
				SetRgb(EColour::COLOUR_BLUE_ON_BLACK);
				break;
			case ESHIPTYPE::DESTROYER:
				toPrint = "D: Destroyer";
				SetRgb(EColour::COLOUR_MAGENTA_ON_BLACK);
				break;
			case ESHIPTYPE::PATROLBOAT:
				toPrint = "P: Patrol Boat";
				SetRgb(EColour::COLOUR_CYAN_ON_BLACK);
				break;
			case ESHIPTYPE::SUBMARINE:
				toPrint = "S: Submarine";
				SetRgb(EColour::COLOUR_YELLOW_ON_BLACK);
			default:
				break;
			}
			std::cout << toPrint;
		}
	}
}

//prints information on map regarding hits, misses, ship locations.  Input bool is to show ships on own map, hide them on opponent map
void PrintMapPoints(int _iXStart, int _iYStart, CParticipant& _user, bool _bOwnMap)
{
	int temp = 0;
	bool shipIsHere = false;
	ESHIPTYPE shipClassPresent;
	EColour desired = EColour::COLOUR_GREEN_ON_BLACK;
	string toPrint = "~";

	EMAPSTATE currentState = EMAPSTATE::INVALID_EMAPSTATE;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//check for character to print to display ships on own map
			shipIsHere = _user.CheckForShip(i, j);
			if (_bOwnMap && shipIsHere)
			{
				temp = _user.GetShipIndex(i, j);
				shipClassPresent = _user.GetShipClass(temp);
				switch (shipClassPresent)
				{
				case ESHIPTYPE::AIRCRAFTCARRIER:
					toPrint = "A";
					desired = EColour::COLOUR_RED_ON_BLACK;
					break;
				case ESHIPTYPE::BATTLESHIP:
					toPrint = "B";
					desired = EColour::COLOUR_BLUE_ON_BLACK;
					break;
				case ESHIPTYPE::DESTROYER:
					toPrint = "D";
					desired = EColour::COLOUR_MAGENTA_ON_BLACK;
					break;
				case ESHIPTYPE::PATROLBOAT:
					toPrint = "P";
					desired = EColour::COLOUR_CYAN_ON_BLACK;
					break;
				case ESHIPTYPE::SUBMARINE:
					toPrint = "S";
					desired = EColour::COLOUR_YELLOW_ON_BLACK;
				default:
					break;
				}
			}
			else {} //do nothing
			
			//checks for hits and misses to display on all map.
			currentState = _user.GetMapState(i, j);
			switch (currentState)
			{
			case EMAPSTATE::INVALID_EMAPSTATE:
				std::cout << "Something Unexpected happened drawing maps";
				break;
			case EMAPSTATE::UNEXPLORED:
				if (_bOwnMap && shipIsHere)
				{
					//Do nothing - don't want to replace the ship indication calculated above
				}
				else
				{
					if (((i % 2 == 1) && (j % 2 == 1)) || ((i % 2 == 0) && (j % 2 == 0)))
					{
						desired = EColour::COLOUR_BLACK_ON_GRAY;
					}
					else
					{
						desired = EColour::COLOUR_GREEN_ON_BLACK;
					}
					toPrint = " ";
				}
				break;
			case EMAPSTATE::EXPLORED_MISS:
				desired = EColour::COLOUR_WHITE_ON_BLACK;
				toPrint = "X";
				break;
			case EMAPSTATE::EXPLORED_HIT:
				desired = EColour::COLOUR_RED_ON_BLACK;
				toPrint = "X";
				break;
			case EMAPSTATE::MAX_EMAPSTATE:
				std::cout << "Something Unexpected happened - 2";
				break;
			default:
				std::cout << "Something Unexpected happened - 3";
				break;
			}

			//prints the character at the current location based on specs identified above
			GoToXY(_iXStart + 2 * i, _iYStart + j);
			SetRgb(desired);
			std::cout << toPrint;
		}
	}
}

//prints menu to middle of screen based on current game state
void MenuPrinter(int _iX, int _iY, int _iSize, string _menuToPrint[])
{
	SetRgb(EColour::COLOUR_BLACK_ON_GRAY);

	int width = 20;
	int height = 10;

	int borderX = _iX - width/2-1;
	int borderY = _iY - 2;
	
	PrintBorder(borderX, borderY, width, height);

	SetRgb(EColour::COLOUR_WHITE_ON_BLACK);
	for (int i = borderY + 1; i < borderY + height - 1; i++)
	{
		GoToXY(borderX + 1, i);
		for (int j = borderX + 1; j < borderX + width - 1; j++)
		{
			std::cout << " ";
		}
	}
	SetRgb(EColour::COLOUR_BLUE_ON_BLACK);

	for (int i = 0; i < _iSize; i++)
	{
		int offset = (static_cast<int>(_menuToPrint[i].length()) / 2) + 3;
		GoToXY(_iX - offset, _iY + i);
		std::cout << i + 1 << ")  " << _menuToPrint[i];
	}
}

//prints " " over the output section of the screen as a method of clearing previous input without having to clear whole screen
void ClearOutputSection(CParticipant& _user)
{
	int startX = _user.s_iMiddleX - 30;
	int startY = _user.s_iOutputY;

	GoToXY(startX, startY);
	SetRgb(EColour::COLOUR_WHITE_ON_BLACK);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			std::cout << " ";
		}
		GoToXY(startX, startY + i);
	}

	startX = startX + 15;
	startY = startY + 6;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			std::cout << " ";
		}
		GoToXY(startX, startY + i);
	}
}

//prints last input and output values to keep user updated on game state
void PrintInOut(CParticipant& _user, CParticipant& _opponent, bool _bGameStarted)
{
	if (_user.GetHumanStatus() || !_bGameStarted)
	{
		ClearOutputSection(_user);

		SetRgb(EColour::COLOUR_CYAN_ON_BLACK);
		string toPrint = _user.GetLastInput();
		GoToXY(_user.s_iMiddleX - 10, _user.s_iOutputY);
		std::cout << toPrint;

		SetRgb(EColour::COLOUR_MAGENTA_ON_BLACK);
		toPrint = _user.GetLastOutput();
		int len = static_cast<int>(toPrint.length());
		GoToXY(_user.s_iMiddleX - (len / 2), _user.s_iOutputY + 1);
		std::cout << toPrint;
	}
	GoToXY(_user.s_iMiddleX-10, _user.s_iOutputY + 2);
}

//prints various game state messages to screen on human player turn or before game has started
void PrintMessage(CParticipant& _user, EMessageType _message, EColour _desiredColour, bool _bGameStarted)
{
	if (_user.GetHumanStatus() || !_bGameStarted)
	{
		int _iX = _user.s_iMiddleX;
		int _iY = _user.s_iOutputY;
		int _iSize = 1;
		int i = 0;
		string placeholder = "hold this";
		string* _menuToPrint = &placeholder;			// TF: Pointer Initialised

		switch (_message)
		{
		case EMessageType::INSTRUCTIONS:
			_iSize = 17;
			_menuToPrint = new string[_iSize];			// TF: Dynamic Memory
			_menuToPrint[i++] = "INSTRUCTIONS";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "The goal: sink your opponent's fleet before they sink yours";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "To play, simply follow the instructions on the screen";
			_menuToPrint[i++] = "Enter the menu option number to choose an option";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "When prompted, Enter Coordinates in the format: LetterNumber";
			_menuToPrint[i++] = "For example A1, or J10";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "To toggle DEBUG mode at any time, type DEBUG instead of a menu option";
			_menuToPrint[i++] = "This will allow you to see the enemy boards - but don't cheat!";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Sound can be turned off/on if desired";
			_menuToPrint[i++] = "Type \"SOUND\" instead of entering coordinates when targetting your opponent";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Press ENTER to continue";
			break;

		case EMessageType::CREDITS:
			_iSize = 4;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Game created by David Fransham";
			_menuToPrint[i++] = "Sounds for free from MixKit.com";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Press ENTER to continue.";
			break;

		case EMessageType::GOODBYE:
			_iSize = 4;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "You chose to exit the game";
			_menuToPrint[i++] = "Thanks for playing!";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Are you sure you want to exit?  N to return to game, Y to exit";
			_desiredColour = EColour::COLOUR_RED_ON_BLACK;
			break;

		case EMessageType::ALREADY_PLACED:
			_iSize = 5;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "This ship has already been placed.";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Please choose a different ship to place.";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Press ENTER to continue";
			_user.UpdateOutput(_menuToPrint[2]);
			break;

		case EMessageType::ENTER_COORDINATES:
			_iSize = 3;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Enter coordinates to place Top Left of ship.";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Letter first, then number";
			_user.UpdateOutput(_menuToPrint[0]);
			break;

		case EMessageType::HORIZONT_OR_VERT:
			_iSize = 4;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Would you like to place it horizontally or vertically?";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "0) for Horizontal";
			_menuToPrint[i++] = "1) for Vertical";
			_user.UpdateOutput(_menuToPrint[0]);
			break;

		case EMessageType::REPOSITION:
			_iSize = 5;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "If you aren't happy with your board, you can start over";
			_menuToPrint[i++] = "This will clear all your ships and return to previous step";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "1) to continue and begin game,";
			_menuToPrint[i++] = "2) to reposition your fleet";
			_user.UpdateOutput(_menuToPrint[0]);
			break;

		case EMessageType::SINGLE_PLAYER:
			_iSize = 3;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "You have chosen Single Player mode.";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Press ENTER to continue";
			break;

		case EMessageType::TWO_PLAYER:
			_iSize = 3;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "You have chosen Two Player mode.";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Press ENTER to continue";
			break;

		case EMessageType::DIFFICULTY_EASY:
			_iSize = 3;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "You have chosen Easy difficulty.";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Press ENTER to continue";
			break;

		case EMessageType::DIFFICULTY_MEDIUM:
			_iSize = 8;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "You have chosen Medium difficulty";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Unfortunately this mode is still in development.";
			_menuToPrint[i++] = "Medium difficulty will be available in a future update of this game";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Your game mode has been returned to Easy mode";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Press ENTER to continue";
			break;

		case EMessageType::DIFFICULTY_HARD:
			_iSize = 8;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "You have chosen Hard difficulty";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Unfortunately this mode is still in development.";
			_menuToPrint[i++] = "Hard difficulty will be available in a future update of this game";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Your game mode has been returned to Easy mode";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Press ENTER to continue";
			break;

		case EMessageType::YOU_HIT_OPPONENT:
			_iSize = 3;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Great stuff! Your shot HIT an opponent's ship!";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "ENTER to continue.";
			break;

		case EMessageType::YOU_MISSED_OPPONENT:
			_iSize = 4;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Your shot fell harmlessly into the ocean.";
			_menuToPrint[i++] = "Better luck next time!";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "ENTER to continue.";
			break;

		case EMessageType::OPPONENT_HIT_YOU:
			_iSize = 3;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Oh dear!  Your opponent HIT one of your ships.";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Enter coordinates to fire back when ready.";
			break;

		case EMessageType::OPPONENT_MISSED_YOU:
			_iSize = 4;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Your opponent's shot fell harmlessly into the ocean.";
			_menuToPrint[i++] = "Lucky for you!";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Enter coordinates to fire back when ready.";
			break;

		case EMessageType::YOU_SUNK_SHIP:
			_iSize = 4;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Fantastic!";
			_menuToPrint[i++] = "Your shot HIT and SUNK an enemy ship!";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "ENTER to continue.";
			_desiredColour = EColour::COLOUR_RED_ON_BLACK;
			break;

		case EMessageType::OPPONENT_SUNK_SHIP:
			_iSize = 4;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Uh-oh!";
			_menuToPrint[i++] = "Your opponent's shot HIT and SUNK one of your ships!";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Enter coordinates to fire back when ready.";
			_desiredColour = EColour::COLOUR_RED_ON_BLACK;
			break;

		case EMessageType::YOU_WON:
			_iSize = 7;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "WINNER!";
			_menuToPrint[i++] = "Congratulations, you won the game.";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Would you like to play again?";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "1) to start again";
			_menuToPrint[i++] = "2) to quit";
			break;

		case EMessageType::YOU_LOST:
			_iSize = 8;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Unforunately, all of your ships were sunk";
			_menuToPrint[i++] = "This means you lost the game.";
			_menuToPrint[i++] = "Better luck next time!";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Would you like to play again?";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "1) to start again";
			_menuToPrint[i++] = "2) to quit";
			break;

		case EMessageType::DONT_CHEAT:
			_iSize = 7;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "DEBUG mode is only here for the purpose of marking the assignment";
			_menuToPrint[i++] = "Use of this mode in an actual game would be considered cheating.";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Your opponent will be notified that you used DEBUG mode during your turn.";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Type DEBUG again to continue to DEBUG mode";
			_menuToPrint[i++] = "Any other input to continue as normal";
			_desiredColour = EColour::COLOUR_RED_ON_BLACK;
			break;

		case EMessageType::OPPONENT_USED_DEBUG:
			_iSize = 5;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Your opponent used DEBUG mode during their turn";
			_menuToPrint[i++] = "This would generally be considered cheating, and they know where your ships are now";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Type EXIT if you wish to quit the game now.";
			_menuToPrint[i++] = "Any other input to continue playing";
			_desiredColour = EColour::COLOUR_RED_ON_BLACK;
			break;

		case EMessageType::AUTO_OR_MANUAL:
			_iSize = 6;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Would you like to manually place your ships?";
			_menuToPrint[i++] = "Or do you want them randomly generated for you?";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Options:";
			_menuToPrint[i++] = "1) For manual entry";
			_menuToPrint[i++] = "2) For random generation";
			break;

		case EMessageType::HIDE_SCREEN:
			_iSize = 5;
			_menuToPrint = new string[_iSize];
			_menuToPrint[i++] = "Your turn is about to begin";
			_menuToPrint[i++] = "Make sure your opponent cannot see your screen";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = " ";
			_menuToPrint[i++] = "Press ENTER when you are ready to continue";
			break;

		default:
			break;
		}

		int width = GetConsoleDimensions();
		int height = GetConsoleDimensions(false);

		SetRgb(EColour::COLOUR_WHITE_ON_BLACK);
		for (int i = _user.s_iOutputY; i < height - 4; i++)
		{
			GoToXY(1, i);
			for (int j = 0; j < width - 2; j++)
			{
				std::cout << " ";
			}
		}

		SetRgb(_desiredColour);

		for (int i = 0; i < _iSize; i++)
		{
			int offset = (static_cast<int>(_menuToPrint[i].length()) / 2);
			GoToXY(_iX - offset, _iY + i);
			std::cout << _menuToPrint[i];
		}
		int y = GetCursorPos().Y;
		GoToXY(_user.s_iMiddleX - 10, y + 1);

		delete[] _menuToPrint;
		_menuToPrint = nullptr;
	}
}

//prints player info maps if debug mode is active
void PrintDebugInfo(CParticipant& _user, CParticipant& _opponent, bool _bGameStarted)
{
	//restricts printing debug info on computer turn or before game is started unless specified
	if (_user.GetHumanStatus() || !_bGameStarted)
	{
		string title = " ";
		if (_user.s_bDebugOn)
		{
			title = "OPPONENT'S (DEBUG)";
			PrintBorder(_user.s_iLeftMapX, _user.s_iBottomMapY, 27, 14);
			PrintCoordinateTitles(_user.s_iLeftMapX, _user.s_iBottomMapY, title);

			title = "YOURS (DEBUG)";
			PrintBorder(_user.s_iRightMapX, _user.s_iBottomMapY, 27, 14);
			PrintCoordinateTitles(_user.s_iRightMapX, _user.s_iBottomMapY, title);

			PrintShipStatus(_user.s_iLeftShipsX, _user.s_iBottomMapY + 2, _opponent);
			PrintShipStatus(_user.s_iRightShipsX, _user.s_iBottomMapY + 2, _user);
			PrintMapPoints(_user.s_iLeftMapX + 4, _user.s_iBottomMapY + 2, _opponent, true);
			PrintMapPoints(_user.s_iRightMapX + 4, _user.s_iBottomMapY + 2, _user, false);

			GoToXY(_user.s_iMiddleX - 10, _user.s_iOutputY + 3);
		}
	}
}