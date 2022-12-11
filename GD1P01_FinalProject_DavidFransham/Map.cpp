/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Map.cpp
Description : Map class definition file - to hold a 10x10 grid with states for operation of battleship game
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#include "Map.h"
#include <iostream>

//Default Constructor
CMap::CMap()
{
	m_iNumShips = 5;

	PopulateDefaultFleet(m_iNumShips);
};

//Destructor
CMap::~CMap()
{
	
}

//creates and stores 5 ship objects of various sizes for default fleet
void CMap::PopulateDefaultFleet(int _numShips)
{
	m_MyFleet[0] = CShip::CShip(ESHIPTYPE::AIRCRAFTCARRIER);
	m_MyFleet[1] = CShip::CShip(ESHIPTYPE::BATTLESHIP);
	m_MyFleet[2] = CShip::CShip(ESHIPTYPE::DESTROYER);
	m_MyFleet[3] = CShip::CShip(ESHIPTYPE::SUBMARINE);
	m_MyFleet[4] = CShip::CShip(ESHIPTYPE::PATROLBOAT);
}

//attempts to place the ship on the map without intersecting other ships or going out of bounds
//reports back success or failure with a boolean
bool CMap::SuccessfullyPlaceShip(int _iShipToPlaceIndex, int _iXstart, int _iYstart, bool _bVertical)
{
	int len = m_MyFleet[_iShipToPlaceIndex].GetHealth();
	
	if (_bVertical)
	{
		if ((_iXstart + len) > 10)
		{
			return false;
		}
		else
		{
			for (int i = _iXstart; i < (_iXstart + len); i++)
			{
				if (m_MapGrid[i][_iYstart].IsShipHere())
				{
					return false;
				}
			}
		}
	}
	else
	{
		if ((_iYstart + len) > 10)
		{
			return false;
		}
		else
		{
			for (int i = _iYstart; i < (_iYstart + len); i++)
			{
				if (m_MapGrid[_iXstart][i].IsShipHere())
				{
					return false;
				}
			}
		}
	}


	if (_bVertical)
	{
		for (int i = _iXstart; i < (_iXstart + len); i++)
		{
			m_MapGrid[i][_iYstart].AddShip(_iShipToPlaceIndex);
		}
	}
	else
	{
		for (int i = _iYstart; i < (_iYstart + len); i++)
		{
			m_MapGrid[_iXstart][i].AddShip(_iShipToPlaceIndex);
		}
	}
	PlaceShip(_iShipToPlaceIndex, true);

	return true;
}

//returns the ship type of a ship with given index number
ESHIPTYPE CMap::GetShipType(int _iShipToCheckIndex) const
{
	return (m_MyFleet[_iShipToCheckIndex].GetShipType());
}

//returns the index number for a ship at the given location.  Returns -1 if no ship present
int CMap::GetShipIndex(int _iX, int _iY) const
{
	if (CheckForShip(_iX, _iY))
	{
		return m_MapGrid[_iX][_iY].GetShipIndex();
	}
	else
	{
		return -1;
	}
	
}

//returns the current map state of the point at a given location
EMAPSTATE CMap::GetCurrentPointState(int _iX, int _iY) const
{
	return m_MapGrid[_iX][_iY].GetCurrentState();
}

//changes map state at given coordinates to reflect hit or miss
int CMap::Explore(int _iX, int _iY)
{
	return m_MapGrid[_iX][_iY].Explore();
}

//returns the number of ships that haven't been sunk yet.
int CMap::GetNumShipsRemaining() const
{
	return m_iNumShips;
}

//returns true if ship with given index still has health greater than 0
bool CMap::GetShipHealthStatus(int _iShipToCheckIndex) const
{
	return (m_MyFleet[_iShipToCheckIndex].GetHealth() > 0);
}

//returns true if there is a ship at the given location.=
bool CMap::CheckForShip(int _iX, int _iY) const
{
	return m_MapGrid[_iX][_iY].IsShipHere();
}

//reduces health of ship with given index.  If that brings the ship to 0 health, reduces life counter by 1
void CMap::ShootShip(int _iIndex)
{
	m_MyFleet[_iIndex].ReduceHealth();
	if (m_MyFleet[_iIndex].GetHealth() == 0)
	{
		m_iNumShips--;
	}
}

//calls map function to update status of ship with given index number
void CMap::PlaceShip(int _iIndex, bool _togglePlace)
{
	m_MyFleet[_iIndex].PlaceShip(_togglePlace);
}

//reports back status of whether ship with given indes = p or not
bool CMap::IsPlaced(int _iIndex) const
{
	return  m_MyFleet[_iIndex].GetPlacedStatus();
}

//resets map grid and fleet to initial values for restarting the game.
void CMap::ResetFleet()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_MapGrid[i][j].RevertToDefault();
		}
	}
	for (int j = 0; j < 5; j++)
	{
		m_MyFleet[j].RevertToDefault();
	}
}