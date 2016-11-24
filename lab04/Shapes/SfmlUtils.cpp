#include "stdafx.h"
#include "SfmlUtils.h"

using namespace std;

unsigned ColorFromStringToUnsigned(string colorString)
{
	unsigned colorUnsigned;
	stringstream ss;
	ss << std::hex << colorString;
	ss >> colorUnsigned;
	return colorUnsigned;
}