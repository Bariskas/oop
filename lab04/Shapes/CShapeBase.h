#pragma once
#include "IShape.h"

class CShapeBase : IShape
{
public:
	virtual ~CShapeBase() {};
	std::string ToString() const final;
protected:
	virtual std::string GetAdditionalInformation() const = 0;
};