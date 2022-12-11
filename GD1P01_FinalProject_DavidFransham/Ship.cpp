/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Ship.cpp
Description : Ship class implementation file - creating ships to use in Battleship game
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#include "Ship.h"

//Default constructor
CShip::CShip()
{
	m_eShipClass = ESHIPTYPE::INVALID_ESHIPTYPE;
	m_iHealth = 1;
	m_bAlreadyPlaced = false;
}

//Constructor
CShip::CShip(ESHIPTYPE _eShipType)
{
	m_eShipClass = _eShipType;
	SetShipHealth(m_eShipClass);
	m_bAlreadyPlaced = false;
}

//Destructor
CShip::~CShip()
{

}

//Reduces health of ship on hit
void CShip::ReduceHealth()
{
	if (m_iHealth > 0)
	{
		m_iHealth--;
	}
}

//returns current health of ship
int CShip::GetHealth() const
{
	return m_iHealth;
}

//Sets ship type if it was created by default constructor
void CShip::SetShipType(ESHIPTYPE _eShipType)
{
	m_eShipClass = _eShipType;
	SetShipHealth(_eShipType);
}

//returns type of ship
ESHIPTYPE CShip::GetShipType() const
{
	return m_eShipClass;
}

//used to set max health of ship when setting ship type
void CShip::SetShipHealth(ESHIPTYPE _eShipType)
{
	switch (_eShipType) //set health value for newly created ship
	{
	case ESHIPTYPE::INVALID_ESHIPTYPE:
		m_iHealth = 1;
		break;
	case ESHIPTYPE::PATROLBOAT:
		m_iHealth = 2;
		break;
	case ESHIPTYPE::SUBMARINE: //fall through
	case ESHIPTYPE::DESTROYER:
		m_iHealth = 3;
		break;
	case ESHIPTYPE::BATTLESHIP:
		m_iHealth = 4;
		break;
	case ESHIPTYPE::AIRCRAFTCARRIER:
		m_iHealth = 5;
		break;
	case ESHIPTYPE::MAX_ESHIPTYPE:
		m_iHealth = 1;
		break;
	default:
		break;
	}
}

//updates status of ship as Placed or NotPlace based on boolean input
void CShip::PlaceShip(bool _togglePlace)
{
	m_bAlreadyPlaced = _togglePlace;
}

//returns value identifying if ship is placed on map or not
bool CShip::GetPlacedStatus() const
{
	return m_bAlreadyPlaced;
}

//resets ship to initial status for resetting game
void CShip::RevertToDefault()
{
	SetShipHealth(m_eShipClass);
	m_bAlreadyPlaced = false;
}