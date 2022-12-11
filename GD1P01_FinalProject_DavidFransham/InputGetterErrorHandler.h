/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : InputGetterErrorHandler.h
Description : Header file to collect the functions relating to getting input and checking errors
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "ScreenPrinter.h"
#include "Participant.h"

using std::string;

enum class EInputErrors
{
	NOT_NUMBER,
	NOT_INT,
	NOT_FLOAT,
	NOT_ON_MENU,
	NOT_VALID_FORMAT,
	INPUT_OUTSIDE_RANGE,
	INVALID_INPUT_TYPE,
	NO_INPUT_GIVEN,
};


int GetRandomNumber(int _iMaxRand, int _iMinRand = 0);

bool IsOnlyNumbers(const string& str, bool _incDecimal = false, bool _incNegative = false);

string GetUserInput(int _iX);

bool IsValidMapCoord(const string);

bool CheckCoordChar(const char _cCheck, int _iIndex);

void InvalidInput(EInputErrors ErrCode, CParticipant& _user);

