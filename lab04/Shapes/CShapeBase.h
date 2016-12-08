#pragma once
#include "IShape.h"

class CShapeBase : virtual public IShape
{
public:
	CShapeBase(std::string outlineColor);
	virtual ~CShapeBase() {};
	std::string ToString() const final;
	std::string GetOutlineColor() const final;
protected:
	virtual void AppendAdditionalInformation(std::stringstream& ss) const = 0;
	virtual std::string GetShapeType() const = 0;
protected:
	std::string m_outlineColor;
};