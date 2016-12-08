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

	void Draw(CCanvas& canvas) const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	void AppendAdditionalInformation(std::stringstream& ss) const final;
	std::string GetShapeType() const final;
private:
	CPoint m_startPoint;
	CPoint m_endPoint;
};
