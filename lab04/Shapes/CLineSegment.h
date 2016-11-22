#pragma once
#include "IShape.h"
#include "CPoint.h"

class CLineSegment : public IShape
{
public:
	virtual double GetArea();
	virtual double GetPerimeter();
	virtual std::string ToString();
	virtual std::string GetOutlineColor();
public:
	CPoint GetStartPoint();
	CPoint GetEndPoint();
};