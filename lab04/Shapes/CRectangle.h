#pragma once

#include "ISolidShape.h"
#include "CPoint.h"

class CRectangle : public ISolidShape
{
public:
	virtual double GetArea();
	virtual double GetPerimeter();
	virtual std::string ToString();
	virtual std::string GetOutlineColor();

	virtual std::string GetFillColor();

	CPoint GetLeftTop();
	CPoint GetRightBottom();
	double GetWidth();
	double GetHeight();

private:

private:
	CPoint m_leftTopPoint;
	double m_width;
	double m_height;
};