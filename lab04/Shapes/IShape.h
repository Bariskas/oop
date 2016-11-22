#pragma once

#include "stdafx.h"

class IShape
{
public:
	virtual ~IShape() {};
	virtual double GetArea() = 0;
	virtual double GetPerimeter() = 0;
	virtual std::string ToString() = 0;
	virtual std::string GetOutlineColor() = 0;

protected:
	std::string m_outlineColor;
};