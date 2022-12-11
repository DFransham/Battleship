/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : GameControl.h
Description : GameControl class declaration file
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/
#pragma once

#include <memory>
#include <iostream>
#include "Map.h"
#include "Participant.h"
#include "Menu.h"
#include "ScreenPrinter.h"
#include "InputGetterErrorHandler.h"
#include <Windows.h>

#ifndef __GAMECONTROL_H__
#define __GAMECONTROL_H__

enum class EOpponentDifficulty
{
	EASY,
	MEDIUM,
	HARD,
};

enum class EPrintPosition
{
	TOP_LEFT,
	TOP_MIDDLE,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_MIDDLE,
	BOTTOM_RIGHT,
};

class CGameControl										// TF: Class
{
public:													// TF: Access Specifier
	CGameControl(CMap& mapOne, CMap& mapTwo);			// TF: Reference
	~CGameControl();

	CParticipant m_PlayerOne;
	CParticipant m_PlayerTwo;

	bool GameSetup(CParticipant& _user, CParticipant& _opponent);

	int GetScreenWidth() const;
	int GetScreenHeight() const;

private:
	CMenu m_MyMenu;
	EOpponentDifficulty m_eDifficulty;
	EMessageType m_eLastMessage;

	int m_iWidth;
	int m_iHeight;
	int m_iTurnCount;

	bool m_b2Player;
	bool m_bDebugUsed;
	bool m_bTurnToggle;
	bool m_bRestartGame;
	bool m_bSoundOn;

	void PrepareToPlaceShips(CParticipant& _user, CParticipant& _opponent);
	void PlaceSingleShip(CParticipant& _user, CParticipant& _opponent, int _iShipIndex);
	bool PlaceFleet(CParticipant& _user, CParticipant& _opponent);
	void MainGameLoop(CParticipant& _user, CParticipant& _opponent);
	void TakeTurn(CParticipant& _user, CParticipant& _opponent);
	void ToggleTurn();

	void ResetGame(CParticipant& _user, CParticipant& _opponent);

	int GetTurnCount() const;
	bool GetDebugMode(CParticipant& _user) const;		// TF: Constant
	bool Get2PlayerMode() const;
	bool GetSoundStatus() const;
	EOpponentDifficulty GetDifficulty() const;

	void SetScreenDimensions(int, int);
	void SetDebugMode(bool);
	void Set2PlayerMode(CParticipant& _user, bool _bIsHuman);
	void SetDifficulty(EOpponentDifficulty);
	void IncrementTurnCounter();
	void TurnSoundOnOff();

	void PrintScreenInfo();
	void RedrawEverything(CParticipant& _user, CParticipant& _opponent, bool _bGameStarted = true);		// TF: Default Parameter
	void DisplayPreviousTurnInfo(CParticipant& _user, CParticipant& _opponent);
};

#endif // !__GAMECONTROL_H__