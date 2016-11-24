#include "stdafx.h"
#include "MyUtils.h"
#include "CPoint.h"

using namespace std;

CPoint::CPoint()
	: x(0)
	, y(0)
{}

CPoint::CPoint(double x, double y)
	: x(x)
	, y(y)
{}

istream & operator>>(istream & input, CPoint & point)
{
	rd(input, point.x);
	rd(input, point.y);
	return input;
}
