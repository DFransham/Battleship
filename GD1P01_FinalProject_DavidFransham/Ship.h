/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Ship.h
Description : Ship class declaration file
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#pragma once

#ifndef __SHIP_H__
#define __SHIP_H__

enum class ESHIPTYPE
{
	INVALID_ESHIPTYPE = 0,
	PATROLBOAT = 1,
	SUBMARINE = 2,
	DESTROYER = 3,
	BATTLESHIP = 4,
	AIRCRAFTCARRIER = 5,
	MAX_ESHIPTYPE
};

class CShip
{
	//CMap is friend: it is owns the ships needs to be able to modify them
	friend class CMap; 
public:
	CShip();
	CShip(ESHIPTYPE);
	~CShip();

	void ReduceHealth();
	void SetShipType(ESHIPTYPE);

	int GetHealth() const;
	ESHIPTYPE GetShipType() const;

private:
	int m_iHealth;
	bool m_bAlreadyPlaced;
	ESHIPTYPE m_eShipClass;

	void SetShipHealth(ESHIPTYPE);
	void PlaceShip(bool _togglePlace);
	bool GetPlacedStatus() const;
	void RevertToDefault();
};

#endif // !__SHIP_H__