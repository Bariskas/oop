#pragma once

enum Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:
	CHttpUrl();
	~CHttpUrl();
	CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol = HTTP,
		unsigned short port = 80);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

	static std::string ProtocolToString(Protocol protocol);
	static unsigned short GetDefaultPortForProtocol(Protocol protocol);
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
