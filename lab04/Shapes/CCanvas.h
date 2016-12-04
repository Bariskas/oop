#pragma once

#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas();
	void Display();
	void DrawLine(CPoint from, CPoint to, unsigned long lineColor) override;
	void FillPolygon(std::vector<CPoint> points, unsigned long fillColor) override;
	void DrawCircle(CPoint center, double radius, unsigned long lineColor) override;
	void FillCircle(CPoint center, double radius, unsigned long fillColor) override;
private:
	sf::RenderWindow m_window;
};