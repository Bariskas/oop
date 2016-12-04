#pragma once
#include "stdafx.h"
#include "CPoint.h"

class ICanvas
{
public:
	virtual ~ICanvas() {};
	virtual void DrawLine(CPoint from, CPoint to, unsigned long lineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> points, unsigned long fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, unsigned long lineColor) = 0;
	virtual void FillCircle(CPoint center, double radius, unsigned long fillColor) = 0;
};