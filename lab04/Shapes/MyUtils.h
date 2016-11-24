#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

inline std::istream& rd(std::istream & inputStream, double& number)
{
	if (inputStream.eof())
	{
		throw runtime_error("attempt to read from ended stream");
	}
	std::string numberString;
	inputStream >> numberString;
	if (numberString == "")
	{
		throw runtime_error("empty stream");
	}
	std::stringstream ss(numberString);
	ss >> number;
	if (!ss.eof())
	{
		throw std::invalid_argument(numberString + " is not double");
	}
	return inputStream;
}

inline stringstream getLineSS(std::istream & inputStream)
{
	if (inputStream.eof())
	{
		throw runtime_error("attempt to read from ended stream");
	}
	string line;
	getline(inputStream, line);
	stringstream ss(line);
	return ss;
}