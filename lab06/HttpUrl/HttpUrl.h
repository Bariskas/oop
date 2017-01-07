#pragma once

#include "UrlParsingError.h"

enum Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol = HTTP);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

	static std::string ProtocolToString(Protocol protocol);
	static unsigned short GetDefaultPortForProtocol(Protocol protocol);
private:
	static std::string GenerateUrl(Protocol protocol, std::string const& domain, 
		unsigned short port, std::string const& document);
	static unsigned short GetPortFromString(std::string const& portString);
	static void ValidateDomain(std::string const& domainString);
	static void ValidateDocument(std::string const& documentString);
	static std::string GetUrlPortPart(unsigned short port, Protocol protocol);
private:
	std::string m_url;
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	static const std::string URL_REGEXP;
	static const std::string DOMAIN_REGEXP;
	static const std::string DOCUMENT_REGEXP;
	static const int SSL_SYMBOL_MR_INDEX;
	static const int DOMAIN_MR_INDEX;
	static const int DOCUMENT_MR_INDEX;
	static const int PORT_MR_INDEX;
};
