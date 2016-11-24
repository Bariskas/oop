#pragma once

#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas();
	void DrawLine(CPoint from, CPoint to, unsigned lineColor) override;
	void FillPolygon(std::vector<CPoint> points, unsigned fillColor) override;
	void DrawCircle(CPoint center, double radius, unsigned lineColor) override;
	void FillCircle(CPoint center, double radius, unsigned fillColor) override;
private:
	sf::RenderWindow m_window;
};