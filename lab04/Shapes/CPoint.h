#pragma once

class CPoint
{
public:
	CPoint();
	CPoint(double x, double y);
	~CPoint() {};
	CPoint& operator+=(const CPoint& rArg);
private:
	float m_x;
	float m_y;
};