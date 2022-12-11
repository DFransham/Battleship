/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Main.cpp
Description : Main file to operate Battleship game for GD1PO1 final project
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#include <iostream>
#include <Windows.h>
#include <string>

#include "GameControl.h"
#include "Map.h"
#include "Participant.h"
#include "Ship.h"
#include "ScreenPrinter.h"
#include "InputGetterErrorHandler.h"

using std::string;

int CParticipant::s_iMiddleX;
int CParticipant::s_iRightMapX;
int CParticipant::s_iRightShipsX;
bool CParticipant::s_bDebugOn;

int main()
{
	//seed pseudorandom number generator to increase appearance of randomness
	srand(static_cast<unsigned int>(time(0)));

	//boolean to control game loop to enable restarting
	bool playAgain = true;			// TF: Variable Type
			
	while (playAgain)				// TF: Iteration Structure
	{
		//create map objects in order to create game control object
		CMap MapOne = CMap::CMap();	// TF: Class Instance
		CMap MapTwo = CMap::CMap();
		CGameControl MyGame = CGameControl::CGameControl(MapOne, MapTwo);

		//set font size to default for the purposes of restarting the game with consistent resolution
		SetFontSize(16);
		ResizeConsoleWindow(MyGame.GetScreenWidth(), MyGame.GetScreenHeight());
		SetFontSize(18);

		//coin toss to see which player is starting first
		bool firstPlayerFirst = GetRandomNumber(1, 0);
		if (firstPlayerFirst)		// TF: Conditional Statement
		{
			playAgain = MyGame.GameSetup(MyGame.m_PlayerOne, MyGame.m_PlayerTwo);
		}
		else
		{
			playAgain = MyGame.GameSetup(MyGame.m_PlayerTwo, MyGame.m_PlayerOne);
		}
	}	
	return 0;
}