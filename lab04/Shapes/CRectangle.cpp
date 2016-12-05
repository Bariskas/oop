#include "stdafx.h"
#include "CRectangle.h"
#include "SfmlUtils.h"

using namespace std;

CRectangle::CRectangle(CPoint leftTopPoint, double width, 
	double height, string outlineColor, string fillColor)
	: m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
	, m_leftTopPoint(leftTopPoint)
	, m_width(width)
	, m_height(height)
{}

double CRectangle::GetArea() const
{
	return m_height * m_width;
}

double CRectangle::GetPerimeter() const
{
	return 2 * m_height + 2 * m_width;
}

string CRectangle::ToString() const
{
	stringstream ss;
	ss << "Shape - rectangle" << endl
		<< "area = " << GetArea() << endl
		<< "perimeter = " << GetPerimeter() << endl
		<< "leftTopPoint.x = " << m_leftTopPoint.x << endl
		<< "leftTopPoint.y = " << m_leftTopPoint.y << endl
		<< "width = " << m_width << endl
		<< "height = " << m_height << endl
		<< "outlineColor = " << m_outlineColor << endl
		<< "fillColor = " << m_fillColor << endl;
	return ss.str();
}

string CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

string CRectangle::GetFillColor() const
{
	return m_fillColor;
}

void CRectangle::Draw(CCanvas& canvas) const
{
	vector<CPoint> points{
		{ m_leftTopPoint.x, m_leftTopPoint.y },
		{ m_leftTopPoint.x, m_leftTopPoint.y + m_height },
		{ m_leftTopPoint.x + m_width, m_leftTopPoint.y + m_height },
		{ m_leftTopPoint.x + m_width, m_leftTopPoint.y }
	};
	canvas.FillPolygon(points, sf::Color::Blue.toInteger());//ColorFromStringToUnsigned(m_fillColor));

	int recPointsNumber = points.size();
	unsigned long outlineColor = ColorFromStringToUnsigned(m_outlineColor);
	for (int i = 0; i < recPointsNumber; ++i)
	{
		canvas.DrawLine(points[i], points[(i + 1) % recPointsNumber], outlineColor);
	}
}

CPoint CRectangle::GetLeftTop()
{
	return m_leftTopPoint;
}

CPoint CRectangle::GetRightBottom()
{
	return CPoint(m_leftTopPoint.x + m_width, m_leftTopPoint.y + m_height);
}

double CRectangle::GetWidth()
{
	return m_width;
}

double CRectangle::GetHeight()
{
	return m_height;
}

