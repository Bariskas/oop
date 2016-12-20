#include "stdafx.h"
#include "InputStreamUtils.h"

using namespace std;

double InputStreamUtils::ReadDouble(std::istream & inputStream)
{
#if 0
	double result = 0;
	if (inputStream >> result)
	{
		return result;
	}
	throw std::runtime_error("Invalid argument: " + numberString);
#else
	ThrowIfEof(inputStream);
	auto numberString = GetStringFromStream(inputStream);
	if (!IsValidStringForDouble(numberString))
	{
		throw std::runtime_error("Invalid argument: " + numberString);
	}
	return atof(numberString.c_str());
#endif
}

string InputStreamUtils::ReadColorString(std::istream & inputStream)
{
	ThrowIfEof(inputStream);
	auto colorString = GetStringFromStream(inputStream);;
	ValidateStringForColor(colorString);
	return colorString;
}

void InputStreamUtils::ThrowIfEof(const std::istream & stream)
{
	if (stream.eof())
	{
		throw std::runtime_error("Unexpected end of stream.");
	}
}

bool InputStreamUtils::IsValidStringForDouble(const std::string & numberString)
{
	return all_of(numberString.begin(), numberString.end(),
		[&](char ch) { return ch >= '0' && ch <= '9' || ch == '.'; });
}

void InputStreamUtils::ValidateStringForColor(const std::string& colorString)
{
	if (!all_of(colorString.begin(), colorString.end(), 
		[&](char ch) { return isxdigit(ch); }))
	{
		throw invalid_argument("\"" + colorString + "\" contains wrong symbols for color value.");
	}
	if (colorString.length() != 6 && colorString.length() != 8)
	{
		throw invalid_argument("\"" + colorString + "\" has wrong format. String format must be like FFFFFF or FFFFFFFF");
	}
}

string InputStreamUtils::GetStringFromStream(std::istream & stream)
{
	string nextString;
	stream >> nextString;
	if (nextString == "")
	{
		throw std::runtime_error("Unexpected spaces in stream.");
	}
	return nextString;
}
