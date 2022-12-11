/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : ScreenPrinter.h
Description : Collection of functions relating to printing output to console
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#pragma once
#include <Windows.h>
#include <iostream>
#include "Ship.h"
#include "Menu.h"
#include "Participant.h"

using std::string;

enum class EColour
{
	COLOUR_WHITE_ON_BLACK = 0, // White on Black.
	COLOUR_RED_ON_BLACK = 1, // Red on Black.
	COLOUR_GREEN_ON_BLACK = 2, // Green on Black.
	COLOUR_YELLOW_ON_BLACK = 3, // Yellow on Black.
	COLOUR_BLUE_ON_BLACK = 4, // Blue on Black.
	COLOUR_MAGENTA_ON_BLACK = 5, // Magenta on Black.
	COLOUR_CYAN_ON_BLACK = 6, // Cyan on Black.
	COLOUR_BLACK_ON_GRAY = 7, // Black on Gray.
	COLOUR_BLACK_ON_WHITE = 8, // Black on White.
	COLOUR_RED_ON_WHITE = 9, // Red on White.
	COLOUR_GREEN_ON_WHITE = 10, // Green on White.
	COLOUR_YELLOW_ON_WHITE = 11, // Yellow on White.
	COLOUR_BLUE_ON_WHITE = 12, // Blue on White.
	COLOUR_MAGENTA_ON_WHITE = 13,// Magenta on White.
	COLOUR_CYAN_ON_WHITE = 14, // Cyan on White.
	COLOUR_WHITE_ON_WHITE = 15 // White on White.
};

enum class EMessageType
{
	INSTRUCTIONS,
	CREDITS,
	GOODBYE,
	ALREADY_PLACED,
	ENTER_COORDINATES,
	HORIZONT_OR_VERT,
	REPOSITION,
	SINGLE_PLAYER,
	TWO_PLAYER,
	DIFFICULTY_EASY,
	DIFFICULTY_MEDIUM,
	DIFFICULTY_HARD,
	YOU_HIT_OPPONENT,
	YOU_MISSED_OPPONENT,
	OPPONENT_HIT_YOU,
	OPPONENT_MISSED_YOU,
	YOU_SUNK_SHIP,
	OPPONENT_SUNK_SHIP,
	YOU_WON,
	YOU_LOST,
	DONT_CHEAT,
	OPPONENT_USED_DEBUG,
	NO_MESSAGE,
	AUTO_OR_MANUAL,
	HIDE_SCREEN
};

//array for printing "PLAYER" when changing turns
const int playerPrint[10][20] =
{
	{ 1,5,2,2,6,4,2,2,2,2,1,6,1,5,1 },
	{ 1,6,1,2,5,6,1,2,2,2,1,6,1,6 },
	{ 1,2,2,2,1,2,5,2,2,2,1,2,2,2,1,2,5,2,2,2 },
	{ 1,2,2,2,1,2,5,2,2,2,1,2,2,2,1,2,5,2,2,2 },
	{ 1,6,1,2,5,6,1,6,1,4,3,6 }, 
	{ 1,5,2,2,5,6,2,4,2,4,3,5,1 },
	{ 1,2,5,2,5,2,2,2,3,2,3,2,5,4,2 },
	{ 1,2,5,2,5,2,2,2,3,2,3,2,5,2,1,2,1 },
	{ 1,2,5,6,1,2,2,2,3,2,3,6,1,2,1,2,1 },
	{ 1,2,5,6,1,2,2,2,3,2,3,6,1,2,2,2 }
};

//array for printing "ONE" when changing turns
const int onePrint[10][20] =
{
	{ 2,4,2,2,3,2,1,6 },
	{ 1,6,1,2,3,2,1,6 },
	{ 1,2,2,2,1,3,2,2,1,2,4 },
	{ 1,2,2,2,1,3,2,2,1,2,4 },
	{ 1,2,2,2,1,4,1,2,1,4,2 },
	{ 1,2,2,2,1,2,1,4,1,4,2 },
	{ 1,2,2,2,1,2,2,3,1,2,4 },
	{ 1,2,2,2,1,2,2,3,1,2,4 },
	{ 1,6,1,2,3,2,1,6 },
	{ 2,4,2,2,3,2,1,6 }
};

//array for printing "TWO" when changing turns
const int twoPrint[10][20] =
{
	{ 1,6,1,1,5,1,2,4,1 },
	{ 1,6,1,2,3,2,1,6 },
	{ 3,2,3,2,3,2,1,2,2,2 },
	{ 3,2,3,2,1,1,1,2,1,2,2,2 },
	{ 3,2,3,2,1,1,1,2,1,2,2,2 },
	{ 3,2,3,7,1,2,2,2 },
	{ 3,2,3,7,1,2,2,2 },
	{ 3,2,3,3,1,3,1,2,2,2 },
	{ 3,2,3,2,3,2,1,6 },
	{ 3,2,3,1,5,1,2,4,1 }
};

void ResizeConsoleWindow(int _iWidth, int _iHeight);
void SetFontSize(int _iSize);
void GoToXY(int _iX, int _iY);
void SetRgb(EColour colour);

int GetConsoleDimensions(bool _bWidth = true);
COORD GetCursorPos();

void ClearScreen();
void ClearOutputSection(CParticipant& _user);

void PrintPlayerPauseScreen(CParticipant& _user, int _iPlayerNum);
void PrintBorder(int _iXstart, int _iYstart, int _iWidth, int _iHeight);
void PrintBetweenArray(const int (&_arrToPrint)[10][20], int _iXstart, int _iYstart);
void PrintBattleshipUI(CParticipant& _user, CParticipant& _opponent);
void PrintCoordinateTitles(int _iXStart, int _iYStart, string _sTitle);
void PrintShipStatus(int _iXStart, int _iYStart, const CParticipant& _user);
void PrintMapPoints(int _iXStart, int _iYStart, CParticipant& _user, bool _bOwnMap = false);
void PrintInOut(CParticipant& _user, CParticipant& _opponent, bool _bgameStarted = true);
void PrintDebugInfo(CParticipant& _user, CParticipant& _opponent, bool _bGameStarted = true);
void MenuPrinter(int _iX, int _iY, int _iSize, string _menuToPrint[]);
void PrintMessage(CParticipant& _user, EMessageType _message, 
	EColour _desiredColour = EColour::COLOUR_GREEN_ON_BLACK, bool _bGameStarted = true);