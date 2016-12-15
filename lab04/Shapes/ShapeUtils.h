#pragma once

#include "stdafx.h"
#include "CPoint.h"
#include "CShapeBase.h"

double GetDistanceBeetwen(CPoint point1, CPoint point2);
ShapePtr GetShapeWithMaxArea(const std::vector<ShapePtr>& shapes);
ShapePtr GetShapeWithMinPerimeter(const std::vector<ShapePtr>& shapes);