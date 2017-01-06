#include "stdafx.h"
#include "UrlParsingError.h"


CUrlParsingError::CUrlParsingError()
	: invalid_argument("")
{
}

CUrlParsingError::CUrlParsingError(std::string errorMessage)
	: invalid_argument(errorMessage)
{
}

CUrlParsingError::~CUrlParsingError()
{
}
