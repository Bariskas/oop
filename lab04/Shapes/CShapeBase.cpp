#include "stdafx.h"
#include "CShapeBase.h"

using namespace std;

CShapeBase::CShapeBase(std::string outlineColor)
	: m_outlineColor(outlineColor)
{
}

std::string CShapeBase::ToString() const
{
	stringstream ss;
	ss << "Shape: " << GetShapeType() << " Area: " << GetArea() << " Perimeter: "
		<< GetPerimeter() << endl;
	AppendAdditionalInformation(ss);
	return ss.str();
}

std::string CShapeBase::GetOutlineColor() const
{
	return m_outlineColor;
}
