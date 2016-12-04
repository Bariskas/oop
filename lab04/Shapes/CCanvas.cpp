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

void CCanvas::DrawLine(CPoint from, CPoint to, unsigned long lineColor)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(from.x, from.y), sf::Color::Green),// Color(lineColor)),
		sf::Vertex(sf::Vector2f(to.x, to.y), sf::Color::Green)// Color(lineColor))
	};

	m_window.draw(line, 2, sf::LineStrip);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, unsigned long fillColor)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	size_t pointIndex = 0;
	for (auto& point : points)
	{
		polygon.setPoint(pointIndex++, sf::Vector2f(point.x, point.y));
	}
	polygon.setFillColor(Color(fillColor));
	m_window.draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, unsigned long lineColor)
{
	sf::CircleShape circle(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(sf::Vector2f(center.x, center.y));
	circle.setOutlineColor(sf::Color(lineColor));
	circle.setFillColor(sf::Color::Transparent);
	m_window.draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, unsigned long fillColor)
{
	sf::CircleShape circle(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(sf::Vector2f(center.x, center.y));
	circle.setFillColor(sf::Color(fillColor));
	circle.setOutlineThickness(0);
	m_window.draw(circle);
}
