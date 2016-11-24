#pragma once

#include "stdafx.h"
#include "ISolidShape.h"
#include "ICanvasDrawable.h"
#include "CCanvas.h"
#include "CPoint.h"

class CRectangle : public ISolidShape, public ICanvasDrawable
{
public:
	CRectangle(CPoint leftTopPoint, double width, 
		double height, std::string fillColor, std::string outlineColor);
	~CRectangle() {};
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;

	std::string GetFillColor() const override;

	void Draw(CCanvas& canvas) const;

	CPoint GetLeftTop();
	CPoint GetRightBottom();
	double GetWidth();
	double GetHeight();

private:
	std::string m_fillColor;
	std::string m_outlineColor;

	CPoint m_leftTopPoint;
	double m_width;
	double m_height;
};