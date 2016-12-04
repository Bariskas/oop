#include "stdafx.h"
#include "InputStreamUtils.h"
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
	point.x = InputStreamUtils::ReadDouble(input);
	point.y = InputStreamUtils::ReadDouble(input);
	return input;
}
