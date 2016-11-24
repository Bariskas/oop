#include "stdafx.h"
#include "CLineSegment.h"

using namespace std;

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, std::string outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0.;
}

double CLineSegment::GetPerimeter() const
{
	return 0.;
}

string CLineSegment::ToString() const
{
	stringstream ss;
	ss << "Shape - line" << endl
		<< "startPoint.x = " << m_startPoint.x << endl
		<< "startPoint.y = " << m_startPoint.y << endl
		<< "endPoint.x = " << m_endPoint.x << endl
		<< "endPoint.y = " << m_endPoint.y << endl
		<< "outlineColor = " << m_outlineColor << endl;
	return ss.str();
}

std::string CLineSegment::GetOutlineColor() const
{
	return std::string();
}

void CLineSegment::Draw(CCanvas & canvas) const
{
}

CPoint CLineSegment::GetStartPoint()
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint()
{
	return m_endPoint;
}
