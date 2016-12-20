#pragma once
#include "stdafx.h"
#include "CPoint.h"

class ICanvas
{
public:
	virtual ~ICanvas() {};
	virtual void DrawLine(const CPoint from, const CPoint to, unsigned long lineColor) = 0;
	virtual void FillPolygon(const std::vector<CPoint> points, unsigned long fillColor) = 0;
	virtual void DrawCircle(const CPoint center, double radius, unsigned long lineColor) = 0;
	virtual void FillCircle(const CPoint center, double radius, unsigned long fillColor) = 0;
};