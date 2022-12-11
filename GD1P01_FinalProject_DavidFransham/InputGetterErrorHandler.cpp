/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : InputGetterErrorHandler.cpp
Description : Implementatoin file for collected functions relating to getting input and checking errors 
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#include "InputGetterErrorHandler.h"

//returns a (pseudo)random number between user's chosen minimum and maximum values
int GetRandomNumber(int _iMaxRand, int _iMinRand)
{
	return _iMinRand + rand() % ((_iMaxRand - _iMinRand) + 1);			// TF: Pseudo Random Number
}

//Function checks string contains only numbers and optional initial negative sign and/or optional single decimal place
bool IsOnlyNumbers(const string& str, bool _bIncDecimal, bool _bIncNegative)
{
	bool decimalUsed = false;
	bool negativeUsed = true;

	if (_bIncNegative && (str[0] == '-'))
	{
		negativeUsed = false;
	}

	for (char const& c : str)
	{
		if (std::isdigit(c) == 0)
		{
			if (_bIncNegative && (c == '-'))
			{
				if (negativeUsed)
				{
					return false;
				}
				else
				{
					negativeUsed = true;
				}
			}
			else if (_bIncDecimal && (c == '.'))
			{
				if (decimalUsed)
				{
					return false;
				}
				else
				{
					decimalUsed = true;
				}
			}
			else 
			{
				return false;
			}
		}
	}
	
	return true;
}

//gets user input via getline, checks if it is empty and returns string for further use
string GetUserInput(int _iX)
{
	COORD cursor = GetCursorPos();
	int y = cursor.Y;

	SetRgb(EColour::COLOUR_CYAN_ON_BLACK);
	string tempStr;
	std::getline(std::cin, tempStr);
	
	GoToXY(_iX, y + 1);

	if (tempStr.empty())
	{
		return "NO_INPUT_GIVEN";
	}
	SetRgb(EColour::COLOUR_MAGENTA_ON_BLACK);
	return tempStr;
}

//checks input string to see if it is A-J or a-j following by 1-10
bool IsValidMapCoord(const string _sInput)
{
	int len = static_cast<int>(_sInput.length());
	if (len == 2 || len == 3)
	{
		char first = _sInput[0];
		char second = _sInput[1];
		
		if (len == 2)
		{
			return (CheckCoordChar(first, 0) && CheckCoordChar(second, 1));
		}
		else if (len == 3)
		{
			char third = _sInput[2];
			return (CheckCoordChar(first, 0) && CheckCoordChar(second, 2) && CheckCoordChar(third,3));
		}
	}
	return false;
}

//checks characters in string based on index value
bool CheckCoordChar(const char _cCheck, int _iIndex)
{
	switch (_iIndex)
	{
	case 0: //first character in string - checks for a-j both upper and lower cases
		return (((_cCheck >= 65) && (_cCheck <= 74)) || ((_cCheck >= 97) && (_cCheck <= 106)));
		break;
	case 1: //second character in 2char string - checks for 1-9
		return ((_cCheck >= 49) && (_cCheck <= 74));
		break;
	case 2: //second character in 3char string - checks for 1
		return (_cCheck == '1');
		break;
	case 3: //third character in 3char string - checks for 0
		return (_cCheck == '0');
		break;
	default:
		return false;
		break;
	}
}

//prints relevant error messages after input validation during code
void InvalidInput(EInputErrors ErrCode, CParticipant& _user)
{

	SetRgb(EColour::COLOUR_MAGENTA_ON_BLACK);
	switch (ErrCode)
	{
	case EInputErrors::NOT_NUMBER:
		_user.UpdateOutput("--Enter just a number--");
		break;
	case EInputErrors::NOT_INT:
		_user.UpdateOutput("--Enter an integer--");
		break;
	case EInputErrors::NOT_FLOAT:
		_user.UpdateOutput("--Enter a valid number--");
		break;
	case EInputErrors::NOT_ON_MENU:
		_user.UpdateOutput("--Number not on menu--");
		break;
	case EInputErrors::NOT_VALID_FORMAT:
		_user.UpdateOutput("--Input format not recognised--");
		break;
	case EInputErrors::INPUT_OUTSIDE_RANGE:
		_user.UpdateOutput("--Input out of valid range--");
		break;
	case EInputErrors::INVALID_INPUT_TYPE:
		_user.UpdateOutput("--Input not valid type--");
		break;
	case EInputErrors::NO_INPUT_GIVEN:
		_user.UpdateOutput("--Enter something first--");
		break;
	default: //shouldn't be called, but in case of changes in future this will be picked up.
		std::cout << "\n  Something unexpected happened.  See developer for more info.\n\n  ";
		break;
	}
}