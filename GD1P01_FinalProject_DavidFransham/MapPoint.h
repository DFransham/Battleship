/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : MapPoint.h
Description : MapPoint class declaration file
Author : David Fransham
Mail : david.fransham@mds.ac.nz
**************************************************************************/

#pragma once

#ifndef __MAPPOINT_H__
#define __MAPPOINT_H__

#include "Ship.h"
#include <iostream>

enum class EMAPSTATE
{
	INVALID_EMAPSTATE = 0,
	UNEXPLORED,
	EXPLORED_MISS,
	EXPLORED_HIT,
	MAX_EMAPSTATE = 4
};

class CMapPoint
{
public:
	CMapPoint();
	CMapPoint(int _ShipIndex);
	CMapPoint(const CMapPoint&);
	~CMapPoint();

	// "Get" functions
	bool IsShipHere() const;
	int GetShipIndex() const;
	EMAPSTATE GetCurrentState() const;

	//"set" functions
	void AddShip(int _iShipIndex);
	void RemoveShip();
	int Explore();
	void RevertToDefault();

private:
	bool m_bShipHere;
	EMAPSTATE m_eCurrentState;
	int m_iShipPresentIndex;
};

#endif // !__MAPPOINT_H__
