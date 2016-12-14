#pragma once
#include "ISolidShape.h"
#include "CShapeBase.h"

class CSolidShapeBase : public ISolidShape, public CShapeBase
{
public:
	virtual ~CSolidShapeBase() {};
	CSolidShapeBase(std::string outlineColor, std::string fillColor);
	std::string GetFillColor() const override;
protected:
	std::string m_fillColor;
};
