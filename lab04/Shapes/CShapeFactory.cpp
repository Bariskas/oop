#include "stdafx.h"
#include "InputStreamUtils.h"
#include "CShapeFactory.h"

using namespace std;
using namespace std::placeholders;

CShapeFactory::CShapeFactory()
	: m_shapeInitializerMap({
		{ "Line", bind(&CShapeFactory::InitLineSegment, this, _1) },
		{ "Triangle", bind(&CShapeFactory::InitTriangle, this, _1) },
		{ "Rectangle", bind(&CShapeFactory::InitRectangle, this, _1) },
		{ "Circle", bind(&CShapeFactory::InitCircle, this, _1) }
})
{}

vector<ShapePtr> CShapeFactory::GetShapeFromStream(istream& inputStream) const
{
	vector<ShapePtr> shapes;
	stringstream shapeRepresentationStream;
	string shapeStringRepresentation;
	string shapeType;
	while (getline(inputStream, shapeStringRepresentation))
	{
		shapeRepresentationStream.clear();
		shapeRepresentationStream.str(shapeStringRepresentation);
		shapeRepresentationStream >> shapeType;
		auto initializerMapIt = m_shapeInitializerMap.find(shapeType);
		if (initializerMapIt == m_shapeInitializerMap.end())
		{
			throw invalid_argument("Unknow shape type: " + shapeType + " in string \"" + shapeStringRepresentation + "\".");
		}

		try
		{
			shapes.push_back(initializerMapIt->second(shapeRepresentationStream));
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
		
	}
	return shapes;
}

ShapePtr CShapeFactory::InitLineSegment(istream& inputStream) const
{
	CPoint startPoint;
	inputStream >> startPoint;
	CPoint endPoint;
	inputStream >> endPoint;
	return make_shared<CLineSegment>(startPoint, endPoint,
		InputStreamUtils::ReadColorString(inputStream));
}

ShapePtr CShapeFactory::InitTriangle(istream& inputStream) const
{
	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;
	inputStream >> vertex1 >> vertex2 >> vertex3;
	return make_shared<CTriangle>(vertex1, vertex2, vertex3,
		InputStreamUtils::ReadColorString(inputStream),
		InputStreamUtils::ReadColorString(inputStream));
}

ShapePtr CShapeFactory::InitRectangle(istream& inputStream) const
{
	CPoint leftTopPoint;
	inputStream >> leftTopPoint;
	auto width = InputStreamUtils::ReadDouble(inputStream);
	auto height = InputStreamUtils::ReadDouble(inputStream);
	auto outlineColor = InputStreamUtils::ReadColorString(inputStream);
	auto fillColor = InputStreamUtils::ReadColorString(inputStream);
	return make_shared<CRectangle>(leftTopPoint, width, height, outlineColor, fillColor);
}

ShapePtr CShapeFactory::InitCircle(istream&  inputStream) const
{
	CPoint center;
	inputStream >> center;
	return make_shared<CCircle>(center, InputStreamUtils::ReadDouble(inputStream),
		InputStreamUtils::ReadColorString(inputStream),
		InputStreamUtils::ReadColorString(inputStream));
}
