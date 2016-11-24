#pragma once
#include "stdafx.h"
#include "CPoint.h"

class ICanvas
{
public:
	virtual ~ICanvas() {};
	virtual void DrawLine(CPoint from, CPoint to, unsigned lineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> points, unsigned fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, unsigned lineColor) = 0;
	virtual void FillCircle(CPoint center, double radius, unsigned fillColor) = 0;
};