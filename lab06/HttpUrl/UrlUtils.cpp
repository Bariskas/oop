#include "stdafx.h"
#include "UrlUtils.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

using namespace std;

std::vector<CHttpUrl> CUrlUtils::ReadUrls(std::istream& inputStream, std::ostream& errorStream)
{
	vector<CHttpUrl> urls;
	string tempString;
	while (inputStream >> tempString)
	{
		try
		{
			CHttpUrl url(tempString);
			urls.emplace_back(url);
		}
		catch (const CUrlParsingError& e)
		{
			errorStream << '"' << tempString << "\": " << e.what() << endl;
		}
		catch (const exception& e)
		{
			errorStream << e.what() << endl;
		}
	}
	return urls;
}

void CUrlUtils::WriteUrlsInfo(std::vector<CHttpUrl> urls, std::ostream& outputStream)
{
	for (const auto& url : urls)
	{
		outputStream << "Url: " << url.GetURL() << endl
			<< "Protocol: " << CHttpUrl::ProtocolToString(url.GetProtocol()) << endl
			<< "Domen: " << url.GetDomain() << endl
			<< "Port: " << url.GetPort() << endl
			<< "Document: " << url.GetDocument() << endl;
	}
}
