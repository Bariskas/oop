#include "stdafx.h"
#include "UrlUtils.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

using namespace std;

std::vector<CHttpUrl> CUrlUtils::ReadUrls(std::istream& inputStream)
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
			cout << e.what() << endl;
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}
	return urls;
}

void CUrlUtils::WriteUrlsInfo(std::vector<CHttpUrl> urls, std::ostream& inputStream)
{
	for (const auto& url : urls)
	{
		cout << "Protocol: " << CHttpUrl::ProtocolToString(url.GetProtocol()) << endl
			<< "Port: " << url.GetPort() << endl
			<< "Domen: " << url.GetDomain() << endl
			<< "Document: " << url.GetDocument() << endl;
	}
}
