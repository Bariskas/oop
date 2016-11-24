#pragma once

#include "stdafx.h"
#include "ISolidShape.h"
#include "CPoint.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint center, double radius,
		std::string fillColor, std::string outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;

	std::string GetFillColor() const override;

	CPoint GetCenter();
	double GetRadius();

private:
	std::string m_fillColor;
	std::string m_outlineColor;

	CPoint m_center;
	double m_radius;
};