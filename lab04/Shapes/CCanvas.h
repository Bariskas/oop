#pragma once

#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas();
	void Display();
	void DrawLine(const CPoint from, const CPoint to, unsigned long lineColor) override;
	void FillPolygon(const std::vector<CPoint> points, unsigned long fillColor) override;
	void DrawCircle(const CPoint center, double radius, unsigned long lineColor) override;
	void FillCircle(const CPoint center, double radius, unsigned long fillColor) override;
private:
	sf::RenderWindow m_window;
	sf::RenderTexture m_renderTexture;
};