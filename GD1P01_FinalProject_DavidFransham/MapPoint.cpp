/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : MapPoint.cpp
Description : MapPoint class definition file - creates points for the map to run battleship game
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#include "MapPoint.h"

//Default Constructor
CMapPoint::CMapPoint()
{
	m_iShipPresentIndex = -1;
	m_bShipHere = false;
	m_eCurrentState = EMAPSTATE::UNEXPLORED;
}

//Parameterised constructor
CMapPoint::CMapPoint(int _ShipIndex)
{
	m_iShipPresentIndex = _ShipIndex;
	m_bShipHere = true;
	m_eCurrentState = EMAPSTATE::UNEXPLORED;
}

//Copy Constructor
CMapPoint::CMapPoint(const CMapPoint& _MPobj)		 // TF: Copy Constructor
{
	m_iShipPresentIndex = _MPobj.m_iShipPresentIndex;
	m_bShipHere = _MPobj.m_bShipHere;
	m_eCurrentState = _MPobj.m_eCurrentState;
}

//Destructor
CMapPoint::~CMapPoint()
{
	
}

//resets map point to initial state for resetting game/restarting ship placement
void CMapPoint::RevertToDefault()
{
	m_iShipPresentIndex = -1;
	m_bShipHere = false;
	m_eCurrentState = EMAPSTATE::UNEXPLORED;
}

//Shot fired at this location - change state to hit or miss appropriately
int CMapPoint::Explore()
{
	if (m_eCurrentState == EMAPSTATE::UNEXPLORED)
	{
		if (m_bShipHere)
		{
			m_eCurrentState = EMAPSTATE::EXPLORED_HIT;
		}
		else
		{
			m_eCurrentState = EMAPSTATE::EXPLORED_MISS;
		}
	}
	else
	{
		m_eCurrentState = EMAPSTATE::INVALID_EMAPSTATE; //shouldn't get called but included as a default error handler
	}
	return m_iShipPresentIndex;
}

//returns whether ship is present or not
bool CMapPoint::IsShipHere() const
{
	return m_bShipHere;
}

//returns index of ship present at this location
int CMapPoint::GetShipIndex() const
{
	return m_iShipPresentIndex;
}

//change boolean to indicate ship is present, add pointer to ship object
void CMapPoint::AddShip(int _iShipIndex)
{
	m_iShipPresentIndex = _iShipIndex;
	m_bShipHere = true;
}

//remove ship from this point
void CMapPoint::RemoveShip()
{
	m_iShipPresentIndex = -1;
	m_bShipHere = false;
}

//returns the current map state of this location
EMAPSTATE CMapPoint::GetCurrentState() const
{
	return m_eCurrentState;
}