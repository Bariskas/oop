// HttpUrl.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlUtils.h"

using namespace std;

int main()
{
	auto urls = CUrlUtils::ReadUrls(cin);
	CUrlUtils::WriteUrlsInfo(urls);
    return 0;
}

