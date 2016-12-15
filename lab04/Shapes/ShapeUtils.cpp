#include "stdafx.h"
#include "ShapeUtils.h"
#include "CPoint.h"

double GetDistanceBeetwen(CPoint point1, CPoint point2)
{
	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}