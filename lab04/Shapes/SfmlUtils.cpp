#include "stdafx.h"
#include "SfmlUtils.h"

using namespace std;

unsigned long ColorFromStringToUnsigned(const string colorString)
{
	unsigned long colorUnsigned;
	stringstream ss;
	ss << std::hex << colorString;
	ss >> colorUnsigned;
	return colorUnsigned;
}