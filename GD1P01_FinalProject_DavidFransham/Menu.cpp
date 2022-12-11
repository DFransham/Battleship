/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Menu.cpp
Description : Menu Class implementation file
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#include "Menu.h"

//default constructor
CMenu::CMenu()
{
	m_WhichMenu = ECurrentMenu::MAIN;
}

//default destructor
CMenu::~CMenu()
{
}

//prints menu to box in middle of screen, depending on which menu state the game is currently in
void CMenu::PrintMenu(CParticipant& _user)
{
	int _iXStart = _user.s_iMiddleX;
	int _iYStart = _user.s_iMenuY;

	switch (m_WhichMenu)
	{
	case ECurrentMenu::MAIN:
		MenuPrinter(_iXStart + 1, _iYStart, 6, m_MainMenu);
		break;
	case ECurrentMenu::GAME_MODE:
		MenuPrinter(_iXStart + 1, _iYStart, 3, m_ModeMenu);
		break;
	case ECurrentMenu::DIFFICULTY:
		MenuPrinter(_iXStart + 1, _iYStart, 4, m_DifficultyMenu);
		break;
	case ECurrentMenu::SHIP_SELECTION:
		MenuPrinter(_iXStart + 1, _iYStart, 6, m_ShipSelecctionMenu);
		break;
	case ECurrentMenu::READY_TO_PLAY:
		MenuPrinter(_iXStart + 1, _iYStart, 3, m_ReadyToPlayMenu);
		break;
	case ECurrentMenu::BLANK_MENU:
		//do nothing
		break;
	}
}

//changes variable containing current menu state
void CMenu::ChangeMenus(ECurrentMenu _toChangeTo)
{
	m_WhichMenu = _toChangeTo;
}

//returns current menu state
ECurrentMenu CMenu::GetMenu() const
{
	return m_WhichMenu;
}

//returns menu choice from user input based on current menu state
EMainMenuOptions CMenu::MenuSelection(int _iInput) const
{
	switch (m_WhichMenu)
	{
	case ECurrentMenu::MAIN:
		switch (_iInput)
		{
		case 1:
			return EMainMenuOptions::PLAY;
			break;
		case 2:
			return EMainMenuOptions::INSTRUCTIONS;
			break;
		case 3:
			return EMainMenuOptions::CREDITS;
			break;
		case 4:
			return EMainMenuOptions::GAME_MODE;
			break;
		case 5:
			return EMainMenuOptions::DIFFICULTY;
			break;
		case 6:
			return EMainMenuOptions::EXIT_GAME;
			break;
		default:
			return EMainMenuOptions::INPUT_OUTSIDE_RANGE;
			break;
		}		
		break;

	case ECurrentMenu::GAME_MODE:
		switch (_iInput)
		{
		case 1:
			return EMainMenuOptions::M_ONE_PLAYER;
			break;
		case 2:
			return EMainMenuOptions::M_TWO_PLAYER;
			break;
		case 3:
			return EMainMenuOptions::RETURN;
			break;
		default:
			return EMainMenuOptions::INPUT_OUTSIDE_RANGE;
			break;
		}
		break;

	case ECurrentMenu::DIFFICULTY:
		switch (_iInput)
		{
		case 1:
			return EMainMenuOptions::D_EASY;
			break;
		case 2:
			return EMainMenuOptions::D_MEDIUM;
			break;
		case 3:
			return EMainMenuOptions::D_HARD;
			break;
		case 4:
			return EMainMenuOptions::RETURN;
			break;
		default:
			return EMainMenuOptions::INPUT_OUTSIDE_RANGE;
			break;
		}
		break;

	case ECurrentMenu::SHIP_SELECTION:
		switch (_iInput)
		{
		case 1:
			return EMainMenuOptions::AIRCRAFT_CARRIER;
			break;
		case 2:
			return EMainMenuOptions::BATTLESHIP;
			break;
		case 3:
			return EMainMenuOptions::DESTROYER;
			break;
		case 4:
			return EMainMenuOptions::SUBMARINE;
			break;
		case 5:
			return EMainMenuOptions::PATROL_BOAT;
			break;
		case 6:
			return EMainMenuOptions::EXIT_GAME;
			break;
		default:
			return EMainMenuOptions::INPUT_OUTSIDE_RANGE;
			break;
		}
		break;

	case ECurrentMenu::READY_TO_PLAY:
		switch (_iInput)
		{
		case 1:
			return EMainMenuOptions::REPOSITION_SHIP;
			break;
		case 2:
			return EMainMenuOptions::LETS_GO;
			break;
		case 3:
			return EMainMenuOptions::EXIT_GAME;
			break;
		default:
			return EMainMenuOptions::INPUT_OUTSIDE_RANGE;
			break;
		}
		break;

	case ECurrentMenu::BLANK_MENU:
		//do nothing
		return EMainMenuOptions::UNKNOWN_ERROR_ENCOUNTERED;
		break;

	default:
		return EMainMenuOptions::UNKNOWN_ERROR_ENCOUNTERED; //I don't know how we got here!
		break;
	}
}