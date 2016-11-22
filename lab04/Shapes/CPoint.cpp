#include "stdafx.h"
#include "CPoint.h"

CPoint::CPoint()
	: m_x(0)
	, m_y(0)
{}

CPoint::CPoint(double x, double y)
	: m_x(x)
	, m_y(y)
{}

CPoint& CPoint::operator+=(const CPoint& rArg)
{
	m_x += rArg.m_x;
	m_y += rArg.m_y;
	return *this;
}
