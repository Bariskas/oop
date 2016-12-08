#pragma once

#include "IShape.h"

class ISolidShape : virtual public IShape
{
public:
	virtual ~ISolidShape() {};
	virtual std::string GetFillColor() const = 0;
};