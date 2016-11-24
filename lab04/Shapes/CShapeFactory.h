#pragma once

#include "stdafx.h"
#include "IShape.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"

class CShapeFactory
{
public:
	CShapeFactory();
	std::vector<ShapePtr> GetShapeFromStream(std::istream& inputStream) const;
private:
	ShapePtr InitLineSegment(std::istream& inputStream) const;
	ShapePtr InitTriangle(std::istream& inputStream) const;
	ShapePtr InitRectangle(std::istream& inputStream) const;
	ShapePtr InitCircle(std::istream& inputStream) const;
private:
	const std::map<std::string,
		std::function<ShapePtr(std::istream&)>> m_shapeInitializerMap;
};