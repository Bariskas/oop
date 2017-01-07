#include "stdafx.h"
#include "UrlParsingError.h"

CUrlParsingError::CUrlParsingError(std::string errorMessage)
	: invalid_argument(errorMessage)
{
}

