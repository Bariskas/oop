#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

using namespace std;

string const CHttpUrl::DOMAIN_REGEXP = R"(([\w\.]+\.[a-z]{2,6}\.?))";
string const CHttpUrl::DOCUMENT_REGEXP = R"((\/[\w\.]*)*\/?)";
string const CHttpUrl::URL_REGEXP = R"(^(http(s)?:\/\/)?([\w\.]+\.[a-z]{2,6}\.?)(:([\d]{1,5}))?((\/[\w\.]*)*)\/?$)";
int const CHttpUrl::SSL_SYMBOL_MR_INDEX = 2;
int const CHttpUrl::DOMAIN_MR_INDEX = 3;
int const CHttpUrl::PORT_MR_INDEX = 5;
int const CHttpUrl::DOCUMENT_MR_INDEX = 6;

CHttpUrl::CHttpUrl()
{
}

CHttpUrl::~CHttpUrl()
{
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	cmatch cm;
	regex regExp(URL_REGEXP);
	if (regex_match(url.c_str(), cm, regExp))
	{
		m_url = url;
		m_protocol = cm[SSL_SYMBOL_MR_INDEX].length() == 0 ? HTTP : HTTPS;
		m_domain = cm[DOMAIN_MR_INDEX];
		m_document = cm[DOCUMENT_MR_INDEX];
		int portValue = cm[PORT_MR_INDEX].length() != 0 ? stoi(cm[PORT_MR_INDEX]) : GetDefaultPortForProtocol(m_protocol);
		if (portValue > numeric_limits<unsigned short>::max())
		{
			throw out_of_range(url + ": max port value is 65535");
		}
		m_port = portValue;
	}
	else
	{
		throw CUrlParsingError(url + ": wrong url format");
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_protocol(protocol)
	, m_port(port)
{
	regex regExp(DOMAIN_REGEXP);
	if (regex_match(domain.c_str(), regExp))
	{
		m_domain = domain;
	}
	else
	{
		throw invalid_argument(domain + ": wrong domain format");
	}
	regExp.assign(DOCUMENT_REGEXP);
	if (regex_match(document.c_str(), regExp))
	{
		m_document = document[0] == '/' ? document : '/' + document;
	}
	else
	{
		throw invalid_argument(document + ": wrong document format");
	}
	stringstream ss;
	ss << ProtocolToString(protocol) << "://" << m_domain << m_document;
	m_url = ss.str();
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
