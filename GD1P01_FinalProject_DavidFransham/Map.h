/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Map.h
Description : Map class declaration file
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#pragma once

#include "MapPoint.h"
#include "Ship.h"

#ifndef __MAP_H__
#define __MAP_H__

class CMap
{
public:
	CMap();
	~CMap();
	
	bool GetShipHealthStatus(int _iShipToCheckIndex) const;
	bool CheckForShip(int _iX, int _iY) const;
	bool IsPlaced(int _iIndex) const;
	
	int GetNumShipsRemaining() const;
	int GetShipIndex(int _iX, int _iY) const;
	
	EMAPSTATE GetCurrentPointState(int _iX, int _iY) const;
	ESHIPTYPE GetShipType(int _iShipToCheckIndex) const;
			
	int Explore(int _iX, int _iY);
	
	bool SuccessfullyPlaceShip(int _iShipToPlaceIndex, int _iXstart, int _iYstart, bool _bVertical);
	void PlaceShip(int _iIndex, bool _togglePlace); 
	void ShootShip(int _iIndex);
	
	void ResetFleet();

private:
	CMapPoint m_MapGrid[10][10];
	CShip m_MyFleet[5];
	int m_iNumShips;

	void PopulateDefaultFleet(int _numShips);
};

#endif // !__MAP_H__

