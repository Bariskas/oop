#include "stdafx.h"
#include "CLineSegment.h"
#include "SfmlUtils.h"

using namespace std;

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, std::string outlineColor)
	: CShapeBase(outlineColor)
	, m_startPoint(startPoint)
	, m_endPoint(endPoint)
{
}

double CLineSegment::GetArea() const
{
	return 0.;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow(m_endPoint.x - m_startPoint.x, 2) + pow(m_endPoint.y - m_startPoint.y, 2));
}

void CLineSegment::Draw(CCanvas & canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, ColorFromStringToUnsigned(m_outlineColor));
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::AppendAdditionalInformation(stringstream& ss) const
{
	ss << "from: " << m_startPoint.x << ":" << m_startPoint.y << " to: " << m_endPoint.x << ":" << m_endPoint.y << endl;
}

std::string CLineSegment::GetShapeType() const
{
	return "line";
}
