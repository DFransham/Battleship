/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Participant.h
Description : Participant class declaration file
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#pragma once
#include "Map.h"
#include <memory>
#include <iostream>

using std::string;
enum class EMessageType;
int GetRandomNumber(int _iMaxRand, int _iMinRand);

enum class EShotResult
{
	HIT,
	HIT_AND_SUNK,
	MISS,
	OPPONENT_DEFEATED,
	INVALID_SHOT,
};

#ifndef __PARTICIPANT_H__
#define __PARTICIPANT_H__

class CParticipant
{
public:
	//static variables for overall game management
	const static int s_iTopMapY = 3;
	const static int s_iLeftMapX = 2;
	const static int s_iBottomMapY = s_iTopMapY + 18;
	const static int s_iLeftShipsX = s_iLeftMapX + 28;
	const static int s_iMenuY = 8;
	const static int s_iOutputY = s_iMenuY + 9;

	static int s_iRightShipsX;
	static int s_iRightMapX;
	static int s_iMiddleX;

	static bool s_bDebugOn;

	CParticipant(CMap _myMap);
	~CParticipant();

	//"Get" functions
	ESHIPTYPE GetShipClass(int _shipIndex) const;
	EMAPSTATE GetMapState(int _iX, int _iY) const;
	string GetLastInput() const;
	string GetLastOutput() const;

	//bool GetReadyStatus() const;
	bool GetHumanStatus() const;
	int GetShipIndex(int _iX, int _iY) const;
	bool CheckForShip(int _iX, int _iY) const;
	bool IsStillAlive() const;
	bool IsShipAlive(int _shipIndex) const;
	
	//"Set" functions
	void UpdateOutput(string _sNewOutput);
	void UpdateInput(string _sNewInput);
	void SetReadyStatus(bool _bReady);
	void SetHumanStatus(bool _isHuman);
	void UpdateStaticX(int _iScreenWidth);

	bool AttemptToPlaceShip(int _iShipToPlaceIndex, int _iXstart, int _iYstart, bool _bVertical);
	bool IsShipPlaced(int _iIndex);

	EShotResult MakeShot(int _iX, int _iY);
	void GenerateAIPositions();

	void ResetFleet();
	void RevertToDefault();

private:
	CMap m_MyMap;

	bool m_bReadyToPlay;
	bool m_bHumanPlayer;
	bool m_bStillFighting;

	string m_sLastInput;
	string m_sLastOutput;

	bool CheckShotValid(int _iX, int _iY) const;
	void PlaceShip(int _iIndex, bool _togglePlace);
};

#endif // !__PARTICIPANT_H__
