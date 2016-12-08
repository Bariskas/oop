#include "stdafx.h"
#include "CCircle.h"

using namespace std;

CCircle::CCircle(CPoint center, double radius, string outlineColor, string fillColor)
	: CSolidShapeBase(outlineColor, fillColor)
	, m_center(center)
	, m_radius(radius)
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

void CCircle::AppendAdditionalInformation(stringstream& ss) const
{
	ss <<
		"center: " << m_center.x << ":" << m_center.y 
	<< " radius: " << m_radius << endl;
}

void CCircle::Draw(CCanvas & canvas) const
{
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
