#pragma once
#include "ISolidShape.h"
#include "CShapeBase.h"

class CSolidShapeBase : public ISolidShape, public CShapeBase
{
public:
	virtual ~CSolidShapeBase() {};
	CSolidShapeBase(std::string outlineColor, std::string fillColor);
	std::string GetFillColor() const override;

	virtual std::string ToString() const override final;
	virtual std::string GetOutlineColor() const override final;
private:
	std::string m_fillColor;
};
