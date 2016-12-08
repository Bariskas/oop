#include "stdafx.h"
#include "CTriangle.h"
#include "ShapeUtils.h"
#include "SfmlUtils.h"

using namespace std;

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, std::string outlineColor, std::string fillColor)
	: CSolidShapeBase(outlineColor, fillColor)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{}

double CTriangle::GetArea() const
{
	auto hP = GetPerimeter() / 2; // hP - halfPerimeter
	return sqrt(hP * (hP - GetSide1()) * (hP - GetSide2()) * (hP - GetSide3()));
}

double CTriangle::GetPerimeter() const
{
	return GetSide1() + GetSide2() + GetSide3();
}

void CTriangle::AppendAdditionalInformation(stringstream& ss) const
{
	ss <<
		"vertex1: " << m_vertex1.x << ":" << m_vertex1.y 
	<< " vertex2: " << m_vertex2.x << ":" << m_vertex2.y 
	<< " vertex3: " << m_vertex3.x << ":" << m_vertex3.y 
	<< endl;
}

std::string CTriangle::GetShapeType() const
{
	return "triangle";
}

void CTriangle::Draw(CCanvas& canvas) const
{
	canvas.FillPolygon({m_vertex1, m_vertex2, m_vertex3}, ColorFromStringToUnsigned(GetFillColor());
	auto outlineColor = ColorFromStringToUnsigned(CShapeBase::GetOutlineColor());
	canvas.DrawLine(m_vertex1, m_vertex2, outlineColor);
	canvas.DrawLine(m_vertex2, m_vertex3, outlineColor);
	canvas.DrawLine(m_vertex3, m_vertex2, outlineColor);
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