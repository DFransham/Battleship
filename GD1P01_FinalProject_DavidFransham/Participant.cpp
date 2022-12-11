/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Participant.cpp
Description : Participant class definition file - to create an actor in the battleship game
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#include "Participant.h"

//Parameterised Constructor - no default constructor as participant always needs to be associated with a map object
CParticipant::CParticipant(CMap _myMap)
{
	m_MyMap = _myMap;
	m_bReadyToPlay = false;
	m_bHumanPlayer = true;
	m_bStillFighting = true;

}

//Destructor
CParticipant::~CParticipant()
{

}

//checks that a shot at position _iX, _iY has not already been made
bool CParticipant::CheckShotValid(int _iX, int _iY) const
{
	switch (m_MyMap.GetCurrentPointState(_iX, _iY))
	{
	case EMAPSTATE::EXPLORED_HIT:  //fall through
	case EMAPSTATE::EXPLORED_MISS:
		break;
	case EMAPSTATE::UNEXPLORED:
		return true;
	default:
		std::cout << "Something Unexpected happened";
		break;
	}
	return false;
}

//take shot and return appropriate information regarding miss, hit, game over
EShotResult CParticipant::MakeShot(int _iX, int _iY)
{
	if (!CheckShotValid(_iX, _iY))
	{
		return EShotResult::INVALID_SHOT;
	}
	else
	{
		int shipPresentIndex = m_MyMap.Explore(_iX, _iY);
		if (shipPresentIndex < 0)
		{
			return EShotResult::MISS;
		}
		else
		{
			m_MyMap.ShootShip(shipPresentIndex);
			if (IsShipAlive(shipPresentIndex))
			{
				return EShotResult::HIT;
			}
			else
			{
				if (m_MyMap.GetNumShipsRemaining() > 0)
				{
					return EShotResult::HIT_AND_SUNK;
				}
				else
				{
					m_bStillFighting = false;
					return EShotResult::OPPONENT_DEFEATED;
				}
			}
		}
	}
}

//returns ship class of ship with given index number
ESHIPTYPE CParticipant::GetShipClass(int _shipIndex) const
{
	return (m_MyMap.GetShipType(_shipIndex));
}

//queries ship object with given index number for health status
bool CParticipant::IsShipAlive(int _shipIndex) const
{
	return (m_MyMap.GetShipHealthStatus(_shipIndex));
}

//checks map object at given coordinates for the presence of a ship object
bool CParticipant::CheckForShip(int _iX, int _iY) const
{
	return m_MyMap.CheckForShip(_iX, _iY);
}

//checks map object for mappoint object state 
EMAPSTATE CParticipant::GetMapState(int _iX, int _iY) const
{
	return m_MyMap.GetCurrentPointState(_iX, _iY);
}

//returns ship index from map object at given coordinates
int CParticipant::GetShipIndex(int _iX, int _iY) const
{
	return m_MyMap.GetShipIndex(_iX, _iY);
}

//updates static variables relating to screen width - dependent on being set by other functions
void CParticipant::UpdateStaticX(int _iScreenWidth)
{
	s_iRightMapX = _iScreenWidth - 29;
	s_iRightShipsX = s_iRightMapX - 20;
	s_iMiddleX = _iScreenWidth / 2;
}

//returns last value input by user
string CParticipant::GetLastInput() const
{
	return m_sLastInput;
}

//updates last value input by user
void CParticipant::UpdateInput(string _sNewInput)
{
	m_sLastInput = _sNewInput;
}

//returns last output string to keep user informed after redrawing
string CParticipant::GetLastOutput() const
{
	return m_sLastOutput;
}

//updates last output string for keeping user informed
void CParticipant::UpdateOutput(string _sNewOutput)
{
	m_sLastOutput = _sNewOutput;
}

//generates random numbers and positions ships, keeps trying until valid options are chosen
void CParticipant::GenerateAIPositions()
{
	bool placed = false;
	for (int i = 0; i < 5; i++)
	{
		while (!placed)
		{
			int x = GetRandomNumber(10,1);
			int y = GetRandomNumber(10,1);
			int dir = GetRandomNumber(1,0);
			placed = m_MyMap.SuccessfullyPlaceShip(i, x, y, dir);
		}
		placed = false;
	}
	m_bReadyToPlay = true;
}

//returned whether user is a human or AI user
bool CParticipant::GetHumanStatus() const
{
	return m_bHumanPlayer;
}

//updates bool to indicate whether player is human or AI
void CParticipant::SetHumanStatus(bool _isHuman)
{
	m_bHumanPlayer = _isHuman;
}

//update status that player is ready to begin
void CParticipant::SetReadyStatus(bool _bReady)
{
	m_bReadyToPlay = _bReady;
}

//accepts ship index, x/y coords, bool for vertical/horizontal placement.  Attempts to place ship, reports success or failure
bool CParticipant::AttemptToPlaceShip(int _iShipToPlaceIndex, int _iXstart, int _iYstart, bool _bVertical)
{
	return m_MyMap.SuccessfullyPlaceShip( _iShipToPlaceIndex,  _iXstart,  _iYstart,  _bVertical);
}

//Updates map object with ship index number present
void CParticipant::PlaceShip(int _iIndex, bool _togglePlace)
{
	m_MyMap.PlaceShip(_iIndex, _togglePlace);
}

//checks map object for whether a given ship index has been placed yet
bool CParticipant::IsShipPlaced(int _iIndex)
{
	return  m_MyMap.IsPlaced(_iIndex);
}

//updates map object by resetting placed status of all ships to 0, and resets all map points to initial status
void CParticipant::ResetFleet()
{
	for (int i = 0; i < 5; i++)
	{
		PlaceShip(i, false);
	}
	m_MyMap.ResetFleet();
}

//resets participant object to initial state and then calls reset fleet function to reset game
void CParticipant::RevertToDefault()
{
	m_bReadyToPlay = false;
	m_bHumanPlayer = true;
	m_bStillFighting = true;
	ResetFleet();
}

//reports on whether player has any ships remaining or has been defeated
bool CParticipant::IsStillAlive() const
{
	return m_bStillFighting;
}