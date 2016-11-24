#pragma once

class CPoint
{
public:
	CPoint();
	CPoint(double x, double y);
	~CPoint() {};
	friend std::istream & operator>>(std::istream & input, CPoint & point);
public:
	double x;
	double y;
};