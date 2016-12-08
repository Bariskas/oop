#pragma once
#include "ISolidShape.h"
#include "CShapeBase.h"

class CSolidShapeBase : virtual public ISolidShape, CShapeBase
{
public:
	CSolidShapeBase(std::string outlineColor, std::string fillColor);
	std::string GetFillColor() const override;
protected:
	std::string m_fillColor;
};
