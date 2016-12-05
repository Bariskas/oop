#include "stdafx.h"
#include "CShapeBase.h"

using namespace std;

std::string CShapeBase::ToString() const
{
	return string("Shape: " + GetShapeType() + " Area: " + to_string(GetArea()) + " Perimeter: " + to_string(GetPerimeter()) + "\n" + GetAdditionalInformation());
}
