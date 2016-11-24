#pragma once

#include "stdafx.h"
#include "CPoint.h"

using namespace std;

inline double GetDistanceBeetwen(CPoint point1, CPoint point2)
{
	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}