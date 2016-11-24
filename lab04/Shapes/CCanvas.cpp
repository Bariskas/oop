#include "stdafx.h"
#include "CCanvas.h"

using namespace std;
using namespace sf;

CCanvas::CCanvas()
	: m_window(VideoMode(800, 600), "Window title")
{}

void CCanvas::Display()
{
	m_window.display();
}

void CCanvas::DrawLine(CPoint from, CPoint to, unsigned lineColor)
{
}

void CCanvas::FillPolygon(std::vector<CPoint> points, unsigned fillColor)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	int pointIndex = 0;
	for (auto& point : points)
	{
		polygon.setPoint(pointIndex++, sf::Vector2f(point.x, point.y));
	}
	polygon.setFillColor(Color(fillColor));
	m_window.draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, unsigned lineColor)
{
}

void CCanvas::FillCircle(CPoint center, double radius, unsigned fillColor)
{
}
