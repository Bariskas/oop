#pragma once
#pragma once

#include "stdafx.h"
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3,
		std::string outlineColor, std::string fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;

	std::string GetFillColor() const override;

	void Draw(CCanvas& canvas) const;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	double GetSide1() const;
	double GetSide2() const;
	double GetSide3() const;

private:
	std::string m_fillColor;
	std::string m_outlineColor;

	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	double m_side1 = 0;
	double m_side2 = 0;
	double m_side3 = 0;
};