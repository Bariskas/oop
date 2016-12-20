#include "stdafx.h"
#include "CCanvas.h"

using namespace std;
using namespace sf;

CCanvas::CCanvas()
	: m_window(VideoMode(800, 600), "Shapes")
	, m_renderTexture()
{
	m_renderTexture.create(800, 600);
	m_renderTexture.clear();
}

void CCanvas::Display()
{
	m_renderTexture.display();
	sf::Sprite sprite(m_renderTexture.getTexture());
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		m_window.clear(sf::Color::White);
		m_window.draw(sprite);
		m_window.display();
	}
}

void CCanvas::DrawLine(CPoint from, CPoint to, unsigned long lineColor)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y)), Color(lineColor)),
		sf::Vertex(sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y)), Color(lineColor))
	};

	m_renderTexture.draw(line, 2, sf::LineStrip);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, unsigned long fillColor)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	size_t pointIndex = 0;
	for (auto& point : points)
	{
		polygon.setPoint(pointIndex++, sf::Vector2f(static_cast<float>(point.x), static_cast<float>(point.y)));
	}
	polygon.setFillColor(Color(fillColor));
	m_renderTexture.draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, unsigned long lineColor)
{
	auto fRadius = static_cast<float>(radius);
	sf::CircleShape circle(fRadius);
	circle.setOrigin(fRadius, fRadius);
	circle.setPosition(sf::Vector2f(static_cast<float>(center.x), static_cast<float>(center.y)));
	circle.setOutlineColor(sf::Color(lineColor));
	circle.setOutlineThickness(1);
	circle.setFillColor(sf::Color::Transparent);
	m_renderTexture.draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, unsigned long fillColor)
{
	auto fRadius = static_cast<float>(radius);
	sf::CircleShape circle(fRadius);
	circle.setOrigin(fRadius, fRadius);
	circle.setPosition(sf::Vector2f(static_cast<float>(center.x), static_cast<float>(center.y)));
	circle.setFillColor(sf::Color(fillColor));
	circle.setOutlineThickness(0);
	m_renderTexture.draw(circle);
}
