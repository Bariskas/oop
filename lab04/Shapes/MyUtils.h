#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

inline std::istream& rd(std::istream & inputStream, double& number)
{
	if (inputStream.eof())
	{
		throw std::runtime_error("attempt to read from ended stream");
	}
	std::string numberString;
	inputStream >> numberString;
	if (numberString == "")
	{
		throw std::runtime_error("empty stream");
	}
	std::stringstream ss(numberString);
	ss >> number;
	if (!ss.eof())
	{
		throw std::invalid_argument(numberString + " is not double");
	}
	return inputStream;
}

inline std::stringstream getLineSS(std::istream & inputStream)
{
	if (inputStream.eof())
	{
		throw std::runtime_error("attempt to read from ended stream");
	}
	std::string line;
	getline(inputStream, line);
	std::stringstream ss(line);
	return ss;
}