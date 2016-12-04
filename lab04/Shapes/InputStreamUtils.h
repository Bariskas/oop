#pragma once
#include "stdafx.h"

class InputStreamUtils
{
public:
	static double ReadDouble(std::istream & inputStream);
	static std::string ReadColorString(std::istream & inputStream);
private:
	static void ThrowIfEof(const std::istream& stream);
	static bool IsValidStringForDouble(const std::string& numberString);
	static void ValidateStringForColor(const std::string& colorString);
	static std::string GetStringFromStream(std::istream& stream);
};