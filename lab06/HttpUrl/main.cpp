// HttpUrl.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlUtils.h"

using namespace std;

int main()
{
	stringstream ss(
		"http://google.com:66000/index.html https://www.google.com/opopop/index.html"
	);
	auto urls = CUrlUtils::ReadUrls(cin);
	CUrlUtils::WriteUrlsInfo(urls, cout);
    return 0;
}

