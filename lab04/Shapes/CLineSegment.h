#pragma once
#include "IShape.h"
#include "CPoint.h"
#include "CShapeBase.h"

class CLineSegment : public CShapeBase
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint,
		std::string outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	virtual std::string GetOutlineColor() const override;

	void Draw(CCanvas& canvas) const;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	std::string GetAdditionalInformation();

	std::string m_outlineColor;
	CPoint m_startPoint;
	CPoint m_endPoint;
};
