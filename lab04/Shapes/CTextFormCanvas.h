#pragma once

#include "ICanvas.h"

class CTextFormCanvas : public ICanvas
{
public:
	CTextFormCanvas(std::ostream & outputStream);
	void Display();
	void DrawLine(CPoint from, CPoint to, unsigned long lineColor) override;
	void FillPolygon(std::vector<CPoint> points, unsigned long fillColor) override;
	void DrawCircle(CPoint center, double radius, unsigned long lineColor) override;
	void FillCircle(CPoint center, double radius, unsigned long fillColor) override;
private:
	std::ostream& m_outputStream;
};
