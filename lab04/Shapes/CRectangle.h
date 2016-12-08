#pragma once

#include "stdafx.h"
#include "CPoint.h"
#include "CSolidShapeBase.h"

class CRectangle : public CSolidShapeBase
{
public:
	CRectangle(CPoint leftTopPoint, double width, 
		double height, std::string outlineColor, std::string fillColor);
	~CRectangle() {};
	double GetArea() const override;
	double GetPerimeter() const override;

	void Draw(CCanvas& canvas) const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
private:
	void AppendAdditionalInformation(std::stringstream& ss) const final;
	std::string GetShapeType() const final;
private:
	CPoint m_leftTopPoint;
	double m_width;
	double m_height;
};
