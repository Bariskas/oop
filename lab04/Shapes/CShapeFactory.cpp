#include "stdafx.h"
#include "MyUtils.h"
#include "CShapeFactory.h"

using namespace std;
using namespace std::placeholders;

CShapeFactory::CShapeFactory()
	: m_shapeInitializerMap({
		{ "LineSegment", bind(&CShapeFactory::InitLineSegment, this, _1) },
		{ "Triangle", bind(&CShapeFactory::InitTriangle, this, _1) },
		{ "Rectangle", bind(&CShapeFactory::InitRectangle, this, _1) },
		{ "Circle", bind(&CShapeFactory::InitCircle, this, _1) }
})
{}

vector<ShapePtr> CShapeFactory::GetShapeFromStream(istream& inputStream) const
{
	vector<ShapePtr> shapes;
	string shapeType;
	while (inputStream >> shapeType)
	{
		auto initializerMapIt = m_shapeInitializerMap.find(shapeType);
		if (initializerMapIt == m_shapeInitializerMap.end())
		{
			throw invalid_argument("unknow shape type: " + shapeType);
		}

		shapes.push_back(initializerMapIt->second(getLineSS(inputStream)));
	}
	return shapes;
}

ShapePtr CShapeFactory::InitLineSegment(istream& inputStream) const
{
	CPoint startPoint;
	inputStream >> startPoint;
	CPoint endPoint;
	inputStream >> endPoint;
	string outlineColor;
	inputStream >> outlineColor;
	return make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
}

ShapePtr CShapeFactory::InitTriangle(istream& inputStream) const
{
	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;
	inputStream >> vertex1 >> vertex2 >> vertex3;
	string outlineColor;
	inputStream >> outlineColor;
	string fillColor;
	inputStream >> fillColor;
	return make_shared<CTriangle>(vertex1, vertex2, vertex3,
		outlineColor, fillColor);
}

ShapePtr CShapeFactory::InitRectangle(istream& inputStream) const
{
	CPoint leftTopPoint;
	inputStream >> leftTopPoint;
	double width;
	double height;
	inputStream >> width >> height;
	string outlineColor;
	inputStream >> outlineColor;
	string fillColor;
	inputStream >> fillColor;
	return make_shared<CRectangle>(leftTopPoint, width, height,
		outlineColor, fillColor);
}

ShapePtr CShapeFactory::InitCircle(istream&  inputStream) const
{
	CPoint center;
	inputStream >> center;
	double radius;
	inputStream >> radius;
	string outlineColor;
	inputStream >> outlineColor;
	string fillColor;
	inputStream >> fillColor;
	return make_shared<CCircle>(center, radius,
		outlineColor, fillColor);
}
