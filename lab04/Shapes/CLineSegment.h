#pragma once
#include "IShape.h"
#include "CPoint.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, std::string outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	virtual std::string ToString() const override;
	virtual std::string GetOutlineColor() const override;

	CPoint GetStartPoint();
	CPoint GetEndPoint();

private:
	std::string m_outlineColor;
	CPoint m_startPoint;
	CPoint m_endPoint;
};