#pragma once
#include "HttpUrl.h"

class CUrlUtils
{
public:
	CUrlUtils() = delete;
	~CUrlUtils() = delete;
	static std::vector<CHttpUrl> ReadUrls(std::istream& inputStream, std::ostream& errorStream = std::cout);
	static void WriteUrlsInfo(std::vector<CHttpUrl> urls, std::ostream& outputStream = std::cout);
};

