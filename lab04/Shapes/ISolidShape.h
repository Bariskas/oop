#pragma once

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape() {};
	virtual std::string GetFillColor() = 0;

protected:
	std::string m_fillColor;
};