#pragma once

#include "stdafx.h"
#include "CPoint.h"
#include "CShapeBase.h"

double GetDistanceBeetwen(const CPoint point1, const CPoint point2);
ShapePtr GetShapeWithMaxArea(const std::vector<ShapePtr>& shapes);
ShapePtr GetShapeWithMinPerimeter(const std::vector<ShapePtr>& shapes);