#pragma once

class CPoint
{
public:
	CPoint();
	CPoint(double x, double y);
	~CPoint() {};
public:
	double x;
	double y;
};

std::istream & operator >> (std::istream & input, CPoint & point);
bool operator == (const CPoint& p1, const CPoint& p2);