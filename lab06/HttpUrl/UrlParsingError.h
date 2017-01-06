#pragma once

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError();
	CUrlParsingError(std::string errorMessage);
	~CUrlParsingError();
};

