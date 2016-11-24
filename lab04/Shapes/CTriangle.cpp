#include "stdafx.h"
#include "CTriangle.h"
#include "ShapeUtils.h"

using namespace std;

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, std::string fillColor, std::string outlineColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetArea() const
{
	auto hP = GetPerimeter() / 2; // hP - halfPerimeter
	return sqrt(hP * (hP - GetSide1()) * (hP - GetSide2()) * (hP - GetSide3()));
}

double CTriangle::GetPerimeter() const
{
	return GetSide1() + GetSide2() + GetSide3();
}

string CTriangle::ToString() const
{
	stringstream ss;
	ss << "Shape - triangle" << endl
		<< "area = " << GetArea() << endl
		<< "perimeter = " << GetPerimeter() << endl
		<< "vertex1.x = " << m_vertex1.x << endl
		<< "vertex1.y = " << m_vertex1.y << endl
		<< "vertex2.x = " << m_vertex2.x << endl
		<< "vertex2.y = " << m_vertex2.y << endl
		<< "vertex3.x = " << m_vertex3.x << endl
		<< "vertex3.y = " << m_vertex3.y << endl
		<< "outlineColor = " << m_outlineColor << endl
		<< "fillColor = " << m_fillColor << endl;
	return ss.str();
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

double CTriangle::GetSide1() const
{
	return (m_side1 == 0) ? GetDistanceBeetwen(m_vertex1, m_vertex2) : m_side1;
}

double CTriangle::GetSide2() const
{
	return (m_side2 == 0) ? GetDistanceBeetwen(m_vertex2, m_vertex3) : m_side2;
}

double CTriangle::GetSide3() const
{
	return (m_side3 == 0) ? GetDistanceBeetwen(m_vertex3, m_vertex1) : m_side3;
}

string CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

string CTriangle::GetFillColor() const
{
	return m_fillColor;
}

