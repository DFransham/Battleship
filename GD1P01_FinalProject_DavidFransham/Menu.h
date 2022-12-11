/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Menu.h
Description : Header file for Menu class
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/
#pragma once

#ifndef __MENU_H__
#define __MENU_H__

#include <iostream>
#include "ScreenPrinter.h"
#include "Participant.h"

using std::string;

enum class ECurrentMenu
{
	MAIN,
	GAME_MODE,
	DIFFICULTY,
	SHIP_SELECTION,
	READY_TO_PLAY,
	BLANK_MENU
};

enum class EMainMenuOptions
{
	PLAY = 1,
	INSTRUCTIONS = 2,
	CREDITS = 3,
	GAME_MODE = 4,
	DIFFICULTY = 5,
	M_ONE_PLAYER = 11,
	M_TWO_PLAYER = 12,
	D_EASY = 21,
	D_MEDIUM = 22,
	D_HARD = 23,
	RETURN = 30,
	AIRCRAFT_CARRIER = 40,
	BATTLESHIP = 41,
	DESTROYER = 42,
	SUBMARINE = 43,
	PATROL_BOAT = 44,
	REPOSITION_SHIP = 50,
	LETS_GO = 51,
	BLANK_OPTION = 90,
	EXIT_GAME = 91,
	INPUT_OUTSIDE_RANGE = 92,
	UNKNOWN_ERROR_ENCOUNTERED = 100
};

class CMenu
{
public:
	CMenu();
	~CMenu();

	void PrintMenu(CParticipant& _user);
	void ChangeMenus(ECurrentMenu _toChangeTo);
	ECurrentMenu GetMenu() const;
	EMainMenuOptions MenuSelection(int _iInput) const;

private:
	string m_MainMenu[6] = { "Play", "Instructions", "Credits", "Mode", "Difficulty", "Exit Game" };
	string m_ModeMenu[3] = { "One Player", "Two Player" , "Return to Main" };
	string m_DifficultyMenu[4] = { "Easy", "Medium", "Hard", "Return to Main" };
	string m_ShipSelecctionMenu[6] = { "Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat", "Exit" };
	string m_ReadyToPlayMenu[3] = { "Reposition", "Let's start!", "Exit" };
	string m_BlankMenu[1] = { " " };

	ECurrentMenu m_WhichMenu;

};

#endif // !__MENU_H__