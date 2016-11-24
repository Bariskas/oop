#include "stdafx.h"
#include "CCircle.h"

using namespace std;

CCircle::CCircle(CPoint center, double radius, string outlineColor, string fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

double CCircle::GetArea() const
{
	return m_radius * m_radius * M_PI;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

string CCircle::ToString() const
{
	stringstream ss;
	ss << "Shape - line" << endl
		<< "center.x = " << m_center.x << endl
		<< "center.y = " << m_center.y << endl
		<< "radius = " << m_radius << endl
		<< "outlineColor = " << m_outlineColor << endl
		<< "fillColor = " << m_fillColor << endl;
	return ss.str();
}

string CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

string CCircle::GetFillColor() const
{
	return m_fillColor;
}

void CCircle::Draw(CCanvas & canvas) const
{
}

CPoint CCircle::GetCenter()
{
	return m_center;
}

double CCircle::GetRadius()
{
	return m_radius;
}
