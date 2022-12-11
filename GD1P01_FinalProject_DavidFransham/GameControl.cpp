/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : GameControl.cpp
Description : GameControl class definition file - holds overarching information to run battleship game
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#include "GameControl.h"

//Constructor - requires two map objects to create
CGameControl::CGameControl(CMap& _mapOne, CMap& _mapTwo) : m_PlayerOne (_mapOne), m_PlayerTwo (_mapTwo)		// TF: Constructor
{
	m_MyMenu = CMenu::CMenu();
	m_eDifficulty = EOpponentDifficulty::EASY;
	m_eLastMessage = EMessageType::NO_MESSAGE;
	
	m_iTurnCount = 0;
	m_iWidth = 1100;
	m_iHeight = 700;

	m_bDebugUsed = false;
	m_bRestartGame = false;
	m_b2Player = false;
	m_bTurnToggle = false;
}	

//Destructor
CGameControl::~CGameControl()				// TF: Destructor
{
}

//sets default parameters and begins setup steps for the game.
//also returns boolean to main function at game end to indicate restart or not
bool CGameControl::GameSetup(CParticipant& _user, CParticipant& _opponent)
{
	_user.UpdateStaticX(GetConsoleDimensions());
	RedrawEverything(_user, _opponent, false);
	
	Set2PlayerMode(_opponent, false);
	SetDebugMode(false);
	m_MyMenu.PrintMenu(_user);
	PrintScreenInfo();
	
	GoToXY(_user.s_iMiddleX - 10, _user.s_iOutputY);

	//takes user input for various menu states, starts game when setup is finished
	string temp;
	while (!m_bRestartGame)
	{
		string pauseToRead;
		temp = GetUserInput(_user.s_iMiddleX - 10);
		_user.UpdateInput(temp);
		if (temp == "DEBUG" || temp == "debug")			// TF: Logical Operator
		{
			SetDebugMode(!GetDebugMode(_user));
			_user.UpdateOutput("Debug mode has changed.");
			PrintInOut(_user, _opponent, false);
		}
		else if (temp == "NO_INPUT_GIVEN")				// TF: Relational Operator
		{
			InvalidInput(EInputErrors::NO_INPUT_GIVEN, _user);
		}
		else if (IsOnlyNumbers(temp))
		{
			int choice = std::stoi(temp);
			EMainMenuOptions thisChoice = m_MyMenu.MenuSelection(choice);
			switch (thisChoice)
			{

			case EMainMenuOptions::PLAY:
				m_MyMenu.ChangeMenus(ECurrentMenu::SHIP_SELECTION);
				_user.UpdateOutput("Select a ship to place");
				RedrawEverything(_user, _opponent, false);
				MainGameLoop(_user, _opponent);
				break;

			case EMainMenuOptions::INSTRUCTIONS:
				PrintMessage(_user, EMessageType::INSTRUCTIONS, EColour::COLOUR_GREEN_ON_BLACK, false);
				pauseToRead = GetUserInput(_user.s_iMiddleX);
				_user.UpdateOutput(" ");
				break;

			case EMainMenuOptions::CREDITS:
				PrintMessage(_user, EMessageType::CREDITS, EColour::COLOUR_GREEN_ON_BLACK, false);
				pauseToRead = GetUserInput(_user.s_iMiddleX);
				_user.UpdateOutput(" ");
				break;

			case EMainMenuOptions::GAME_MODE:
				m_MyMenu.ChangeMenus(ECurrentMenu::GAME_MODE);
				_user.UpdateOutput("Select a menu option");
				break;

			case EMainMenuOptions::DIFFICULTY:
				m_MyMenu.ChangeMenus(ECurrentMenu::DIFFICULTY);
				_user.UpdateOutput("Select a menu option");
				break;

			case EMainMenuOptions::M_ONE_PLAYER:
				Set2PlayerMode(_opponent, false);
				PrintMessage(_user, EMessageType::SINGLE_PLAYER, EColour::COLOUR_GREEN_ON_BLACK, false);
				_user.UpdateOutput(" ");
				pauseToRead = GetUserInput(_user.s_iMiddleX);
				break;

			case EMainMenuOptions::M_TWO_PLAYER:
				Set2PlayerMode(_opponent, true);
				PrintMessage(_user, EMessageType::TWO_PLAYER, EColour::COLOUR_GREEN_ON_BLACK, false);
				_user.UpdateOutput(" ");
				pauseToRead = GetUserInput(_user.s_iMiddleX);
				break;

			case EMainMenuOptions::D_EASY:
				SetDifficulty(EOpponentDifficulty::EASY);
				PrintMessage(_user, EMessageType::DIFFICULTY_EASY, EColour::COLOUR_GREEN_ON_BLACK, false);
				pauseToRead = GetUserInput(_user.s_iMiddleX);
				_user.UpdateOutput(" ");
				break;

			case EMainMenuOptions::D_MEDIUM:
				SetDifficulty(EOpponentDifficulty::MEDIUM);
				PrintMessage(_user, EMessageType::DIFFICULTY_MEDIUM, EColour::COLOUR_GREEN_ON_BLACK, false);
				pauseToRead = GetUserInput(_user.s_iMiddleX);
				_user.UpdateOutput(" ");
				break;

			case EMainMenuOptions::D_HARD:
				SetDifficulty(EOpponentDifficulty::HARD);
				PrintMessage(_user, EMessageType::DIFFICULTY_HARD, EColour::COLOUR_GREEN_ON_BLACK, false);
				pauseToRead = GetUserInput(_user.s_iMiddleX);
				_user.UpdateOutput(" ");
				break;

			case EMainMenuOptions::RETURN:
				m_MyMenu.ChangeMenus(ECurrentMenu::MAIN);
				_user.UpdateOutput("Select a menu option");
				break;

			case EMainMenuOptions::EXIT_GAME:
				PrintMessage(_user, EMessageType::GOODBYE, EColour::COLOUR_RED_ON_BLACK, false);
				temp = GetUserInput(_user.s_iMiddleX);
				while (temp != "Y" && temp != "N" && temp != "y" && temp != "n")
				{
					_user.UpdateOutput("Invalid input.  Please choose Y to exit or N to return to game");
					PrintInOut(_user, _opponent, false);
					temp = GetUserInput(_user.s_iMiddleX);
				}
				if (temp == "Y" || temp == "y")
				{
					exit(0);
				}
				break;
				
			case EMainMenuOptions::INPUT_OUTSIDE_RANGE:
				InvalidInput(EInputErrors::NOT_ON_MENU, _user);
				break;

			case EMainMenuOptions::UNKNOWN_ERROR_ENCOUNTERED:
				std::cout << "whoopsie"; //I don't know how we got here
				break;
			default:
				break;
			}
		}
		else
		{
			InvalidInput(EInputErrors::NOT_NUMBER, _user);
		}
		RedrawEverything(_user, _opponent, false);

	}
	return m_bRestartGame;
}

//not used at this time, but was implemented with the idea of resizing screen more readily
void CGameControl::SetScreenDimensions(int _iPixelHeight, int _iPixelWidth)
{
	m_iHeight = _iPixelHeight;
	m_iWidth = _iPixelWidth;
}

//used for resizing screen from default values - functionality exists for modifying this more dynamically
int CGameControl::GetScreenWidth() const
{
	return m_iWidth;
}

//used for resizing screen from default values - functionality exists for modifying this more dynamically
int CGameControl::GetScreenHeight() const
{
	return m_iHeight;
}

//turns debug mode on or off - doesn't matter which player is called as it is static variable
void CGameControl::SetDebugMode(bool _bDebugOn)
{
	m_PlayerOne.s_bDebugOn = _bDebugOn;
}

//sets game to two player mode, also changes human status of opponent
void CGameControl::Set2PlayerMode(CParticipant& _opponent, bool _b2PlayerModeOn)
{
	m_b2Player = _b2PlayerModeOn;
	_opponent.SetHumanStatus(_b2PlayerModeOn);
}

//allows for changing difficulty mode - as it was not implemented in this release it switches back to easy mode for now
void CGameControl::SetDifficulty(EOpponentDifficulty _eDifficulty)
{
	m_eDifficulty = _eDifficulty;

	//because I have not implemented this option yet, set to easy
	m_eDifficulty = EOpponentDifficulty::EASY;
}

//returns difficulty mode
EOpponentDifficulty CGameControl::GetDifficulty() const
{
	return m_eDifficulty;
}

//returns current debug mode - static variable so _user not really relevant
bool CGameControl::GetDebugMode(CParticipant& _user) const
{
	return _user.s_bDebugOn;
}

//returns whether game is currently 2 player mode
bool CGameControl::Get2PlayerMode() const
{
	return m_b2Player;
}

//increases turn counter by one to keep track of game progress
void CGameControl::IncrementTurnCounter()
{
	m_iTurnCount++;
}

//returns current turn counter
int CGameControl::GetTurnCount() const
{
	return m_iTurnCount;
}

//finishes setup, controls turn order for game
void CGameControl::MainGameLoop(CParticipant& _user, CParticipant& _opponent)
{
	PrepareToPlaceShips(_user, _opponent);
	PrepareToPlaceShips(_opponent, _user);

	m_MyMenu.ChangeMenus(ECurrentMenu::BLANK_MENU);
	_user.UpdateOutput("Enter coordinates to fire at");
	IncrementTurnCounter();
	RedrawEverything(_user, _opponent);
	
	bool GameOn = true;
	while (GameOn)
	{
		if (!m_bTurnToggle)
		{
			TakeTurn(_user, _opponent);
			if (_user.IsStillAlive())
			{
				ToggleTurn();
			}
			else
			{
				GameOn = false;
			}
		}
		else
		{
			TakeTurn(_opponent, _user);
			if (_opponent.IsStillAlive())
			{
				ToggleTurn();
			}
			else
			{
				GameOn = false;
			}
			IncrementTurnCounter();
		}

		if (m_bRestartGame)
		{
			GameOn = false;
		}
	}
	return;
}

//controls printing of menu headers, game state info such as debug mode etc 
void CGameControl::PrintScreenInfo()
{
	int width = GetConsoleDimensions();
	int height = GetConsoleDimensions(false);

	SetRgb(EColour::COLOUR_CYAN_ON_BLACK);
	string toPrint = " ";

	ECurrentMenu current = m_MyMenu.GetMenu();
	switch (current)
	{
	case ECurrentMenu::MAIN:
		toPrint = "Main Menu";
		break;
	case ECurrentMenu::GAME_MODE:
		toPrint = "Select game mode";
		break;
	case ECurrentMenu::DIFFICULTY:
		toPrint = "Select difficulty";
		break;
	case ECurrentMenu::SHIP_SELECTION:
		toPrint = "Select ship to position";
		break;
	case ECurrentMenu::READY_TO_PLAY:
		toPrint = "Everything ready?";
		break;
	case ECurrentMenu::BLANK_MENU:
		toPrint = "Turn # ";
		toPrint += std::to_string(m_iTurnCount);
		break;
	default:
		break;
	}
		
	int len = static_cast<int>(toPrint.length());
	GoToXY((width / 2) - (len / 2), 4);
	std::cout << toPrint;

	string part2;
	
	toPrint = "Game Mode: ";
	EColour desired = EColour::COLOUR_WHITE_ON_BLACK;
	switch (m_b2Player)
	{
	case false:
		part2 = "Single Player vs AI";
		desired = EColour::COLOUR_MAGENTA_ON_BLACK;
		break;
	case true:
		part2 = "Two Player";
		desired = EColour::COLOUR_BLUE_ON_BLACK;
		break;
	}
	len = static_cast<int>(toPrint.length() + part2.length());		// TF: Arithmetic Operator
	GoToXY((width / 2) - (len / 2), height - 3);
	std::cout << toPrint;

	SetRgb(desired);
	std::cout << part2;

	SetRgb(EColour::COLOUR_CYAN_ON_BLACK);
	toPrint = "Debug mode: ";
	GoToXY(3, height - 3);
	std::cout << toPrint;
	
	switch (m_PlayerOne.s_bDebugOn)
	{
	case true:
		SetRgb(EColour::COLOUR_YELLOW_ON_BLACK);
		std::cout << "ON";
		break;
	case false:
		SetRgb(EColour::COLOUR_RED_ON_BLACK);
		std::cout << "OFF";
		break;
	}
	SetRgb(EColour::COLOUR_CYAN_ON_BLACK);

	if (!m_b2Player)
	{
		switch (m_eDifficulty)
		{
		case EOpponentDifficulty::EASY:
			toPrint = "EASY";
			SetRgb(EColour::COLOUR_GREEN_ON_BLACK);
			len = 4;
			break;
		case EOpponentDifficulty::MEDIUM:
			toPrint = "MEDIUM";
			len = 6;
			SetRgb(EColour::COLOUR_YELLOW_ON_BLACK);
			break;
		case EOpponentDifficulty::HARD:
			toPrint = "HARD";
			len = 4;
			SetRgb(EColour::COLOUR_RED_ON_BLACK);
			break;
		default:
			toPrint = "Something went wrong";
			len = static_cast<int>(toPrint.length());
			break;
		}

		GoToXY(width - len - 3, height - 3);
		std::cout << toPrint;

		toPrint = "Difficulty: ";
		len += static_cast<int>(toPrint.length());
		SetRgb(EColour::COLOUR_CYAN_ON_BLACK);
		GoToXY(width - len - 3, height - 3);
		std::cout << toPrint;
	}
	
}

//toggles the turn order loop
void CGameControl::ToggleTurn()
{
	m_bTurnToggle = !m_bTurnToggle;
}

//toggles sounds on or off
void CGameControl::TurnSoundOnOff()
{
	m_bSoundOn = !m_bSoundOn;
}

//returns whether sounds should be played or not
bool CGameControl::GetSoundStatus() const
{
	return m_bSoundOn;
}

//calls numerous "print" functions to redraw the game state in totality
void CGameControl::RedrawEverything(CParticipant& _user, CParticipant& _opponent, bool _bGameStarted)
{
	if (_user.GetHumanStatus() || !_bGameStarted)
	{
		ClearScreen();
		PrintBattleshipUI(_user, _opponent);
		PrintShipStatus(_user.s_iLeftShipsX, _user.s_iTopMapY + 2, _user);
		PrintShipStatus(_user.s_iRightShipsX, _user.s_iTopMapY + 2, _opponent);
		PrintMapPoints(_user.s_iLeftMapX + 4, _user.s_iTopMapY + 2, _user, true);
		PrintMapPoints(_user.s_iRightMapX + 4, _user.s_iTopMapY + 2, _opponent, false);

		m_MyMenu.PrintMenu(_user);
		PrintInOut(_user, _opponent, _bGameStarted);
		if (_user.s_bDebugOn)
		{
			PrintDebugInfo(_user, _opponent, _bGameStarted);
		}
		PrintScreenInfo();
		GoToXY(_user.s_iMiddleX - 10, _user.s_iOutputY + 2);
	}
}

//continues game setup, calls functions to manually or randomly place ships on map
void CGameControl::PrepareToPlaceShips(CParticipant& _user, CParticipant& _opponent)
{
	bool isHuman = _user.GetHumanStatus();
	bool endLoop = false;
	string temp = " ";
	switch (isHuman)
	{
	case true:
		
		if (m_b2Player)
		{
			PrintPlayerPauseScreen(_user, m_bTurnToggle);
			temp = GetUserInput(_user.s_iMiddleX);
			ClearScreen();
			PrintMessage(_user, EMessageType::HIDE_SCREEN);
			temp = GetUserInput(_user.s_iMiddleX);
			ToggleTurn();
		}
		RedrawEverything(_user, _opponent, false);
		PrintMessage(_user, EMessageType::AUTO_OR_MANUAL);
		while (!endLoop)
		{
			temp = GetUserInput(_user.s_iMiddleX - 10);
			_user.UpdateInput(temp);
			if (IsOnlyNumbers(temp))
			{
				if (temp == "1")
				{
					endLoop = PlaceFleet(_user, _opponent);
				}
				else if (temp == "2")
				{
					_user.GenerateAIPositions();
					endLoop = true;
				}
				else
				{
					_user.UpdateOutput("Invalid input. Please choose 1 or 2");
					PrintInOut(_user, _opponent, false);
				}
			}
			else
			{
				_user.UpdateOutput("Invalid input. Please choose 1 or 2");
				PrintInOut(_user, _opponent, false);
			}
		}
		break;

	case false:
		_user.GenerateAIPositions();
	}
}

//controls overall manual placement of ships on map, returns boolean to report on success
bool CGameControl::PlaceFleet(CParticipant& _user, CParticipant& _opponent)
{
	bool shipsPlaced[5] = { false, false, false, false, false };		// TF: Array
	RedrawEverything(_user, _opponent, false);
	string temp;
	string pauseToRead = " ";
	bool repeat = false;
	do
	{
		while (!(shipsPlaced[0] && shipsPlaced[1] && shipsPlaced[2] && shipsPlaced[3] && shipsPlaced[4]))
		{
			string pauseToRead;
			temp = GetUserInput(_user.s_iMiddleX - 10);
			_user.UpdateInput(temp);
			if (temp == "DEBUG" || temp == "debug")
			{
				SetDebugMode(!GetDebugMode(_user));
				_user.UpdateOutput("Debug mode has changed.");
				RedrawEverything(_user, _opponent, false);
			}
			else if (temp == "NO_INPUT_GIVEN")
			{
				InvalidInput(EInputErrors::NO_INPUT_GIVEN, _user);
			}
			else if (IsOnlyNumbers(temp))
			{
				int choice = std::stoi(temp);
				EMainMenuOptions thisChoice = m_MyMenu.MenuSelection(choice);

				switch (thisChoice)
				{

				case EMainMenuOptions::RETURN:
					m_MyMenu.ChangeMenus(ECurrentMenu::MAIN);
					_user.UpdateOutput("Select a menu option");
					break;

				case EMainMenuOptions::AIRCRAFT_CARRIER:
					PlaceSingleShip(_user, _opponent, 0);
					shipsPlaced[0] = true;
					break;

				case EMainMenuOptions::BATTLESHIP:
					PlaceSingleShip(_user, _opponent, 1);
					shipsPlaced[1] = true;
					break;

				case EMainMenuOptions::DESTROYER:
					PlaceSingleShip(_user, _opponent, 2);
					shipsPlaced[2] = true;
					break;

				case EMainMenuOptions::SUBMARINE:
					PlaceSingleShip(_user, _opponent, 3);
					shipsPlaced[3] = true;
					break;

				case EMainMenuOptions::PATROL_BOAT:
					PlaceSingleShip(_user, _opponent, 4);
					shipsPlaced[4] = true;
					break;

				case EMainMenuOptions::EXIT_GAME:
					PrintMessage(_user, EMessageType::GOODBYE, EColour::COLOUR_RED_ON_BLACK, false);
					temp = GetUserInput(_user.s_iMiddleX);
					if (temp == "NO_INPUT_GIVEN" || temp == "Y" || temp == "y")
					{
						exit(0);
					}
					break;

				case EMainMenuOptions::INPUT_OUTSIDE_RANGE:
					InvalidInput(EInputErrors::NOT_ON_MENU, _user);
					break;

				case EMainMenuOptions::UNKNOWN_ERROR_ENCOUNTERED:
					std::cout << "whoopsie";
					break;

				default:
					break;
				}
			}
			else
			{
				InvalidInput(EInputErrors::NOT_NUMBER, _user);
			}
			RedrawEverything(_user, _opponent, false);
		}
		m_MyMenu.ChangeMenus(ECurrentMenu::READY_TO_PLAY);
		_user.UpdateOutput("Are you happy with your ship placement? Choose from menu above");
		RedrawEverything(_user, _opponent, false);

		temp = GetUserInput(_user.s_iMiddleX - 10);
		_user.UpdateInput(temp);
		if (temp == "DEBUG" || temp == "debug")
		{
			SetDebugMode(!GetDebugMode(_user));
			_user.UpdateOutput("Debug mode has changed.");
		}
		else if (temp == "NO_INPUT_GIVEN")
		{
			InvalidInput(EInputErrors::NO_INPUT_GIVEN, _user);
		}
		else if (IsOnlyNumbers(temp))
		{
			int choice = std::stoi(temp);
			EMainMenuOptions thisChoice = m_MyMenu.MenuSelection(choice);
			string result = " ";
				
			switch (thisChoice)
			{
			case EMainMenuOptions::REPOSITION_SHIP:
				PrintMessage(_user, EMessageType::REPOSITION, EColour::COLOUR_GREEN_ON_BLACK, false);
				result = GetUserInput(_user.s_iMiddleX);
				_user.UpdateInput(result);

				if (IsOnlyNumbers(result))
				{
					if (result == "1")
					{
						//start game
						return true;
					}
					else if (result == "2")
					{
						_user.ResetFleet();
						for (int i = 0; i < 5; i++)
						{
							shipsPlaced[i] = false;
						}
						repeat = true;
						m_MyMenu.ChangeMenus(ECurrentMenu::SHIP_SELECTION);
						_user.UpdateOutput("Select a ship to place");
						RedrawEverything(_user, _opponent, false);
						break;
					}
					else
					{
						InvalidInput(EInputErrors::INPUT_OUTSIDE_RANGE, _user);
						PrintInOut(_user, _opponent, false);
						PrintDebugInfo(_user, _opponent, false);
					}
				}
				else
				{
					InvalidInput(EInputErrors::NOT_NUMBER, _user);
				}

				break;

			case EMainMenuOptions::LETS_GO:
				_user.SetReadyStatus(true);
				return true;
				break;

			case EMainMenuOptions::BLANK_OPTION:
				break;

			case EMainMenuOptions::EXIT_GAME:
				PrintMessage(_user, EMessageType::GOODBYE, EColour::COLOUR_RED_ON_BLACK, false);
				temp = GetUserInput(_user.s_iMiddleX);
				if (temp == "NO_INPUT_GIVEN" || temp == "Y" || temp == "y")
				{
					exit(0);
				}
				break;

			case EMainMenuOptions::INPUT_OUTSIDE_RANGE:
				InvalidInput(EInputErrors::NOT_ON_MENU, _user);
				break;

			case EMainMenuOptions::UNKNOWN_ERROR_ENCOUNTERED:
				std::cout << "whoopsie";
				break;

			default:
				break;
			}
		}
	} while (repeat);
	return true;
}

//checks if chosen ship is already on map.  If not, places it on map.
void CGameControl::PlaceSingleShip(CParticipant& _user, CParticipant& _opponent, int _iIndex)
{
	//checks ship isn't already placed
	string pauseToRead;
	if (_user.IsShipPlaced(_iIndex))
	{
		PrintMessage(_user, EMessageType::ALREADY_PLACED, EColour::COLOUR_GREEN_ON_BLACK, false);
		pauseToRead = GetUserInput(_user.s_iMiddleX);
		return;
	}
	PrintMessage(_user, EMessageType::ENTER_COORDINATES, EColour::COLOUR_GREEN_ON_BLACK, false);
	
	//attempts to get input and place ship - keeps looping until completed successfully
	bool tryAgain = true;
	while (tryAgain)
	{
		int len = 0;
		string toPrint = " ";
		string result = GetUserInput(_user.s_iMiddleX);
		
		//checking input for valid map coordinate, then translating it into int values
		if (IsValidMapCoord(result))
		{
			len = static_cast<int>(result.length());

			char cFirst = result[0];
			int iFirst = static_cast<int>(cFirst);

			if (iFirst < 80)
			{
				iFirst -= 65;
			}
			else
			{
				iFirst -= 97;
			}

			int iSecond = 0;
			if (len == 3)
			{
				iSecond = 9;
			}
			else
			{
				iSecond = (static_cast<int>(result[1])) - 49;
			}

			//asks for input about orientation of ship
			PrintMessage(_user, EMessageType::HORIZONT_OR_VERT, EColour::COLOUR_GREEN_ON_BLACK, false);
			result = GetUserInput(_user.s_iMiddleX);
			if (IsOnlyNumbers(result))
			{
				if (result == "0")
				{
					if (_user.AttemptToPlaceShip(_iIndex, iFirst, iSecond, true))
					{
						_user.UpdateOutput("Ship placed successfully.");
						tryAgain = false;
					}
					else
					{
						_user.UpdateOutput("Placement failed, try another position");
					}
				}
				else if (result == "1")
				{
					if (_user.AttemptToPlaceShip(_iIndex, iFirst, iSecond, false))
					{
						_user.UpdateOutput("Ship placed successfully.");
						tryAgain = false;
					}
					else
					{
						_user.UpdateOutput("Placement failed, try another position");
					}
				}
				else
				{
					_user.UpdateOutput("Bad input.  Enter coordinates again");
				}
				PrintInOut(_user, _opponent, false);
			}
			else
			{
				_user.UpdateOutput("Bad input.  Enter coordinates again");
				PrintInOut(_user, _opponent, false);
			}
		}
		else
		{
			_user.UpdateOutput("Bad input.  Enter coordinates again");
			PrintInOut(_user, _opponent, false);
			tryAgain = true;
		}
	}
	return;
}

//controls actions taken during each player's turn - human or "ai"
void CGameControl::TakeTurn(CParticipant& _user, CParticipant& _opponent)
{
	bool isHuman = _user.GetHumanStatus();
	bool placeholder = false;
	string pauseToRead = " ";
	bool successful = false;
	bool sndPlayed = false;
	
	switch (isHuman)
	{
	//human player's turn
	case true:
		if (m_b2Player)  //only display interim screens for two player game
		{
			PrintPlayerPauseScreen(_user, m_bTurnToggle);
			pauseToRead = GetUserInput(_user.s_iMiddleX);
			ClearScreen();
			PrintMessage(_user, EMessageType::HIDE_SCREEN);
			pauseToRead = GetUserInput(_user.s_iMiddleX);
		}
		RedrawEverything(_user, _opponent);
		DisplayPreviousTurnInfo(_user, _opponent);

		//loop to keep asking for input until valid input received
		while (!successful)
		{
			string input;
			input = GetUserInput(_user.s_iMiddleX - 10);
			_user.UpdateInput(input);
			if (input == "DEBUG" || input == "debug")
			{
				bool debugSwitch = true;
				if (m_b2Player)
				{
					PrintMessage(_user, EMessageType::DONT_CHEAT);

					string result = GetUserInput(_user.s_iMiddleX);
					_user.UpdateInput(result);

					if (result == "DEBUG" || result == "debug")
					{
						//do nothing, debug switch is already on
					}
					else
					{
						debugSwitch = false;
						_user.UpdateOutput("Debug mode cancelled.  Please enter coordinates to attack.");
						PrintInOut(_user, _opponent);
						PrintDebugInfo(_user, _opponent);
					}
				}
				else
				{
					//do nothing - debug switch is already on
				}
				if (debugSwitch)
				{
					SetDebugMode(!GetDebugMode(_user));
					m_bDebugUsed = true;
					RedrawEverything(_user, _opponent);
				}
			}
			else if (input == "SOUND" || input == "sound")
			{
				TurnSoundOnOff();
				if (m_bSoundOn)
				{
					input = "on";
				}
				else
				{
					input = "off";
				}
				input = "Sound turned " + input + ". Please enter coordinates to attack.";
				_user.UpdateOutput(input);
				PrintInOut(_user, _opponent);
			}
			else if (input == "NO_INPUT_GIVEN")
			{
				InvalidInput(EInputErrors::NO_INPUT_GIVEN, _user);
				PrintInOut(_user, _opponent);
			}
			else if (IsValidMapCoord(input))
			{
				int len = static_cast<int>(input.length());
				
				char cFirst = input[0];
				
				int iFirst = static_cast<int>(cFirst);
				
				if (iFirst < 80)
				{
					iFirst -= 65;
				}
				else
				{
					iFirst -= 97;
				}
				
				int iSecond = 0;
				if (len == 3)
				{
					iSecond = 9;
				}
				else
				{
					iSecond = (static_cast<int>(input[1])) - 49;
				}

				//sends valid input to opponent object to fire at a ship
				EShotResult myShot = _opponent.MakeShot(iFirst, iSecond);

				//controls feedback on result of shot
				switch (myShot)
				{
				case EShotResult::HIT:
					RedrawEverything(_user, _opponent);
					PrintMessage(_user, EMessageType::YOU_HIT_OPPONENT);
					if (m_bSoundOn)
					{
						sndPlayed = PlaySound(TEXT("sndBoom"), NULL, SND_ALIAS);
					}
					_user.UpdateOutput("Enter coordinates to fire at:");
					pauseToRead = GetUserInput(_user.s_iMiddleX);
					m_eLastMessage = EMessageType::OPPONENT_HIT_YOU;
					successful = true;
					break;

				case EShotResult::HIT_AND_SUNK:
					RedrawEverything(_user, _opponent);
					PrintMessage(_user, EMessageType::YOU_SUNK_SHIP);
					if (m_bSoundOn)
					{
						sndPlayed = PlaySound(TEXT("sndBoom.wav"), NULL, SND_ALIAS);
					
					}
					_user.UpdateOutput("Enter coordinates to fire at:");
					pauseToRead = GetUserInput(_user.s_iMiddleX);
					m_eLastMessage = EMessageType::OPPONENT_SUNK_SHIP;
					successful = true;
					break;

				case EShotResult::MISS:
					RedrawEverything(_user, _opponent);
					PrintMessage(_user, EMessageType::YOU_MISSED_OPPONENT);
					if (m_bSoundOn)
					{
						sndPlayed = PlaySound(TEXT("sndSplash.wav"), NULL, SND_ALIAS);
					}
					_user.UpdateOutput("Enter coordinates to fire at:");
					pauseToRead = GetUserInput(_user.s_iMiddleX);
					m_eLastMessage = EMessageType::OPPONENT_MISSED_YOU;
					successful = true;
					break;

				case EShotResult::OPPONENT_DEFEATED:
					RedrawEverything(_user, _opponent);
					PrintMessage(_user, EMessageType::YOU_WON);
					if (m_bSoundOn)
					{
						sndPlayed = PlaySound(TEXT("sndWin.wav"), NULL, SND_ALIAS);
					}

					pauseToRead = GetUserInput(_user.s_iMiddleX);
					while (pauseToRead != "1" && pauseToRead != "2")
					{
						_user.UpdateOutput("Invalid input.  Please choose 1 or 2");
						PrintInOut(_user, _opponent);
						pauseToRead = GetUserInput(_user.s_iMiddleX);
					}
					if (pauseToRead == "1")
					{
						ResetGame(_user, _opponent);
						RedrawEverything(_user, _opponent);
						m_bRestartGame = true;
						return;
					}
					else if (pauseToRead == "2")
					{
						exit(0);
					}
					
					m_eLastMessage = EMessageType::OPPONENT_SUNK_SHIP;
					successful = true;
					break;

				case EShotResult::INVALID_SHOT:
					if (_opponent.GetMapState(iFirst, iSecond) == EMAPSTATE::EXPLORED_HIT || 
						_opponent.GetMapState(iFirst, iSecond) == EMAPSTATE::EXPLORED_MISS)
					{
						_user.UpdateOutput("You've already fired there, try somewhere new!");
					}
					else
					{
						_user.UpdateOutput("Invalid coordinates, please try again");
					}
					PrintInOut(_user, _opponent);
					PrintDebugInfo(_user, _opponent);

					successful = false;
					break;

				default:
					std::cout << "I don't know how we got here";
					break;
				}
			}			
			else
			{
				_user.UpdateOutput("Format not recognised. Please try again");
				PrintInOut(_user, _opponent);
				PrintDebugInfo(_user, _opponent);
			}
 
		}
		break;

	//generate ai shot in a single player game
	case false:
		
		m_bDebugUsed = false;
		while (!successful)
		{
			int x = GetRandomNumber(9, 0);
			int y = GetRandomNumber(9, 0);

			EShotResult myShot = _opponent.MakeShot(x, y);

			switch (myShot)
			{
			case EShotResult::HIT:
				m_eLastMessage = EMessageType::OPPONENT_HIT_YOU;
				successful = true;
				break;

			case EShotResult::HIT_AND_SUNK:
				m_eLastMessage = EMessageType::OPPONENT_SUNK_SHIP;
				successful = true;
				break;

			case EShotResult::MISS:
				m_eLastMessage = EMessageType::OPPONENT_MISSED_YOU;
				successful = true;
				break;

			case EShotResult::OPPONENT_DEFEATED:
				m_eLastMessage = EMessageType::OPPONENT_SUNK_SHIP;
				successful = true;
				break;

			case EShotResult::INVALID_SHOT:
				successful = false;
				break;

			default:
				std::cout << "I don't know how we got here";
				break;
			}
		}
		break;
	}
}

//displays feedback on what occurred during opponent's turn
void CGameControl::DisplayPreviousTurnInfo(CParticipant& _user, CParticipant& _opponent)
{
	string pauseToRead = " ";
	if (m_bDebugUsed)
	{
		PrintMessage(_user, EMessageType::OPPONENT_USED_DEBUG);

		string result = GetUserInput(_user.s_iMiddleX);
		_user.UpdateInput(result);

		if (result == "EXIT" || result == "exit" || result == "Exit")
		{
			exit(0);
		}
		else
		{
			_user.UpdateOutput("Game continuing.");
			PrintInOut(_user, _opponent);
		}
		m_bDebugUsed = false;
	}

	bool sndPlayed = false;
	switch (m_eLastMessage)
	{
	case EMessageType::OPPONENT_HIT_YOU: //fallthrough
	case EMessageType::OPPONENT_MISSED_YOU://fallthrough
	case EMessageType::OPPONENT_SUNK_SHIP:
		PrintMessage(_user, m_eLastMessage, EColour::COLOUR_YELLOW_ON_BLACK);
		if (GetDebugMode(_user))
		{
			PrintDebugInfo(_user, _opponent);
			GoToXY(GetCursorPos().X, GetCursorPos().Y + 1);
		}
		break;
	
	default:
		break;
	}
	
	if (!_user.IsStillAlive())
	{
		PrintMessage(_user, EMessageType::YOU_LOST);
		
		if (m_bSoundOn)
		{
			sndPlayed = PlaySound(TEXT("sndLose.wav"), NULL, SND_ALIAS);
		}
		string result = GetUserInput(_user.s_iMiddleX);
		_user.UpdateInput(result);

		if (result == "2")
		{
			exit(0);
		}
		else
		{
			_user.UpdateOutput("Game restarting");
			ResetGame(_user, _opponent);
			RedrawEverything(_user, _opponent);
			m_bRestartGame = true;
		}
	}
}

//reset all objects to initial state to reset and restart game
void CGameControl::ResetGame(CParticipant& _user, CParticipant& _opponent)
{
	m_MyMenu.ChangeMenus(ECurrentMenu::MAIN);
	
	_user.RevertToDefault();
	_opponent.RevertToDefault();
	_user.UpdateInput(" ");
	_user.UpdateOutput(" ");
	_opponent.UpdateInput(" ");
	_opponent.UpdateOutput(" ");

	m_b2Player = false;
	m_eDifficulty = EOpponentDifficulty::EASY;
	m_iTurnCount = 0;
	m_bTurnToggle = false;
	m_eLastMessage = EMessageType::NO_MESSAGE;
	m_bDebugUsed = false;

	_user.UpdateStaticX(GetConsoleDimensions());
}