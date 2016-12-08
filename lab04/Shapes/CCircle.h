#pragma once

#include "stdafx.h"
#include "CPoint.h"
#include "CSolidShapeBase.h"

class CCircle : public CSolidShapeBase
{
public:
	CCircle(CPoint center, double radius,
		std::string fillColor, std::string outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;

	void Draw(CCanvas& canvas) const override;

	CPoint GetCenter() const;
	double GetRadius() const;
private:
	void AppendAdditionalInformation(std::stringstream& ss) const final;
private:
	CPoint m_center;
	double m_radius;
};
