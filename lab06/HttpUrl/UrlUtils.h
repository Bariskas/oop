#pragma once
#include "HttpUrl.h"

class CUrlUtils
{
public:
	CUrlUtils() = delete;
	~CUrlUtils() = delete;
	static void ReadAndWriteUrls(std::istream& inputStream, 
		std::ostream& outputStream = std::cout, std::ostream& errorStream = std::cout);
	static void CUrlUtils::WriteUrlInfo(CHttpUrl url, std::ostream& outputStream);
};

