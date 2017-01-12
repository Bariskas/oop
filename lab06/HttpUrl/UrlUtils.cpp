#include "stdafx.h"
#include "UrlUtils.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

using namespace std;

void CUrlUtils::ReadAndWriteUrls(std::istream& inputStream, 
	std::ostream& outputStream, std::ostream& errorStream)
{
	string tempString;
	while (inputStream >> tempString)
	{
		try
		{
			CHttpUrl url(tempString);
			WriteUrlInfo(url, outputStream);
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
}

void CUrlUtils::WriteUrlInfo(CHttpUrl url, std::ostream& outputStream)
{
	outputStream << "Url: " << url.GetURL() << endl
		<< "Protocol: " << CHttpUrl::ProtocolToString(url.GetProtocol()) << endl
		<< "Domen: " << url.GetDomain() << endl
		<< "Port: " << url.GetPort() << endl
		<< "Document: " << url.GetDocument() << endl;
}
