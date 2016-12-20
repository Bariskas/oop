#pragma once
#include "IShape.h"

class CShapeBase : virtual public IShape
{
public:
	CShapeBase(std::string outlineColor);
	virtual ~CShapeBase() {};
	std::string ToString() const override;
	std::string GetOutlineColor() const override;
protected:
	virtual void AppendAdditionalInformation(std::stringstream& ss) const = 0;
	virtual std::string GetShapeType() const = 0;
private:
	std::string m_outlineColor;
};