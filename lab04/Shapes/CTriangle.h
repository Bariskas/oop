#pragma once

#include "stdafx.h"
#include "CPoint.h"
#include "CSolidShapeBase.h"

class CTriangle : public CSolidShapeBase
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3,
		std::string outlineColor, std::string fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;

	void Draw(CCanvas& canvas) const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	void AppendAdditionalInformation(std::stringstream& ss) const final;
	std::string GetShapeType() const final;
	double GetSide1() const;
	double GetSide2() const;
	double GetSide3() const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	double m_side1 = 0;
	double m_side2 = 0;
	double m_side3 = 0;
};
