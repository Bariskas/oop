#include "stdafx.h"
#include "CTextFormCanvas.h"

using namespace std;
using namespace sf;

CTextFormCanvas::CTextFormCanvas(ostream & outputStream)
	: m_outputStream(outputStream)
{}

void CTextFormCanvas::Display()
{
	m_outputStream << "Displaying." << endl;
}

void CTextFormCanvas::DrawLine(const CPoint from, const CPoint to, unsigned long lineColor)
{
	m_outputStream << "Draw: line; from " << from.x << ":" << from.y << 
		" to " << to.x << ":" << to.y << endl;
}

void CTextFormCanvas::FillPolygon(const std::vector<CPoint> points, unsigned long fillColor)
{
	m_outputStream << "Draw: polygon filling; polygon coordinates";
	for (auto& point : points)
	{
		m_outputStream << " " << point.x << ":" << point.y;
	}
	m_outputStream << endl;
}

void CTextFormCanvas::DrawCircle(const CPoint center, double radius, unsigned long lineColor)
{
	m_outputStream << "Draw: circle outline; radius " << radius <<
		" center " << center.x << ":" << center.y << endl;
}

void CTextFormCanvas::FillCircle(const CPoint center, double radius, unsigned long fillColor)
{
	m_outputStream << "Draw: circle filling; radius " << radius <<
		" center " << center.x << ":" << center.y << endl;
}
