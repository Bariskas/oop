#include "stdafx.h"
#include "CRectangle.h"
#include "SfmlUtils.h"

using namespace std;

CRectangle::CRectangle(CPoint leftTopPoint, double width, 
	double height, string outlineColor, string fillColor)
	: CSolidShapeBase(outlineColor, fillColor)
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

void CRectangle::AppendAdditionalInformation(stringstream& ss) const
{
	ss << "width: " << m_width << "height: " << m_height << " left top point: " << m_leftTopPoint.x << ":" << m_leftTopPoint.y << endl;
}

std::string CRectangle::GetShapeType() const
{
	return "rectangle";
}

void CRectangle::Draw(CCanvas& canvas) const
{
	vector<CPoint> points{
		{ m_leftTopPoint.x, m_leftTopPoint.y },
		{ m_leftTopPoint.x + m_width, m_leftTopPoint.y },
		{ m_leftTopPoint.x + m_width, m_leftTopPoint.y + m_height },
		{ m_leftTopPoint.x, m_leftTopPoint.y + m_height }
	};
	canvas.FillPolygon(points, ColorFromStringToUnsigned(GetFillColor()));

	int recPointsNumber = points.size();
	unsigned long outlineColor = ColorFromStringToUnsigned(GetOutlineColor());
	for (int i = 0; i < recPointsNumber; ++i)
	{
		canvas.DrawLine(points[i], points[(i + 1) % recPointsNumber], outlineColor);
	}
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopPoint;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTopPoint.x + m_width, m_leftTopPoint.y + m_height);
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

