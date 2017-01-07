#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

using namespace std;

string const CHttpUrl::DOMAIN_REGEXP = R"(([\w\.]+\.[a-z]{2,6}\.?))";
string const CHttpUrl::DOCUMENT_REGEXP = R"((\/?[\w\.]*)*\/?)";
string const CHttpUrl::URL_REGEXP = R"(^(http(s)?:\/\/)?([\w\.]+\.[a-z]{2,6}\.?)(:([\d]{1,5}))?((\/[\w\.]*)*)\/?$)";
int const CHttpUrl::SSL_SYMBOL_MR_INDEX = 2;
int const CHttpUrl::DOMAIN_MR_INDEX = 3;
int const CHttpUrl::PORT_MR_INDEX = 5;
int const CHttpUrl::DOCUMENT_MR_INDEX = 6;

CHttpUrl::CHttpUrl(std::string const& url)
{
	cmatch cm;
	regex regExp(URL_REGEXP);
	if (regex_match(url.c_str(), cm, regExp))
	{
		m_url = url;
		m_protocol = cm[SSL_SYMBOL_MR_INDEX].length() == 0 ? HTTP : HTTPS;
		m_domain = cm[DOMAIN_MR_INDEX];
		m_document = cm[DOCUMENT_MR_INDEX].length() != 0 ? cm[DOCUMENT_MR_INDEX].str() : "/";
		int portValue = cm[PORT_MR_INDEX].length() != 0 
			? GetPortFromString(cm[PORT_MR_INDEX])
			: GetDefaultPortForProtocol(m_protocol);
		m_port = portValue;
	}
	else
	{
		throw CUrlParsingError("Wrong url format");
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: m_protocol(protocol)
{
	ValidateDomain(domain);
	m_domain = domain;
	ValidateDocument(document);
	m_document = document[0] == '/' ? document : '/' + document;
	m_port = GetDefaultPortForProtocol(protocol);

	m_url = GenerateUrl(m_protocol, m_domain, m_port, m_document);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_protocol(protocol)
	, m_port(port)
{
	ValidateDomain(domain);
	m_domain = domain;
	ValidateDocument(document);
	m_document = document[0] == '/' ? document : '/' + document;
	
	m_url = GenerateUrl(m_protocol, m_domain, m_port, m_document);
}

std::string CHttpUrl::GetURL() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::ProtocolToString(Protocol protocol)
{
	return protocol == HTTP ? "http" : "https";
}

unsigned short CHttpUrl::GetDefaultPortForProtocol(Protocol protocol)
{
	return protocol == HTTP ? 80 : 443;
}

std::string CHttpUrl::GenerateUrl(Protocol protocol, std::string const& domain, 
	unsigned short port, std::string const& document)
{
	string urlPortPart = GetUrlPortPart(port, protocol);
	stringstream ss;
	ss << ProtocolToString(protocol) << "://" << domain << urlPortPart << document;
	return ss.str();
}

unsigned short CHttpUrl::GetPortFromString(std::string const& portString)
{
	int portValue = stoul(portString);
	if (portValue > numeric_limits<unsigned short>::max())
	{
		throw CUrlParsingError("Max port value is 65535");
	}
	return portValue;
}

void CHttpUrl::ValidateDomain(std::string const& domainString)
{
	regex regExp(DOMAIN_REGEXP);
	if (!regex_match(domainString.c_str(), regExp))
	{
		throw CUrlParsingError(domainString + ": wrong domain format");
	}
}


void CHttpUrl::ValidateDocument(std::string const& documentString)
{
	regex regExp(DOCUMENT_REGEXP);
	if (!regex_match(documentString.c_str(), regExp))
	{
		throw CUrlParsingError(documentString + ": wrong document format");
	}
}

std::string CHttpUrl::GetUrlPortPart(unsigned short port, Protocol protocol)
{
	return GetDefaultPortForProtocol(protocol) == port ? "" : ':' + to_string(port);
}
