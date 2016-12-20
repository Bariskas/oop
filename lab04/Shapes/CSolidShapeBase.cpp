#include "stdafx.h"
#include "CSolidShapeBase.h"

using namespace std;

CSolidShapeBase::CSolidShapeBase(string outline, string fillColor)
	: CShapeBase(outline) 
    , m_fillColor(fillColor)
{	
}

string CSolidShapeBase::GetFillColor() const
{
	return m_fillColor;
}

std::string CSolidShapeBase::ToString() const
{
	return CShapeBase::ToString();
}

std::string CSolidShapeBase::GetOutlineColor() const
{
	return CShapeBase::GetOutlineColor();
}

