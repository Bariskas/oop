#pragma once
#include "HttpUrl.h"

class CUrlUtils
{
public:
	CUrlUtils() = delete;
	~CUrlUtils() = delete;
	static std::vector<CHttpUrl> ReadUrls(std::istream& inputStream);
	static void WriteUrlsInfo(std::vector<CHttpUrl> urls, std::ostream&  inputStream);
};

