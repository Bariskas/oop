#include "stdafx.h"
#include "ShapeUtils.h"
#include "CPoint.h"

double GetDistanceBeetwen(CPoint point1, CPoint point2)
{
	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

ShapePtr GetShapeWithMaxArea(const std::vector<ShapePtr>& shapes)
{
	auto shapeWithMaxArea = std::max_element(shapes.begin(), shapes.end(),
		[](const ShapePtr& leftShape, const ShapePtr& rightShape)
	{
		return leftShape->GetArea() < rightShape->GetArea();
	});

	return shapeWithMaxArea != shapes.end()
		? *shapeWithMaxArea
		: std::shared_ptr<IShape>();
}

ShapePtr GetShapeWithMinPerimeter(const std::vector<ShapePtr>& shapes)
{
	auto shapeWithMinPerimeter = std::min_element(shapes.begin(), shapes.end(),
		[](const ShapePtr& leftShape, const ShapePtr& rightShape)
	{
		return leftShape->GetPerimeter() < rightShape->GetPerimeter();
	});

	return shapeWithMinPerimeter != shapes.end()
		? *shapeWithMinPerimeter
		: std::shared_ptr<IShape>();
}
