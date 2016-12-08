#pragma once

#include "ICanvasDrawable.h"
#include "stdafx.h"

class IShape : public ICanvasDrawable
{
public:
	virtual ~IShape() {};
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual std::string GetOutlineColor() const = 0;
};

typedef std::shared_ptr<IShape> ShapePtr;